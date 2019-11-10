#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int map[9][9];
int Cmap[9][9];
int visit[9][9];
int movedir[4][2] = { {1,0},{-1,0},{0,-1},{0,1} }; // 상하 좌우
int x, y;
int maxzero;

bool isindoor(int a, int b) {
	return (0 <= a && a < y) && (0 <= b && b < x);
}

// 안전영역의 개수를 세는 함수
int countzero() {
	int cnt = 0;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (map[i][j] == 0) {
				cnt++;
			}
		}
	}
	return cnt;
}

void dfs(int a, int b) {
	map[a][b] = 2; // 바이러스 확산

	for (int i = 0; i < 4; i++) {
		int next_a = a + movedir[i][0];
		int next_b = b + movedir[i][1];

		// 방문하지 않았고 길이면
		if (visit[next_a][next_b]) continue;
		if (!isindoor(next_a, next_b)) continue;
		if (map[next_a][next_b] == 0) {
			visit[next_a][next_b] = true;
			dfs(next_a, next_b);
		}
	}
}

void dfs_wall(int wallnum) {
	if (wallnum == 3) { // 벽을 세개 세운 후
		memset(visit, 0, sizeof(visit));
		memcpy(map, Cmap, sizeof(Cmap));

		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (map[i][j] == 2) {
					dfs(i, j); // 바이러스 확산
				}
			}
		}
		maxzero = max(maxzero, countzero()); // 안전 영역 최대값 구하기
		return;
	}

	// 모든경우의수 다 따짐
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (Cmap[i][j] == 0) { // 길이면
				Cmap[i][j] = 1; // 벽세우기
				dfs_wall(wallnum + 1); // 재귀
				Cmap[i][j] = 0; // 벽 다시 없애기
			}
		}
	}
}

int main(void) {

	cin >> y >> x;

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			cin >> map[i][j];
		}
	}

	memcpy(Cmap, map, sizeof(map));

	dfs_wall(0);
	cout << maxzero;

	return 0;
}