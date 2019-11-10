#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct node {
	int r, c, id;
};

int N, M;
int map[8][8];
int min_value = 987654321;
vector<node> v;
// 비트마스크
int U = 1 << 0; // 0001
int R = 1 << 1; // 0010
int D = 1 << 2; // 0100
int L = 1 << 3; // 1000
int direct[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} }; // URDL 순서

vector<int> dir[6] = {
	{},
	{U,R,D,L}, // 1번 CCTV
	{U | D, L | R}, // 2번 CCTV
	{U | R, R | D, D | L, L | U}, // 3번 CCTV
	{L | U | R, U | R | D, R | D | L, D | L | U }, // 4번 CCTV
	{L | U | R | D} // 5번 CCTV
};

bool isindoor(int r, int c) {
	return (0 <= r && r < N) && (0 <= c && c < M);
}

void observe(int r, int c, int d) {
	for (int i = 0; i < 4; i++) { // 상하좌우
		if (d & (1 << i)) { // 
			int nr = r;
			int nc = c;
			while (map[nr][nc] != 6 && isindoor(nr, nc)) { // 벽을만날때까지
				map[nr][nc] = 7; // 감시하는 부분 표시
				nr += direct[i][0];
				nc += direct[i][1];
			}
		}
	}
}

int countzero() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) cnt++;
		}
	}
	return cnt;
}

void dfs(int n) { // n 은 cctv 번호
	if (n == v.size()) { // 모든 cctv 탐색 완료
		min_value = min(min_value, countzero());
		return;
	}

	int r = v[n].r;
	int c = v[n].c;
	int id = v[n].id;
	int Cmap[8][8];
	memcpy(Cmap, map, sizeof(map)); // 원본 저장

	for (int i = 0; i < dir[id].size(); i++) {
		observe(r, c, dir[id][i]);
		dfs(n + 1);
		memcpy(map, Cmap, sizeof(Cmap)); // 다시 되돌리기
	}
}
int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (1 <= map[i][j] && map[i][j] <= 5) {
				v.push_back({ i, j, map[i][j] }); // CCTV 위치 저장
			}
		}
	}

	dfs(0);

	cout << min_value << endl;

	return 0;
}