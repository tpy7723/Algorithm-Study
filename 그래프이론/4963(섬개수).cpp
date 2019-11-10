#include <iostream>

using namespace std;


int w, h;
int map[51][51];
int cnt;
int dir[8][2] = { {1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };

bool isindoor(int y, int x) {
	return ((0 <= y && y < h) && (0 <= x && x < w));
}

void dfs(int y, int x) {
	map[y][x] = 0;

	for (int i = 0; i < 8; i++) {
		int next_y = y + dir[i][0];
		int next_x = x + dir[i][1];

		if (isindoor(next_y, next_x) && map[next_y][next_x] == 1) {
			dfs(next_y, next_x);
		}
	}
}

int main() {
	while (cin >> w >> h) {
		if (w == 0 && h == 0) break;

		cnt = 0;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
			}
		}

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (map[i][j] == 1) {
					cnt++;
					dfs(i, j);
				}
			}
		}
		
		cout << cnt << endl;
	}


	return 0;
}