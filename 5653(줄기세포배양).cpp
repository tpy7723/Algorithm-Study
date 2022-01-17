#include<iostream>
#include<queue>
#include<vector>
#include<map>

using namespace std;
struct cell {
	int dieAt; // �״½ð�
	int bornAt; // �¾ �ð�
	int lifespan; // ���� ����
	int x, y;
	//bool operator <(const cell& c) const { // �¾ �ð��� ������ �켱
	//	if (bornAt == c.bornAt) {
	//		return lifespan < c.lifespan;
	//	}
	//	return bornAt > c.bornAt;
	//}
};

struct compare {
	bool operator()(cell a, cell b) const { // �¾ �ð��� ������ �켱
		if (a.bornAt == b.bornAt) {
			return a.lifespan < b.lifespan;
		}
		return a.bornAt > b.bornAt;
	}
};

int T;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
priority_queue<cell, vector<cell>, compare> q; // priority_queue<�ڷ���, ����ü, �� ������>
map<pair<int, int>, bool> m; // ��ǥ, 

int main() {
	cin >> T;
	for (int t = 0; t < T; t++) {
		int N, M, K, x;
		int cnt = 0;
		m.clear();
		cin >> N >> M >> K;

		//0�� ��
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> x;
				if (x != 0) {
					q.push({ x + x, x, x, i,j });
					cnt++; // ����ִ� �ٱ⼼�� ����
					m[make_pair(i, j)] = true; // �ٱ⼼����ġ ����
				}
			}
		}
		//1�ʺ��� K���϶�
		// bfs
		for (int i = 1; i <= K; i++) {
			while (q.top().bornAt == i - 1) {
				cell info = q.top(); // bornAt�� ���� ������ ����
				q.pop();
				if (info.dieAt <= K) { // ���� �ٱ⼼�� ����
					cnt--;
				}
				for (int d = 0; d < 4; d++) {
					int nx = info.x + dx[d];
					int ny = info.y + dy[d];
					if (m.find(make_pair(nx, ny)) == m.end()) { // ���������ʴ´ٸ�
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