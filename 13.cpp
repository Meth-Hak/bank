#include <iostream>
#include <stdio.h>
using namespace std;

#define MAX_LEN 20
#define MAX_MEMBER 100

//������ ���� ����
//typedef struct {
//	int accId;
//	int balance;
//	char cusName[20];
//}Account;

class Account {

private:
	int accID;
	int balance;
	int Resident_registration_number;
	char* cusName;

public:
	//������ ���̵�, �ݾ�, �ֹε�Ϲ�ȣ, �̸�
	Account(int accID, int balance, int Resident_registration_number, char* cusName)
	{
		this->accID = accID;
		this->balance = balance;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	//�Ҹ���
	~Account() {
		cout << "��ü�� �����˴ϴ�." << endl;

		delete[] cusName;
	}

	//���� ������
	Account(const Account& copy_user)
		: accID(copy_user.accID), Resident_registration_number(copy_user.Resident_registration_number)
	{
		cout << "���� ������ ȣ��" << endl;
		this->balance = copy_user.balance;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, copy_user.cusName);
	}

	char* getAccountMember() const {
		return cusName;
	}

	//�Ա�
	void Deposit(int balance) {
		this->balance += balance;
	}

	//���� Ȯ��
	bool CheckAccount(int accountId) const {
		return this->accID == accountId;
	}

	//���
	bool Withdraw(int balance) {
		if (this->balance < balance) {
			return false;
		}

		this->balance -= balance;
		return true;
	}

	//���� ��ü ���
	void PrintAccount() const {
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << endl;
	}

	//�ֹε�Ϲ�ȣ Ȯ��
	bool Check_SSN(int Resident_registration_number) {
		return this->Resident_registration_number == Resident_registration_number;
	}

};

class AccountManager {

public:
	//��ü ����
	Account* account[MAX_MEMBER];
	int Member_Number = 0; //��� ���� ī��Ʈ

	//���� ���� �Լ�
	void creatAccount() {
		int accountId;
		int accountBalance;
		char accountName[20];
		int Resident_registration_number;

		cout << "[���°���]" << endl;
		cout << "����ID:  ";
		cin >> accountId;
		cout << "��  ��: ";
		cin >> accountName;
		cout << "�Աݾ�: ";
		cin >> accountBalance;
		//�ּ� �Ա� �ݾ� Ȯ��
		while (1) {
			if (accountBalance < 10) {
				cout << "�ּ� �Ա� �ݾ��� 10���Դϴ�." << endl;
				cout << "�Աݾ�: ";
				cin >> accountBalance;
			}
			else {
				break;
			}
		}

		cout << "�ֹε�Ϲ�ȣ: ";
		cin >> Resident_registration_number;

		account[Member_Number] = new Account(accountId, accountBalance,
			Resident_registration_number, accountName);

		Member_Number++;

		cout << endl;
	}

	//�Ա� �Լ�
	void deposit() const {
		int depositInput = 0; //�Ա� �ݾ�
		int checkAccId; //���̵� �Է� �޴� ����
		char* memberList[MAX_MEMBER]; //������� �̸� ����� �޾ƿ��� �迭
		int AccCheck_SSN = 0; //�ֹε�Ϲ�ȣ�� �Է� �޴� ����

		cout << "[�Ա�]" << endl;
		cout << "ID: ";
		cin >> checkAccId;
		for (int i = 0; i < Member_Number; i++) {
			if (account[i]->CheckAccount(checkAccId)) {
				for (int j = 0; j < Member_Number; j++) {
					for (int k = 0; k < Member_Number; k++) {
						memberList[k] = account[k]->getAccountMember();
					}
					//�̸� ���� ����� �ִ��� �˻�
					//�ִٸ� �ֹε�Ϲ�ȣ �ޱ�
					if (memberList[i] == memberList[j]) {
						cout << "�̸��� ���� ����� ����" << endl;
						cout << "�ֹε�Ϲ�ȣ �Է�: ";
						cin >> AccCheck_SSN;
						cout << endl;

						//�ش� �ֹε�Ϲ�ȣ�� ���� ����� ������ �Ա�
						if (account[i]->Check_SSN(AccCheck_SSN)) {
							cout << "�Աݾ�: ";
							cin >> depositInput;
							cout << endl;
							account[i]->Deposit(depositInput);
							return;
						}
					}
				}
			}
			//������ return
			else {
				cout << "��ȿ���� ���� ID �Դϴ�." << endl;
				return;
			}

		}
	}

	//��� �Լ�
	void withdraw() const {
		int withdrawAmount = 0; //��� �ݾ�
		int checkAccId; //���̵� �Է� �޴� ����
		char* memberList[MAX_MEMBER]; //������� �̸� ����� �޾ƿ��� �迭
		int AccCheck_SSN = 0; //�ֹε�Ϲ�ȣ�� �Է� �޴� ����

		cout << "[���]" << endl;
		cout << "ID: ";
		cin >> checkAccId;
		for (int i = 0; i < Member_Number; i++) {
			if (account[i]->CheckAccount(checkAccId)) {
				for (int j = 0; j < Member_Number; j++) {
					for (int k = 0; k < Member_Number; k++) {
						memberList[k] = account[k]->getAccountMember();
					}
					//�̸� ���� ����� �ִ��� �˻�
					//�ִٸ� �ֹε�Ϲ�ȣ �ޱ�
					if (memberList[i] == memberList[j]) {
						cout << "�̸��� ���� ����� ����" << endl;
						cout << "�ֹε�Ϲ�ȣ �Է�: ";
						cin >> AccCheck_SSN;
						cout << endl;
					}
					//�ش� �ֹε�Ϲ�ȣ�� ���� ����� ������ ���
					if (account[i]->Check_SSN(AccCheck_SSN)) {
						cout << "�󸶸� ����Ͻðڽ��ϱ�?" << endl;
						cin >> withdrawAmount;
						cout << endl;
						account[i]->Withdraw(withdrawAmount);
						return;
					}
				}
			}
			//������ return
			else {
				cout << "��ȿ���� ���� ID �Դϴ�." << endl;
				return;
			}
		}

	}

	//��� �Լ�
	void Printaccount() const {
		for (int i = 0; i < Member_Number; i++) {
			cout << endl;
			account[i]->PrintAccount();
		}
	}
};

//AccountManager ��ü ����
AccountManager accountManager;

//���� �Լ�
int main() {
	while (1) {
		int input = 0;

		cout << "-----Menu-----\n1. ���°���\n2. �Ա�\n3. ���\n4. �������� ��ü ���\n5. ���α׷� ����\n����: ";
		cin >> input;

		switch (input) {
		case 1:
			accountManager.creatAccount();
			break;
		case 2:
			accountManager.deposit();
			break;
		case 3:
			accountManager.withdraw();
			break;
		case 4:
			accountManager.Printaccount();
			break;
		case 5:
			cout << "���α׷� ����" << endl;
			for (int i = 0; i < accountManager.Member_Number; i++) {
				delete accountManager.account[i];
			}
			return 0;
		default:
			printf("6���ʹ� ������ �ȵ�! �ٷ� ����!!");
		}
	}
}