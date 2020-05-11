#include<iostream>
#include<cstring>
#define NAME_LEN 20
using namespace std;

enum { ACCMAKE = 1, DEPOSIT, WITHDRAW, ALLPRINT, EXIT };

typedef struct
{
	int accID; //���� ��ȣ
	int balance; //�ܾ�
	int cusName[NAME_LEN]; //���̸�

} Account;

Account* arr = new Account[100];
int Count = 0;

void AccMake(); //���� �����
void Deposit(); //�Ա�
void Withdrawal(); //���
void AllPrint(); // ��ü �������� ���

void AccMake() //���� �輳
{
	if (Count >= 100) {
		cout << "�輳 �� �� �ִ� ������ �Ѿ����ϴ�." << endl;
		return;
	}

	BACK:
	cout << "[���� �ż�]" << endl;
	cout << "ID �Է�: "; cin >> arr[Count].accID;
	for (int i = 0; i < Count; i++) {
		if (arr[Count].accID <= 0 || arr[i].accID == arr[Count].accID)
		{
			cout << "�̹� �輳�� �Ǿ��ų� ���� �� ���� ���� ��ȣ �Դϴ�." << endl;
			cout << ' ' << endl;
			cout << "�ٽ� �Է� ���ּ���." << endl;
			goto BACK; //�ٽ� �����
		}
	}

	cout << "���� ��: ";cin >> arr[Count].cusName[NAME_LEN];
	cout << "���� �輳 �ʱ� �Աݾ��� �־� �ּ���.(10�� �̻�)" << endl;
	BACK1:
	cout << "�ݾ�: "; cin >> arr[Count].balance;
	if (arr[Count].balance < 10)
	{
		cout << "�ʼ� �ݾ��� 10�� �̻� �Դϴ�." << endl;
		cout << ' ' << endl;
		cout << "�ٽ� �ʱ� �ݾ� �־� �ּ���." << endl;
		goto BACK1;
	}

	
	Count++;
	cout << "���� �輳�� ���� �Ͽ����ϴ�." << endl;
	return;
}

void Deposit() //�Ա�
{

	if (Count == 0)
	{
		cout << "�輳�� ���°� �����ϴ�." << endl;
		return;
	}

	int ID = 0;
	int money = 0;


	cout << "���� ��ȣ �Է�: "; cin >> ID;
	for (int i = 0; i < Count; i++)
	{
		 if (arr[i].accID == ID)
		{
			cout << "�Աݾ�: "; cin>> money;
				if (money <= 0)
				{
					cout << "0���� �Ա� �� �� �����ϴ�." << endl;
				}
			arr[i].balance += money;
			cout << money << "�ԱݵǾ��� ���� �ݾ���" << arr[i].balance << endl;
		 }
		 else
		 {
			 cout << "���� ���� ��ȣ �Դϴ�." << endl;
		 }
	}
	
}

void Withdrawal() //���
{

	if (Count == 0)
	{
		cout << "�輳�� ���°� �����ϴ�." << endl;
		return;
	}

	int ID = 0;
	int money = 0;

	cout << "���� ��ȣ �Է�: "; cin >> ID;
	for (int i = 0; i < Count; i++)
	{
		if (arr[i].accID == ID)
		{
			cout << "��ݾ�: "; cin >> money;
			if (money <= 0)
			{
				cout << "0���� ��� �� �� �����ϴ�." << endl;
			}
			arr[i].balance -= money;
			cout << money << "��ݵǾ��� ���� �ݾ���" << arr[i].balance << endl;
			return;
		}
		cout << "���� ���� ��ȣ �Դϴ�." << endl;
	}

}

void AllPrint()//���� ��ü ����
{

	if (Count == 0)
	{
		cout << "�輳�� ���°� �����ϴ�." << endl;
		return;
	}

	for (int i = 0; i < Count; i++)
	{
		cout << "[" << i << "]" << "��°" << endl;
		cout << "���� ��: " << arr[i].cusName[NAME_LEN] << endl;
		cout << "���� ��ȣ: " << arr[i].accID << endl;
		cout << "���� �ݾ�: " << arr[i].balance << endl;
	}
	return;
}

void showMenu() //���� â
{
	cout << "\n";
	cout << "**�����**" << endl;
	cout << "1. ���� ����" << endl;
	cout << "2. �Ա�" << endl;
	cout << "3. ���" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
}

int main(void)
{
	int select;
	while (1) {
		showMenu();
		cout << "���� : ";
		cin >> select;

		switch (select) {
		case ACCMAKE:
			AccMake();
			break;
		case DEPOSIT:
			Deposit();
			break;
		case WITHDRAW:
			Withdrawal();
			break;
		case ALLPRINT:
			AllPrint();
			break;
		case EXIT: delete[] arr;
			return 0;
		default:
			cout << "�߸��� �޴� ��ȣ�Դϴ�." << endl;
			break;
		}
	}
}