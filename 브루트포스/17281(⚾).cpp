#include <iostream>
#include <algorithm>

using namespace std;

int n, res, out;
int player[50][9];
bool visited[9];
int seq[9];

void dfs(int cnt) {
	if (cnt == 3) { // 네번째 선수는 고정이므로
		dfs(cnt + 1);
		return;
	}

	if (cnt == 9) {
		int score = 0;  // 점수
		int index = 0;  // 칠 순서

		for (int i = 0; i < n; i++) { // 이닝
			int lu[3] = { 0, }; // 루 초기화

			while (1) {
				index %= 9;

				if (player[i][seq[index]] == 0) { // 아웃
					out += 1;

					if (out == 3) { // 쓰리 아웃
						index++;
						out = 0;
						break;
					}
				}

				else if (player[i][seq[index]] == 1) {
					if (lu[2] != 0) {
						lu[2] = 0, score += 1;
					}
					if (lu[1] != 0) {
						lu[2] = 1, lu[1] = 0;
					}
					if (lu[0] != 0) {
						lu[1] = 1, lu[0] = 0;
					}
					if (lu[0] == 0) {
						lu[0] = 1;
					}
				}

				else if (player[i][seq[index]] == 2) {
					if (lu[2] != 0) {
						lu[2] = 0, score += 1;
					}
					if (lu[1] != 0) {
						lu[1] = 0, score += 1;
					}
					if (lu[1] == 0) {
						lu[1] = 1;
					}
					if (lu[0] != 0) {
						lu[2] = 1, lu[0] = 0;
					}
				}

				else if (player[i][seq[index]] == 3) {
					if (lu[2] != 0) {
						lu[2] = 0, score += 1;
					}
					if (lu[2] == 0) {
						lu[2] = 1;
					}
					if (lu[1] != 0) {
						lu[1] = 0, score += 1;
					}
					if (lu[0] != 0) {
						lu[0] = 0, score += 1;
					}
				}

				else if (player[i][seq[index]] == 4) {
					if (lu[2] != 0) {
						lu[2] = 0, score += 1;
					}
					if (lu[1] != 0) {
						lu[1] = 0, score += 1;
					}
					if (lu[0] != 0) {
						lu[0] = 0, score += 1;
					}
					score += 1;
				}
				index++;
			}
		}

		res = max(res, score);

		return;
	}

	// 1부터 8로 이루어진 8자리 순열을 구함
	for (int i = 1; i < 9; i++) {
		if (!visited[i]) {// 이미 사용한 숫자
			seq[cnt] = i; // cnt 번째 자리에 입력받은 i 번쨰 사람이 와라

			visited[i] = true; // 해당 숫자 사용 했다.
			dfs(cnt + 1); // 한명 추가
			visited[i] = false; // 다시 되돌림 ( 순열 구현 )
		}
	}
}

int main(void) {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> player[i][j];
		}
	}

	dfs(0); // 순열 구하고 시뮬레이션하기

	cout << res << endl;

	return 0;
}