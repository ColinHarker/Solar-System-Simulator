#include "linker.h"

int main()
{

	sf::RenderWindow window(sf::VideoMode(width, height), "Title");
	window.setFramerateLimit(60);
	sf::View view(sf::Vector2f(width / 2.0f, height / 2.0f), sf::Vector2f(width, height));

	sf::Event event;

	std::vector<Body> vecBodys = addBodies(kFile_Name);

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

		for (auto& body : vecBodys)
		{
			body.total_fx = 0.0;
			body.total_fy = 0.0;
			for (auto& target : vecBodys)
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

