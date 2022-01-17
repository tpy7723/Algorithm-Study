#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
int minN, maxN;
int answer = 0;
int dir[4][2] = { {0,-1},{0,1} ,{-1,0} ,{1,0} };
vector<vector<int>> v;
vector<vector<int>> dist;

bool indoor(int i, int j) {
	return (1 <= i && i <= N) && (1 <= j && j <= N);
}

void OneLine() {
	//4. 일렬로 정렬 
	int a = 1;
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			if (v[i][j] != 10001) {
				v[1][a++] = v[i][j];
			}
		}
	}

	for (int i = 2; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			v[i][j] = 10001;
		}
	}
}

void Rotation() {
	// 5. 공중 부양 작업을 해야 한다. 이번에는 가운데를 중심으로 왼쪽 N/2개를 공중 부양시켜 전체를 시계 방향으로 180도 회전 시킨 다음
		//, 오른쪽 N/2개의 위에 놓아야 한다. 이 작업은 두 번 반복해야한다. 
	int count = N / 2;
	for (int i = 0; i < N / 2; i++) {
		v[2][count + 1] = v[1][N - count];
		v[1][N - count] = 10001;
		count++;
	}

	count = N - (N / 4);
	for (int i = 0; i < N / 4; i++) {
		v[3][count + 1] = v[2][N - count + (N / 2)];
		v[2][N - count + (N / 2)] = 10001;

		v[4][count + 1] = v[1][N - count + (N / 2)];
		v[1][N - count + (N / 2)] = 10001;
		count++;
	}
}

bool Check() {
	// 8. 물고기가 가장 많이 들어있는 어항과 가장 적게 들어있는 어항의 물고기 수 차이가 K 이하인지 체크
	minN = 10001;
	maxN = -1;
	for (int i = 1; i <= N; i++) {
		if (maxN < v[1][i]) {
			maxN = v[1][i];
		}
		if (minN > v[1][i]) {
			minN = v[1][i];
		}
	}

	return abs(maxN - minN) <= K;
}
void Arrange() {
	// 3. 물고기 수 조절.  모든 인접한 두 어항에 대해서, 물고기 수의 차이를 구한다. 차이를 5로 나눈 몫을 d. d가 0보다 크면, 
	// 두 어항 중 물고기의 수가 많은 곳에 있는 물고기 d 마리를 적은 곳에 있는 곳으로 보낸다.
	dist.assign(101, vector<int>(101, 0));   // 0으로 초기화된 101X101
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (v[i][j] != 10001) {

				for (int k = 0; k < 4; k++) {
					int dx = i + dir[k][0];
					int dy = j + dir[k][1];

					if (v[dx][dy] != 10001 && indoor(dx, dy)) {
						dist[i][j] += ((v[dx][dy] - v[i][j]) / 5);
					}
				}

			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			v[i][j] += dist[i][j];
		}
	}
}

void Add() {
	// 1. 물고기의 수가 가장 적은 어항에 물고기를 한 마리 넣는다.  만약, 그러한 어항이 여러개라면 물고기의 수가 최소인 어항 모두에 한 마리씩 넣는다.
	minN = *min_element(v[1].begin(), v[1].end());

	for (int i = 1; i <= N; i++) {
		if (v[1][i] == minN) {
			v[1][i]++;
		}
	}
}

void FishRotation() {
	// 2-1. 맨 왼쪽 어항을 왼쪽 두번째 어항에 쌓기
	v[2][2] = v[1][1];
	v[1][1] = 10001;

	// 2-2. 2개 이상 쌓여있는 어항을 모두 공중 부양시킨 다음, 전체를 반시계방향으로 90도 회전시킨다. (반복)

	int stop_flag = 0;
	while (1) {
		for (int i = N; i >= 1; i--) { // 2칸이상인 라인 찾기
			if (v[2][i] != 10001) {
				int col = i;
				int row = 1;
				int temp = 2;
				for (int j = 1; j <= N; j++) {
					if (v[j][i] == 10001) {
						row = j - 1; // 최대 높이
						break;
					}
				}

				//공중 부양시킨 어항 중 가장 오른쪽에 있는 어항의 아래에 바닥에 있는 어항이 있을때까지 반복
				if (N - i < row) {
					stop_flag = 1;
					break;
				}

				for (int k = col; k >= 1; k--) {
					if (v[1][k] == 10001) break;
					int temp2 = col + 1;
					for (int m = 1; m <= row; m++) {
						v[temp][temp2++] = v[m][k];
						v[m][k] = 10001;
					}
					temp++;
				}
				break;
			}
		}
		if (stop_flag) break;
	}
}

int main() {
	v.assign(101, vector<int>(101, 10001));   // 10001으로 초기화된 101X101

	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		cin >> v[1][i];
	}
	
	while (1) {
		answer++;
			
		// 1. 물고기 추가
		Add();

		// 2. 물고기 회전
		FishRotation();

		// 3. 물고기 수 조절
		Arrange();

		// 4. 일렬로 정렬 
		OneLine();

		// 5. 공중 부양 작업
		Rotation();
		
		// 6. 물고기 수 조절
		Arrange();			

		// 7. 일렬로 정렬
		OneLine();

		// 8. 물고기 수 체크
		if (Check()) break;

	}

	cout << answer << endl;
}
