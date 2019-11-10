#include <iostream>
#include <queue>

using namespace std;

const int MAX = 100000 + 1;

int N, T;
int A[MAX];
int copyA[MAX];
int result[MAX];

// 이분 탐색을 진행하며 T번의 변경 안에 모든 인접한 숫자의 차가 mid 이하이면 true 아니라면 false를 반환하는 possible 함수
// 인접한 숫자가 간격이 diff이하로 만들수 있는지
bool possible(int diff) {
	for (int i = 0; i < N; i++)
		copyA[i] = A[i];

	int cnt = 0;

	//인접한 오른쪽 체크
	for (int i = 0; i < N - 1; i++)
		if (copyA[i + 1] - copyA[i] > diff) {
			cnt += copyA[i + 1] - (copyA[i] + diff); // diff 만큼 차이나도록 바꿀 떄 필요한 찌르는 횟수
			copyA[i + 1] = copyA[i] + diff; // diff 만큼 차이나도록 바꾼다.
		}

	//인접한 왼쪽 체크
	for (int i = N - 1; i > 0; i--)
		if (copyA[i - 1] - copyA[i] > diff) {
			cnt += copyA[i - 1] - (copyA[i] + diff);
			copyA[i - 1] = copyA[i] + diff;
		}

	//변경 횟수가 T 이하인가 체크
	if (cnt <= T)
		return true;
	else 
		return false;
}

int main(void) {
	cin >> N >> T;

	for (int i = 0; i < N; i++) cin >> A[i];

	int low = 0, high = MAX;

	// 이분 탐색
	while (low <= high){
		int mid = (low + high) / 2;

		if (possible(mid))	{
			for (int i = 0; i < N; i++) {
				result[i] = copyA[i];
			}
			high = mid - 1;
		}
		else
			low = mid + 1;
	}

	for (int i = 0; i < N; i++)
		cout << result[i] << " ";

	return 0;
}

