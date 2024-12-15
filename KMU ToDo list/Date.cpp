#include "Date.h"

_DATE::_DATE() {
	year = 2000;
	month = 1;
	day = 1;
}

std::string _DATE::ReturnDate() {
	std::string date_temp;
	date_temp = std::to_string(year) + "³â " + std::to_string(month) + "¿ù " + std::to_string(day) + "ÀÏ";
	return date_temp;
}

int _DATE::ReturnDateInt() {
	return year * 10000 + month * 100 + day;
}