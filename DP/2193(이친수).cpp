#include <iostream>
#include <algorithm>

using namespace std;

long long int dp[91][2];

int main() {
	int n;
	cin >> n;

	dp[1][0] = 0; // 0으로 끝나는 경우의 수
	dp[1][1] = 1; // 1로 끝나는 경우의 수

	for (int i = 2; i <= n; i++) {
		dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
		dp[i][1] = dp[i - 1][0];
	}

	cout << dp[n][0] + dp[n][1]  << endl;

	return 0;
}