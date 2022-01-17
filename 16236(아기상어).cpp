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
//	int r, c, s; // ��ġ �� ũ��
//};
//
//struct node {
//	int y, x;
//};
//
//
//int cnt; // ����������
//int time;
//int N;
//int map[21][21];
//int visit[21][21];
//int shark_r, shark_c, shark_s;
//vector<fish> v;
//
//int movedir[4][2] = { {1,0},{-1,0},{0,-1},{0,1} }; // ���� �¿�
//
//bool isindoor(int a, int b) {
//	return ((0 <= a && a < N) && (0 <= b && b < N));
//}
//
//// �Ÿ� ���ϴ� �뵵
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
//	return visit[shark_r][shark_c] - 1; // �������� �Ÿ�
//}
//
//int eat_fish() {
//	int min_d = 10000;
//	int dead_fish = -1; // ��Ƹ����� ����� �ε���
//
//	for (int i = 0; i < v.size(); i++) {
//		if (v[i].s < shark_s) { // ��� ũ�⺸�� ���� ������
//			int d = bfs(v[i].r, v[i].c); // bfs�� �̿��Ͽ� �Ÿ��� ����
//			if (d < min_d && d >= 0) {
//				min_d = d; // �ּ� �Ÿ� �ֽ�ȭ
//				dead_fish = i; // ���� ����� �ε���
//			}
//		}
//	}
//
//	if (min_d != 10000) { // ����⸦ ������
//		//��� �̵�
//		map[shark_r][shark_c] = 0;
//		shark_r = v[dead_fish].r;
//		shark_c = v[dead_fish].c;
//		map[shark_r][shark_c] = 9;
//
//		v.erase(v.begin() + dead_fish); // ����� ����Ʈ���� ����
//
//		time += min_d; // �ð� �߰�
//		cnt++; // ����Ƚ�� 1����
//		if (shark_s == cnt) { // ��������Ƚ���� ��������� ������
//			shark_s++; // ��� ũ�� ����
//			cnt = 0; // ��������Ƚ�� �ʱ�ȭ
//		}
//
//	}
//
//	return min_d; // d�� 10000�̸� ��ó ����Ⱑ ���� ��
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
//			if (map[i][j] != 9 && map[i][j] != 0) { // ����� ��ǥ ����
//				v.push_back({ i, j, map[i][j] });
//			}
//			if (map[i][j] == 9) { // ��� ��ǥ ����
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


//// ��� 2 �켱���� ť

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

// r = x  ,  c = y  ȥ�� ����
struct shark {
	int d, x, y;
	// Min Heap (priority : distance > x position > y position)
	bool operator < (const shark &t) const {
		if (d == t.d) { // �Ÿ��� ���ٸ�
			if (x == t.x) return y > t.y; // ���� ���� ��������
			else return x > t.x; // ���� ���� ��������
		}
		else return d > t.d; // �Ÿ��� ª������ �������� 
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

			// �Ѹ����� ���� �ֳ��ϸ� ���� ����� ������̱� ����
			// Initializing distance, visited check, and queue.
			d = 0;
			memset(check, false, sizeof(check)); // �ٽ� �װ����� Ž�� ����
			while (!q.empty()) q.pop();
		}
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			// Cannot pass if fish is bigger than shark, or already visited.
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;  // �迭 ���� ���
			if (check[nx][ny]) continue; // �̹� �ߴ� ��� ����
			if (a[nx][ny] > body) continue; // �ڽź��� ū ����� ��������
			// Update next moving.
			q.push({ d + 1, nx, ny });
			check[nx][ny] = true;
		}
	}
}

void solve() {
	body = 2; // ��� ������
	bfs();
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
			if (a[i][j] == 9) { // �Ʊ���
				q.push({ 0, i, j }); //  d x y
				a[i][j] = 0; // ���� pq���� ���
			}
		}
	}
	solve();
	printf("%d\n", ans);
	return 0;
}