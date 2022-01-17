#include <iostream>
#define MOD 1000000007

using namespace std;

int n, m;
char block[2001][2001];
int cnt = 0;
int sum;


int pow(int x) {  // 2의 x승 구하는 함수

	if (x == 0) return 1;
	if (x == 1) return 2;

	long long value = pow(x / 2) % MOD;

	if (x % 2 == 0) {
		return (value * value) % MOD; // 2^2x = 2^x * 2^x
	}
	else {
		return (((value * value) % MOD) * 2) % MOD; // 2^(2x + 1) = 2^x * 2^x * 2
	}
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> block[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i == 0 || block[i - 1][j] == block[i][j])
				&& (i == n - 1 || block[i + 1][j] == block[i][j])
				&& (j == 0 || block[i][j - 1] == block[i][j])
				&& (j == m - 1 || block[i][j + 1] == block[i][j])) {
				cnt++; // 인접한 타일이 모두 같은 색깔로 둘러싸인 타일 개수 구하기
			}
		}
	}

	cout << pow(cnt) << endl;
	return 0;

}