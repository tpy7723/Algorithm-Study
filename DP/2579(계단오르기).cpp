#include <iostream>
#include <algorithm>
using namespace std;

int num;
int stair[301];
int arr[301];

int dp(int n) {
	if (n == 1) return arr[n] = stair[1];
	if (n == 2) return arr[n] = stair[1] + stair[2];
	if (n == 3) return arr[n] = max(stair[1] + stair[3], stair[2] + stair[3]);

	if (arr[n] != 0) return arr[n];
	return arr[n] = max(dp(n - 2) + stair[n], dp(n - 3) + stair[n] + stair[n - 1]);
}


int main() {
	cin >> num;
	for (int i = 1; i <= num; i++) {
		cin >> stair[i];
	}

	cout << dp(num) << endl;

	return 0;
}