#include<iostream>
#include<cstring>
#define NAME_LEN 20
#define MAX_ACCOUNT 200
using namespace std;

enum { ACCMAKE = 1, DEPOSIT, WITHDRAW, ALLPRINT, EXIT };

class Account
{
public:
	const int accID; //계좌 번호
	int balance; //잔액
	char cusName[NAME_LEN]; //고객이름

};

Account* arr = new Account[MAX_ACCOUNT];
int Count = 0;

void AccMake(); //계좌 만들기
void Deposit(); //입금
void Withdrawal(); //출금
void AllPrint(); // 전체 계좌정보 출력

void AccMake() //계좌 계설
{
	if (Count >= MAX_ACCOUNT) {
		cout << "계설 할 수 있는 갯수가 넘었습니다." << endl;
		return;
	}

BACK:
	cout << "[계좌 신설]" << endl;
	cout << "ID 입력: "; cin >> arr[Count].accID;
	for (int i = 0; i < Count; i++) {
		if (arr[Count].accID <= 0 || arr[i].accID == arr[Count].accID)
		{
			cout << "이미 계설이 되었거나 만들 수 없는 계좌 번호 입니다." << endl;
			cout << ' ' << endl;
			cout << "다시 입력 해주세요." << endl;
			goto BACK; //다시 만들기
		}
	}

	cout << "계좌 명: "; cin >> arr[Count].cusName[NAME_LEN];
	cout << "계좌 계설 초기 입금액을 넣어 주세요.(10원 이상)" << endl;
BACK1:
	cout << "금액: "; cin >> arr[Count].balance;
	if (arr[Count].balance < 10)
	{
		cout << "초소 금액은 10원 이상 입니다." << endl;
		cout << ' ' << endl;
		cout << "다시 초기 금액 넣어 주세요." << endl;
		goto BACK1;
	}


	Count++;
	cout << "계좌 계설에 성공 하였습니다." << endl;
	return;
}

void Deposit() //입금
{

	if (Count == 0)
	{
		cout << "계설된 계좌가 없습니다." << endl;
		return;
	}

	int ID = 0;
	int money = 0;


	cout << "계좌 번호 입력: "; cin >> ID;
	for (int i = 0; i < Count; i++)
	{
		if (arr[i].accID == ID)
		{
			cout << "입금액: "; cin >> money;
			if (money <= 0)
			{
				cout << "0원은 입금 할 수 없습니다." << endl;
			}
			arr[i].balance += money;
			cout << money << "입금되었고 남은 금액은" << arr[i].balance << endl;
		}
		else
		{
			cout << "없는 계좌 번호 입니다." << endl;
		}
	}

}

void Withdrawal() //출금
{

	if (Count == 0)
	{
		cout << "계설된 계좌가 없습니다." << endl;
		return;
	}

	int ID = 0;
	int money = 0;

	cout << "계좌 번호 입력: "; cin >> ID;
	for (int i = 0; i < Count; i++)
	{
		if (arr[i].accID == ID)
		{
			cout << "출금액: "; cin >> money;
			if (money <= 0)
			{
				cout << "0원은 출금 할 수 없습니다." << endl;
			}
			arr[i].balance -= money;
			cout << money << "출금되었고 남은 금액은" << arr[i].balance << endl;
			return;
		}
		cout << "없는 계좌 번호 입니다." << endl;
	}

}

void AllPrint()//계좌 전체 보기
{

	if (Count == 0)
	{
		cout << "계설된 계좌가 없습니다." << endl;
		return;
	}

	for (int i = 0; i < Count; i++)
	{
		cout << "[" << i << "]" << "번째" << endl;
		cout << "계좌 명: " << arr[i].cusName[NAME_LEN] << endl;
		cout << "계좌 변호: " << arr[i].accID << endl;
		cout << "계좌 금액: " << arr[i].balance << endl;
	}
	return;
}

void showMenu() //선택 창
{
	cout << "\n";
	cout << "**사용자**" << endl;
	cout << "1. 계좌 개설" << endl;
	cout << "2. 입금" << endl;
	cout << "3. 출금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

int main_1(void)
{
	int select;
	while (1) {
		showMenu();
		cout << "선택 : ";
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
			cout << "잘못된 메뉴 번호입니다." << endl;
			break;
		}
	}
}