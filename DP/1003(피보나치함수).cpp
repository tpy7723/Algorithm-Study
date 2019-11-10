#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;



pair<int, int> dp[41] = {};

int cnt[2];

pair<int, int> fibonacci(int n) {
	if (n == 0) {
		return dp[0] = make_pair(1, 0); // 0의 개수 1의 개수
	}
	else if (n == 1) {
		return dp[1] = make_pair(0, 1);
	}
	else if (dp[n] != make_pair(0,0)) {
		return dp[n];
	}
	else {
		return dp[n] =make_pair(fibonacci(n - 1).first + fibonacci(n - 2).first, fibonacci(n - 1).second + fibonacci(n - 2).second);
	}
}

int main() {
	int t, input;
	cin >> t;

	while (t--) {
		cin >> input;
		
		cout << fibonacci(input).first << " " << fibonacci(input).second << endl;
		memset(cnt, 0, sizeof(cnt));
	}


	return 0;
}