#include "ToDo.h"
#include <chrono>
#include <iomanip>

bool is_valid_date_input(const std::string& date) {
	if (date.length() != 8) return false;
	for (char ch : date) {
		if (!std::isdigit(ch)) return false;
	}
	return true;
}

void TODO::SetTitle() {
	std::cout << "제목을 입력하여 주십시오." << std::endl << ">> ";
	if (std::cin.peek() == '\n') std::cin.ignore();
	std::getline(std::cin, title);

	if (title.length() > MaxTitle) MaxTitle = title.length();
}

void TODO::SetContents() {
	std::cout << "내용을 입력하여 주십시오." << std::endl << ">> ";
	if (std::cin.peek() == '\n') std::cin.ignore();
	std::getline(std::cin, contents);
}

void TODO::SetStartDate() {
	std::string Start_Date;
	std::string word;
	std::cout << "시작일을 입력하여 주십시오.(YYYYMMDD)" << std::endl << ">> ";
	std::cin >> Start_Date;
	word = Start_Date;
	start_date.year = std::stoi(word.substr(0, 4));
	word = Start_Date;
	start_date.month = std::stoi(word.substr(4, 2));
	word = Start_Date;
	start_date.day = std::stoi(word.substr(6, 2));
}

void TODO::SetEndDate() {
	std::string End_Date;
	std::string word;
	while (true) {
		std::cout << "종료일을 입력하여 주십시오.(YYYYMMDD)" << std::endl << ">>";
		std::cin >> End_Date;

		if (is_valid_date_input(End_Date)) {
			end_date.year = std::stoi(End_Date.substr(0, 4));
			end_date.month = std::stoi(End_Date.substr(4, 2));
			end_date.day = std::stoi(End_Date.substr(6, 2));
			if (end_date.month >= 1 && end_date.month <= 12 && end_date.day >= 1 && end_date.day <= 31) {
				break;
			}
			else {
				std::cout << "유효하지 않은 날짜입니다. 다시 입력해주세요." << std::endl;
			}
		}
		else {
			std::cout << "잘못된 형식입니다. 숫자 8자리로 입력해주세요." << std::endl;
		}
	}
}

void TODO::SetImportance() {
	std::cout << "중요도를 입력하여 주십시오." << std::endl << ">>";
	std::cin >> this->importance;
}

void TODO::SetState(bool state) {
	this->state = state;
}

std::string TODO::GetTitle() {
	return this->title;
}

/*std::string TODO::GetTitleShort() {
	std::string temp(title);
	if (temp.size() > 20) {
		for (int i = 0; i < 18; i++) {
			if (sizeof(title[i]) == 1) {
				temp += title[i];
			}
			else {
				if (temp.size() != 17) {
					temp += title[i];
					temp += title[++i];
				}
			}
		}
	}
	return temp;
}*/

std::string TODO::GetContents() {
	return this->contents;
}

std::string TODO::GetStartDate() {
	return start_date.ReturnDate();
}

std::string TODO::GetEndDate() {
	return end_date.ReturnDate();
}

std::string TODO::GetState() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm local_time;
	localtime_s(&local_time, &now_time);
	int today = (local_time.tm_year + 1900) * 10000
		+ (local_time.tm_mon + 1) * 100
		+ local_time.tm_mday;
	if (state) {
		return "[완료]";
	}
	else {
		if (today == end_date.ReturnDateInt()) {
			return "[D-DAY]";
		}
		else if (today < end_date.ReturnDateInt()) {
			return "[진행]";
		}
		else if (today > end_date.ReturnDateInt()) {
			return "[마감]";
		}
	}
}

/*int TODO::GetImportance() {
	return this->importance;
}*/

void TODO::SetTodo() {
	CONSOLE_CURSOR_INFO Curinfo;
	Curinfo.dwSize = 1;
	Curinfo.bVisible = 1; // 커서 표시
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
	SetTitle();
	SetContents();
	//SetStartDate();
	SetEndDate();
}

void TODO::PrtTodo() {
	/*
	std::cout << "제목: " << GetTitle() << std::endl;
	std::cout << "내용: " << std::endl << GetContents() << std::endl;
	PrtStartDate();
	PrtEndDate();
	*/
}