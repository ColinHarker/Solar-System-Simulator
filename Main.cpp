#include <SFML/Graphics.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <cmath>
#include <math.h>
#include <string>
#include <iostream>


using namespace boost::multiprecision;

constexpr auto width = 2000;
constexpr auto height = 2000;


cpp_dec_float_50 gConst = 6.67 * pow(10, -11);
cpp_dec_float_50 AU = (149.6e6 * 1000);
cpp_dec_float_50 SCALE = 250 / AU;




class Body {

public:

	cpp_dec_float_50 mass = 0.0;
	float radius = 0.0;
	cpp_dec_float_50 vx = 0.0;
	cpp_dec_float_50 vy = 0.0;
	cpp_dec_float_50 px = 0.0;
	cpp_dec_float_50 py = 0.0;
	int id = 0;

	std::string name;

	sf::CircleShape CircleBody;

	void setup_appearance(
		int newRadius,
		sf::Uint8 R,
		sf::Uint8 G,
		sf::Uint8 B)
	{
		CircleBody.setRadius(newRadius);
		CircleBody.setOrigin(newRadius, newRadius);
		CircleBody.setFillColor(sf::Color::Color(R, G, B, 255));

		radius = newRadius;
	};
};

std::vector<Body*> vecBodys;

void addBody(Body* b);
cpp_dec_float_50 findGravitationalForce(cpp_dec_float_50 m1, cpp_dec_float_50 m2, long long int distance);

int main()
{

	sf::RenderWindow window(sf::VideoMode(width, height), "Title");
	window.setFramerateLimit(60);


	Body* pEarth = nullptr;
	Body* pSun = nullptr;
	Body* pVenus = nullptr;


	sf::Event event;

	Body sun;
	sun.name = "Sun";
	sun.mass = 1.989 * pow(10, 30);
	sun.setup_appearance(40, 234, 144, 133);
	pSun = &sun;
	addBody(pSun);

	Body earth;
	earth.name = "Earth";
	earth.mass = 5.972 * pow(10, 24);
	earth.px = -1 * AU;
	earth.vy = 29.783 * 1000;
	earth.setup_appearance(5, 233, 226, 208);
	pEarth = &earth;
	addBody(pEarth);

	/*
	Body venus;
	venus.name = "Venus";
	venus.mass = 4.867 * pow(10, 24);
	venus.px = 0.723 * AU;
	venus.vy = -35.02 * 1000;
	venus.setup_appearance(5, 212, 93, 121);
	pVenus = &venus;
	addBody(pVenus);
	*/


	while (window.isOpen())
	{
		int timestep = 24 * 3600;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}


		for (auto& body : vecBodys)
		{
			for (auto& target : vecBodys)
			{
				if (body->id != target->id)
				{
	
					long long int fDistance = sqrt(((body->px - target->px)*(body->px - target->px)) + ((body->py - target->py) * (body->py - target->py))).convert_to<long long int>();
					cpp_dec_float_50 force = findGravitationalForce(body->mass, target->mass, fDistance);
					
					cpp_dec_float_50 theta = atan2(target->py - body->py, target->px - body->px);
					cpp_dec_float_50 fx = cos(theta) * force;
					cpp_dec_float_50 fy = sin(theta) * force;

					body->vx += fx / body->mass * timestep;
					body->vy += fy / body->mass * timestep;

					double vx = body->vx.convert_to<double>();
					double vy = body->vy.convert_to<double>();

					body->px += vx * timestep;
					body->py += vy * timestep;
				}
			}
		}


		std::cout << (sun.px * (SCALE)).convert_to<float>() << std::endl;
		sun.CircleBody.setPosition(width / 2, height / 2);
		earth.CircleBody.setPosition((earth.px * (SCALE)).convert_to<float>(), (earth.py * (SCALE)).convert_to<float>());
		earth.CircleBody.move(width / 2, height / 2);
		//venus.CircleBody.setPosition((venus.px * (SCALE)).convert_to<float>(), (venus.py * (SCALE)).convert_to<float>());
		//venus.CircleBody.move(width / 2, height / 2);


		window.clear(sf::Color(110, 87, 115, 255));

		window.draw(sun.CircleBody);
		window.draw(earth.CircleBody);
		//window.draw(venus.CircleBody);

		window.display();

		
	}
	return 0;
}


//adds class pointers to vector array
void addBody(Body* b) {

	b->id = vecBodys.size();
	vecBodys.emplace_back(b);
}

cpp_dec_float_50 findGravitationalForce(cpp_dec_float_50 m1, cpp_dec_float_50 m2, long long int distance)
{
	cpp_dec_float_50 force;
	return  force = gConst * ((m1 * m2) / (pow(distance, 2)));
}


