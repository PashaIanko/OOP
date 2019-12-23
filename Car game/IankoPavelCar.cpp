#include "IankoPavelCar.h"

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
