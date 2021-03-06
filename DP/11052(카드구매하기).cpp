#include <iostream>
#include <algorithm>

using namespace std;

int n;
int P[10001];
int arr[10001];
int max_value;

int dp(int n) {
	if (n == 0) return 0;
	if (n == 1) return P[1];
	if (arr[n] != 0) return arr[n];

	for (int i = 1; i <= n; i++) {
		arr[n] = max(arr[n], dp(n - i) + P[i]);
	}
	return arr[n];
}

int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> P[i];
	}

	cout << dp(n) << endl;

	return 0;
}