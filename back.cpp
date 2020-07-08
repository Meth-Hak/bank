#include <iostream>
#include<cstring>

#define MAX_MEMBER 100
#define MAX_LEN 20

enum { ACCMAKE = 1, DEPOSIT, WITHDRAW, ALLPRINT, EXIT };

using namespace std;

//입금, 출금, 출력 ,계좌 확인
class Account
{

private://class 내에서만 사용 가능
	int accID; //계좌 번호
	int balance; //잔액
	int Resident_registration_number;
	char* cusName; //고객이름

public://class 외부에서 사용 가능

	//기본 생성자
	Account() {}

	//생성자
	Account(
		int accID,
		int balance,
		int Resident_registration_number,
		char* cusName 
			)

	{
		//private에서 선언한 변수를 사용하기 위해 this를 사용
		this->accID = accID;
		this->balance = balance;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		//string copy (줄임표현) 문자열 복사
		//strcpy_s(붙여넣을 변수, 문자열 치수, 복사할 변수)
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	~Account()
	{
		cout << "객체가 삭제됩니다" << endl;

		delete[] cusName;
	}

	//복사 생성자
	Account(const Account& CpyUser)
		//복사
		: accID(CpyUser.accID), Resident_registration_number(CpyUser.Resident_registration_number)
	{
		cout << "복사 생성자" << endl;
		//private에서 선언한 변수를 사용하기 위해 this를 사용
		this->balance = CpyUser.balance;
		this->cusName = new char[MAX_LEN];
		//string copy (줄임표현) 문자열 복사
		//strcpy_s(붙여넣을 변수, 문자열 치수, 복사할 변수)
		strcpy_s(this->cusName, MAX_LEN, CpyUser.cusName);
	}

	char* getAccountMember() const
	{
		return cusName;
	}

	//입금
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

	//계좌 확인
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
		cout << "계좌ID: " << accID << endl;
		cout << "이름: " << cusName << endl;
		cout << "잔액: " << balance << endl;
		cout << endl;
	}
};

class AccountManager
{
public:
	//객체 생성
	Account* account[MAX_MEMBER];
	int Member_count = 0;

	//계좌 계설
	void AccMake()
	{
		int accountID;
		int accountBalance;
		char accountName[20];
		int Resident_registration_number;

		cout << "[계좌 계설]" << endl;
		cout << "계좌ID: " << endl;
		cin >> accountID;
		cout << "이름: " << endl;
		cin >> accountName;
		cout << "입금액: " << endl;
		cin >> accountBalance;

		//최소 입금 금액 확인
		while (1)
		{
			if (accountBalance < 10)
			{
				cout << "초소 금액은 10원 이상 입니다." << endl;
				cout << endl;
				cout << "다시 초기 금액 넣어 주세요." << endl;
				cout << "입금액: " << endl;
				cin >> accountBalance;
			}
			else
			{
				break;
			}
		}

		cout << "주민등록번호: " << endl;
		cin >> Resident_registration_number;
		
		//account 생성자 생성 -> Account class의 account배열에 Member_count번째 배열 입력
		account[Member_count] = new Account(accountID, accountBalance, Resident_registration_number, accountName);

		Member_count++;
		cout << endl;
	}

	//입금
	void Deposit() const
	{
		int depositInput = 0; //입력 받을 금액
		int CheckAccID; //입력 받을 아이디
		char* memberList[MAX_MEMBER]; //회원이름 리스트 목록 받아 올 변수
		int AccCheck_SSN = 0; //입력 받을 주민등록번호

		cout << "[입금]" << endl;
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
						cout << "동명 이인이 있음" << endl;
						cout << "주민등록번호: " << endl;
						cin >> AccCheck_SSN;
						cout << endl;

						if (account[i]->Check_SSN(AccCheck_SSN))
						{
							cout << "입금액: " << endl;
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
				cout << "유효하지 않은 ID 입니다." << endl;
				return;
			}
		}

	}

	//출금
	void Withdrawal() const
	{
		int depositInput = 0; //입력 받을 금액
		int CheckAccID; //입력 받을 아이디
		char* memberList[MAX_MEMBER]; //회원이름 리스트 목록 받아 올 변수
		int AccCheck_SSN = 0; //입력 받을 주민등록번호

		cout << "[입금]" << endl;
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
						cout << "동명 이인이 있음" << endl;
						cout << "주민등록번호: " << endl;
						cin >> AccCheck_SSN;
						cout << endl;

						if (account[i]->Check_SSN(AccCheck_SSN))
						{
							cout << "출금액: " << endl;
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
				cout << "유효하지 않은 ID 입니다." << endl;
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

//AccountManager 객체 생성
AccountManager accountManager;

int main()
{
	int select;
	while (1) {
		cout << "-----Menu-----\n1. 계좌개설\n2. 입금\n3. 출금\n4. 계좌정보 전체 출력\n5. 프로그램 종료\n선택: ";
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
			cout << "잘못된 메뉴 번호입니다." << endl;
			break;
		}
	}
}