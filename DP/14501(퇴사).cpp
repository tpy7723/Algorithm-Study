#include <iostream>
#include <algorithm>

#define endl "\n"

using namespace std;

int N;
int max_value = -987654321;
int map[16][2];

void dfs(int n, int s) {
	for (int i = n + 1; i <= N; i++) {
		if (i + (map[i][0] - 1) <= N) {
			int tempn = n;
			int temps = s;
			n = i + (map[i][0] - 1);
			s += map[i][1];
			max_value = max(max_value, s);
			dfs(n, s);
			n = tempn;
			s = temps;
		}
	}
}

int main() {
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> map[i][0] >> map[i][1]; // time, pay
	}

	dfs(0, 0); // 일수, 합계

	if (max_value == -987654321) cout << 0 << endl; // 0일때처리하자!!!!!!
	else cout << max_value << endl;

	return 0;
}