#include<iostream>
#include<queue>
#include<vector>
#include<map>

using namespace std;
struct cell {
	int dieAt; // 죽는시간
	int bornAt; // 태어날 시간
	int lifespan; // 원래 수명
	int x, y;
	//bool operator <(const cell& c) const { // 태어난 시간이 수명보다 우선
	//	if (bornAt == c.bornAt) {
	//		return lifespan < c.lifespan;
	//	}
	//	return bornAt > c.bornAt;
	//}
};

struct compare {
	bool operator()(cell a, cell b) const { // 태어난 시간이 수명보다 우선
		if (a.bornAt == b.bornAt) {
			return a.lifespan < b.lifespan;
		}
		return a.bornAt > b.bornAt;
	}
};

int T;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
priority_queue<cell, vector<cell>, compare> q; // priority_queue<자료형, 구현체, 비교 연산자>
map<pair<int, int>, bool> m; // 좌표, 

int main() {
	cin >> T;
	for (int t = 0; t < T; t++) {
		int N, M, K, x;
		int cnt = 0;
		m.clear();
		cin >> N >> M >> K;

		//0초 때
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> x;
				if (x != 0) {
					q.push({ x + x, x, x, i,j });
					cnt++; // 살아있는 줄기세포 개수
					m[make_pair(i, j)] = true; // 줄기세포위치 저장
				}
			}
		}
		//1초부터 K초일때
		// bfs
		for (int i = 1; i <= K; i++) {
			while (q.top().bornAt == i - 1) {
				cell info = q.top(); // bornAt이 가장 작은게 나옴
				q.pop();
				if (info.dieAt <= K) { // 죽은 줄기세포 빼기
					cnt--;
				}
				for (int d = 0; d < 4; d++) {
					int nx = info.x + dx[d];
					int ny = info.y + dy[d];
					if (m.find(make_pair(nx, ny)) == m.end()) { // 존재하지않는다면
						q.push({ i + info.lifespan * 2, i + info.lifespan, info.lifespan, nx, ny });
						cnt++;
						m[make_pair(nx, ny)] = true;
					}
				}
			}
		}

		cout << "#" << t + 1 << " " << cnt << endl;
		while (!q.empty()) q.pop();
	}
	return 0;
}