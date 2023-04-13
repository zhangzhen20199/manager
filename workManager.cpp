#include "workManager.h"

WorkManager::WorkManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{	
		cout << "�ļ�������" << endl;

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
		cout << "�ļ�Ϊ��" << endl;

		this->m_ArrNum = 0;
		this->m_worker = nullptr;
		this->m_File_is_Empty = true;

		ifs.close();

		return;
	}

	int num = this->get_PeopleNum();
	//cout << "ְ������Ϊ��" << num << endl;

	this->m_ArrNum = num;
	this->m_File_is_Empty = false;


	//test code
	this->m_worker = new Worker*[this->m_ArrNum];
	this->init_people();

	/*for (size_t i = 0; i < this->m_ArrNum; i++)
	{
		cout << "ְ����ţ�" << this->m_worker[i]->m_id
			<< "������" << this->m_worker[i]->m_name
			<< "���ű�ţ�" << this->m_worker[i]->m_depid << endl;
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
		cout << "��ǰ�ļ������ڻ���Ϊ��" << endl;
	}

	for (int i = 0; i < m_ArrNum; i++)
	{
		//���ö�̬�����麯������ͬ���඼����д
		this->m_worker[i]->showInfo();
	}

	system("pause");
	system("cls");
}

void WorkManager::Show_Menu()
{
	cout << "*************************************" << endl;
	cout << "********��ӭʹ��ְ������ϵͳ��********" << endl;
	cout << "***********0.�˳��������************" << endl;
	cout << "***********1.����ְ����Ϣ************" << endl;
	cout << "***********2.��ʾְ����Ϣ************" << endl;
	cout << "***********3.ɾ����ְְ��************" << endl;
	cout << "***********4.�޸�ְ����Ϣ************" << endl;
	cout << "***********5.����ְ����Ϣ************" << endl;
	cout << "***********6.���ձ������************" << endl;
	cout << "***********7.��������ĵ�************" << endl;
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
	cout << "���������ְ��������" << endl;
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

			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����ְ�����֣�" << endl;
			cin >> name;

			cout << "�������" << i + 1 << "����ְ����λ��" << endl;
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
				cout << "����ĸ�λ����" << endl;
				break;
			}

			newSpace[this->m_ArrNum + i] = people;
		}

		delete[] this->m_worker;

		this->m_worker = newSpace;

		this->m_ArrNum = total_num;

		this->m_File_is_Empty = false;

		cout << "��ӳɹ�" << add_Num << "����ְ��" << endl;

		this->saved();
	}
	else
	{
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");
}

void WorkManager::Del_people()
{
	if (this->m_File_is_Empty)
	{
		cout << "�ļ������ڻ���Ϊ��"<<endl;
	}
	else
	{
		cout << "�����뱻ɾ����Ա�����" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index==-1)
		{
			cout << "��Ա��������" << endl;
		}
		else
		{
			for (int i = index; i < this->m_ArrNum-1; i++)
			{
				this->m_worker[i] = this->m_worker[i + 1];
			}

			this->m_ArrNum--;
			this->saved();

			cout << "ɾ���ɹ�" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkManager::Modified_people()
{
	if (this->m_File_is_Empty) {
		cout << "�ļ������ڻ���Ϊ��" <<endl;
	}
	else
	{
		int Id = 0;
		cout << "������ְ����ţ�" << endl;
		cin >> Id;

		int ret = this->IsExist(Id);
		if (ret!=-1)
		{
			cout << "��Ա�������ҵ�" << endl;
			delete this->m_worker[ret];

			int id = 0;
			string newName = "";
			int newDid = 0;

			cout << "�������µ�id��" << endl;
			cin >> id;
			cout << "�������µ�������" << endl;
			cin >> newName;
			cout << "�������λ��" << endl;
			cout << "1��Ա��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			cout << "��Ա�޸ĳɹ�" << endl;
		}
		else
		{
			cout << "���޴���" << endl;
		}

		system("pause");
		system("cls");
	}
}

void WorkManager::Find_people()
{
	if (this->m_File_is_Empty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1������ְ����ţ�" << endl;
		cout << "2������ְ��������" << endl;
		int type = 0;
		cin >> type;
		if (type==1)
		{
			cout << "������ְ����ţ�" << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);

			if (ret!=-1)
			{
				cout << "��ְ������Ϣ����" << endl;
				this->m_worker[ret]->showInfo();
			}
			else
			{
				cout << "���޴���" << endl;
			}
		}
		else if(type==2)
		{
			bool flags = false;
			cout << "������Ա��������" << endl;
			string name;
			cin >> name;

			for (int i = 0; i < this->m_ArrNum; i++)
			{
				if (this->m_worker[i]->m_name == name)
				{
					cout << "��Ա����Ϣ���£�" << endl;
					this->m_worker[i]->showInfo();
					flags = true;
				}
			}

			if (!flags) {
				cout << "���޴���" << endl;
			}
		}
		else
		{
			cout << "���뷽ʽ����" << endl;
		}

		system("pause");
		system("cls");
	}	
}

void WorkManager::Sort_people()
{
	if (this->m_File_is_Empty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ�񹤺�����ʽ��" << endl;
		cout << "1������" << endl;
		cout << "2������" << endl;
		int type = 0;
		cin >> type;
		//ѡ������
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

		cout << "����ɹ��������Ľ��Ϊ��" << endl;

		this->saved();
		this->show_people();
	}
}

void WorkManager::clear_File()
{
	cout << "�Ƿ�ɾ����" << endl;
	cout << "1���ǣ�" << endl;
	cout << "2����" << endl;

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

		cout<<"��ճɹ���" << endl;
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
