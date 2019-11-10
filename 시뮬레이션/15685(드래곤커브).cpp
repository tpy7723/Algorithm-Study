#include <iostream>
#include <vector>

using namespace std;

int N;
int map[101][101];
vector<int> vec;
int dir[4][2] = { {0,1},{-1,0},{0,-1},{1,0} };

int countsqure() {
	int cnt = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1) cnt++;
		}
	}
	return cnt;
}
vector<int> generation(int r, int c, int d, int g) {
	vector<int> v;
	v.push_back(d); // 0세대

	while (g--) {
		int idx = v.size() - 1;
		for (int i = idx; i >= 0; i--) {
			int input = (v[i] + 1) % 4;
			v.push_back(input);
		}
	}
	return v;
}

bool isindoor(int r, int c) {
	return (0 <= r && r < 101) && (0 <= c && c < 101);
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int r, c, d, g;
		cin >> c >> r >> d >> g;  // 좌표, 시작방향, 세대
									// 0123 동북서남

		vec = generation(r, c, d, g);
		int nr = r;
		int nc = c;
		map[nr][nc] = 1;

		for (int j = 0; j < vec.size(); j++) {
			nr += dir[vec[j]][0];
			nc += dir[vec[j]][1];
			if (isindoor(nr, nc)) {
				map[nr][nc] = 1;
			}
		}
	}

	cout << countsqure() << endl;

	return 0;
}