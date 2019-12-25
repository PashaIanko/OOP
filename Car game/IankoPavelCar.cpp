#include "IankoPavelCar.h"

void IankoCar::set_body_type(b2BodyType type_) {
	body_descriptor.type = type_;
}

void IankoCar::set_wheel_type(b2BodyType type_) {
	wheel_descriptor.type = type_;
}

void IankoCar::set_body_position(float32 x, float32 y) {
	body_descriptor.position.Set(x, y);
}

void IankoCar::set_wheel_position(float32 x, float32 y) {
	wheel_descriptor.position.Set(x, y);
}

void IankoCar::init_wheel_structure() {

	wheels_info.circle.m_radius = 0.4f;

	wheels_info.phys_properties.shape = &wheels_info.circle;
	wheels_info.phys_properties.density = 1.0f;
	wheels_info.phys_properties.friction = 0.9f;
}

b2PolygonShape IankoCar::create_chassis()
{
	b2PolygonShape chassis;
	b2Vec2 vertices[8];
	vertices[0].Set(-1.5f, -0.5f);
	vertices[1].Set(1.5f, -0.5f);
	vertices[2].Set(1.5f, 0.0f);
	vertices[3].Set(0.0f, 0.9f);
	vertices[4].Set(-1.15f, 0.9f);
	vertices[5].Set(-1.5f, 0.2f);
	chassis.Set(vertices, 6);
	return chassis;
}

void IankoCar::create_car_body() {
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(0.0f, 1.0f);

	car_details.body = m_world->CreateBody(&bd);
	m_car = m_world->CreateBody(&bd);
	m_car->CreateFixture((car_details.chassis), 1.0f);

}

void IankoCar::joint_wheel(b2Body* wheel, const b2Vec2 & axis, const JointParams& params) {
	wheel_joint_descriptor.Initialize(m_car, wheel, wheel->GetPosition(), axis);
	
	wheel_joint_descriptor.motorSpeed = params.motorSpeed;
	wheel_joint_descriptor.maxMotorTorque = params.maxMotorTorque;
	wheel_joint_descriptor.enableMotor = params.enableMotor;
	wheel_joint_descriptor.frequencyHz = params.frequencyHz;
	wheel_joint_descriptor.dampingRatio = params.dampingRatio;
	//m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);
}

void IankoCar::create_polygon(const float32 x_start) {

	grnd_shape.Set({ -20.0f + x_start, 0.0f }, { 20.0f + x_start, 0.0f });
	ground->CreateFixture(&grnd_properties); /*задать свойства*/
	ground_end = 20.0f + x_start;

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
			}*/

}
