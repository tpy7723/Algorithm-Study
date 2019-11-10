#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, c, ans, weight[31];
vector<int> v1, v2;

void dfs(int start, int end, int sum, vector<int>& v) {
	if (sum > c) return; // 허용 무게보다 초과시 무시
	if (start > end) return v.push_back(sum); // 만들 수 있는 무게의 경우의 수를 넣음

	dfs(start + 1, end, sum, v); // 안넣음
	dfs(start + 1, end, sum + weight[start], v); // 넣음
}

int main() {
	cin >> n >> c;

	for (int i = 0; i < n; i++) {
		cin >> weight[i];
	}

	dfs(0, n / 2 - 1, 0, v1); 
	sort(v1.begin(), v1.end());

	dfs(n / 2, n - 1, 0, v2); 
	sort(v2.begin(), v2.end());

	int e = v2.size() - 1;

	// 모든 경우의 수 찾기
	for (int s = 0; s < v1.size(); s++) {
		while (e >= 0 && v1[s] + v2[e] > c) e--; // 허용 무게 벗어나는 것은 제외
		ans += e + 1;
	}
	
	cout << ans << endl;

	return 0;
}
