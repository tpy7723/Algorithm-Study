#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

struct node {
	int a, b; // a와 b의 사이는
	int c; // 비용 cost 이다

	// 생성자
	node(int a_, int b_, int c_) {
		a = a_;
		b = b_;
		c = c_;
	}

	// 오름차순 정렬을 위해 비용이 큰게 큰 것으로 정의
	bool operator<(node &n) {
		return c < n.c;
	}
};

// 좌표
struct xynode {
	int r, c;
};

int N, M;
int key = 1; // 섬 구분
int mymap[101][101];
int parent[8];
int dir[4][2] = { {1,0}, {-1,0}, {0,-1}, {0,1} };
vector<node> v; // 간선 정보 저장
vector<xynode> save[8]; // 각 섬별로 위치 저장

// 아래 3개 함수는 크루스칼 함수
int getParent(int a) {
	if (parent[a] == a) return a;
	return parent[a] = getParent(parent[a]);
}

void Union(int a, int b) {
	a = getParent(a);
	b = getParent(b);

	if (a < b) parent[b] = a;
	else parent[a] = b;
}

bool confirm(int a, int b) {
	a = getParent(a);
	b = getParent(b);

	if (a == b) return true;
	else return false;
}

bool isindoor(int r, int c) {
	return (0 <= r && r < N) && (0 <= c && c < M);
}

// dfs를 이용하여 섬에 이름을 새김
void dfs(int r, int c, int key) {
	mymap[r][c] = key;
	save[key].push_back({ r,c });

	for (int i = 0; i < 4; i++) {
		int nextr = r + dir[i][0];
		int nextc = c + dir[i][1];

		if (isindoor(nextr, nextc) && mymap[nextr][nextc] == 1) {
			dfs(nextr, nextc, key);
		}
	}
}

// 다리를 세울 때 필요한 최소거리를 계산
void bfs(int vnum, int d) { // 방향을 입력받음
	queue<xynode> q;
	int visit[101][101] = { 0, };

	int distance[8] = { 0, };

	for (int i = 0; i < save[vnum].size(); i++) {
		q.push({ save[vnum][i].r, save[vnum][i].c });
		visit[save[vnum][i].r][save[vnum][i].c] = 1;
	}

	while (!q.empty()) {
		int curr = q.front().r;
		int curc = q.front().c;

		q.pop();

		// 한쪽 방향으로만 이동
		int nextr = curr + dir[d][0];
		int nextc = curc + dir[d][1];

		if (isindoor(nextr, nextc) && !visit[nextr][nextc]) {
			if (mymap[nextr][nextc] == 0) {
				q.push({ nextr ,nextc });
				visit[nextr][nextc] = visit[curr][curc] + 1;
			}
			else { // 다른 섬 만났을 때
				// 거리가 2이상되고
				if (visit[curr][curc] - 1 >= 2) {
					// 최소 거리만 저장
					if (distance[mymap[nextr][nextc]] > visit[curr][curc] - 1
						|| distance[mymap[nextr][nextc]] == 0) {
						distance[mymap[nextr][nextc]] = visit[curr][curc] - 1;
					}
				}
			}
		}
	}

	//얻어낸 간선 정보 저장
	for (int i = 2; i <= key; i++) {
		if (distance[i] != 0) {
			v.push_back({ vnum, i, distance[i] });
		}
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> mymap[i][j];
		}
	}

	// 섬 구분하기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (mymap[i][j] == 1) {
				dfs(i, j, ++key);
			}
		}
	}

	// 2부터 key-1 개의 섬
	// 간선관계 구하기 
	for (int k = 2; k <= key; k++) {
		for (int d = 0; d < 4; d++) {
			bfs(k, d); // 상하좌우
		}
	}

	for (int i = 2; i <= key; i++) {
		parent[i] = i;
	}

	// 비용을 기준으로 오름차순 정렬
	sort(v.begin(), v.end());

	// 크루스칼
	int sum = 0;
	for (int i = 0; i < v.size(); i++) {
		if (!confirm(v[i].a, v[i].b)) {
			sum += v[i].c;
			Union(v[i].a, v[i].b);
		}
	}

	// 연결이 모두 되었는지 확인
	int temp = getParent(2);
	for (int i = 3; i <= key; i++) {
		if (temp != getParent(i)) {
			cout << -1 << endl;
			return 0;
		}
	}
	cout << sum << endl;

	return 0;
}