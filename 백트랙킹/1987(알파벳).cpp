#include <iostream>
#include <algorithm>
#include <string>
#define endl "\n"


using namespace std;
string v;
int r, c;
char map[22][22];
int maxdepth;
int dx[] = { 1,0,-1,0 };
int dy[] = { 0,1,0,-1 };

bool isindoor(int y, int x) {
	return (1 <= y && y <= r) && (1 <= x && x <= c);
}

void dfs(int r, int c, int depth) {
	maxdepth = max(maxdepth, depth); // 최대 이동 많이

	for (int i = 0; i < 4; i++) {
		int nextr = r + dy[i];
		int nextc = c + dx[i];

		if (isindoor(nextr, nextc)) {
			if (v.find(map[nextr][nextc]) == string::npos) { // 해당 문자열이 없을 때 npos를 반환
				v.push_back(map[nextr][nextc]);
				dfs(nextr, nextc, depth + 1);
				v.pop_back();
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> r >> c;

	for (int i = 1; i <= r; i++) {
		cin >> map[i] + 1; // 배열 1,1 부터 넣기위해서
	}

	v.push_back(map[1][1]); // 시작 지점

	dfs(1, 1, 1);

	cout << maxdepth << endl;
	return 0;
}
