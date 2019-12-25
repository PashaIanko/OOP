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
		//b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);


			grnd_properties.shape = &grnd_shape;
			grnd_properties.density = 0.0f;
			grnd_properties.friction = 0.6f;
			
			
			create_polygon(0.0f);

			/*b2EdgeShape shape;
			init_wheel_structure();
			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;

			shape.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
			ground->CreateFixture(&fd);

			float32 hs[10] = { 0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f };

			float32 x = 20.0f, y1 = 0.0f, dx = 5.0f;

			for (int32 i = 0; i < 10; ++i)
			{
				float32 y2 = hs[i];
				shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
				ground->CreateFixture(&fd);
				y1 = y2;
				x += dx;
			}

			for (int32 i = 0; i < 10; ++i)
			{
				float32 y2 = hs[i];
				shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
				ground->CreateFixture(&fd);
				y1 = y2;
				x += dx;
			}

			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
			ground->CreateFixture(&fd);

			x += 80.0f;
			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
			ground->CreateFixture(&fd);

			x += 40.0f;
			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 10.0f, 5.0f));
			ground->CreateFixture(&fd);

			x += 20.0f;
			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
			ground->CreateFixture(&fd);

			x += 40.0f;
			shape.Set(b2Vec2(x, 0.0f), b2Vec2(x, 20.0f));
			ground->CreateFixture(&fd);*/
		}

	//	// Teeter
	//	{
	//		b2BodyDef bd;
	//		bd.position.Set(140.0f, 1.0f);
	//		bd.type = b2_dynamicBody;
	//		b2Body* body = m_world->CreateBody(&bd);

	//		b2PolygonShape box;
	//		box.SetAsBox(10.0f, 0.25f);
	//		body->CreateFixture(&box, 1.0f);

	//		b2RevoluteJointDef jd;
	//		jd.Initialize(ground, body, body->GetPosition());
	//		jd.lowerAngle = -8.0f * b2_pi / 180.0f;
	//		jd.upperAngle = 8.0f * b2_pi / 180.0f;
	//		jd.enableLimit = true;
	//		m_world->CreateJoint(&jd);

	//		body->ApplyAngularImpulse(100.0f, true);
	//	}

	//	// Bridge
	//	{
	//		int32 N = 20;
	//		b2PolygonShape shape;
	//		shape.SetAsBox(1.0f, 0.125f);

	//		b2FixtureDef fd;
	//		fd.shape = &shape;
	//		fd.density = 1.0f;
	//		fd.friction = 0.6f;

	//		b2RevoluteJointDef jd;

	//		b2Body* prevBody = ground;
	//		for (int32 i = 0; i < N; ++i)
	//		{
	//			b2BodyDef bd;
	//			bd.type = b2_dynamicBody;
	//			bd.position.Set(161.0f + 2.0f * i, -0.125f);
	//			b2Body* body = m_world->CreateBody(&bd);
	//			body->CreateFixture(&fd);

	//			b2Vec2 anchor(160.0f + 2.0f * i, -0.125f);
	//			jd.Initialize(prevBody, body, anchor);
	//			m_world->CreateJoint(&jd);

	//			prevBody = body;
	//		}

	//		b2Vec2 anchor(160.0f + 2.0f * N, -0.125f);
	//		jd.Initialize(prevBody, ground, anchor);
	//		m_world->CreateJoint(&jd);
	//	}

	//	// Boxes
	//	{
	//		b2PolygonShape box;
	//		box.SetAsBox(0.5f, 0.5f);

	//		b2Body* body = NULL;
	//		b2BodyDef bd;
	//		bd.type = b2_dynamicBody;

	//		bd.position.Set(230.0f, 0.5f);
	//		body = m_world->CreateBody(&bd);
	//		body->CreateFixture(&box, 0.5f);

	//		bd.position.Set(230.0f, 1.5f);
	//		body = m_world->CreateBody(&bd);
	//		body->CreateFixture(&box, 0.5f);

	//		bd.position.Set(230.0f, 2.5f);
	//		body = m_world->CreateBody(&bd);
	//		body->CreateFixture(&box, 0.5f);

	//		bd.position.Set(230.0f, 3.5f);
	//		body = m_world->CreateBody(&bd);
	//		body->CreateFixture(&box, 0.5f);

	//		bd.position.Set(230.0f, 4.5f);
	//		body = m_world->CreateBody(&bd);
	//		body->CreateFixture(&box, 0.5f);
	//	}

		// Car
		{
			init_wheel_structure();
			b2PolygonShape chassis = create_chassis();


			set_body_type(b2_dynamicBody);
			set_wheel_type(b2_dynamicBody);
			
			Wheel* wh = builder.get_wheel(-1.0f, 0.35f);

			set_body_position(0.0f, 1.0f);
			m_car = m_world->CreateBody(&body_descriptor);
			m_car->CreateFixture(&chassis, 1.0f);


			set_wheel_position(-1.0f, 0.35f);
			m_wheel1 = m_world->CreateBody(&wheel_descriptor);
			m_wheel1->CreateFixture(&wheels_info.phys_properties);

			set_wheel_position(1.0f, 0.4f);
			m_wheel2 = m_world->CreateBody(&wheel_descriptor);
			m_wheel2->CreateFixture(&wheels_info.phys_properties);

			b2Vec2 axis(0.0f, 1.0f);

			joint_wheel(m_wheel1, axis, left_wheel_characteristics);
			m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&wheel_joint_descriptor);

			joint_wheel(m_wheel2, axis, right_wheel_characteristics);
			m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&wheel_joint_descriptor);
		}
	}

	void Keyboard(int key)
	{
		switch (key)
		{
		case GLFW_KEY_A:
			m_spring1->SetMotorSpeed(m_speed);
			break;

		case GLFW_KEY_S:
			m_spring1->SetMotorSpeed(0.0f);
			break;

		case GLFW_KEY_D:
			m_spring1->SetMotorSpeed(-m_speed);
			break;

		case GLFW_KEY_Q:
			m_hz = b2Max(0.0f, m_hz - 1.0f);
			m_spring1->SetSpringFrequencyHz(m_hz);
			m_spring2->SetSpringFrequencyHz(m_hz);
			break;

		case GLFW_KEY_E:
			m_hz += 1.0f;
			m_spring1->SetSpringFrequencyHz(m_hz);
			m_spring2->SetSpringFrequencyHz(m_hz);
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

		g_camera.m_center.x = car_x;//m_car->GetPosition().x;
		g_camera.m_center.y = car_y;//m_car->GetPosition().y;

		/*create further landscape if close to the end*/
		float32 distance_to_see = 10.0f;
		if (fabs(ground_end - car_x) < distance_to_see) {
			create_polygon(car_x);
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
	float32 m_speed = 50.0f;

	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;

	private:
		b2Vec2 impulse{ jump_intensity_x, jump_intensity_y };
		const float32 jump_intensity_y = 0.05f;
		const float32 jump_intensity_x = 0.0f;
		
		b2BodyDef body_descriptor{};
		b2BodyDef wheel_descriptor{};
		b2WheelJointDef wheel_joint_descriptor{};

		WheelStructure wheels_info{};
		//b2FixtureDef wheel_structure{};

		void set_body_type(b2BodyType type_);
		void set_wheel_type(b2BodyType type_);

		void set_body_position(float32 x, float32 y);
		void set_wheel_position(float32 x, float32 y);
		void init_wheel_structure();

		b2PolygonShape create_chassis();
		void create_car_body();
		void joint_wheel(b2Body* wheel, const b2Vec2 & axis, const JointParams& params);
		void create_polygon(const float32 x_start);

		CarBuilder builder;

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
			10.0f,
			false,
			m_hz,
			m_zeta
		};
};

#endif

