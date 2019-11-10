#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

struct virus {
	int x, y;
};
int min_value = 10000000;
int a[50][50];
int dist[50][50];
int n, m, k, ans = 1e9;
bool visited[10];
vector<virus> v;
queue<virus> q;

const int dx[] = { -1, 0 , 1, 0 }, dy[] = { 0, 1, 0, -1 };

bool isindoor(int y, int x) {
	return (0 <= y && y < n) && (0 <= x && x < n);
}

void bfs() { //bfs
	int infect = 0, times = 0;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (isindoor(ny, nx)) {
				if (a[nx][ny] != 1 && dist[nx][ny] == -1) { // 벽이아니고 방문한 적이 없으면
					dist[nx][ny] = dist[x][y] + 1; // 거리 1 증가
					q.push({ nx, ny });
					infect += 1; // 감염 1 증가
					times = dist[nx][ny]; // 최고 시간 저장
				}
			}
		}
	}

	if (infect == k && ans > times) ans = times; // 감염 수와 길의 수가 같을떄,  time 최소 값 
}

void solve(int idx, int cnt) { // dfs
	if (cnt == m) {
		memset(dist, -1, sizeof(dist));
		for (int i = 0; i < v.size(); i++) {
			// m개의 바이러스 활성화
			if (visited[i]) {
				q.push({ v[i].x, v[i].y });
				dist[v[i].x][v[i].y] = 0;
			}
		}
		bfs();

		return;
	}
	for (int i = idx; i < v.size(); i++) { // idx 부터 안세면 시간초과
		if (!visited[i]) { // 활성 바이러스 체크 용도
			visited[i] = true; // 활성
			solve(i + 1, cnt + 1);
			visited[i] = false; // 비활성
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 2) v.push_back({ i, j }); // 바이러스를 놓을 수 있는 카
			if (a[i][j] == 0) k++; // 길의 개수
		}
	}
	k = k + v.size() - m; // 감염시켜야할 칸의 개수

	solve(0, 0);

	cout << ((ans == 1e9) ? -1 : ans) << endl;

	return 0;
}