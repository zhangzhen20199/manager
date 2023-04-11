#pragma once
#include<iostream>

using namespace std;
 
#include<string>
#include"worker.h"

class Employee:public Worker
{
public:

	Employee(int id, string name, int dId);

	virtual void showInfo();

	virtual string getDepName();
};


class Manager :public Worker
{
public:

	Manager(int id, string name, int dId);

	virtual void showInfo();

	virtual string getDepName();
};


class Boss :public Worker
{
public:

	Boss(int id, string name, int dId);

	virtual void showInfo();

	virtual string getDepName();
};

