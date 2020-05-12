#include "Body.h"

Body::Body(std::string n, cpp_dec_float_50 m, cpp_dec_float_50 position, cpp_dec_float_50 velocity, float _radius, int R, int G, int B)
	{
		name = n;
		mass = m;
		px = position;
		vy = velocity;
		setup_appearance(_radius, R, G, B);
	}
void Body::setup_appearance(
		float newRadius,
		sf::Uint8 R,
		sf::Uint8 G,
		sf::Uint8 B)
	{
		CircleBody.setRadius(newRadius);
		CircleBody.setOrigin(newRadius, newRadius);
		CircleBody.setFillColor(sf::Color::Color(R, G, B, 255));

		radius = newRadius;
	};



