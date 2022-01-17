#include <iostream>
#include <deque>
#include <vector>

#define endl "\n"

using namespace std;

struct node {
	int r, c;
};

struct change {
	int t, r;
};

int N, K;
int tr, tc;
int tn;
int t;
char r;
int time;
int result;
int d; // 0123 �����»�
int dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
int curr = 1, curc = 1; // ��Ӹ���ġ
int map[101][101];
vector<change> v;
deque<node> snake;

bool isindoor(int r, int c) {
	return (1 <= r && r <= N) && (1 <= c && c <= N);
}

int main() {
	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> tr >> tc;
		map[tr][tc] = 1; // ��� ��ġ
	}
	cin >> tn;
	for (int i = 0; i < tn; i++) {
		cin >> t >> r;
		v.push_back({ t,r });
	}

	map[1][1] = 2; // ����ġ
	snake.push_back({ 1,1 });

	time = -1;
	while (1) {
		time++;
		// ���� ��ȯ
		for (int i = 0; i < v.size(); i++) {
			if (time == v[i].t) {
				if (v[i].r == 'D') {
					d = (d + 1) % 4;
				}
				else if (v[i].r == 'L') {
					d = (d + 3) % 4; // �߿�
				}
			}
		}
		curr += dir[d][0];
		curc += dir[d][1];
		if (!isindoor(curr, curc)) break; // ��
		if (map[curr][curc] == 2) break; // ��

		snake.push_back({ curr, curc }); // �� �Ӹ� �߰�

		if (map[curr][curc] == 0) {
			int temp_r = snake.front().r;
			int temp_c = snake.front().c;
			snake.pop_front(); // �����κ� ����
			map[temp_r][temp_c] = 0; // �����κ� ����
		}
		map[curr][curc] = 2; // ���� �ִ� �� ǥ��
	}

	cout << time + 1;
	return 0;
}