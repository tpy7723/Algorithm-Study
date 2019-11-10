#include <iostream>
#include <algorithm>

using namespace std;

int n;
int score[100001];
int arr[100001];
int max_value;

int dp(int n) {
	if (n == 1) return arr[n] = score[1];

	if (arr[n] != 0) return arr[n];

	if (dp(n - 1) + score[n] > score[n]) { //연속된 합 저장
		arr[n] = dp(n - 1) + score[n];
	}
	else {
		arr[n] = score[n];
	}

	max_value = max(arr[n], max_value);
	return arr[n];
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> score[i];
	}
	max_value = score[1]; // 중요
	dp(n);

	cout << max_value << endl;
	return 0;
}