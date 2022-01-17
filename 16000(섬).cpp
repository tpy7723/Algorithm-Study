#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int dx[] = { 0,0,-1,1 }, dy[] = { -1,1,0,0 };
const int n_ = 2000 + 2, nm_ = 4000000 + 1;

char a[n_][n_];
int n, m, cnt, num, visit[n_][n_], check[nm_], con[nm_], isSum[nm_];
vector<int> stk, graph[nm_];

void dfs(int x, int y, int num) {
	visit[x][y] = num; // �� ID
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (a[x][y] == a[nx][ny] && !visit[nx][ny]) { // ���� ��� ã��
			dfs(nx, ny, num);
		}
		else if (a[x][y] != a[nx][ny] && visit[nx][ny]) { // ���� �ʰ� �̹� �湮�ߴ� ���̸�
			if (con[visit[nx][ny]] == num) continue; // �̹� ����Ȯ���ߴ� ���

			// �׷��� ����
			graph[num].push_back(visit[nx][ny]);
			graph[visit[nx][ny]].push_back(num);

			// ���� ����
			con[num] = num;
			con[visit[nx][ny]] = num;
		}
	}
}

void gogo(int now) {
	int mn = num;
	check[now] = ++cnt;
	stk.push_back(now);
	for (int nxt : graph[now]) { // ����� �� Ž��
		if (!check[nxt]) {
			gogo(nxt);
			if (isSum[now] && check[nxt] == check[now]) { // ���̰� 
				while (!stk.empty() && stk.back() != now) {
					con[stk.back()] = 1;
					stk.pop_back();
				}
			}
			stk.push_back(now);
		}
		mn = min(mn, check[nxt]);
	}
	check[now] = mn;
	return;
}


int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		cin >> a[i] + 1;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!visit[i][j]) {
				dfs(i, j, ++num);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << visit[i][j];
		}
		cout << endl;
	}

	fill(con, con + num + 1, 0);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == '#') { // ����
				isSum[visit[i][j]] = 1; // ������ �ƴ��� ǥ��
			}
		}
	}

	gogo(1); // ���� �ٱ� �ٴٺ���  Ž��

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == '.') {
				cout << ".";
				continue;
			}
			int num = visit[i][j];
			cout << ((con[num] && check[num] != 1) ? 'X' : 'O');
		}
		cout << endl;
	}

	return 0;
}