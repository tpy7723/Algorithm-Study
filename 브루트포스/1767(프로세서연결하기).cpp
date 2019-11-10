#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	int r, c;
};

int map[13][13];
int visit[13][13];
int test_num = 1;
int result = 10000000;
int n;
int dx[] = { 1,-1,0,0 };
int dy[] = { 0, 0, 1, -1 };
int cnt;
int max_success;
vector<node> v;

bool isindoor(int y, int x) {
	return (1 <= y && y <= n) && (1 <= x && x <= n);
}

int draw_line(int r, int c, int d) {
	r += dy[d];
	c += dx[d];

	bool finish = false; // 끝점에 닫는지
	vector<node> temp;

	//범위안에 속하고 방문한적 없고 빈칸 인 곳
	while (isindoor(r, c) && map[r][c] == 0 && visit[r][c] == 0) {
		temp.push_back({ r, c });

		if (r == 1 || r == n || c == 1 || c == n) {
			finish = true;
			break;
		}

		r += dy[d];
		c += dx[d];
	}
	if (finish == true) {
		for (int i = 0; i < temp.size(); i++) {
			visit[temp[i].r][temp[i].c] = 2;
		}
		return 1;
	}
	else {
		return 0;
	}
}

void erase_line(int r, int c, int d) {
	int nextr = r + dy[d];
	int nextc = c + dx[d];

	while (visit[nextr][nextc] == 2) {
		visit[nextr][nextc] = 0;
		nextr += dy[d];
		nextc += dx[d];
	}
}

int count_line() {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (visit[i][j] == 2) {
				cnt++;
			}
		}
	}
	return cnt;
}

void dfs(int num, int success) {
	// 모든 프로세서 연결
	if (num == v.size()) {
		if (success > max_success) {
			max_success = success;
			result = count_line();
		}
		else if (success == max_success) {
			result = min(result, count_line());
		}
		return;
	}

	//현재 위치
	int r = v[num].r;
	int c = v[num].c;

	//완탐
	for (int i = 0; i < 4; i++) {
		int suc = draw_line(r, c, i); // 선그리는 함수

		// ★ 가지치기 중요 ★
		if (success + suc + (v.size() - num - 1) < max_success) { // 앞으로 다 성공해도 max보다 작으면 무시
			continue;
		}

		dfs(num + 1, success + suc);

		if (suc) {
			erase_line(r, c, i); // 선지우는 함수
		}
	}

}
int main() {
	int t;

	cin >> t;

	while (t--) {
		cin >> n;

		max_success = 0;
		result = 0;
		v.clear();

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> map[i][j];
				// 테두리에 있지 않은 프로세서 위치 저장
				if (map[i][j] == 1 && i != 1 && j != 1 && i != n && j != n) {
					v.push_back({ i,j });
				}
			}
		}

		memcpy(visit, map, sizeof(map));

		dfs(0, 0);

		cout << "#" << test_num++ << " " << result << endl;
	}

	return 0;
}