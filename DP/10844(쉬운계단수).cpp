#include <iostream>
#include <algorithm>

#define mod 1000000000

using namespace std;

int n;
int digit[101][10];

int main() {
	cin >> n;

	// n = 1 일 때 끝에 오는 수가 i 일 때 1가지씩 있음
	for (int i = 1; i < 10; i++) {
		digit[1][i] = 1;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == 0) { // 0과 차이나는 것은 1밖에 없음
				digit[i][j] = (digit[i - 1][j + 1]) % mod;
			}
			else if (j == 9) { // 9와 차이나는 것은 8밖에 없음
				digit[i][j] = (digit[i - 1][j - 1]) % mod;
			}
			else { // 플러스 마이너스 1씩
				digit[i][j] = (digit[i - 1][j - 1] + digit[i - 1][j + 1]) % mod;
			}
		}
	}
	
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		sum = (sum + digit[n][i]) % mod;
	}
	cout << sum << endl;

	return 0;
}