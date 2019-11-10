#include <iostream>

using namespace std;

int arr[31];

int dp(int x) {
	if (x == 0) return 1; // 아무것도안하는 경우 1가지
	if (x == 1) return 0;
	if (x == 2) return 3;
	if (arr[x]) return arr[x];

	int result = 3 * dp(x - 2);
	for (int i = 3; i <= x; i++) {
		if (i % 2 == 0) {
			result += 2 * dp(x - i);
		}
	}
	return arr[x] = result;
}


int main() {
	int input;
	cin >> input;
	cout << dp(input);

	return 0;
}