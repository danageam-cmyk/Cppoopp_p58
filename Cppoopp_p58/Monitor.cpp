#include "Monitor.h"
#include <format>

double Monitor::getDiagonal() const {
	return diagonal;
}

Monitor* Monitor::setDiagonal(double diagonal) {
	this->diagonal = diagonal;
	return this;
}

std::string Monitor::toString() const {
	return std::format(
		"{} {}'' {} hrn ({} W)",
		getName(),
		diagonal,
		getPrice(),	
		getPower()
	);
}