#include <iostream>
#include <algorithm>
#include <vector>

#define endl "\n"

using namespace std;

struct node {
	int r, c;
};
int N, M;
int map[51][51];
int visit[13];
int min_value = 987654321;
int cnt;
vector<node> v, v2;

void dfs(int depth, int num) {
	if (num == M) { // M개 뽑기
		int sum = 0;
		for (int i = 0; i < v2.size(); i++) {
			int d = 987654321;
			for (int j = 0; j < v.size(); j++) {
				if (visit[j] == 1) {
					d = min(d, abs(v2[i].r - v[j].r) + abs(v2[i].c - v[j].c));
				}
			}
			sum += d;
		}
		min_value = min(min_value, sum);
		return;
	}

	for (int i = depth; i < v.size(); i++) {
		if (!visit[i]) {
			visit[i] = true;
			dfs(i + 1, num + 1);
			visit[i] = false;
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				v.push_back({ i,j }); // 치킨집 위치 저장
			}
			else if (map[i][j] == 1) {
				v2.push_back({ i,j }); // 집 위치 저장
			}
		}
	}

	dfs(0, 0);

	cout << min_value << endl;
	return 0;
}