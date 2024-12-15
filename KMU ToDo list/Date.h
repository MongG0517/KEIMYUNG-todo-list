#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class _DATE {
public:
	int year;
	int month;
	int day;
	_DATE();
	std::string ReturnDate();
	int ReturnDateInt();
};

#endif