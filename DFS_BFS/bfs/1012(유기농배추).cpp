#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int map[51][51];
int x, y, x_, y_, n;
int movedir[4][2] = { {1,0},{-1,0},{0,-1},{0,1} }; // 상하 좌우

bool isindoor(int a, int b) {
	return (0 <= a && a < y) && (0 <= b && b < x);
}

void dfs(int a, int b) {
	map[a][b] = 2; // 이미 확인했다는 의미

	for (int i = 0; i < 4; i++) {
		int dy = a + movedir[i][0];
		int dx = b + movedir[i][1];

		if (isindoor(dy, dx) && map[dy][dx] == 1) {
			dfs(dy, dx);
		}
	}
}

int Solution(int y, int x) {
	int cnt = 0;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (map[i][j] == 1) {
				cnt++;
				dfs(i, j);
			}
		}
	}

	return cnt;
}

int main(void) {
	int testcase;
	cin >> testcase;

	for (int t = 0; t < testcase; t++) {
		cin >> x >> y >> n;

		memset(map, 0, sizeof(map));

		for (int i = 0; i < n; i++) {
			cin >> x_ >> y_;
			map[y_][x_] = 1;
		}

		cout << Solution(y, x) << endl;
	}


	return 0;
}