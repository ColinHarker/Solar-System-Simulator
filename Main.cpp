#include "linker.h"
#include "functions.h"

int main()
{

	sf::RenderWindow window(sf::VideoMode(constant::kWidth, constant::kHeight), "Title");
	window.setFramerateLimit(60);
	sf::View view(sf::Vector2f(constant::kWidth / 2.0f, constant::kHeight / 2.0f), sf::Vector2f(constant::kWidth, constant::kHeight));

	sf::Event event;

	std::vector<Body> vecBodys = addBodies(constant::kFile_Name);

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
			body.total_fx = (cpp_dec_float_50)0.0;
			body.total_fy = (cpp_dec_float_50)0.0;
			for (auto& target : vecBodys)
			{
				if (body.id != target.id)
				{

					long long int fDistance = static_cast<long long int>(sqrt(((body.px - target.px) * (body.px - target.px)) + ((body.py - target.py) * (body.py - target.py))));
					cpp_dec_float_50 force = findGravitationalForce(body.mass, target.mass, static_cast<cpp_dec_float_50>(fDistance));

					cpp_dec_float_50 theta = atan2(target.py - body.py, target.px - body.px);
					cpp_dec_float_50 fx = cos(theta) * force;
					cpp_dec_float_50 fy = sin(theta) * force;

					body.total_fx += fx;
					body.total_fy += fy;
				}
			}
			body.vx += body.total_fx / body.mass * static_cast<cpp_dec_float_50>(timestep);
			body.vy += body.total_fy / body.mass * static_cast<cpp_dec_float_50>(timestep);

			double vx = static_cast<double>(body.vx);
			double vy = static_cast<double>(body.vy);

			body.px += static_cast<cpp_dec_float_50>(vx) * static_cast<cpp_dec_float_50>(timestep);
			body.py += static_cast<cpp_dec_float_50>(vy)* static_cast<cpp_dec_float_50>(timestep);

			body.CircleBody.setPosition(static_cast<float>(body.px * (constant::SCALE)), static_cast<float>(body.py * (constant::SCALE)));
			body.CircleBody.move(static_cast<float>(constant::kWidth / 2), static_cast<float>(constant::kHeight / 2));
			window.draw(body.CircleBody);
		}

		window.display();
	}
	return 0;
}

