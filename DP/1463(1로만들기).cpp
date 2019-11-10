#include <iostream>

using namespace std;

int n;
int arr[1000001];

int dp(int n) {
	if (n == 1) return 0;
	if (n == 2) return 1;
	if (n == 3) return 1;
	if (arr[n] != 0) return arr[n];

	if (n % 3 == 0) {
		if ((dp(n - 1) + 1) <= (dp(n / 3) + 1)) {
			return arr[n] = dp(n - 1) + 1;
		}
		else {
			return arr[n] = dp(n / 3) + 1;
		}
	}
	else if (n % 2 == 0) {
		if ((dp(n - 1) + 1) <= (dp(n / 2) + 1)) {
			return arr[n] = dp(n - 1) + 1;
		}
		else {
			return arr[n] = dp(n / 2) + 1;
		}
	}
	else {
		return arr[n] = dp(n - 1) + 1;
	}
}

int main() {

	cin >> n;
	cout << dp(n) << endl;
	return 0;
}