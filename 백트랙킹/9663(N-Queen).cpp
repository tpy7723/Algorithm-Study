#include <iostream>

using namespace std;

int N;
int answer;
int board[15];

// 놓아도 되는지 체크함
bool check(int row) {
	for (int i = 0; i < row; i++) { // i는 0행부터 마지막 여왕이 위치한 곳 바로 윗 행까지
									
		if (board[row] == board[i] || abs(row - i) == abs(board[row] - board[i])) { //같은 열에 있거나 || 대각선에 위치한다면
			return false;
		}
	}
	return true;
}

void dfs(int row) {
	if (row == N) { // N개를 모두 놓는 경우
		answer++;
		return;
	}

	//첫 번째 행에 놓이는 돌의 위치를 i가 정함
	for (int i = 0; i < N; i++) { // i가 열의 위치
		board[row] = i; // row 행 i열에 퀸을 놓았다.
		if (check(row)) //check한 게 통과하면 (가지치기)
			dfs(row + 1);
		board[row] = 0; //통과한 거 다 끝내고나면 되돌림
	}
}

int main(void) {
	cin >> N;

	dfs(0);

	cout << answer << endl;
}