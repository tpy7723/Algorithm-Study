//2차원 dp 문제 longlong 안하니까 틀리네여
// https://www.youtube.com/watch?v=kYoKLm8BZtI&t=862s

#include <iostream>

using namespace std;
long long int d[2][1000001];

long long int dp(int x) {
	d[0][0] = 1;
	d[0][1] = 2;
	d[0][2] = 7;
	d[1][2] = 0;
	for (int i = 3; i <= x; i++) {
		d[1][i] = (d[1][i - 1] + d[0][i - 3]) % 1000000007 ;
		d[0][i] = (3 * d[0][i - 2] + 2 * d[0][i - 1] + 2 * d[1][i]) % 1000000007;
	}
	return d[0][x];
}

int main() {
	int input;
	cin >> input;
	cout << dp(input);

	return 0;
}