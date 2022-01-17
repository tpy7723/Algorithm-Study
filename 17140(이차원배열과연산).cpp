#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	int n, v; // ����, ����>

	bool operator <(const node &a) const {
		if (v == a.v) { //v �� ���ٸ�
			return n < a.n; // n�� ū�� ũ��
		}
		else return v < a.v; // v �� ū�� ũ��.
	}
};

int r, c, k;
int A[101][101];
int CA[101][101];
int num[101];
int max_r, max_c;
vector<node> v;

void R_search() {
	// ��Ž��
	int count = 0;
	memset(CA, 0, sizeof(CA));
	for (int i = 1; i <= max_r; i++) {
		memset(num, 0, sizeof(num));

		// �ش� ���� ���ڵ��� ī��Ʈ ��
		for (int j = 1; j <= max_c; j++) {
			num[A[i][j]]++;
		}
		// ���ڿ� ������ ���Ϳ� ����
		for (int k = 1; k < 101; k++) {
			if (num[k] != 0) {
				v.push_back({ k,num[k] });
			}
		}
		// ����
		sort(v.begin(), v.end());

		int size_ = v.size();
		count = max(count, size_); // �ִ� ���� ����
		int idx = 1;
		for (int k = 0; k < v.size(); k++) {
			CA[i][idx] = v[k].n;
			CA[i][idx + 1] = v[k].v;
			idx += 2;
		}
		v.clear();
	}

	memcpy(A, CA, sizeof(CA));
	max_c = 2 * count;
}

void C_search() {
	// ��Ž��
	int count = 0;
	memset(CA, 0, sizeof(CA));
	for (int i = 1; i <= max_c; i++) {
		memset(num, 0, sizeof(num));

		for (int j = 1; j <= max_r; j++) {
			num[A[j][i]]++;
		}
		for (int k = 1; k < 101; k++) {
			if (num[k] != 0) {
				v.push_back({ k,num[k] });
			}
		}
		sort(v.begin(), v.end());
		int size_ = v.size();
		count = max(count, size_);
		int idx = 1;
		for (int k = 0; k < v.size(); k++) {
			CA[idx][i] = v[k].n;
			CA[idx + 1][i] = v[k].v;
			idx += 2;
		}
		v.clear();
	}

	memcpy(A, CA, sizeof(CA));
	max_r = 2 * count;
}

// �ش� ĭ�� K ���� Ȯ���ϴ� �Լ�
bool check() {
	return (CA[r][c] == k);
}

int main() {
	cin >> r >> c >> k;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> A[i][j];
		}
	}

	memcpy(CA, A, sizeof(A)); // �迭 ����

	// ���� ��� ���� ����
	max_r = 3;
	max_c = 3;

	int result = 0;

	while (!check()) { // K�� ���ö�����
		result++; // Ƚ��
		if (result > 100) { // 100�� ������ -1 ���
			cout << -1 << endl;
			return 0;
		}
		if (max_r >= max_c) {  // ���ǰ��� >= ���� ����
			R_search(); // R����
		}
		else { // ���ǰ��� <= ���� ����
			C_search(); // C����
		}
	}
			
	cout << result << endl;

	return 0;
}