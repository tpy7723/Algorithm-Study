#include <iostream>
#include <algorithm>

using namespace std;
int dp[10001];
int coin[101];
int n;
int k;

int main() {
	cin >> n >> k;

	for(int i=1; i<=n; i++){
		cin >> coin[i];
	}

	dp[0] = 1; // 0원을 만드는 가지수 1

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			if (j - coin[i] >= 0) { // 인덱스 음수 방지
				dp[j] += dp[j - coin[i]];
			}
		}
	}

	cout << dp[k] << endl;
	return 0;
}
