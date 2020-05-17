#include "functions.h"

std::vector<Body> addBodies(std::string file_name) {
	std::vector<Body> temp_list;

	std::ifstream ifs;

	ifs.open(file_name);

	std::string name, mass, position, velocity, radius, r, g, b;
	while (getline(ifs, name, ',')) {
		getline(ifs, mass, ',');
		getline(ifs, position, ',');
		getline(ifs, velocity, ',');
		getline(ifs, radius, ',');
		getline(ifs, r, ',');
		getline(ifs, g, ',');
		getline(ifs, b, '\n');

		std::cout << name << mass << position << velocity << radius << r << g << b << std::endl;
		Body temp(name, static_cast<cpp_dec_float_50>(mass), static_cast<cpp_dec_float_50>(position)* AU, static_cast<cpp_dec_float_50>(velocity) * 1000, std::stof(radius), std::stoi(r), std::stoi(g), std::stoi(b));
		temp.id = temp_list.size();
		temp_list.push_back(temp);
	}
	return temp_list;
}

cpp_dec_float_50 findGravitationalForce(cpp_dec_float_50& m1, cpp_dec_float_50& m2, long long int& distance)
{
	cpp_dec_float_50 force;
	return force = gConst * ((m1 * m2) / (pow(distance, 2)));
}

