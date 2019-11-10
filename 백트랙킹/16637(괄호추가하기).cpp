#include<iostream>
#include<string>
#include<algorithm>
#include<climits>


int min_value = INT_MIN;

#define endl "\n"
#define MAX 10

using namespace std;

int N, Oper_Num;
int Answer = -987654321;
int Num[MAX], Oper[MAX];

int Calculate(int N1, int N2, char B){
	if (B == '+') return N1 + N2;
	else if (B == '-') return N1 - N2;
	else if (B == '*') return N1 * N2;
}

void DFS(int Idx, int Result)
{
	if (Idx >= Oper_Num){
		Answer = max(Answer, Result);
		return;
	}

	int Cur_Result = Calculate(Result, Num[Idx + 1], Oper[Idx]);
	DFS(Idx + 1, Cur_Result);

	if (Idx + 1 < Oper_Num) {
		int After_Result = Calculate(Num[Idx + 1], Num[Idx + 2], Oper[Idx + 1]);
		int Cur_Result = Calculate(Result, After_Result, Oper[Idx]);
		DFS(Idx + 2, Cur_Result);
	}
}

void Solution(){
	if (N == 1){
		cout << Num[0] << endl;
		return;
	}
	else if (N == 3){
		cout << Calculate(Num[0], Num[1], Oper[0]) << endl;
		return;
	}

	DFS(0, Num[0]);
	cout << Answer << endl;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	int Idx = 0;
	int Idx2 = 0;

	string Inp;
	cin >> Inp;
	for (int i = 0; i < Inp.length(); i++)
	{
		if (i % 2 == 0) Num[Idx++] = Inp[i] - '0'; // 숫자를 담음
		else Oper[Idx2++] = Inp[i]; // 연산자를 담음
	}
	Oper_Num = N / 2; // 연산자 개수

	Solution();

	return 0;
}
