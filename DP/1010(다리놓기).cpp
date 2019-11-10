#include <iostream>

using namespace std;

int dp[30][30]; // nCr 조합 n개중에 r개 뽑기
				// nCr = n-1Cr-1 + n-1Cr
				// nC0 = nCn = 1
int main() {
	int t;
	cin >> t;
	
	// 동쪽m 이 n이고 서쪽n이 r 이다
	for (int i = 0; i < 30; i++) { // 동쪽이 i
		dp[i][0] = dp[i][i] = 1; // nC0 = nCn = 1
		for (int j = 1; j <= i; j++) { // 서쪽이 j
			dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; // nCr = n-1Cr-1 + n-1Cr
		}
	}

	while (t--) {
		int n, m;
		cin >> n >> m; // 서쪽 동쪽
		cout << dp[m][n] << endl;
	}
	return 0;
}