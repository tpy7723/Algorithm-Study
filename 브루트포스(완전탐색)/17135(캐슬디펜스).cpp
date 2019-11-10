#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct node {
	int r, c;
};

vector<node> v;
int max_value;
int N, M, D;
int map[16][15];
int Cmap[16][15];
int visit[15];
int arrsize;
int dir[4][2] = { {0,-1}, {-1,0}, {1,0}, {0,1} }; // 왼쪽 위 오른쪽으로 일부러 탐색하게 하였음

// 배열 범위 체크
bool isindoor(int r, int c) {
	return (0 <= r && r < N) && (0 <= c && c < M);
}

// 아래로 한칸씩 이동
void move() {
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < M; j++) {
			map[i + 1][j] = map[i][j];
			if (i == 0) map[i][j] = 0;
		}
	}
}

void bfs(int r, int c) {
	int visit[16][15];
	memset(visit, -1, sizeof(visit)); // 방문 안한 곳은 -1

	queue<node> q;

	q.push({ r,c });
	visit[r][c] = 0; // 궁수

	while (!q.empty()) {
		int curr = q.front().r;
		int curc = q.front().c;

		if (visit[curr][curc] > D) break; // 최대 거리까지만 활을 쏨
		if (map[curr][curc] == 1) { // 현재 위치가 적인 경우 (최소 거리)
			v.push_back({ curr,curc }); // 적의 위치를 벡터에 담음
			break; // 즉시 종료
		}

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextr = curr + dir[i][0];
			int nextc = curc + dir[i][1];

			if (!isindoor(nextr, nextc)) continue;
			if (visit[nextr][nextc] != -1) continue;

			visit[nextr][nextc] = visit[curr][curc] + 1;
			q.push({ nextr, nextc });
		}
	}
}

int check() {
	v.clear(); // 죽인 적의 위치를 저장할 벡터

	for (int i = 0; i < M; i++) { // 궁수 한명에 대해 bfs 돌려서 가장 거리가 짧으면서 왼쪽인 적을 찾음, 죽인 1명의 적의 위치를 벡터에 담음
		if (map[N][i] == 2) {
			bfs(N, i);
		}
	}

	// 아래는 죽인 적의 중복을 처리하기 위함
	int score = 0;
	int tempr = 0;
	int tempc = 0;
	for (int i = 0; i < v.size(); i++) {
		// 이전 값과 비교
		if (tempr == v[i].r && tempc == v[i].c) continue; // 중복 적
		score++; // 점수 더함
		map[v[i].r][v[i].c] = 0; // 적이 사라짐
		tempr = v[i].r;
		tempc = v[i].c;
	}
	return score;
}

int play() {
	int time = N; // 모든행 내려보기
	int result = 0;

	while (time--) { // 모든행 내려보기

		// 모든 적이 죽었을 경우 스톱!
		bool isAllzero = true;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] != 0) {
					isAllzero = false;
					break;
				}
			}
			if (!isAllzero) break;
		}
		if (isAllzero) break;

		result += check(); // 화살을 쏴서 적을 죽이며 점수를 더함
		move(); // 모든 행 한칸씩 아래로 이동
	}

	return result;
}
void dfs(int idx, int cnt) {
	if (cnt == 3) { // 궁수 세명 선택
		memcpy(map, Cmap, sizeof(Cmap)); // 원본 맵을 가지고 해야한다.

		for (int i = 0; i < M; i++) {
			if (visit[i]) {
				map[N][i] = 2; // 궁수 표시
			}
		}
		max_value = max(max_value, play()); // 시뮬레이션하며 최대 값 저장
		return;
	}

	// 백트렉킹을 이용한 조합 mC3
	for (int i = idx; i < M; i++) { // 궁수 위치 정하기
		if (!visit[i]) {
			visit[i] = 1;
			dfs(i + 1, cnt + 1);
			visit[i] = 0;
		}
	}
}

int main() {
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	memcpy(Cmap, map, sizeof(map)); // 원본 맵 저장

	dfs(0, 0);

	cout << max_value << endl;

	return 0;
}