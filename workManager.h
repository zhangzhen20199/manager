#pragma once
#include<iostream>

using namespace std;

#include"worker.h"
#include"People.h"

#include<fstream>

#define FILENAME "people_information.txt"

class WorkManager
{
public:
	WorkManager();

	void Show_Menu();

	void Exit_system();

	void init_people();

	void show_people();

	void add_People();

	int IsExist(int id);

	void Del_people();

	void Modified_people();

	void Find_people();

	int get_PeopleNum();

	void saved();

	~WorkManager();


	int m_ArrNum;
	
	Worker** m_worker;

	bool m_File_is_Empty;
};
