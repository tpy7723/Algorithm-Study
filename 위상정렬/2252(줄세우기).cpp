#include <iostream>
#include <vector>
#include <queue>

#define MAX 32001

using namespace std;

int N, M;
int inDegree[MAX];
vector<int> a[MAX];

void topologySort() {
	int result[MAX];
	queue<int> q;

	// 진입 차수가 0인 노드를 큐에 삽입합니다. 
	for (int i = 1; i <= N; i++) {
		if (inDegree[i] == 0) q.push(i);
	}

	// 정렬이 완전히 수행되려면 정확히 n개의 노드를 방문합니다.
	for (int i = 1; i <= N; i++) {
		// n개를 방문하기 전에 큐가 비어버리면 사이클이 발생한 것입니다. 
		if (q.empty()) {
			break;
		}
		int x = q.front();
		q.pop();
		result[i] = x;
		for (int i = 0; i < a[x].size(); i++) {
			int y = a[x][i];
			// 새롭게 진입차수가 0이 된 정점을 큐에 삽입합니다. 
			if (--inDegree[y] == 0)
				q.push(y);
		}
	}
	for (int i = 1; i <= N; i++) {
		cout << result[i] << " ";
	}
}

int main(void) {
	cin >> N >> M;

	int inputA, inputB;
	for (int i = 0; i < M; i++) {
		cin >> inputA >> inputB;
		a[inputA].push_back(inputB);
		inDegree[inputB]++;
	}

	topologySort();

	return 0;
}
