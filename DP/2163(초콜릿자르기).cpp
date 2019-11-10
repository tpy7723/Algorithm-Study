#include <iostream>

using namespace std;

int dp[301][301];
int n, m;

int main() {
	cin >> n >> m;

	for (int i = 1; i <= 300; i++) {
		for (int j = 1; j <= 300; j++) {
			if (i % 2 == 0 && j % 2 ==0) { // °¡·Î ¼¼·Î Â¦¼ö
				dp[i][j] = 4 * dp[i / 2][j / 2] + 3;
			}
			else if (i % 2 == 0) { // °¡·Î Â¦¼ö
				dp[i][j] = 2 * dp[i / 2][j] + 1;
			}
			else if (j % 2 == 0) { // ¼¼·Î Â¦¼ö
				dp[i][j] = 2 * dp[i][j / 2] + 1;
			}
			else { // ¸ðµÎ È¦¼ö
				dp[i][j] = (j-1) + j * (i-1);
			}
		}
	}
	cout << dp[n][m] << endl;
	return 0;
}