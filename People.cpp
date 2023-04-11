#include"People.h"

Employee::Employee(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depid = dId;
}

void Employee::showInfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t部门：" << this->getDepName()
		<< "\t岗位职责：完成经理交待的任务" << endl;

}

string Employee::getDepName()
{
	return string("员工");   
}


Manager::Manager(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depid = dId;
}

void Manager::showInfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t部门：" << this->getDepName()
		<< "\t岗位职责：完成老板交待的任务" << endl;
}

string Manager::getDepName()
{
	return string("经理");
}


Boss::Boss(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depid = dId;
}

void Boss::showInfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t部门：" << this->getDepName()
		<< "\t岗位职责：布置任务" << endl;
}


string Boss::getDepName()
{
	return string("老板");
}
