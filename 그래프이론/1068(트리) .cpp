#include <iostream>
#include <vector>

using namespace std;

int n;
int parent;
int delete_node;
int cnt;
int visit[51];

vector<int> v[51];
vector<int> root_node;

void dfs(int start, int delete_node) {
	if (v[start].size() == 0) { // 자식이 없다면 리프노드이다.
		cnt++;
	}
	else {
		for (int i = 0; i < v[start].size(); i++) {
			int next = v[start][i];
			if (next == delete_node) { // 자식이 삭제할 노드이고
				if (v[start].size() == 1) { // 리프노드의 부모도 자식이 1개뿐이면 부모가 리프노드가 됨
					cnt++;
				}
				continue;
			}

			dfs(next, delete_node);
		}
	}
}
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> parent;
		if (parent != -1) {
			v[parent].push_back(i); // 루트 노드 아닌 노드 들
		}
		else {
			root_node.push_back(i); // 루트 노드
		}
	}

	cin >> delete_node;

	for (int i = 0; i < root_node.size(); i++) {
		if (delete_node != root_node[i]) {
			dfs(root_node[i], delete_node);
		}
	}

	cout << cnt << endl;

	return 0;
}