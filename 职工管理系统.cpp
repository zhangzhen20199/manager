#include<iostream>
#include"workManager.h"
#include"worker.h"
#include"People.h"

using namespace std;

#define EXIT_SYSTEM     0x00;
#define ADD_WORKERS     0x01;
#define PRINT_WORKERS   0x02;
#define DELETE_WORKERS  0x03;
#define MODIFY_WORKER   0x04;
#define FIND_WORKERS    0x05;
#define ORDER           0x06;
#define CLEAR_FILES     0x07;

int main()
{
	/*Worker* worker = NULL;
	worker = new Employee(1, "aa", 1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "bb", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "cc", 3);
	worker->showInfo();
	delete worker;*/

	WorkManager wm;
	int choice = 0;
	while (1)
	{
		wm.Show_Menu();
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ£º" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			wm.Exit_system();
			break;
		case 1:
			wm.add_People();
			break;
		case 2:
			wm.show_people();
			break;
		case 3:
			wm.Del_people();
			break;
		case 4:
			wm.Modified_people();
			break;
		case 5:
			wm.Find_people();
			break;
		case 6:
			break;
		case 7:
			break;
		default:
			system("cls");
			break;
		}
	}
	
	wm.~WorkManager();
	system("pause");
	return 0;
}