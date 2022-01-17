//#include <iostream>
//#include <cmath>
//#include <algorithm>
//#include <vector>
//#include <queue>
//#include <cstring>
//
//using namespace std;
//
//struct fish {
//	int r, c, s; // 위치 및 크기
//};
//
//struct node {
//	int y, x;
//};
//
//
//int cnt; // 먹은물고기수
//int time;
//int N;
//int map[21][21];
//int visit[21][21];
//int shark_r, shark_c, shark_s;
//vector<fish> v;
//
//int movedir[4][2] = { {1,0},{-1,0},{0,-1},{0,1} }; // 상하 좌우
//
//bool isindoor(int a, int b) {
//	return ((0 <= a && a < N) && (0 <= b && b < N));
//}
//
//// 거리 구하는 용도
//int bfs(int y, int x) {
//	queue<node> q;
//	
//	memset(visit, 0, sizeof(visit));
//	q.push({ y, x });
//
//	visit[y][x] = 1;
//
//	while (!q.empty()) {
//		int cur_y = q.front().y;
//		int cur_x = q.front().x;
//		q.pop();
//
//		for (int i = 0; i < 4; i++) {
//			int next_y = cur_y + movedir[i][0];
//			int next_x = cur_x + movedir[i][1];
//
//			if (isindoor(next_y, next_x)
//				&& (map[next_y][next_x] <= shark_s || map[next_y][next_x] == 9)
//				&& visit[next_y][next_x] == 0) {
//				q.push({ next_y, next_x });
//				visit[next_y][next_x] = visit[cur_y][cur_x] + 1;
//			}
//		}
//	}
//
//	return visit[shark_r][shark_c] - 1; // 상어까지의 거리
//}
//
//int eat_fish() {
//	int min_d = 10000;
//	int dead_fish = -1; // 잡아먹히는 물고기 인덱스
//
//	for (int i = 0; i < v.size(); i++) {
//		if (v[i].s < shark_s) { // 상어 크기보다 작은 물고기면
//			int d = bfs(v[i].r, v[i].c); // bfs를 이용하여 거리를 구함
//			if (d < min_d && d >= 0) {
//				min_d = d; // 최소 거리 최신화
//				dead_fish = i; // 죽은 물고기 인덱스
//			}
//		}
//	}
//
//	if (min_d != 10000) { // 물고기를 먹으면
//		//상어 이동
//		map[shark_r][shark_c] = 0;
//		shark_r = v[dead_fish].r;
//		shark_c = v[dead_fish].c;
//		map[shark_r][shark_c] = 9;
//
//		v.erase(v.begin() + dead_fish); // 물고기 리스트에서 삭제
//
//		time += min_d; // 시간 추가
//		cnt++; // 먹은횟수 1증가
//		if (shark_s == cnt) { // 물고기먹은횟수가 상어사이즈랑 같으면
//			shark_s++; // 상어 크기 증가
//			cnt = 0; // 물고기먹은횟수 초기화
//		}
//
//	}
//
//	return min_d; // d가 10000이면 근처 물고기가 없는 것
//}
//
//int main() {
//	cin >> N;
//
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//
//			cin >> map[i][j];
//
//			if (map[i][j] != 9 && map[i][j] != 0) { // 물고기 좌표 저장
//				v.push_back({ i, j, map[i][j] });
//			}
//			if (map[i][j] == 9) { // 상어 좌표 저장
//				shark_r = i;
//				shark_c = j;
//				shark_s = 2;
//			}
//		}
//	}
//
//	while (eat_fish() != 10000) {
//	}
//
//	cout << time << endl;
//
//	return 0;
//}


//// 방법 2 우선순위 큐

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

// r = x  ,  c = y  혼동 주의
struct shark {
	int d, x, y;
	// Min Heap (priority : distance > x position > y position)
	bool operator < (const shark &t) const {
		if (d == t.d) { // 거리가 같다면
			if (x == t.x) return y > t.y; // 왼쪽 것이 먼저나옴
			else return x > t.x; // 위쪽 것이 먼저나옴
		}
		else return d > t.d; // 거리가 짧은것이 먼저나옴 
	}
};

int n, body, eat, ans;
int a[20][20];
bool check[20][20];
priority_queue<shark> q;
const int dx[] = { -1, 0, 0, 1 }, dy[] = { 0, -1, 1, 0 };

void bfs() {
	while (!q.empty()) {
		int d = q.top().d, x = q.top().x, y = q.top().y;
		q.pop();
		// Shark can eat fish, if fish is smaller than shark.
		if (0 < a[x][y] && a[x][y] < body) {
			// Count eating fish.
			a[x][y] = 0;
			eat++;
			// Body size + 1
			if (eat == body) {
				body++;
				eat = 0;
			}
			ans += d;

			// 한마리만 먹음 왜냐하면 가장 가까운 물고기이기 떄문
			// Initializing distance, visited check, and queue.
			d = 0;
			memset(check, false, sizeof(check)); // 다시 그곳에서 탐색 시작
			while (!q.empty()) q.pop();
		}
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			// Cannot pass if fish is bigger than shark, or already visited.
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;  // 배열 범위 벗어남
			if (check[nx][ny]) continue; // 이미 했던 경로 무시
			if (a[nx][ny] > body) continue; // 자신보다 큰 물고기 못지나감
			// Update next moving.
			q.push({ d + 1, nx, ny });
			check[nx][ny] = true;
		}
	}
}

void solve() {
	body = 2; // 상어 사이즈
	bfs();
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
			if (a[i][j] == 9) { // 아기상어
				q.push({ 0, i, j }); //  d x y
				a[i][j] = 0; // 상어는 pq에서 사용
			}
		}
	}
	solve();
	printf("%d\n", ans);
	return 0;
}