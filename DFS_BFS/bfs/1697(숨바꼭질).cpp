#include <iostream>
#include <queue>

using namespace std;

int visit[100001];

bool isindoor(int a) {
	return (0 <= a && a < 100001);
}

void bfs(int subin, int sister) {
	queue<int> q;

	q.push(subin);

	while (!q.empty()) {
		int cur = q.front();

		q.pop();

		if (cur == sister) { // 동생을 찾은 경우
			break;
		}

		else {
			if (isindoor(cur - 1) && visit[cur - 1] == 0) {
				q.push(cur - 1);
				visit[cur - 1] = visit[cur] + 1;
			}

			if (isindoor(cur + 1) && visit[cur + 1] == 0) {
				q.push(cur + 1);
				visit[cur + 1] = visit[cur] + 1;
			}

			if (isindoor(cur * 2) && visit[cur * 2] == 0) {
				q.push(cur * 2);
				visit[cur * 2] = visit[cur] + 1;
			}
		}
	}
}

int main(void) {
	int subin, sister;

	cin >> subin >> sister;

	bfs(subin, sister);

	cout << visit[sister] << " ";

	return 0;
}