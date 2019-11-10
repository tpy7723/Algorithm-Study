#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

int map[101][101];
int visit[101][101];
int movedir[4][2] = { {1,0},{-1,0},{0,-1},{0,1} }; // 상하 좌우
int x, y;

bool isindoor(int a, int b) {
	return (0 <= a && a < y) && (0 <= b && b < x);
}

void bfs() {
	queue<pair<int, int>> q;

	int cur_x = 0;
	int cur_y = 0;

	q.push(make_pair(cur_y, cur_x));

	visit[cur_y][cur_x] = 1;

	while (!q.empty()) {
		cur_y = q.front().first;
		cur_x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_y = cur_y + movedir[i][0];
			int next_x = cur_x + movedir[i][1];

			if (isindoor(next_y, next_x) && map[next_y][next_x] == 1 && visit[next_y][next_x] == 0) {
				visit[next_y][next_x] = visit[cur_y][cur_x] + 1;
				q.push(make_pair(next_y, next_x));
			}

		}
	}
}

int main(void) {

	cin >> y >> x;

	char input;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			scanf("%1d", &map[i][j]); // 숫자 한개만 받기
		}
	}

	bfs();

	cout << visit[y - 1][x - 1] << endl;

	return 0;
}