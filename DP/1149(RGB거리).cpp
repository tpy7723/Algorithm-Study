#include <iostream>
#include <algorithm>

using namespace std;

int dp[1001][3];
int cost[1001][3];

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
	}

	for (int i = 1; i <= n; i++) {
		dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + cost[i][0]; // i번째 집에 빨간색을 칠할때 최소 비용
		dp[i][1] = min(dp[i - 1][2], dp[i - 1][3]) + cost[i][1];
		dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + cost[i][2];
	}

	cout << min(dp[n][0], min(dp[n][1], dp[n][2])) << endl;

	return 0;
}