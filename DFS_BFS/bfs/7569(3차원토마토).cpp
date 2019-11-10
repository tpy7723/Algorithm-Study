#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

int map[101][101][101];
int movedir[6][3] = { {1,0,0},{-1,0,0}, {0,-1,0},{0,1,0},{0,0,1}, {0,0,-1} }; // 상하 좌우 위 아래 y x z
int x, y, z;

bool isindoor(int a, int b, int c) {
	return (0 <= a && a < y) && (0 <= b && b < x) && (0 <= c && c < z);
}

struct ijk {
	int z;
	int y;
	int x;
	int day; // 방문배열
};

int main(void) {
	cin >> x >> y >> z;

	queue<ijk> q;
	for (int z_ = 0; z_ < z; z_++) {
		for (int y_ = 0; y_ < y; y_++) {
			for (int x_ = 0; x_ < x; x_++) {
				scanf("%2d", &map[z_][y_][x_]); // 높이 행 열
				// 익은 토마토 Queue에 넣기
				if (map[z_][y_][x_] == 1) {
					q.push({ z_,y_,x_,0 });
				}
			}
		}
	}

	int maxDay = 0;

	while (!q.empty()) {
		int cur_x = q.front().x;
		int cur_y = q.front().y;
		int cur_z = q.front().z;
		int cur_day = q.front().day;

		q.pop();

		for (int i = 0; i < 6; i++) {
			int next_y = cur_y + movedir[i][0];
			int next_x = cur_x + movedir[i][1];
			int next_z = cur_z + movedir[i][2];

			// 익지 않은 토마토이면
			if (isindoor(next_y, next_x, next_z) && map[next_z][next_y][next_x] == 0) {
				map[next_z][next_y][next_x] = 1; // 익은 토마토가 됨
				q.push({ next_z, next_y, next_x, cur_day + 1 }); // 일수가 증가됨
			}
		}

		maxDay = max(maxDay, cur_day);
	}

	for (int z_ = 0; z_ < z; z_++) {
		for (int y_ = 0; y_ < y; y_++) {
			for (int x_ = 0; x_ < x; x_++) {
				if (map[z_][y_][x_] == 0) {
					cout << -1;
					return 0;
				}
			}
		}
	}

	cout << maxDay;
	return 0;
}