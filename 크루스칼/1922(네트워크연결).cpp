#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class node {
public:
	int a, b;
	int c;
	node(int a, int b, int c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
	bool operator <(node &n) {
		return this->c < n.c;
	}
};

int N, M; // 노드, 간선수
vector<node> v;
int parent[1001];

int getParent(int x) {
	if (parent[x] == x) return x;
	return parent[x] = getParent(parent[x]); // 최신화
}

void Union(int a, int b) {
	a = getParent(a);
	b = getParent(b);
	if (a < b) parent[b] = a;
	else parent[a] = b;
}

bool confirm(int a, int b) {
	a = getParent(a);
	b = getParent(b);
	if (a == b) return true;
	else return false;
}

int main() {
	cin >> N >> M;

	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		v.push_back(node(a, b, c));
	}

	sort(v.begin(), v.end());

	for (int i = 1; i <= N; i++) {
		parent[i] = i;
	}

	int sum = 0;

	for (int i = 0; i < v.size(); i++) {
		if (!confirm(v[i].a, v[i].b)) {
			sum += v[i].c;
			Union(v[i].a, v[i].b);
		}
	}

	cout << sum << endl;
	return 0;
}