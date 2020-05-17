#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "linker.h"

std::vector<Body> addBodies(std::string file_name);
cpp_dec_float_50 findGravitationalForce(cpp_dec_float_50& m1, cpp_dec_float_50& m2, long long int& distance);

#endif // !FUNCTIONS_H
