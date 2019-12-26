#include "Box2D/Dynamics/b2Body.h"
#include "Testbed/Framework/Test.h"
#include "..\Box2D-master\CarUtils\CarBuilder.h"
#include "..\Box2D-master\CarUtils\Structs.h"


#ifndef IANKOCAR_H
#define IANKOCAR_H

struct WheelStructure {
	b2CircleShape circle;
	b2FixtureDef phys_properties;
};

struct JointParams {
	float32 motorSpeed;
	float32 maxMotorTorque;
	bool enableMotor;
	float32 frequencyHz;
	float32 dampingRatio;
};

class IankoCar : public Test
{
public:
	IankoCar()
	{
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			grnd_properties.shape = &grnd_shape;
			grnd_properties.density = 0.0f;
			grnd_properties.friction = 0.6f;
			
			create_polygon(-5.0f);
		}

		// Car
		{
			init_wheel_structure();
			b2PolygonShape chassis = create_chassis();

			set_body_type(b2_dynamicBody);
			set_wheel_type(b2_dynamicBody);
			
			set_body_position(0.0f, 1.0f);
			m_car = m_world->CreateBody(&body_descriptor);
			m_car->CreateFixture(&chassis, 1.0f);


			b2CircleShape circle;
			circle.m_radius = 0.4f;
			b2FixtureDef fd;
			fd.shape = &circle;
			fd.density = 1.0f;
			fd.friction = 0.9f;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;

			bd.position.Set(-1.0f, 0.35f);
			m_wheel1 = m_world->CreateBody(&bd);
			m_wheel1->CreateFixture(&fd);

			bd.position.Set(1.0f, 0.4f);
			m_wheel2 = m_world->CreateBody(&bd);
			m_wheel2->CreateFixture(&fd);


			b2Vec2 axis(0.0f, 1.0f);
			joint_wheel(m_wheel1, axis, left_wheel_characteristics);
			m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&wheel_joint_descriptor);
			joint_wheel(m_wheel2, axis, right_wheel_characteristics);
			m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&wheel_joint_descriptor);

			leader_spring = m_spring1;
		}
	}

	void Keyboard(int key)
	{
		switch (key)
		{
		case GLFW_KEY_A:
			leader_spring->SetMotorSpeed(m_speed);
			break;

		case GLFW_KEY_S:
			leader_spring->SetMotorSpeed(0.0f);
			break;

		case GLFW_KEY_D:
			leader_spring->SetMotorSpeed(-m_speed);
			break;

		case GLFW_KEY_F: /*c заднего привода на передний*/
			m_spring1->EnableMotor(false);
			m_spring2->EnableMotor(true);
			change_leader_wheel(m_spring1, m_spring2);
			break;

		case GLFW_KEY_B: /*c переднего привода на задний*/
			m_spring1->EnableMotor(true);
			m_spring2->EnableMotor(false);
			change_leader_wheel(m_spring2, m_spring1);
			break;

    
		case GLFW_KEY_J: 
			m_wheel1->ApplyForce(b2Vec2(0, 400), m_wheel1->GetLocalCenter(), true);
			m_wheel2->ApplyForce(b2Vec2(0, 400), m_wheel2->GetLocalCenter(), true);
			break;

		case GLFW_KEY_L: //Accelerate
			if_accelerate = true;
			break;
		}


	}

	void KeyboardUp(int key) {
		switch (key) {
		case GLFW_KEY_L: //Disable Acceleration
			if_accelerate = false;
			break;
		}
	}
	
	
	void Step(Settings* settings)
	{
		g_debugDraw.DrawString(5, m_textLine, "Keys: left = a, brake = s, right = d, hz down = q, hz up = e");
		m_textLine += DRAW_STRING_NEW_LINE;
		g_debugDraw.DrawString(5, m_textLine, "frequency = %g hz, damping ratio = %g", m_hz, m_zeta);
		m_textLine += DRAW_STRING_NEW_LINE;

		float32 car_x = m_car->GetPosition().x;
		float32 car_y = m_car->GetPosition().y;

		g_camera.m_center.x = car_x;
		g_camera.m_center.y = car_y;

		/*create further landscape if close to the end*/
		float32 distance_to_see = 50.0f;
		
		if (fabs(ground_end - car_x) < distance_to_see) {
			create_polygon(ground_end);
		}
		
		if (if_accelerate) {
			static float32 vel = 0;
			vel += 0.05f;
			leader_spring->SetMotorSpeed(-m_speed - vel);
		}
		
		
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new IankoCar;
	}

	CarDetails car_details{};

	b2Body* ground = NULL;
	b2EdgeShape grnd_shape;
	b2FixtureDef grnd_properties;
	float32 ground_end{};

	b2Body* m_car;
	b2Body* m_wheel1;
	b2Body* m_wheel2;

	float32 m_hz = 4.0f;
	float32 m_zeta = 0.7f;
	float32 m_speed = 30.0f;

	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	b2WheelJoint* leader_spring;

	private:
		b2Vec2 impulse{ jump_intensity_x, jump_intensity_y };
		const float32 jump_intensity_y = 0.05f;
		const float32 jump_intensity_x = 0.0f;
		
		b2BodyDef body_descriptor{};
		b2BodyDef wheel_descriptor{};
		b2WheelJointDef wheel_joint_descriptor{};

		WheelStructure wheels_info{};

		void set_body_type(b2BodyType type_);
		void set_wheel_type(b2BodyType type_);

		void set_body_position(float32 x, float32 y);
		void set_wheel_position(float32 x, float32 y);
		void init_wheel_structure();
		void change_leader_wheel(b2WheelJoint* from, b2WheelJoint* to);

		b2PolygonShape create_chassis();
		void create_car_body();
		void joint_wheel(b2Body* wheel, const b2Vec2 & axis, const JointParams& params);
		void create_polygon(const float32 x_start);

		bool if_accelerate = false;

		const JointParams left_wheel_characteristics
		{
			0.0f,
			20.0f,
			true,
			m_hz,
			m_zeta
		};
		const JointParams right_wheel_characteristics
		{
			0.0f,
			20.0f,
			false, //для переключения мощности, enable_motor к обеим колёсам
			m_hz,
			m_zeta
		};
};

#endif

