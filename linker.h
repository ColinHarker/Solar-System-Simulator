#pragma once

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Body.h"
#include "functions.h"

constexpr auto width = 1920;
constexpr auto height = 1080;

std::string kFile_Name = "bodies.csv";

cpp_dec_float_50
gConst = 6.67 * pow(10, -11),
AU = (149.6e6 * 1000),
SCALE = 250 / AU;

