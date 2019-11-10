//#include <iostream>
//#include <queue>
//#include <algorithm>
//#include <vector>
//#include <cstring>
//
//using namespace std;
//
//struct node {
//	int r, c;
//};
//
//int N, result = 987654321;
//vector<node> v[10001];
//int map[103][103];
//int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
//
//void bfs(int r, int c, int key) {
//	queue<node> q;
//	int visit[103][103];
//	memset(visit, 0, sizeof(visit));
//
//	q.push({ r,c });
//	visit[r][c] = 1;
//	map[r][c] = key;
//	v[key].push_back({ r,c });
//
//	while (!q.empty()) {
//		int curr = q.front().r;
//		int curc = q.front().c;
//
//		q.pop();
//
//		for (int i = 0; i < 4; i++) {
//			int nextr = curr + dir[i][0];
//			int nextc = curc + dir[i][1];
//
//			if (0 <= nextr && nextr <= N && 0 <= nextc && nextc <= N
//				&& map[nextr][nextc] == 1) {
//				if (visit[nextr][nextc]) continue;
//
//				q.push({ nextr ,nextc });
//				visit[nextr][nextc] = 1;
//				map[nextr][nextc] = key;
//				v[key].push_back({ nextr,nextc });
//			}
//		}
//	}
//}
//
//int spread(int key) {
//	int visit[103][103];
//	memset(visit, 0, sizeof(visit));
//
//	queue<node> q;
//
//	for (int i = 0; i < v[key].size(); i++) {
//		q.push({ v[key][i].r, v[key][i].c });
//		visit[v[key][i].r][v[key][i].c] = 1;
//	}
//
//	while (!q.empty()) {
//		int curr = q.front().r;
//		int curc = q.front().c;
//
//		q.pop();
//
//		for (int i = 0; i < 4; i++) {
//			int nextr = curr + dir[i][0];
//			int nextc = curc + dir[i][1];
//
//			if (0 <= nextr && nextr <= N && 0 <= nextc && nextc <= N
//				&& visit[nextr][nextc] == 0) {
//				if (map[nextr][nextc] == 0) {
//					q.push({ nextr ,nextc });
//					visit[nextr][nextc] = visit[curr][curc] + 1;
//				}
//				else if (map[nextr][nextc] != key) {
//					return visit[curr][curc] - 1;
//				}
//			}
//		}
//	}
//	
//	return 0;
//}
//
//int main() {
//	cin >> N;
//
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			cin >> map[i][j];
//		}
//	}
//
//	int key = 2;
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			if (map[i][j] == 1) {
//				bfs(i, j, key);
//				key++;
//			}
//		}
//	}
//	// 2부터 key -1 까지 존재
//	int distance = 0;
//	for (int k = 2; k < key; k++) {
//		distance = spread(k);
//		result = min(result, distance);
//	}
//
//	cout << result << endl;
//
//	return 0;
//}