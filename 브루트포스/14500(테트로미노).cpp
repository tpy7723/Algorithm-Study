#include <iostream>
#include <algorithm>

#define endl "\n"

using namespace std;

int N, M;
int max_value = -987654321;
int map[501][501];
int visit[501][501];
int sum;
int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
int dir2[4][3][2] = {
	{ {0,1},{0,2},{-1,1} } , // 위
	{ {0,1},{0,2},{1,1} } , // 아래
	{ {1,0},{2,0},{1,1} } , // 오른쪽
	{ {1,0},{2,0},{1,-1} }  // 왼쪽
};

bool isindoor(int r, int c) {
	return (0 <= r && r < N) && (0 <= c && c < M);
}

void dfs(int r, int c, int n) {
	if (n == 4) {
		max_value = max(max_value, sum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nextr = r + dir[i][0];
		int nextc = c + dir[i][1];

		if (!isindoor(nextr, nextc)) continue;
		if (visit[nextr][nextc]) continue;

		visit[nextr][nextc] = 1;
		sum += map[nextr][nextc];

		dfs(nextr, nextc, n + 1);

		visit[nextr][nextc] = 0;
		sum -= map[nextr][nextc];
	}
}

void middlefinger(int r, int c) {
	for (int i = 0; i < 4; i++) { // 도형 회전
		int s = map[r][c];
		for (int j = 0; j < 3; j++) {
			if (!isindoor(r + dir2[i][j][0], c + dir2[i][j][1])) break; // 리턴 ㄴㄴ
			s += map[r + dir2[i][j][0]][c + dir2[i][j][1]];
		}
		max_value = max(max_value, s);
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visit[i][j] = 1;
			sum += map[i][j];

			dfs(i, j, 1);

			sum -= map[i][j];
			visit[i][j] = 0;
			///////////////////
			middlefinger(i, j);
		}
	}

	cout << max_value << endl;
	return 0;
}