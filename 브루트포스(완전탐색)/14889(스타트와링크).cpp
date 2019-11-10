#include <iostream>
#include <algorithm>

#define endl "\n"
using namespace std;

int N;
int map[21][21];
int visit[21];
int team0[11];
int team1[11];
int pick;
int min_value = 987654321;

// 백트레킹 조합
void dfs(int cnt) {
	if (pick == N / 2) { // 팀 절반 선택
		int t0 = 1;
		int t1 = 1;
		// 팀 구분
		for (int i = 1; i <= N; i++) {
			if (visit[i] == 0) {
				team0[t0++] = i;
			}
			else if (visit[i] == 1) {
				team1[t1++] = i;
			}
		}
		// 각 팀 능력치
		int s0 = 0;
		int s1 = 0;
		for (int i = 1; i <= N / 2; i++) {
			for (int j = 1; j <= N / 2; j++) {
				s0 += map[team0[i]][team0[j]];
				s1 += map[team1[i]][team1[j]];
			}
		}
		// 차이를 최소로
		int differ = abs(s0 - s1);
		min_value = min(min_value, differ);

		return;
	}

	for (int i = cnt; i <= N; i++) {
		if (pick < N / 2) {
			pick++;
			visit[i] = 1;
			dfs(i + 1);
			pick--;
			visit[i] = 0;
		}
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	// 조합
	dfs(1);

	cout << min_value << endl;
	return 0;
}

