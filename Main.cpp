#include <SFML/Graphics.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <cmath>
#include <math.h>
#include <string>
#include <iostream>

using namespace boost::multiprecision;

constexpr auto width = 1920;
constexpr auto height = 1080;

cpp_dec_float_50
	gConst = 6.67 * pow(10, -11),
	AU = (149.6e6 * 1000),
	SCALE = 250 / AU;

class Body
{

public:
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
	std::vector<Body> vecBodys;
	std::string name;

	sf::CircleShape CircleBody;

	Body(std::string n, cpp_dec_float_50 m, cpp_dec_float_50 position, cpp_dec_float_50 velocity, float _radius, int R, int G, int B)
	{
		name = n;
		mass = m;
		px = position;
		vy = velocity;
		setup_appearance(_radius, R, G, B);
	}

	void setup_appearance(
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
};

std::vector<Body> vecBodys;

void addBody(Body b);
cpp_dec_float_50 findGravitationalForce(cpp_dec_float_50 m1, cpp_dec_float_50 m2, long long int distance);
void resizeView(const sf::RenderWindow &window, sf::View &view);

int main()
{

	sf::RenderWindow window(sf::VideoMode(width, height), "Title");
	window.setFramerateLimit(60);
	sf::View view(sf::Vector2f(width / 2.0f, height / 2.0f), sf::Vector2f(width, height));

	sf::Event event;

	Body sun("Sun", 1.989 * pow(10, 30), 0.0, 0.0, 40, 234, 144, 133);
	addBody(sun);

	Body earth("Earth", 5.972 * pow(10, 24), -1 * AU, 29.783 * 1000, 5, 233, 226, 208);
	addBody(earth);

	Body venus("Venus", 4.867 * pow(10, 24), 0.723 * AU, 35.02 * 1000, 5, 212, 93, 121);
	addBody(venus);

	Body mercury("Mercury", 3.285 * pow(10, 23), 0.4 * AU, -48 * 1000, 5, 212, 93, 121);
	addBody(mercury);

	Body mars("Mars", 6.39 * pow(10, 23), 1.524 * AU, -24.07 * 1000, 5, 195, 93, 121);
	addBody(mars);

	Body jupiter("Jupiter", 1.898 * pow(10, 27), 5.2 * AU, -13.1 * 1000, 15, 195, 93, 121);
	addBody(jupiter);

	Body saturn("Saturn", 5.683 * pow(10, 26), 9.6 * AU, -9.68 * 1000, 15, 195, 93, 121);
	addBody(saturn);

	while (window.isOpen())
	{
		int timestep = 24 * 3600;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseWheelScrolled:
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{

					std::cout << event.mouseWheelScroll.delta << std::endl;
					if (event.mouseWheelScroll.delta > 0)
					{
						view.zoom(0.9f);
					}
					else if (event.mouseWheelScroll.delta < 0)
					{
						view.zoom(1.1f);
					}
				}
			}
				//case sf::Event::Resized:
				//resizeView(window, view);
				//break;
			}
		}

		window.clear(); //sf::Color(110, 87, 115, 255));
		window.setView(view);

		for (auto &body : vecBodys)
		{
			body.total_fx = 0.0;
			body.total_fy = 0.0;
			for (auto &target : vecBodys)
			{
				if (body.id != target.id)
				{

					long long int fDistance = sqrt(((body.px - target.px) * (body.px - target.px)) + ((body.py - target.py) * (body.py - target.py))).convert_to<long long int>();
					cpp_dec_float_50 force = findGravitationalForce(body.mass, target.mass, fDistance);

					cpp_dec_float_50 theta = atan2(target.py - body.py, target.px - body.px);
					cpp_dec_float_50 fx = cos(theta) * force;
					cpp_dec_float_50 fy = sin(theta) * force;

					body.total_fx += fx;
					body.total_fy += fy;
				}
			}
			body.vx += body.total_fx / body.mass * timestep;
			body.vy += body.total_fy / body.mass * timestep;

			double vx = body.vx.convert_to<double>();
			double vy = body.vy.convert_to<double>();

			body.px += vx * timestep;
			body.py += vy * timestep;

			body.CircleBody.setPosition((body.px * (SCALE)).convert_to<float>(), (body.py * (SCALE)).convert_to<float>());
			body.CircleBody.move(width / 2, height / 2);
			window.draw(body.CircleBody);
		}

		window.display();
	}
	return 0;
}

//adds class pointers to vector array
void addBody(Body b)
{

	b.id = vecBodys.size();
	vecBodys.emplace_back(b);
}

cpp_dec_float_50 findGravitationalForce(cpp_dec_float_50 m1, cpp_dec_float_50 m2, long long int distance)
{
	cpp_dec_float_50 force;
	return force = gConst * ((m1 * m2) / (pow(distance, 2)));
}

void resizeView(const sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(height * aspectRatio, height);
}
