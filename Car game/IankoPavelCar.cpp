#include "IankoPavelCar.h"
#include <vector>
#include <algorithm>
#include <cstdlib>

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

void IankoCar::change_leader_wheel(b2WheelJoint * from, b2WheelJoint * to) {
	if (leader_spring != to) {
		float32 chunk = m_speed / 600;
		float32 decrem_speed = m_speed;
		float32 increm_speed = 0.0f;
		for (size_t i = 0; i < 100; ++i) {
			decrem_speed -= chunk;
			increm_speed += chunk;
			from->SetMotorSpeed(decrem_speed);
			to->SetMotorSpeed(increm_speed);
		}
		/*final assignment*/
		from->SetMotorSpeed(0.0f);
		to->SetMotorSpeed(m_speed);
		leader_spring = to;
	}
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

	grnd_shape.Set({ x_start, 0.0f }, { 20.0f + x_start, 0.0f });
	ground->CreateFixture(&grnd_properties); /*задать свойства*/

	// Generate 10 random heights
	size_t rand_heights_size = 10;
	std::vector<float32> rand_heights(rand_heights_size);
	int32 max_height = 2;
	std::generate(rand_heights.begin(), rand_heights.end(), 
		[max_height]() {
		return rand() % max_height;
	});

	float32 x = 20.0f + x_start;
	float32 y1 = 0.0f; 
	float32 dx = 5.0f;

	for (int32 i = 0; i < rand_heights_size; ++i) {

		float32 cur_height = rand_heights[i];

		grnd_shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, cur_height));
		ground->CreateFixture(&grnd_properties);
		y1 = cur_height;
		x += dx;
	}

	grnd_shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, 0.0f)); //вернуться к нулевой высоте
	ground->CreateFixture(&grnd_properties);
	x += dx;

	grnd_shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 5.0f, 0.0f));
	ground->CreateFixture(&grnd_properties);
	x += 5.0f;

	//ground_end = x;

	//след. этап от x до x+20 - коробки
	grnd_shape.Set({ x, 0.0f }, { 10.0f + x, 0.0f });
	ground->CreateFixture(&grnd_properties); /*задать свойства*/

	// Boxes
	{
		/*Random position*/
		
		auto boxes_pos = std::rand() % (int)(10.0f);


		b2PolygonShape box;
		box.SetAsBox(0.25f, 0.25f);

		b2Body* body = NULL;
		b2BodyDef bd;
		bd.type = b2_dynamicBody;

		bd.position.Set(x + boxes_pos, 0.25f);
		body = m_world->CreateBody(&bd);
		body->CreateFixture(&box, 0.5f);

		bd.position.Set(x + boxes_pos, 0.75f);
		body = m_world->CreateBody(&bd);
		body->CreateFixture(&box, 0.5f);

		bd.position.Set(x + boxes_pos, 1.25f);
		body = m_world->CreateBody(&bd);
		body->CreateFixture(&box, 0.5f);

		bd.position.Set(x + boxes_pos, 1.75f);
		body = m_world->CreateBody(&bd);
		body->CreateFixture(&box, 0.5f);

		bd.position.Set(x + boxes_pos, 2.25f);
		body = m_world->CreateBody(&bd);
		body->CreateFixture(&box, 0.5f);
		
	}

	x += 10.0f;
	ground_end = x;

	/*далее - маятник*/
	//grnd_shape.Set({ x, 0.0f }, { 10.0f + x, 0.0f });

	/* //Teeter
	{
		auto teeter_pos = std::rand() % (int)(10.0f);

		b2BodyDef bd;
		bd.position.Set(x + teeter_pos, 1.0f);
		bd.type = b2_dynamicBody;
		b2Body* body = m_world->CreateBody(&bd);

		b2PolygonShape box;
		box.SetAsBox(10.0f, 0.25f);
		body->CreateFixture(&box, 1.0f);

		b2RevoluteJointDef jd;
		jd.Initialize(ground, body, body->GetPosition());
		jd.lowerAngle = -8.0f * b2_pi / 180.0f;
		jd.upperAngle = 8.0f * b2_pi / 180.0f;
		jd.enableLimit = true;
		m_world->CreateJoint(&jd);

		body->ApplyAngularImpulse(100.0f, true);
	}

	x += 10.0f;
	ground_end = x;*/

}
