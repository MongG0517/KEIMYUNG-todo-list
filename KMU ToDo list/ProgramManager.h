#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include "ToDo.h"
#include <fstream>

class MANAGER {
private:
	std::vector<TODO> list;
public:
	void LoadTasks(const std::string& filename);
	void SaveTasks(const std::string& filename);
	void SortList();
	void SetPos(int x, int y);
	void PrtTodo();
	void AddTodo();
	void DeleteTodo();
	void ModifyTodo();
	void FinishTodo();
	void PrtUi();
	void StartTodo();
};

#endif // !PROGRAM_MANAGER_H