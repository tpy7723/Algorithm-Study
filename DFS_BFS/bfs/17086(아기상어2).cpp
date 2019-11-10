#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct node {
	int y, x;
};

int N, M; // 세로 가로
int map[51][51];
int visit[51][51];
queue<node> q;

int dir[8][2] = {
	{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1},{0,-1},{0,1}
};

bool isindoor(int y, int x) {
	return (0 <= y && y < N) && (0 <= x && x < M);
}

void bfs() {
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;

		q.pop();

		for (int i = 0; i < 8; i++) {
			int next_x = x + dir[i][1];
			int next_y = y + dir[i][0];

			if (isindoor(next_y, next_x) && visit[next_y][next_x] == 0
				&& map[next_y][next_x] == 0) {
				q.push({ next_y ,next_x });
				visit[next_y][next_x] = visit[y][x] + 1;
			}
		}
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				q.push({ i, j }); // 아기상어 위치
				visit[i][j] = 1; // 방문처리
			}
		}
	}

	bfs();

	int max_value = -100000000;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			max_value = max(max_value, visit[i][j]);
		}
	}

	cout << max_value - 1 << endl;
	return 0;
}