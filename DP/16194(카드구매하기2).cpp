#include <iostream>
#include <algorithm>

using namespace std;

int n;
int P[10001];
int arr[10001];
int max_value;

int dp(int n) {
	if (n == 0) return arr[n] = 0;
	if (n == 1) return arr[n] = P[1];
	if (n == 2) return arr[n] = min(2 * P[1], P[2]);
	if (n == 3) return arr[n] = min(3 * P[1], min(P[3], P[1] + P[2]));

	if (arr[n] != 100000) return arr[n];

	for (int i = 1; i <= n; i++) {
		arr[n] = min(arr[n], dp(n - i) + P[i]);
	}
	return arr[n];
}

int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> P[i];
	}

	for (int i = 1; i <= n; i++) {
		arr[i] = 100000;
	}

	cout << dp(n) << endl;

	return 0;
}