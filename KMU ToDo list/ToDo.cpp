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
	std::cout << "������ �Է��Ͽ� �ֽʽÿ�." << std::endl << ">> ";
	if (std::cin.peek() == '\n') std::cin.ignore();
	std::getline(std::cin, title);

	if (title.length() > MaxTitle) MaxTitle = title.length();
}

void TODO::SetContents() {
	std::cout << "������ �Է��Ͽ� �ֽʽÿ�." << std::endl << ">> ";
	if (std::cin.peek() == '\n') std::cin.ignore();
	std::getline(std::cin, contents);
}

void TODO::SetStartDate() {
	std::string Start_Date;
	std::string word;
	std::cout << "�������� �Է��Ͽ� �ֽʽÿ�.(YYYYMMDD)" << std::endl << ">> ";
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
		std::cout << "�������� �Է��Ͽ� �ֽʽÿ�.(YYYYMMDD)" << std::endl << ">>";
		std::cin >> End_Date;

		if (is_valid_date_input(End_Date)) {
			end_date.year = std::stoi(End_Date.substr(0, 4));
			end_date.month = std::stoi(End_Date.substr(4, 2));
			end_date.day = std::stoi(End_Date.substr(6, 2));
			if (end_date.month >= 1 && end_date.month <= 12 && end_date.day >= 1 && end_date.day <= 31) {
				break;
			}
			else {
				std::cout << "��ȿ���� ���� ��¥�Դϴ�. �ٽ� �Է����ּ���." << std::endl;
			}
		}
		else {
			std::cout << "�߸��� �����Դϴ�. ���� 8�ڸ��� �Է����ּ���." << std::endl;
		}
	}
}

void TODO::SetImportance() {
	std::cout << "�߿䵵�� �Է��Ͽ� �ֽʽÿ�." << std::endl << ">>";
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
		return "[�Ϸ�]";
	}
	else {
		if (today == end_date.ReturnDateInt()) {
			return "[D-DAY]";
		}
		else if (today < end_date.ReturnDateInt()) {
			return "[����]";
		}
		else if (today > end_date.ReturnDateInt()) {
			return "[����]";
		}
	}
}

/*int TODO::GetImportance() {
	return this->importance;
}*/

void TODO::SetTodo() {
	CONSOLE_CURSOR_INFO Curinfo;
	Curinfo.dwSize = 1;
	Curinfo.bVisible = 1; // Ŀ�� ǥ��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
	SetTitle();
	SetContents();
	//SetStartDate();
	SetEndDate();
}

void TODO::PrtTodo() {
	/*
	std::cout << "����: " << GetTitle() << std::endl;
	std::cout << "����: " << std::endl << GetContents() << std::endl;
	PrtStartDate();
	PrtEndDate();
	*/
}