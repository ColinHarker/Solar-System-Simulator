#ifndef BODY_H
#define BODY_H


#include "linker.h"

using namespace boost::multiprecision;

struct Body
{
	float radius = 0.0;
	cpp_dec_float_50
		mass = 0.0,
		vx = 0.0,
		vy = 0.0,
		px = 0.0,
		py = 0.0,
		total_fx = 0.0,
		total_fy = 0.0;
	int id = 0;
	std::string name;

	sf::CircleShape CircleBody;

	Body() = default;

	Body(std::string n, cpp_dec_float_50 m, cpp_dec_float_50 position, cpp_dec_float_50 velocity, float radius, int R, int G, int B) {
		name = n;
		mass = m;
		px = position;
		vy = velocity;
		setup_appearance(radius, R, G, B);
	}

	void setup_appearance(
		float newRadius,
		sf::Uint8 R,
		sf::Uint8 G,
		sf::Uint8 B) {
		CircleBody.setRadius(newRadius);
		CircleBody.setOrigin(newRadius, newRadius);
		CircleBody.setFillColor(sf::Color::Color(R, G, B, 255));

		radius = newRadius;
	};
};

#endif // !BODY_H
