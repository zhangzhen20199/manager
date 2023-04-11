#include"People.h"

Employee::Employee(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depid = dId;
}

void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t���ţ�" << this->getDepName()
		<< "\t��λְ����ɾ�����������" << endl;

}

string Employee::getDepName()
{
	return string("Ա��");   
}


Manager::Manager(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depid = dId;
}

void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t���ţ�" << this->getDepName()
		<< "\t��λְ������ϰ彻��������" << endl;
}

string Manager::getDepName()
{
	return string("����");
}


Boss::Boss(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_depid = dId;
}

void Boss::showInfo()
{
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t���ţ�" << this->getDepName()
		<< "\t��λְ�𣺲�������" << endl;
}


string Boss::getDepName()
{
	return string("�ϰ�");
}
