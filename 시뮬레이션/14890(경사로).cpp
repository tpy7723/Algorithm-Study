#include <iostream>
#include <cstring>
using namespace std;

int N, L;
int map[100][100];
int visit[100];
int result;

void findrow() {
	for (int i = 0; i < N; i++) {
		int cnt = 1; // 평평한 땅 길이
		bool success = true;
		memset(visit, 0, sizeof(visit));

		for (int j = 0; j < N - 1; j++) {
			if (abs(map[i][j] - map[i][j + 1]) > 1) {
				success = false;
				break; // 차이가 1 초과
			}

			if (abs(map[i][j] - map[i][j + 1]) == 0) { // 같은 높이일 경우
				cnt++;
				continue;
			}
			if (map[i][j] - map[i][j + 1] == -1) { // 뒤에 것이 높은 경우
				if (cnt >= L) {
					bool check = true;
					for (int k = 0; k < L; k++) {
						if (visit[j - k] != 0) { // 이미 다리가 있는 경우
							check = false;
							success = false;
							break;
						}
						visit[j - k] = 1; // 다리를 놓음
					}
					if (!check) break; // 이미 다리가 있는 경우
					cnt = 1;
				}
				else {
					success = false;
					break; // 다리를 놓을 공간이 없을 경우
				}
			}
			if (map[i][j] - map[i][j + 1] == 1) { // 앞에 것이 높은 경우
				bool check = true;
				for (int k = 0; k < L; k++) {
					if (map[i][j + 1 + k] != map[i][j + 1]) {
						check = false;
						success = false;
						break;
					}
					visit[j + 1 + k] = 1;
				}
				if (!check) break; // 다리 놓을 공간이 없을 경우
				j += L - 1;
				cnt = 0;
			}
		}

		if (success) result++;
	}
}
void findcol() {
	for (int j = 0; j < N; j++) {
		int cnt = 1; // 평평한 땅 길이
		bool success = true;
		memset(visit, 0, sizeof(visit));

		for (int i = 0; i < N - 1; i++) {
			if (abs(map[i][j] - map[i + 1][j]) > 1) {
				success = false;
				break; // 차이가 1 초과
			}

			if (abs(map[i][j] - map[i + 1][j]) == 0) { // 같은 높이일 경우
				cnt++;
				continue;
			}
			if (map[i][j] - map[i + 1][j] == -1) { // 뒤에 것이 높은 경우
				if (cnt >= L) {
					bool check = true;
					for (int k = 0; k < L; k++) {
						if (visit[i - k] != 0) { // 이미 다리가 있는 경우
							check = false;
							success = false;
							break;
						}
						visit[i - k] = 1; // 다리를 놓음
					}
					if (!check) break; // 이미 다리가 있는 경우
					cnt = 1;
				}
				else {
					success = false;
					break; // 다리를 놓을 공간이 없을 경우
				}
			}
			if (map[i][j] - map[i + 1][j] == 1) { // 앞에 것이 높은 경우
				bool check = true;
				for (int k = 0; k < L; k++) {
					if (map[i + 1 + k][j] != map[i + 1][j]) {
						check = false;
						success = false;
						break;
					}
					visit[i + 1 + k] = 1;
				}
				if (!check) break; // 다리 놓을 공간이 없을 경우
				i += L - 1;
				cnt = 0;
			}
		}
		if (success) result++;
	}
}
int main() {
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	// 행 탐색
	findrow();

	// 열 탐색
	findcol();

	cout << result << endl;
	return 0;
}