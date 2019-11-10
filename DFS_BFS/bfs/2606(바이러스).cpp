#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int visit[101];
vector<int> a[101];

int bfs(int start) { // 큐에서 나가는 순서로 출력
	queue<int> q;

	q.push(start);
	visit[start] = true; //방문 여부

	int num = 0;

	while (!q.empty()) {
		int x = q.front();
		q.pop();

		for (int i = 0; i < a[x].size(); i++) {
			int y = a[x][i];
			if (!visit[y]) {
				q.push(y);
				num++;
				visit[y] = true;
			}
		}
	}
	return num;
}

int main(void) {
	int node, line;
	int inode, onode;

	cin >> node >> line;

	// 그래프 연결
	for (int i = 0; i < line; i++) {
		cin >> inode >> onode;
		a[inode].push_back(onode);
		a[onode].push_back(inode);
	}

	cout << bfs(1) << endl;

	return 0;
}