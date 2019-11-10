#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>
#include <set>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;

	vector<int> a(N);

	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}

	// 작은 것이 먼저나옴
	priority_queue<long long, vector<long long>, greater<long long>> pq;
	set<long long> s;

	pq.push(1);
	long long maxVal = 0;
	bool finish = false;
	// 가장 작은 값을 꺼내서 배열에 곱함 그리고 다시 pq에 넣음
	while (K--) {
		long long pick = pq.top();
		pq.pop();

		for (int i = 0; i < N; i++) {
			long long npick = pick * a[i];

			// 이거 안하면 메모리 초과
			// k번째를 넘어서는 값이기도 하며 v값이 최댓값을 넘긴다면
			// 최소 힙에서 정답과 무관한 값이 계속들어가게 될 것을 방지하기 위해
			if (pq.size() > K && npick > maxVal)
				break;

			// 중복제거
			if (s.find(npick) == s.end()) {
				maxVal = max(maxVal, npick); // 최댓값
				s.insert(npick);
				pq.push(npick);
			}
		}
	}

	cout << pq.top() << endl;
	return 0;
}