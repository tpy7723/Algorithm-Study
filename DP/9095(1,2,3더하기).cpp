#include <iostream>

using namespace std;

int n;
int arr[11];

int dp(int n) {
	if (n == 1) return 1;
	if (n == 2) return 2;
	if (n == 3) return 4;
	if (arr[n] != 0) return arr[n];
	return arr[n] = dp(n - 3) + dp(n - 2) + dp(n - 1);
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		cout << dp(n) << endl;
	}
	return 0;
}