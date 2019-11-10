#include <iostream>
#include <algorithm>

using namespace std;

int N;
int arr[100];

int findPrimeNumber() {
	int cnt = 0;
	int maxNumber = arr[N - 1]; // 최대값
	for (int i = 2; i <= maxNumber; i++) { // 2부터 최대값까지 나눠 봄
		for (int j = 0; j < N; j++) {
			if (arr[j] == 0 || arr[j] == i) continue; // 지워진 값과 나누는 수를 패스
			if (arr[j] % i == 0 || arr[j] == 1) arr[j] = 0; // 나눠지거나 1인 것은 소수가 아님
		}
	}

	for (int i = 0; i < N; i++) {
		if (arr[i] != 0) cnt++; // 소수 개수 세기
	}

	return cnt;	
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);

	cout << findPrimeNumber() << endl; 

	return 0;
}