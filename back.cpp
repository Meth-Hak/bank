#include <iostream>
#include<cstring>

#define MAX_MEMBER 100
#define MAX_LEN 20

enum { ACCMAKE = 1, DEPOSIT, WITHDRAW, ALLPRINT, EXIT };

using namespace std;

//�Ա�, ���, ��� ,���� Ȯ��
class Account
{

private://class �������� ��� ����
	int accID; //���� ��ȣ
	int balance; //�ܾ�
	int Resident_registration_number;
	char* cusName; //���̸�

public://class �ܺο��� ��� ����

	//�⺻ ������
	Account() {}

	//������
	Account(
		int accID,
		int balance,
		int Resident_registration_number,
		char* cusName 
			)

	{
		//private���� ������ ������ ����ϱ� ���� this�� ���
		this->accID = accID;
		this->balance = balance;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		//string copy (����ǥ��) ���ڿ� ����
		//strcpy_s(�ٿ����� ����, ���ڿ� ġ��, ������ ����)
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	~Account()
	{
		cout << "��ü�� �����˴ϴ�" << endl;

		delete[] cusName;
	}

	//���� ������
	Account(const Account& CpyUser)
		//����
		: accID(CpyUser.accID), Resident_registration_number(CpyUser.Resident_registration_number)
	{
		cout << "���� ������" << endl;
		//private���� ������ ������ ����ϱ� ���� this�� ���
		this->balance = CpyUser.balance;
		this->cusName = new char[MAX_LEN];
		//string copy (����ǥ��) ���ڿ� ����
		//strcpy_s(�ٿ����� ����, ���ڿ� ġ��, ������ ����)
		strcpy_s(this->cusName, MAX_LEN, CpyUser.cusName);
	}

	char* getAccountMember() const
	{
		return cusName;
	}

	//�Ա�
	void Deposit(int balance)
	{
		this->balance += balance;
	}

	bool Withdrawal(int balance)
	{
		if (this->balance < balance)
		{
			return;
		}
		this->balance -= balance;
		return true;
	}

	//���� Ȯ��
	bool CheckAccMake(int accountID) const
	{
		return this->accID == accountID;
	}


	bool Check_SSN(int Resident_registration_number)
	{
		return this->Resident_registration_number == Resident_registration_number;
	}

	void AllPrint() const
	{
		cout << "����ID: " << accID << endl;
		cout << "�̸�: " << cusName << endl;
		cout << "�ܾ�: " << balance << endl;
		cout << endl;
	}
};

class AccountManager
{
public:
	//��ü ����
	Account* account[MAX_MEMBER];
	int Member_count = 0;

	//���� �輳
	void AccMake()
	{
		int accountID;
		int accountBalance;
		char accountName[20];
		int Resident_registration_number;

		cout << "[���� �輳]" << endl;
		cout << "����ID: " << endl;
		cin >> accountID;
		cout << "�̸�: " << endl;
		cin >> accountName;
		cout << "�Աݾ�: " << endl;
		cin >> accountBalance;

		//�ּ� �Ա� �ݾ� Ȯ��
		while (1)
		{
			if (accountBalance < 10)
			{
				cout << "�ʼ� �ݾ��� 10�� �̻� �Դϴ�." << endl;
				cout << endl;
				cout << "�ٽ� �ʱ� �ݾ� �־� �ּ���." << endl;
				cout << "�Աݾ�: " << endl;
				cin >> accountBalance;
			}
			else
			{
				break;
			}
		}

		cout << "�ֹε�Ϲ�ȣ: " << endl;
		cin >> Resident_registration_number;
		
		//account ������ ���� -> Account class�� account�迭�� Member_count��° �迭 �Է�
		account[Member_count] = new Account(accountID, accountBalance, Resident_registration_number, accountName);

		Member_count++;
		cout << endl;
	}

	//�Ա�
	void Deposit() const
	{
		int depositInput = 0; //�Է� ���� �ݾ�
		int CheckAccID; //�Է� ���� ���̵�
		char* memberList[MAX_MEMBER]; //ȸ���̸� ����Ʈ ��� �޾� �� ����
		int AccCheck_SSN = 0; //�Է� ���� �ֹε�Ϲ�ȣ

		cout << "[�Ա�]" << endl;
		cout << "ID: ";
		cin >> CheckAccID;

		for (int i = 0; i < Member_count; i++)
		{
			if (account[i]->CheckAccMake(CheckAccID))
			{
				for (int j = 0; j < Member_count; j++)
				{
					for (int k = 0; k < Member_count; k++)
					{
						memberList[k] = account[k]->getAccountMember();
					}

					if (memberList[i] == memberList[j])
					{
						cout << "���� ������ ����" << endl;
						cout << "�ֹε�Ϲ�ȣ: " << endl;
						cin >> AccCheck_SSN;
						cout << endl;

						if (account[i]->Check_SSN(AccCheck_SSN))
						{
							cout << "�Աݾ�: " << endl;
							cin >> depositInput;
							cout << endl;
							account[i]->Deposit(depositInput);
							return;
								
						}
					}
				}
			}
			else
			{
				cout << "��ȿ���� ���� ID �Դϴ�." << endl;
				return;
			}
		}

	}

	//���
	void Withdrawal() const
	{
		int depositInput = 0; //�Է� ���� �ݾ�
		int CheckAccID; //�Է� ���� ���̵�
		char* memberList[MAX_MEMBER]; //ȸ���̸� ����Ʈ ��� �޾� �� ����
		int AccCheck_SSN = 0; //�Է� ���� �ֹε�Ϲ�ȣ

		cout << "[�Ա�]" << endl;
		cout << "ID: ";
		cin >> CheckAccID;

		for (int i = 0; i < Member_count; i++)
		{
			if (account[i]->CheckAccMake(CheckAccID))
			{
				for (int j = 0; j < Member_count; j++)
				{
					for (int k = 0; k < Member_count; k++)
					{
						memberList[k] = account[k]->getAccountMember();
					}

					if (memberList[i] == memberList[j])
					{
						cout << "���� ������ ����" << endl;
						cout << "�ֹε�Ϲ�ȣ: " << endl;
						cin >> AccCheck_SSN;
						cout << endl;

						if (account[i]->Check_SSN(AccCheck_SSN))
						{
							cout << "��ݾ�: " << endl;
							cin >> depositInput;
							cout << endl;
							account[i]->Withdrawal(depositInput);
							return;

						}
					}
				}
			}
			else
			{
				cout << "��ȿ���� ���� ID �Դϴ�." << endl;
				return;
			}
		}

	}

	void AllPrint() const
	{
		for (int i = 0; i < Member_count; i++)
		{
			cout << endl;
			account[i]->AllPrint();
		}
	}
};

//AccountManager ��ü ����
AccountManager accountManager;

int main()
{
	int select;
	while (1) {
		cout << "-----Menu-----\n1. ���°���\n2. �Ա�\n3. ���\n4. �������� ��ü ���\n5. ���α׷� ����\n����: ";
		cin >> select;

		switch (select) {
		case 1:
			accountManager.AccMake();
			break;
		case 2:
			accountManager.Deposit();
			break;
		case 3:
			accountManager.Withdrawal();
			break;
		case 4:
			accountManager.AllPrint();
			break;
		case 5:
			for (int i = 0; i < accountManager.Member_count; i++)
			{
				delete accountManager.account[i];
			}
		default:
			cout << "�߸��� �޴� ��ȣ�Դϴ�." << endl;
			break;
		}
	}
}