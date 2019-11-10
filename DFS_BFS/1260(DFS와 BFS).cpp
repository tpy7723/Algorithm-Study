#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;

int visit[1001];
vector<int> a[1001];


void bfs(int start) { // 큐에서 나가는 순서로 출력
	queue<int> q;

	q.push(start); // 처음꺼 넣기
	visit[start] = true; //방문 여부

	while (!q.empty()) {
		// 큐에 값이 있을경우 계속 반복 실행
		// 큐에 값이 있다. => 아직 방문하지 않은 노드가 존재 한다. 
		int x = q.front();
		q.pop();     // 맨 앞을 저장하고 한개를 뺀다.
		cout << x << " ";
		for (int i = 0; i < a[x].size(); i++) {
			int y = a[x][i];
			if (!visit[y]) { // 방문하지 않았다면..
				visit[y] = true;
				q.push(y);
			}
		}
	}
}

void dfs(int start) { // 방문했던 순서대로 출력
	if (visit[start]) return; // 방문했다면 리턴
	visit[start] = true; // 방문안했다면 방문처리
	cout << start << ' ';
	for (int i = 0; i < a[start].size(); i++) {
		int y = a[start][i]; // 정렬했기 때문에 작은거 부터 탐색
		dfs(y); // 재귀
	}
}

int main(void) {
	int node, line, start, inode, onode;

	cin >> node >> line >> start;

	// 연결
	for (int i = 0; i < line; i++) {
		cin >> inode >> onode;
		a[inode].push_back(onode);
		a[onode].push_back(inode);
	}

	// 정렬 - 낮은거 부터 출력하기 위해
	for (int i = 0; i < node; i++) {
		sort(a[i].begin(), a[i].end());
	}

	dfs(start);

	cout << endl;

	memset(visit, 0, sizeof(visit)); // 방문 배열 초기화

	bfs(start);

	return 0;
}