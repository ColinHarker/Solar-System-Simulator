#pragma once

#include "boost/multiprecision/cpp_dec_float.hpp"
#include <string>

namespace constant {

	constexpr auto kWidth = 1920;
	constexpr auto kHeight = 1080;

	const std::string kFile_Name = "bodies.csv";

	const boost::multiprecision::cpp_dec_float_50
		gConst = 6.67 * pow(10, -11),
		AU = (149.6e6 * 1000),
		SCALE = 250 / AU;
}
