#include <iostream>
#include <queue>

#define endl "\n"

using namespace std;

int d; // 012 우 대각 하
int dir[3][2] = { {0,1},{1,1}, {1,0} }; // 우 대각 하
int map[17][17];
int result;
int N;

struct node {
	int r, c, d;
};

bool isindoor(int r, int c) {
	return (1<=r && r<=N) && (1 <= c && c <= N);
}

void dfs(int cur_r, int cur_c, int cur_d) {
	if (cur_r == N && cur_c == N) {
		result++;
		return;
	}

	if (cur_d == 0) { // 우
		for (int i = 0; i <= 1; i++) {
			int next_r = cur_r + dir[i][0];
			int next_c = cur_c + dir[i][1];
			int next_d = i;

			if (!isindoor(next_r, next_c)) continue;
			if (next_d == 0) {
				if (map[next_r][next_c] == 0) {
					dfs(next_r,next_c,next_d);
				}
			}
			if (next_d == 1) {
				if (map[next_r][next_c] == 0 && map[next_r-1][next_c] == 0 && map[next_r][next_c-1] == 0) {
					dfs(next_r, next_c, next_d);
				}
			}
		}
	}
	else if (cur_d == 1) { //대각
		for (int i = 0; i <= 2; i++) {
			int next_r = cur_r + dir[i][0];
			int next_c = cur_c + dir[i][1];
			int next_d = i;

			if (!isindoor(next_r, next_c)) continue;
			if (next_d == 0 || next_d == 2) {
				if (map[next_r][next_c] == 0) {
					dfs(next_r, next_c, next_d);
				}
			}
			if (next_d == 1) {
				if (map[next_r][next_c] == 0 && map[next_r - 1][next_c] == 0 && map[next_r][next_c - 1] == 0) {
					dfs(next_r, next_c, next_d);
				}
			}
		}
	}
	else if (cur_d == 2) { // 하
		for (int i = 1; i <= 2; i++) {
			int next_r = cur_r + dir[i][0];
			int next_c = cur_c + dir[i][1];
			int next_d = i;

			if (!isindoor(next_r, next_c)) continue;
			if (next_d == 2) {
				if (map[next_r][next_c] == 0) {
					dfs(next_r, next_c, next_d);
				}
			}
			if (next_d == 1) {
				if (map[next_r][next_c] == 0 && map[next_r - 1][next_c] == 0 && map[next_r][next_c - 1] == 0) {
					dfs(next_r, next_c, next_d);
				}
			}
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

	dfs(1,2,d);

	cout << result << endl;
	return 0;
}