#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int map[1001][1001], visit[1001][1001];
int movedir[4][2] = { {1,0},{-1,0},{0,-1},{0,1} }; // 상하 좌우
int x, y;

bool isindoor(int a, int b) {
	return (0 <= a && a < y) && (0 <= b && b < x);
}

int main(void) {
	cin >> x >> y;

	queue<pair<int, int>> q;

	memset(visit, -1, sizeof(visit));
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			scanf("%2d", &map[i][j]); // 음수도 받을 때 사용 00 글자수를 맞춰줌
			if (map[i][j] == 1) {
				q.push({ i,j });
				visit[i][j] = 0;
			}
		}
	}

	while (!q.empty()) {
		int cur_a = q.front().first;
		int cur_b = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_a = cur_a + movedir[i][0];
			int next_b = cur_b + movedir[i][1];

			// 방문하지 않았고 익지 않은 토마토
			if (isindoor(next_a, next_b)
				&& visit[next_a][next_b] == -1
				&& map[next_a][next_b] == 0) {
				visit[next_a][next_b] = visit[cur_a][cur_b] + 1;
				q.push({ next_a ,next_b });
			}
		}
	}

	int result = 0;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (map[i][j] == 0 && visit[i][j] == -1) { //익지않고 방문하지 못한 곳이 있을 때
				cout << -1 << endl;
				return 0;
			}

			result = max(result, visit[i][j]); //최대값 찾기
		}
	}

	cout << result << endl;
	return 0;
}