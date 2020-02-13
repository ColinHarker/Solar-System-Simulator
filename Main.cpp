#include <SFML/Graphics.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <cmath>
#include <math.h>
#include <string>
#include <iostream>


using namespace boost::multiprecision;

constexpr auto width = 1920;
constexpr auto height = 1080;


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
	cpp_dec_float_50 total_fx = 0.0;
	cpp_dec_float_50 total_fy = 0.0;
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
void resizeView(const sf::RenderWindow& window, sf::View& view);

int main()
{

	sf::RenderWindow window(sf::VideoMode(width, height), "Title");
	window.setFramerateLimit(60);
	sf::View view(sf::Vector2f(width / 2.0f, height / 2.0f), sf::Vector2f(width, height));


	Body* pEarth = nullptr;
	Body* pSun = nullptr;
	Body* pVenus = nullptr;
	Body* pMars = nullptr;


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
	earth.vy = 29.783 * 1000; //km/s
	earth.setup_appearance(5, 233, 226, 208);
	pEarth = &earth;
	addBody(pEarth);

	
	Body venus;
	venus.name = "Venus";
	venus.mass = 4.867 * pow(10, 24);
	venus.px = 0.723 * AU;
	venus.vy = -35.02 * 1000;
	venus.setup_appearance(5, 212, 93, 121);
	pVenus = &venus;
	addBody(pVenus);

	Body mars;
	mars.name = "Mars";
	mars.mass = 6.39 * pow(10, 23);
	mars.px = 1.524 * AU;
	mars.vy = -24.07 * 1000;
	mars.setup_appearance(5, 195, 93, 121);
	pMars = &mars;
	addBody(pMars);
	


	while (window.isOpen())
	{
		int timestep = 24 * 3600;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{ 
				case sf::Event::Closed:
					window.close();
					break;
			
				case sf::Event::MouseWheelScrolled:
				{
					if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {

						std::cout << event.mouseWheelScroll.delta << std::endl;
						if (event.mouseWheelScroll.delta > 0)
						{
							view.zoom(0.5f);
						}
						else if (event.mouseWheelScroll.delta < 0)
						{
							view.zoom(1.5f);
						}
					}
				}
				//case sf::Event::Resized:
					//resizeView(window, view);
					//break;
			}
		}

		


		for (auto& body : vecBodys)
		{
			body->total_fx = 0.0;
			body->total_fy = 0.0;
			for (auto& target : vecBodys)
			{
				if (body->id != target->id)
				{
	
					long long int fDistance = sqrt(((body->px - target->px)*(body->px - target->px)) + ((body->py - target->py) * (body->py - target->py))).convert_to<long long int>();
					cpp_dec_float_50 force = findGravitationalForce(body->mass, target->mass, fDistance);
					
					cpp_dec_float_50 theta = atan2(target->py - body->py, target->px - body->px);
					cpp_dec_float_50 fx = cos(theta) * force;
					cpp_dec_float_50 fy = sin(theta) * force;

					body->total_fx += fx;
					body->total_fy += fy;
				}
			}
		}
		for (auto& body : vecBodys)
		{
			body->vx += body->total_fx / body->mass * timestep;
			body->vy += body->total_fy / body->mass * timestep;

			double vx = body->vx.convert_to<double>();
			double vy = body->vy.convert_to<double>();

			body->px += vx * timestep;
			body->py += vy * timestep;
		}
		//std::cout << (sun.px * (SCALE)).convert_to<float>() << std::endl;
		sun.CircleBody.setPosition(width / 2, height / 2);
		earth.CircleBody.setPosition((earth.px * (SCALE)).convert_to<float>(), (earth.py * (SCALE)).convert_to<float>());
		earth.CircleBody.move(width / 2, height / 2);
		venus.CircleBody.setPosition((venus.px * (SCALE)).convert_to<float>(), (venus.py * (SCALE)).convert_to<float>());
		venus.CircleBody.move(width / 2, height / 2);
		mars.CircleBody.setPosition((mars.px * (SCALE)).convert_to<float>(), (mars.py * (SCALE)).convert_to<float>());
		mars.CircleBody.move(width / 2, height / 2);

		window.clear(sf::Color(110, 87, 115, 255));
		window.setView(view);

		window.draw(sun.CircleBody);
		window.draw(earth.CircleBody);
		window.draw(venus.CircleBody);
		window.draw(mars.CircleBody);

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

void resizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(height * aspectRatio, height);
}
