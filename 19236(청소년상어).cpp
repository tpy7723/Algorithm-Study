#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> map;
vector<vector<int>> swim;
pair<vector<vector<int>>, vector<vector<int>>> p;

int answer = 0;

int dir[9][2] = { {0,0}, {0,-1}, {-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1} }; // 열j, 행i

bool indoor(int i, int j) {
	return (0 <= i && i < 4) && (0 <= j && j < 4);
}

pair<vector<vector<int>>, vector<vector<int>>> Swim(pair<vector<vector<int>>, vector<vector<int>>> p) {
	vector<vector<int>> m = p.first;
	vector<vector<int>> s = p.second;

	// 2. 물고기는 번호가 작은 물고기부터 순서대로 이동한다.
	for (int n = 1; n <= 16; n++) {
		int stop = 0;

		for (int i = 0; i < 4; i++) {
			if (stop == 1) break;
			for (int j = 0; j < 4; j++) {
				if (stop == 1) break;
				if (m[i][j] == n) {
					int next = s[i][j];

					for (int k = 0; k < 7; k++) { // 7번 방향 전환
						int dx = j + dir[next][0];
						int dy = i + dir[next][1];

						if (indoor(dy, dx) && m[dy][dx] >= 0) {
							int temp = m[i][j];
							m[i][j] = m[dy][dx];
							m[dy][dx] = temp;

							s[i][j] = next;
							temp = s[i][j];
							s[i][j] = s[dy][dx];
							s[dy][dx] = temp;

							stop = 1;
							break;
						}

						if (next == 8) {
							next = 1;
						}
						else {
							next++;
						}
					}
				}
			}
		}
	}

	p = make_pair(m, s);

	return p;
}

void Shark(int m, int n, int ans, pair<vector<vector<int>>, vector<vector<int>>> p) {
	// 2. 물고기 이동
	p = Swim(p);

	vector<vector<int>> map = p.first;
	vector<vector<int>> swim = p.second;

	if (answer < ans) { // 최대값 갱신
		answer = ans;
	}

	int next = swim[m][n]; // 이동방향
	
	for (int i = 1; i <= 3; i++) { // 이동할 수 있는 칸 수
		int dx = n + (dir[next][0] * i);
		int dy = m + (dir[next][1] * i);
		
		if (indoor(dy, dx)) {
			if (map[dy][dx] > 0) {
				int temp1 = map[dy][dx];
				int temp2 = map[m][n];
				map[dy][dx] = -1;
				map[m][n] = 0;

				int temp3 = swim[m][n];
				swim[m][n] = 0;

				Shark(dy, dx, ans + temp1, make_pair(map, swim));

				// 원복
				map[dy][dx] = temp1;
				map[m][n] = temp2;

				swim[m][n] = temp3;
			}
		}
		else break;
	}
	return;
}

int main() {
	map.assign(4, vector<int>(4, 0));  // 물고기 번호 4X4
	swim.assign(4, vector<int>(4, 0)); // 방향 4X4

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> map[i][j] >> swim[i][j];
		}
	}

	// 1. 청소년 상어는 (0, 0)에 있는 물고기를 먹고, (0, 0)에 들어가게 된다. 상어의 방향은 (0, 0)에 있던 물고기의 방향과 같다
	answer += map[0][0];
	map[0][0] = -1; // 상어 표시 

	Shark(0, 0, answer, make_pair(map,swim)); // 상어 행, 상어 열, 먹은 물고기 점수합, 물고기번호/방향
	
	cout << answer << endl;

	return 0;
}

