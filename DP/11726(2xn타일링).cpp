#include <iostream>

using namespace std;

int arr[1001];

int dp(int x) {
	if (x == 1) return 1;
	if (x == 2) return 2;
	if (arr[x]) return arr[x];
	return arr[x] = (dp(x - 1) + dp(x - 2))%10007;
}

int main() {
	int input;
	cin >> input;
	cout << dp(input);

	return 0;
}