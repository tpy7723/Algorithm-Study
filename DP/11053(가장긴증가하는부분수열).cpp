#include <iostream>
#include <algorithm>

using namespace std;

int n;
int digit[1001];
int dp[1001];
int max_value;

int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> digit[i];
	}

	// 해당 값을 포함하는 경우의 수
	for (int i = 1; i <= n; i++) // 모든 원소 탐색
	{
		int min = 0; // 최소값 초기화
		for (int j = 1; j < i; j++) { 
			if (digit[i] > digit[j]) { // 자기 값이 더 크고
				if (min < dp[j]) // 최소 값보다 더 크면
					min = dp[j];
			}
		}
		dp[i] = min + 1;
	}
	
	for (int i = 1; i <= n; i++) { // dp 중 최대값 저장
		max_value = max(max_value, dp[i]);
	}

	cout << max_value << endl;

	return 0;
}