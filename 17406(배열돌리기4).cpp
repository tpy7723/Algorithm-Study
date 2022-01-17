#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

struct node {
	int leftr, leftc, rightr, rightc;
};

int result = 987654321;
int map[51][51], Cmap[51][51];
int N, M, K;
int inputr, inputc, inputs;
vector<node> v;

// ���� ���� �ּ��� ���� ã�� �Լ�
int findvalue() {
	int minvalue = 987654321;
	for (int i = 1; i <= N; i++) {
		int sum = 0;
		for (int j = 1; j <= M; j++) {
			sum += map[i][j];
		}
		minvalue = min(minvalue, sum);
	}
	return minvalue;
}

// �迭 ������
void myrotate(int leftr, int leftc, int rightr, int rightc) {
	while (leftr != rightr) { // �ۿ��� ������
		// ���ϴ� �ϵ��ڵ�
		int temp, temp2;
		//�� (��->��)
		temp = map[leftr][rightc];
		for (int i = rightc; i > leftc; i--) {
			map[leftr][i] = map[leftr][i - 1];
		}
		//�� (��->��)
		temp2 = map[rightr][rightc];
		for (int i = rightr; i > leftr; i--) {
			map[i][rightc] = map[i - 1][rightc];
		}
		map[leftr + 1][rightc] = temp;

		//�� (��->��)
		temp = map[rightr][leftc];
		for (int i = leftc; i < rightc; i++) {
			map[rightr][i] = map[rightr][i + 1];
		}
		map[rightr][rightc - 1] = temp2;

		//�� (��->��)
		for (int i = leftr; i < rightr; i++) {
			map[i][leftc] = map[i + 1][leftc];
		}
		map[rightr - 1][leftc] = temp;

		// �������� �̵�
		leftr++;
		leftc++;
		rightr--;
		rightc--;
	}
}
int main() {
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
	memcpy(Cmap, map, sizeof(map)); // ���� ����

	for (int i = 0; i < K; i++) {
		cin >> inputr >> inputc >> inputs;
		int leftr = inputr - inputs;
		int leftc = inputc - inputs;
		int rightr = inputr + inputs;
		int rightc = inputc + inputs;
		// ��ɵ��� ���Ϳ� ����
		v.push_back({ leftr, leftc, rightr, rightc });
	}

	// ���� ������ ����
	vector<int> p;
	for (int i = 1; i <= K; i++) {
		p.push_back(i);
	}

	do {
		memcpy(map, Cmap, sizeof(Cmap)); // ����
		for (int i = 0; i < p.size(); i++) { // �迭 ������
			myrotate(v[p[i] - 1].leftr, v[p[i] - 1].leftc, v[p[i] - 1].rightr, v[p[i] - 1].rightc);
		}
		result = min(result, findvalue()); // �ּҰ� ����
		
	} while (next_permutation(p.begin(), p.end()));

	cout << result << endl;;
}