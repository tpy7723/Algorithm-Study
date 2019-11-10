#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

#define endl "\n"

using namespace std;

struct node {
	int r, c, s; // 행 렬 확산정도
};

int T, N, W, H;
int min_value = 1000000000;
int map[16][13];

int dir[4][2] = {
	{1,0},{-1,0},{0,1},{0,-1}
};

bool isindoor(int y, int x) {
	return (0 <= y && y < H) && (0 <= x && x < W);
}

int count_zero() {
	int cnt = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (map[i][j] != 0) cnt++;
		}
	}
	return cnt;
}

void bfs(int r, int c, int spread) {
	queue<node> q;
	q.push({ r,c, spread });

	while (!q.empty()) {
		int curr = q.front().r;
		int curc = q.front().c;
		int curs = q.front().s;
		map[curr][curc] = 0;

		q.pop();

		for (int i = 0; i < 4; i++) { // 상하좌우
			int nextr = curr;
			int nextc = curc;

			for (int j = 0; j < curs; j++) { // 세기만큼 터짐
				nextr += dir[i][0];
				nextc += dir[i][1];

				if (isindoor(nextr, nextc)) {
					if (map[nextr][nextc] - 1 > 0) {
						q.push({ nextr, nextc, map[nextr][nextc] - 1 });
					}
					map[nextr][nextc] = 0;
				}
			}
		}
	}
}


// 블록정렬
void block_down() {
	for (int j = 0; j < W; j++) { // 첫 열 부터 탐색
		int temp = H - 1; // 맨 아래 인덱스
		for (int i = H-1; i >= 0; i--) {  // 맨 아래에서 위로
			if (map[i][j] != 0) {
				map[temp][j] = map[i][j]; // 해당 값에 위에 데이터를 떼와서 넣음
				if (temp != i) { // 사이에 0이 낀 경우
					map[i][j] = 0; // 값이 내려왔기 때문에 0으로 처리
				}
				temp--; // 한칸 위를 봄
			}
		}
	}
}

// 폭탄 투하
void shoot(int col) {
	for (int i = 0; i < H; i++) {
		if (map[i][col] != 0) { // 맨위지점
			bfs(i, col, map[i][col] - 1);
			block_down(); // 블록 정렬
			break;
		}
	}
}
void dfs(int num) {
	if (num == N) { // N번 투하
		min_value = min(min_value, count_zero()); 
		return;
	}

	int Cmap[16][13];
	memcpy(Cmap, map, sizeof(map));

	for (int i = 0; i < W; i++) {
		shoot(i); // 투하
		dfs(num + 1);
		memcpy(map, Cmap, sizeof(Cmap));  // 맵 원상복구
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;

	int tc = 1;
	while (T--) {
		cin >> N >> W >> H;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> map[i][j];
			}
		}

		dfs(0);

		cout << "#" << ++tc << " " << min_value << endl;

		min_value = 1000000000;
	}

	return 0;
}