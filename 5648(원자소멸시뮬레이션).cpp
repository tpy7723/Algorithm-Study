#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

struct info {
	int y, x, d, n; 
};

int tc, N;
int dx[] = { 0,0,-1,1 }, dy[] = { 1,-1,0,0 }; // 상하좌우
int map[4001][4001];

vector<info> v;

int solve() {
	int ans = 0;
	while (!v.empty()) { // 원소가 빌 때까지
		// 이동
		for (int i = 0; i < v.size(); i++) { // 모든 원소에 대해
			map[v[i].x][v[i].y] = 0; // 이동 전 위치는 0으로 초기화
			int x = v[i].x += dx[v[i].d]; // 이동 후 x
			int y = v[i].y += dy[v[i].d]; // 이동 후 y
			if (x < 0 || x > 4000 || y < 0 || y > 4000) { // 범위를 벗어나면
				v[i].n = 0;  // 획득할수있는 점수를 0
				continue;  // 무시
			}
			map[x][y] += v[i].n; // 이동한 칸에 점수를 매김 or 더함
		}
		// 파악
		for (int i = 0; i < v.size(); i++) { // 모든 원소에 대해
			if (!v[i].n) continue; // 범위를 벗어난 것 or 
			int x = v[i].x;
			int y = v[i].y; 
			if (map[x][y] != v[i].n) { // 값이 다르면 충돌임
				ans += map[x][y];
				map[x][y] = 0; // 초기화
				v[i].n = 0; // 충돌 후 획득할수있는 점수를 0
			}
		}

		// 원소 값이 남아있는 것만 걸러냄
		vector<info> tmp;
		tmp = v;
		v.clear();

		for (int i = 0; i < tmp.size(); i++) {
			if (tmp[i].n != 0) {
				v.push_back(tmp[i]);
			}				
		}
	}
	return ans;
}

int main() {
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		cin >> N;

		int y, x, d, n;
		for (int i = 0; i < N; i++)
		{
			cin >> x >> y >> d >> n;
			// 원소 저장
			v.push_back({ 2 * (y + 1000), 2 * (x + 1000), d, n }); // 양수로 만들기, 0.5초 따지기
		}
		cout << "#" << t << " " << solve() << endl;
	}
	return 0;
}
