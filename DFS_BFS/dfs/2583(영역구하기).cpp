#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
#include <algorithm>

using namespace std;

int map[100][100];
bool visit[100][100];
int m, n, k;

int cnt[101];
int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
vector<int> v;

bool indoor(int y, int x) {
	return (0 <= y && y < m) && (0 <= x && x < n);
}

void dfs(int y, int x, int count_num) {
	if (visit[y][x]) return;
	map[y][x] = count_num + 2; // ID
	visit[y][x] = true;

	for (int i = 0; i < 4; i++) {
		int next_x = x + dir[i][1];
		int next_y = y + dir[i][0];

		if (indoor(next_y, next_x) && map[next_y][next_x] == 0 && visit[next_y][next_x] == 0) {
			dfs(next_y, next_x, count_num);
			cnt[count_num]++;
		}
	}
}

void color(pair<int, int> p, pair<int, int> q) {
	// 사각형 범위
	for (int y = p.second; y < q.second; y++)
		for (int x = p.first; x < q.first; x++)
			map[y][x] = 1;
}

int main() {

	cin >> m >> n >> k; // 세로, 가로, 갯수

	pair<int, int> p, q;

	for (int i = 0; i < k; i++) {
		cin >> p.first >> p.second >> q.first >> q.second; // 왼쪽 아래, 오른쪽 위
		color(p, q); // 색칠하기
	}

	int count_num = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 0 && !visit[i][j]) {
				dfs(i, j, count_num++);
			}
		}
	}

	sort(cnt, cnt + count_num);

	cout << count_num << endl;

	for (int i = 0; i < count_num; i++) {
		cout << cnt[i] + 1 << " ";
	}


	return 0;
}
