#ifndef TODO_H
#define TODO_H

#include "Date.h"
#include <Windows.h>
#include <conio.h>

class TODO {
private:

	void SetTitle();
	void SetContents();
	void SetStartDate();
	void SetEndDate();

public:
	std::string title;
	std::string contents;
	std::string start_date_string;
	std::string end_date_string;
	bool state = false;

	_DATE start_date;
	_DATE end_date;

	void SetState(bool);

	std::string GetTitle();
	std::string GetContents();
	std::string GetStartDate();
	std::string GetEndDate();
	std::string GetState();

	void SetTodo();
	void PrtTodo();
};

#endif