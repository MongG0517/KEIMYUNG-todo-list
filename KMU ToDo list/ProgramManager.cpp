#include"ProgramManager.h"

void MANAGER::LoadTasks(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "������ �� �� �����ϴ�: " << filename << std::endl;
		return;
	}

	TODO tempTodo;
	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) continue;

		std::istringstream iss(line);
		std::getline(iss, tempTodo.title, '|');
		std::getline(iss, tempTodo.contents, '|');
		std::string End_Date;
		std::getline(iss, End_Date, '|');
		std::string state;
		std::getline(iss, state, '|');
		tempTodo.state = (state == "1" ? true : false);
		tempTodo.end_date.year = std::stoi(End_Date.substr(0, 4));
		tempTodo.end_date.month = std::stoi(End_Date.substr(4, 2));
		tempTodo.end_date.day = std::stoi(End_Date.substr(6, 2));

		list.push_back(tempTodo);
	}

	file.close();
}

void MANAGER::SaveTasks(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "������ �� �� �����ϴ�: " << filename << std::endl;
		return;
	}

	for (auto& task : list) {
		file << task.title << '|' << task.contents << '|' << task.end_date.ReturnDateInt() << '|' << task.state << '\n';
	}

	file.close();
}

void MANAGER::SortList() {
	if (!list.empty()) {
		for (int i = 0; i < list.size() - 1; i++) {
			for (int j = 0; j < list.size() - i - 1; j++) {
				if (list[i].end_date.year > list[i + 1].end_date.year) {
					TODO temp = list[i];
					list[i] = list[i + 1];
					list[i + 1] = temp;
				}
				else if (list[i].end_date.year == list[i + 1].end_date.year && list[i].end_date.month > list[i + 1].end_date.month) {
					TODO temp = list[i];
					list[i] = list[i + 1];
					list[i + 1] = temp;
				}
				else if (list[i].end_date.year == list[i + 1].end_date.year && list[i].end_date.month == list[i + 1].end_date.month && list[i].end_date.day > list[i + 1].end_date.day) {
					TODO temp = list[i];
					list[i] = list[i + 1];
					list[i + 1] = temp;
				}
			}
		}
	}
}

// Ŀ�� ��ġ ����
void MANAGER::SetPos(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// LIST �߰�
void MANAGER::AddTodo() {
	system("cls");
	TODO temp;
	temp.SetTodo();
	list.push_back(temp);
	system("cls");
}

// LIST ���
void MANAGER::PrtTodo() {
	system("cls");
	int key;
	int cursor = 0;
	int max_cursor = list.size();
	if (list.empty()) {
		std::cout << "   [����Ʈ�� ����ֽ��ϴ�...]";
	}

	while (1) {
		SetPos(0, 4);
		for (int i = 0; i < list.size(); i++) {
			std::cout << "   [" << list[i].GetTitle() << "] " << list[i].GetState() << std::endl;
		}
		SetPos(0, 4 + list.size());
		std::cout << "   [�ڷΰ���]";

		SetPos(0, 4 + cursor);
		std::cout << "��";
		key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // KEY_UP
				if (cursor != 0) {
					cursor--;
				}
				break;
			case 80: // KEY_DOWN
				if (cursor != max_cursor) {
					cursor++;
				}
				break;
			}
		}
		else if (key == 13) {
			if (cursor != max_cursor) {
				system("cls");
				SetPos(0, 4);
				for (int i = 0; i < list.size(); i++) {
					std::cout << "   [" << list[i].GetTitle() << "] " << list[i].GetState() << std::endl;
				}
				SetPos(0, 4 + list.size());
				std::cout << "   [�ڷΰ���]";

				SetPos(0, 4 + cursor);
				std::cout << "��";
				SetPos(list[cursor].title.length() + 5, 5 + cursor);
				std::cout << " [����]                         ";
				SetPos(list[cursor].title.length() + 5, 6 + cursor);
				std::cout << ' ' << list[cursor].GetContents() << "             ";
				SetPos(list[cursor].title.length() + 5, 7 + cursor);
				std::cout << " [������]                       ";
				SetPos(list[cursor].title.length() + 5, 8 + cursor);
				std::cout << ' ' << list[cursor].GetEndDate() << "              ";
				_getch();
				system("cls");
			}

			if (cursor == max_cursor)
				break;
		}
	}
	system("cls");
}

void MANAGER::DeleteTodo() {
	system("cls");
	int key;
	int cursor = 0;
	int max_cursor = list.size();
	if (list.empty()) {
		std::cout << "   [����Ʈ�� ����ֽ��ϴ�...]";
	}

	while (1) {
		SetPos(0, 4);
		for (int i = 0; i < list.size(); i++) {
			std::cout << "   [" << list[i].GetTitle() << "] " << list[i].GetState() << std::endl;
		}
		SetPos(0, 4 + list.size());
		std::cout << "   [�ڷΰ���]";

		SetPos(0, 4 + cursor);
		std::cout << "��";
		key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // KEY_UP
				if (cursor != 0) {
					cursor--;
				}
				break;
			case 80: // KEY_DOWN
				if (cursor != max_cursor) {
					cursor++;
				}
				break;
			}
		}
		else if (key == 13) {
			if (cursor != max_cursor) {
				system("cls");
				SetPos(0, 4);
				for (int i = 0; i < list.size(); i++) {
					std::cout << "   [" << list[i].GetTitle() << "] " << list[i].GetState() << std::endl;
				}
				SetPos(0, 4 + list.size());
				std::cout << "   [�ڷΰ���]";

				SetPos(0, 4 + cursor);
				std::cout << "��";
				SetPos(24, 5 + cursor);
				std::cout << "[�ش� ������Ʈ�� �����Ͻðڽ��ϱ�?]";
				SetPos(24, 6 + cursor);
				std::cout << "[y : ���� | n : ���]";
				while (1) {
					key = _getch();
					if (key == 'y') {
						list.erase(list.begin() + cursor);
						max_cursor = list.size();
						break;
					}
					else if (key == 'n') {
						break;
					}
				}
				system("cls");
			}

			if (cursor == max_cursor)
				break;
		}
	}
	system("cls");
}

void MANAGER::ModifyTodo() {
	system("cls");
	int key;
	int cursor = 0;
	int max_cursor = list.size();
	if (list.empty()) {
		std::cout << "   [����Ʈ�� ����ֽ��ϴ�...]";
	}

	while (1) {
		SetPos(0, 4);
		for (int i = 0; i < list.size(); i++) {
			std::cout << "   [" << list[i].GetTitle() << "] " << list[i].GetState() << std::endl;
		}
		SetPos(0, 4 + list.size());
		std::cout << "   [�ڷΰ���]";

		SetPos(0, 4 + cursor);
		std::cout << "��";
		key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // KEY_UP
				if (cursor != 0) {
					cursor--;
				}
				break;
			case 80: // KEY_DOWN
				if (cursor != max_cursor) {
					cursor++;
				}
				break;
			}
		}
		else if (key == 13) {
			if (cursor != max_cursor) {
				system("cls");
				SetPos(0, 4);
				for (int i = 0; i < list.size(); i++) {
					std::cout << "   [" << list[i].GetTitle() << "] " << list[i].GetState() << std::endl;
				}
				SetPos(0, 4 + list.size());
				std::cout << "   [�ڷΰ���]";

				SetPos(0, 4 + cursor);
				std::cout << "��";
				SetPos(24, 5 + cursor);
				std::cout << "[�ش� ������Ʈ�� �����Ͻðڽ��ϱ�?]";
				SetPos(24, 6 + cursor);
				std::cout << "[y : ���� | n : ���]";
				while (1) {
					key = _getch();
					if (key == 'y') {
						system("cls");
						list[cursor].SetTodo();
						break;
					}
					else if (key == 'n') {
						break;
					}
				}
				system("cls");
			}

			if (cursor == max_cursor)
				break;
		}
	}
	system("cls");
}

void MANAGER::FinishTodo() {
	system("cls");
	int key;
	int cursor = 0;
	int max_cursor = list.size();
	if (list.empty()) {
		std::cout << "   [����Ʈ�� ����ֽ��ϴ�...]";
	}

	while (1) {
		SetPos(0, 4);
		for (int i = 0; i < list.size(); i++) {
			std::cout << "   [" << list[i].GetTitle() << "] " << list[i].GetState() << std::endl;
		}
		SetPos(0, 4 + list.size());
		std::cout << "   [�ڷΰ���]";

		SetPos(0, 4 + cursor);
		std::cout << "��";
		key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // KEY_UP
				if (cursor != 0) {
					cursor--;
				}
				break;
			case 80: // KEY_DOWN
				if (cursor != max_cursor) {
					cursor++;
				}
				break;
			}
		}
		else if (key == 13) {
			if (cursor != max_cursor) {
				system("cls");
				SetPos(0, 4);
				for (int i = 0; i < list.size(); i++) {
					std::cout << "   [" << list[i].GetTitle() << "] " << list[i].GetState() << std::endl;
				}
				SetPos(0, 4 + list.size());
				std::cout << "   [�ڷΰ���]";

				SetPos(0, 4 + cursor);
				std::cout << "��";
				SetPos(24, 5 + cursor);
				std::cout << "[�ش� ������Ʈ�� �Ϸ��ϰų� ����Ͻðڽ��ϱ�?]";
				SetPos(24, 6 + cursor);
				std::cout << "[y : �Ϸ� | n : ���]";
				while (1) {
					key = _getch();
					if (key == 'y') {
						list[cursor].SetState(true);
						break;
					}
					else if (key == 'n') {
						list[cursor].SetState(false);
						break;
					}
				}
				system("cls");
			}

			if (cursor == max_cursor)
				break;
		}
	}
	system("cls");
}

// UI ���
/*void MANAGER::PrtUi() {
	SetPos(0, 0);
	if (list.size() != 0) {

	}
}*/

// ���α׷� ����
void MANAGER::StartTodo() {
	LoadTasks("TODO.txt");
	int key;
	int cursor = 1;
	int cursor_max = 5;
	while (1) {
		CONSOLE_CURSOR_INFO Curinfo;
		Curinfo.dwSize = 1;
		Curinfo.bVisible = 0;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);

		//system("cls");
		SetPos(0, 4);
		std::cout << "   [���]" << std::endl;
		std::cout << "   [�߰�]" << std::endl;
		std::cout << "   [����]" << std::endl;
		std::cout << "   [����]" << std::endl;
		std::cout << "   [�Ϸ�]" << std::endl;
		std::cout << "   [����]" << std::endl;
		SetPos(0, 3 + cursor);
		std::cout << "��";
		SortList();
		key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // KEY_UP
				if (cursor != 1) {
					cursor--;
				}
				break;
			case 80: // KEY_DOWN
				if (cursor != 6) {
					cursor++;
				}
				break;
			}
		}
		else if (key == 13) {
			switch (cursor) {
			case 1:
				// ���
				PrtTodo();
				break;
			case 2:
				// �߰�
				AddTodo();
				break;
			case 3:
				DeleteTodo();
				// ����
				break;
			case 4:
				// ����
				ModifyTodo();
				break;
			case 5:
				// �Ϸ�
				FinishTodo();
				break;
			case 6:
				// ����
				SaveTasks("TODO.txt");
				return;
			}
			cursor = 1;
		}
	}
}