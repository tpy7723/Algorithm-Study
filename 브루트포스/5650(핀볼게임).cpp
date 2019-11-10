#include <iostream>
#include <algorithm>
#include <vector>

#define endl "\n"

using namespace std;
struct node {
	int r, c;
};
int T, N, tc;
bool done = true;
vector<node> v[11];
int initial_r, initial_c;
int map[101][101];
int ball_r = 0, ball_c = 4, ball_d = 0; // 공의 정보
int max_value = 0;
int score;

int dir[4][2] = {
	{-1,0},{1,0},{0,-1},{0,1} // 0 1 2 3 상하좌우
};

bool isindoor(int y, int x) {
	return (0 <= y && y < N) && (0 <= x && x < N);
}

int block[5][4] = { // 각 블록을 맞고 튕기는 방향
	{1,3,0,2},{3,0,1,2},{2,0,3,1},{1,2,3,0},{1,0,3,2}
};

// 벽맞고 튕기는 방향
int wall[4] = {
	1,0,3,2
};

void sliding() {
	// 상하
	if (ball_d < 2) {
		do {
			ball_r += dir[ball_d][0];
			// 초기위치가 되면 종료
			if (ball_r == initial_r && ball_c == initial_c) {
				done = false;
				break;
			}
			//벽 맞고 튕겨 반대방향으로 감
			if (!isindoor(ball_r, ball_c)) {
				ball_r -= dir[ball_d][0];
				ball_d = wall[ball_d];
				score++;

				break;
			}
		} while (map[ball_r][ball_c] == 0);
	}
	// 좌우
	else {
		do {
			ball_c += dir[ball_d][1];
			if (ball_r == initial_r && ball_c == initial_c) {
				done = false;
				break;
			}
			if (!isindoor(ball_r, ball_c)) {
				ball_c -= dir[ball_d][1];
				ball_d = wall[ball_d];
				score++;

				break;
			}
		} while (map[ball_r][ball_c] == 0);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	cin >> T;
	tc = 1;
	while (T--) {
		cin >> N;

		v->clear();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				//빈 공간 저장
				if (map[i][j] == 0) {
					v[0].push_back({ i,j });
				}
				//웜홀 짝 지어서 저장
				if (6 <= map[i][j] && map[i][j] <= 10) {
					v[map[i][j]].push_back({ i,j });
				}
			}
		}

		max_value = 0;

		// 공을 빈 공간에 넣어봄 (완탐)
		for (int i = 0; i < v[0].size(); i++) {
			//볼 위치
			ball_r = v[0][i].r;
			ball_c = v[0][i].c;

			//초기위치 저장 
			initial_r = ball_r;
			initial_c = ball_c;

			int hollnum = 0, temp_r = 0, temp_c = 0, temp_d = 0;

			for (int d = 0; d < 4; d++) { // 출발 네 방향(완탐)
				//초기위치에서 시작
				ball_r = initial_r;
				ball_c = initial_c;
				ball_d = d;

				score = 0;
				done = true;

				while (done) {
					// 이동
					sliding();
					if (!done) break;
					switch (map[ball_r][ball_c])
					{
					case -1: // 블랙홀 들어감
						//종료조건
						done = false;
						break;
					case 0:
						//종료조건
						// 초기위치로 돌아감
						if (ball_r == initial_r && ball_c == initial_c) {
							done = false;
						}
						break;
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
						//블록
						//볼이 튕겨나와서 방향 바뀜
						ball_d = block[map[ball_r][ball_c] - 1][ball_d];
						score++;
						break;
					case 6:
					case 7:
					case 8:
					case 9:
					case 10:
						//웜홀
						hollnum = map[ball_r][ball_c];
						//순간이동
						for (int i = 0; i < 2; i++) {
							if (v[hollnum][i].r == ball_r && v[hollnum][i].c == ball_c) continue;
							temp_r = v[hollnum][i].r;
							temp_c = v[hollnum][i].c;
						}
						ball_r = temp_r;
						ball_c = temp_c;
						break;
					default:
						break;
					}
				}

				// 최대 점수 저장
				max_value = max(max_value, score);
			}
		}

		cout << "#" << tc++ << " " << max_value << endl;
	}

	return 0;
}