#include <bits/stdc++.h>

using namespace std;

int ttt;
int N, cnt_, vil;
int people[11]; // 인원수 저장
int team[11]; // 0과 1로 팀 구분
vector<int> v[11];
int result = 987654321;

// 같은 소속 수 세기
int bfs(int start) {
	int cnt = 0; // 
	int visit[11] = { 0, }; // 방문 배열
	queue<int> q;
	q.push(start);
	visit[start] = 1;

	while (!q.empty()) {
		cnt++;
		int x = q.front();
		q.pop();
		for (int i = 0; i < v[x].size(); i++) {
			if (visit[v[x][i]] || team[v[x][i]] != team[start]) continue;
			q.push(v[x][i]);
			visit[v[x][i]] = 1;
		}
	}

	return cnt;
}

bool check() {
	int countzero = 0;
	int countone = 0;
	int tempzero = 0;
	int tempone = 0;
	for (int i = 1; i <= N; i++) {
		if (team[i] == 0) {
			countzero++;
			tempzero = i;
		}
		else {
			countone++;
			tempone = i;
		}
	}
	int a = bfs(tempzero);
	int b = bfs(tempone);
	if (a == countzero && b == countone) {
		return true;
	}
	else return false;
}

void dfs(int idx, int cnt) {
	if (cnt >= 1 && cnt != N) {
		if (check()) {
			int team0 = 0;
			int team1 = 0;

			for (int i = 1; i <= N; i++) {
				if (team[i] == 0) {
					team0 += people[i];
				}
				else if (team[i] == 1) {
					team1 += people[i];
				}
			}

			int differ = abs(team0 - team1);
			result = min(result, differ);
		}
	}

	for (int i = idx; i <= N; i++) {
		if (!team[i]) {
			team[i] = 1;
			dfs(i + 1, cnt + 1);
			team[i] = 0;
		}
	}
}
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> people[i];
	}

	for (int i = 1; i <= N; i++) {
		cin >> cnt_;
		for (int j = 0; j < cnt_; j++) {
			cin >> vil;
			v[i].push_back(vil);
		}
	}

	dfs(1, 0);

	cout << ((result == 987654321) ? -1 : result) << endl;
	return 0;
}