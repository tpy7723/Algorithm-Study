#include <iostream>
#include <algorithm>

using namespace std;

int n;
int arr[3][100001];
int dp[3][100001]; // n번째 줄의 i번째까지 얻을 수 있는 최고의 점수

int main() {
	int t;
	cin >> t;

	while (t--) {
		cin >> n;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> arr[i][j];
			}
		}

		//초기 값
		dp[1][1] = arr[1][1]; 
		dp[2][1] = arr[2][1];

		for (int j = 2; j <= 100000; j++) {
			dp[1][j] = max(dp[2][j - 1], dp[2][j - 2]) + arr[1][j];
			dp[2][j] = max(dp[1][j - 1], dp[1][j - 2]) + arr[2][j];
		}

		cout << max(dp[1][n], dp[2][n]) << endl;
	}

	return 0;
}