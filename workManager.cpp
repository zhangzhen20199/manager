#include "workManager.h"

WorkManager::WorkManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{	
		cout << "文件不存在" << endl;

		this->m_ArrNum = 0;
		this->m_worker = NULL;

		this->m_File_is_Empty = true;

		ifs.close();

		return;
	}

	char ch;
	ifs >> ch;

	if (ifs.eof())
	{
		cout << "文件为空" << endl;

		this->m_ArrNum = 0;
		this->m_worker = nullptr;
		this->m_File_is_Empty = true;

		ifs.close();

		return;
	}

	int num = this->get_PeopleNum();
	//cout << "职工人数为：" << num << endl;

	this->m_ArrNum = num;
	this->m_File_is_Empty = false;


	//test code
	this->m_worker = new Worker*[this->m_ArrNum];
	this->init_people();

	/*for (size_t i = 0; i < this->m_ArrNum; i++)
	{
		cout << "职工编号：" << this->m_worker[i]->m_id
			<< "姓名：" << this->m_worker[i]->m_name
			<< "部门编号：" << this->m_worker[i]->m_depid << endl;
	}*/
}

int WorkManager::get_PeopleNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num=0;

	while (ifs>>id && ifs>>name && ifs>>dId)
	{
		num++;
	}

	return num;
}

void WorkManager::init_people()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int people_num = 0;

	while (ifs>>id &&ifs>>name &&ifs>>dId)
	{
		Worker* worker = nullptr;
		switch (dId)
		{
		case 1:
			worker = new Employee(id, name, dId);
			break;
		case 2:
			worker = new Manager(id, name, dId);
			break;
		case 3:
			worker = new Boss(id, name, dId);
			break;
		default:
			printf("not find dId\n");
			break;
		}

		this->m_worker[people_num] = worker;
		people_num++;
	}

	ifs.close();

	people_num++;
}

void WorkManager::show_people()
{
	if (this->m_File_is_Empty)
	{
		cout << "当前文件不存在或者为空" << endl;
	}

	for (int i = 0; i < m_ArrNum; i++)
	{
		//利用多态，纯虚函数，不同子类都会重写
		this->m_worker[i]->showInfo();
	}

	system("pause");
	system("cls");
}

void WorkManager::Show_Menu()
{
	cout << "*************************************" << endl;
	cout << "********欢迎使用职工管理系统！********" << endl;
	cout << "***********0.退出管理程序************" << endl;
	cout << "***********1.增加职工信息************" << endl;
	cout << "***********2.显示职工信息************" << endl;
	cout << "***********3.删除离职职工************" << endl;
	cout << "***********4.修改职工信息************" << endl;
	cout << "***********5.查找职工信息************" << endl;
	cout << "***********6.按照编号排序************" << endl;
	cout << "***********7.清空所有文档************" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}

void WorkManager::Exit_system()
{
	cout << "welcome" << endl;
	system("pause");
	exit(0);

}

void WorkManager::add_People()
{
	cout << "请输入添加职工数量：" << endl;
	int add_Num = 0;
	cin >> add_Num;

	if (add_Num > 0)
	{
		int total_num = 0;
		total_num = this->m_ArrNum + add_Num;
		Worker** newSpace = new Worker*[total_num];

		if (this->m_worker != NULL)
		{
			for (int i = 0; i < m_ArrNum; i++)
			{
				newSpace[i] = this->m_worker[i];
			}
		}

		for (int i = 0; i < add_Num; i++)
		{
			int id;
			string name;
			int dSlect;

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工名字：" << endl;
			cin >> name;

			cout << "请输入第" << i + 1 << "个新职工岗位：" << endl;
			cin >> dSlect;

			Worker* people = NULL;
			switch (dSlect)
			{
			case 1:
				people = new Employee(id, name, 1);
				break;
			case 2:
				people = new Manager(id, name, 2);
				break;
			case 3:
				people = new Boss(id, name, 3);
				break;
			default:
				cout << "输入的岗位有误" << endl;
				break;
			}

			newSpace[this->m_ArrNum + i] = people;
		}

		delete[] this->m_worker;

		this->m_worker = newSpace;

		this->m_ArrNum = total_num;

		this->m_File_is_Empty = false;

		cout << "添加成功" << add_Num << "名新职工" << endl;

		this->saved();
	}
	else
	{
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");
}

void WorkManager::Del_people()
{
	if (this->m_File_is_Empty)
	{
		cout << "文件不存在或者为空"<<endl;
	}
	else
	{
		cout << "请输入被删除的员工编号" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index==-1)
		{
			cout << "该员工不存在" << endl;
		}
		else
		{
			for (int i = index; i < this->m_ArrNum-1; i++)
			{
				this->m_worker[i] = this->m_worker[i + 1];
			}

			this->m_ArrNum--;
			this->saved();

			cout << "删除成功" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkManager::Modified_people()
{
	if (this->m_File_is_Empty) {
		cout << "文件不存在或者为空" <<endl;
	}
	else
	{
		int Id = 0;
		cout << "请输入职工编号：" << endl;
		cin >> Id;

		int ret = this->IsExist(Id);
		if (ret!=-1)
		{
			cout << "该员工查已找到" << endl;
			delete this->m_worker[ret];

			int id = 0;
			string newName = "";
			int newDid = 0;

			cout << "请输入新的id号" << endl;
			cin >> id;
			cout << "请输入新的姓名：" << endl;
			cin >> newName;
			cout << "请输入岗位：" << endl;
			cout << "1、员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> newDid;

			Worker* worker = NULL;

			switch (newDid)
			{
			case 1:
				worker = new Employee(id, newName, newDid);
				break;
			case 2:
				worker = new Manager(id, newName, newDid);
				break;
			case 3:
				worker = new Boss(id, newName, newDid);
				break;
			default:
				break;
			}

			this->m_worker[ret] = worker;

			this->saved();
			cout << "人员修改成功" << endl;
		}
		else
		{
			cout << "查无此人" << endl;
		}

		system("pause");
		system("cls");
	}
}

void WorkManager::Find_people()
{
	if (this->m_File_is_Empty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1、按照职工编号：" << endl;
		cout << "2、按照职工姓名：" << endl;
		int type = 0;
		cin >> type;
		if (type==1)
		{
			cout << "请输入职工编号：" << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);

			if (ret!=-1)
			{
				cout << "该职工的信息如下" << endl;
				this->m_worker[ret]->showInfo();
			}
			else
			{
				cout << "查无此人" << endl;
			}
		}
		else if(type==2)
		{
			bool flags = false;
			cout << "请输入员工姓名：" << endl;
			string name;
			cin >> name;

			for (int i = 0; i < this->m_ArrNum; i++)
			{
				if (this->m_worker[i]->m_name == name)
				{
					cout << "该员工信息如下：" << endl;
					this->m_worker[i]->showInfo();
					flags = true;
				}
			}

			if (!flags) {
				cout << "查无此人" << endl;
			}
		}
		else
		{
			cout << "输入方式有误" << endl;
		}

		system("pause");
		system("cls");
	}	
}

void WorkManager::Sort_people()
{
	if (this->m_File_is_Empty)
	{
		cout << "文件为空或不存在" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择工号排序方式：" << endl;
		cout << "1、升序" << endl;
		cout << "2、降序" << endl;
		int type = 0;
		cin >> type;
		//选择排序
		for (int i = 0; i < this->m_ArrNum; i++)
		{
			int minOrmax = i;
			for (int j = i+1; j < this->m_ArrNum; j++)
			{
				if (type==1)
				{
					if (this->m_worker[minOrmax]->m_id>this->m_worker[j]->m_id)
					{
						minOrmax = j;
					}
				}
				else
				{
					if (this->m_worker[minOrmax]->m_id<this->m_worker[j]->m_id)
					{
						minOrmax = j;
					}
				}
			}

			if (i!=minOrmax)
			{
				Worker* tmp = this->m_worker[i];
				this->m_worker[i] = this->m_worker[minOrmax];
				this->m_worker[minOrmax] = tmp;
			}

		}

		cout << "排序成功！排序后的结果为：" << endl;

		this->saved();
		this->show_people();
	}
}

void WorkManager::clear_File()
{
	cout << "是否删除：" << endl;
	cout << "1、是：" << endl;
	cout << "2、否：" << endl;

	int select = 2;
	cin >> select;
	if (select==1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_worker != nullptr)
		{
			for (int i = 0; i < this->m_ArrNum; i++)
			{
				if (this->m_worker[i]!= nullptr)
				{
					delete this->m_worker[i];
					this->m_worker[i] = nullptr;
				}
			}

			this->m_ArrNum = 0;
			delete[] this->m_worker;
			this->m_worker = nullptr;
			this->m_File_is_Empty = true;
		}

		cout<<"清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

int WorkManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_ArrNum; i++)
	{
		if (this->m_worker[i]->m_id == id)
		{
			index = i;
			break;
		}
	}

	return index;
}

void WorkManager::saved()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_ArrNum; i++)
	{
		ofs << this->m_worker[i]->m_id << " "
			<< this->m_worker[i]->m_name << " "
			<< this->m_worker[i]->m_depid << endl;
	}

	ofs.close();
}

WorkManager::~WorkManager()
{
	if (this->m_worker != nullptr)
	{
		for (int i = 0; i < this->m_ArrNum; i++)
		{
			if (this->m_worker[i] != NULL)
			{
				delete this->m_worker[i];
			}
		}
		delete[] this->m_worker;
		this->m_worker = nullptr;
 	}

}
