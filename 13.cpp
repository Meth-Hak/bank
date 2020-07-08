#include <iostream>
#include <stdio.h>
using namespace std;

#define MAX_LEN 20
#define MAX_MEMBER 100

//과거의 나의 행적
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
	//생성자 아이디, 금액, 주민등록번호, 이름
	Account(int accID, int balance, int Resident_registration_number, char* cusName)
	{
		this->accID = accID;
		this->balance = balance;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	//소멸자
	~Account() {
		cout << "객체가 삭제됩니다." << endl;

		delete[] cusName;
	}

	//복사 생성자
	Account(const Account& copy_user)
		: accID(copy_user.accID), Resident_registration_number(copy_user.Resident_registration_number)
	{
		cout << "복사 생성자 호출" << endl;
		this->balance = copy_user.balance;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, copy_user.cusName);
	}

	char* getAccountMember() const {
		return cusName;
	}

	//입금
	void Deposit(int balance) {
		this->balance += balance;
	}

	//계좌 확인
	bool CheckAccount(int accountId) const {
		return this->accID == accountId;
	}

	//출금
	bool Withdraw(int balance) {
		if (this->balance < balance) {
			return false;
		}

		this->balance -= balance;
		return true;
	}

	//계좌 전체 출력
	void PrintAccount() const {
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << endl;
	}

	//주민등록번호 확인
	bool Check_SSN(int Resident_registration_number) {
		return this->Resident_registration_number == Resident_registration_number;
	}

};

class AccountManager {

public:
	//객체 생성
	Account* account[MAX_MEMBER];
	int Member_Number = 0; //멤버 개수 카운트

	//계좌 생성 함수
	void creatAccount() {
		int accountId;
		int accountBalance;
		char accountName[20];
		int Resident_registration_number;

		cout << "[계좌개설]" << endl;
		cout << "계좌ID:  ";
		cin >> accountId;
		cout << "이  름: ";
		cin >> accountName;
		cout << "입금액: ";
		cin >> accountBalance;
		//최소 입금 금액 확인
		while (1) {
			if (accountBalance < 10) {
				cout << "최소 입금 금액은 10원입니다." << endl;
				cout << "입금액: ";
				cin >> accountBalance;
			}
			else {
				break;
			}
		}

		cout << "주민등록번호: ";
		cin >> Resident_registration_number;

		account[Member_Number] = new Account(accountId, accountBalance,
			Resident_registration_number, accountName);

		Member_Number++;

		cout << endl;
	}

	//입금 함수
	void deposit() const {
		int depositInput = 0; //입금 금액
		int checkAccId; //아이디 입력 받는 변수
		char* memberList[MAX_MEMBER]; //멤버들의 이름 목록을 받아오는 배열
		int AccCheck_SSN = 0; //주민등록번호를 입력 받는 변수

		cout << "[입금]" << endl;
		cout << "ID: ";
		cin >> checkAccId;
		for (int i = 0; i < Member_Number; i++) {
			if (account[i]->CheckAccount(checkAccId)) {
				for (int j = 0; j < Member_Number; j++) {
					for (int k = 0; k < Member_Number; k++) {
						memberList[k] = account[k]->getAccountMember();
					}
					//이름 같은 사람이 있는지 검사
					//있다면 주민등록번호 받기
					if (memberList[i] == memberList[j]) {
						cout << "이름이 같은 사람이 있음" << endl;
						cout << "주민등록번호 입력: ";
						cin >> AccCheck_SSN;
						cout << endl;

						//해당 주민등록번호를 가진 사람이 있으면 입금
						if (account[i]->Check_SSN(AccCheck_SSN)) {
							cout << "입금액: ";
							cin >> depositInput;
							cout << endl;
							account[i]->Deposit(depositInput);
							return;
						}
					}
				}
			}
			//없으면 return
			else {
				cout << "유효하지 않은 ID 입니다." << endl;
				return;
			}

		}
	}

	//출금 함수
	void withdraw() const {
		int withdrawAmount = 0; //출금 금액
		int checkAccId; //아이디 입력 받는 변수
		char* memberList[MAX_MEMBER]; //멤버들의 이름 목록을 받아오는 배열
		int AccCheck_SSN = 0; //주민등록번호를 입력 받는 변수

		cout << "[출금]" << endl;
		cout << "ID: ";
		cin >> checkAccId;
		for (int i = 0; i < Member_Number; i++) {
			if (account[i]->CheckAccount(checkAccId)) {
				for (int j = 0; j < Member_Number; j++) {
					for (int k = 0; k < Member_Number; k++) {
						memberList[k] = account[k]->getAccountMember();
					}
					//이름 같은 사람이 있는지 검사
					//있다면 주민등록번호 받기
					if (memberList[i] == memberList[j]) {
						cout << "이름이 같은 사람이 있음" << endl;
						cout << "주민등록번호 입력: ";
						cin >> AccCheck_SSN;
						cout << endl;
					}
					//해당 주민등록번호를 가진 사람이 있으면 출금
					if (account[i]->Check_SSN(AccCheck_SSN)) {
						cout << "얼마를 출금하시겠습니까?" << endl;
						cin >> withdrawAmount;
						cout << endl;
						account[i]->Withdraw(withdrawAmount);
						return;
					}
				}
			}
			//없으면 return
			else {
				cout << "유효하지 않은 ID 입니다." << endl;
				return;
			}
		}

	}

	//출력 함수
	void Printaccount() const {
		for (int i = 0; i < Member_Number; i++) {
			cout << endl;
			account[i]->PrintAccount();
		}
	}
};

//AccountManager 객체 생성
AccountManager accountManager;

//메인 함수
int main() {
	while (1) {
		int input = 0;

		cout << "-----Menu-----\n1. 계좌개설\n2. 입금\n3. 출금\n4. 계좌정보 전체 출력\n5. 프로그램 종료\n선택: ";
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
			cout << "프로그램 종료" << endl;
			for (int i = 0; i < accountManager.Member_Number; i++) {
				delete accountManager.account[i];
			}
			return 0;
		default:
			printf("6부터는 적으면 안돼! 바로 종료!!");
		}
	}
}