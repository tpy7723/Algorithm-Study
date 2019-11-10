#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

struct node {
	int y, x;
};

int N, L, R;
int map[51][51];
int group[51][51];
int key;

int dir[4][2] = {
	{-1,0}, {1,0}, {0,-1}, {0, 1} // 상하좌우
};

bool isindoor(int y, int x) {
	return (0 <= y && y < N) && (0 <= x && x < N);
}

void bfs(int y, int x, int key) {
	int sum = map[y][x];
	int cnt = 1;
	vector<node> save;
	queue<node> q;
	q.push({ y,x });
	group[y][x] = key;
	
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		save.push_back({ y ,x });
		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_x = x + dir[i][1];
			int next_y = y + dir[i][0];

			if (isindoor(next_y, next_x) && group[next_y][next_x] == 0) {
				int differ = abs(map[y][x] - map[next_y][next_x]);
				if (L <= differ && differ <= R) { // 차이가 L~R 사이면
					q.push({ next_y, next_x });
					group[next_y][next_x] = key; // 연결된것은 같은 key 로바꿈
					save.push_back({ next_y ,next_x }); // 바뀌어야할 좌표 저장
					sum += map[next_y][next_x]; // 값을 모두 더한것을 저장
					cnt++;
				}
			}
		}
	}

	int change = sum / cnt; // 바뀌어야할 값

	for (int i = 0; i < save.size(); i++) {
		map[save[i].y][save[i].x] = change; // 값을 넣어줌
	}
}

int main() {
	cin >> N >> L >> R;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	
	int ans = 0; // 인구 이동 
	while (1) {
		ans++;
		key = 1;
		memset(group, 0, sizeof(group));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (group[i][j] == 0) {
					bfs(i, j, key);
					key++;
				}
			}
		}
		if (key-1 == N * N) break; // 하나도 연결될것이 없는 경우
	}

	cout << ans - 1 << endl;ㅌ
	
	return 0;
}