#include <iostream>
#include <algorithm>

using namespace std;

int n;
int stair[10001];
int arr[10001];

int dp(int n) {
	if (n == 1) return stair[1];
	if (n == 2) return stair[1] + stair[2];
	if (n == 3) return max(stair[1] + stair[2] , max(stair[1] + stair[3], stair[2] + stair[3])); // 맨마지막원소 연속 0번선택, 1번선택, 2번선택

	if (arr[n] != 0) return arr[n];

	return arr[n] = max(max(dp(n - 2) + stair[n], dp(n - 3) + stair[n - 1] + stair[n]), dp(n - 1));
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> stair[i];
	}

	cout << dp(n) << endl;
	return 0;
}