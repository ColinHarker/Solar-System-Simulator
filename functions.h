#pragma once

#include "linker.h"
#include "Body.h"

std::vector<Body> addBodies(std::string file_name);
cpp_dec_float_50 findGravitationalForce(cpp_dec_float_50& m1, cpp_dec_float_50& m2, long long int& distance);
void resizeView(const sf::RenderWindow& window, sf::View& view);
