// https://blog.naver.com/pasdfq/221332735719

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <functional>

using namespace std;

const int MAX = 250000 + 1;

int N, Q;
vector<pair<int, int>> coord;
vector<int> ySort, xSort;
//{가중치, {a, b}}
priority_queue < pair<int, pair<int, int>>   ,    vector<pair<int, pair<int, int>>>,    greater<pair<int, pair<int, int>>>   > pq; 
int parent[MAX];
bool answer[MAX];

//Union getParent
int getParent(int x) {
	if (parent[x] == x) return x;
	return parent[x] = getParent(parent[x]);
}

void unionParent(int a, int b) {
	a = getParent(a);
	b = getParent(b);
	if (a < b) parent[b] = a;
	else parent[a] = b;
}

bool y_min(int &a, int &b) {
	if (coord[a].first == coord[b].first) // y 값이 같다면
		return coord[a].second < coord[b].second; // x 값이 작은것이 앞으로
	return coord[a].first < coord[b].first; // y 값이 작은것이 앞으로

}

bool x_min(int &a, int &b) {
	if (coord[a].second == coord[b].second) // x 값이 같다면
		return coord[a].first < coord[b].first; // y 값이 작은것이 앞으로
	return coord[a].second < coord[b].second; // x 값이 작은것이 앞으로
}

int main(void){
	cin >> N >> Q;

	//자기 자신을 부모로 지정
	for (int i = 0; i < MAX; i++) {
		parent[i] = i;
	}

	// 체크포인트 입력
	int y, x;
	for (int i = 0; i < N; i++){
		
		cin >> y >> x;

		coord.push_back({ y, x });

		// x좌표 y좌표 따로 저장
		ySort.push_back(i);
		xSort.push_back(i);
	}



	//ySort에 y좌표가 작은 순서대로 인덱스 저장
	sort(ySort.begin(), ySort.end(), y_min);

	//xSort에 x좌표가 작은 순서대로 인덱스 저장
	sort(xSort.begin(), xSort.end(), x_min);

	//우선순위 큐에 간선들을 {가중치, {a, b}} 형태로 집어넣는다
	for (int i = 0; i < N - 1; i++){
		int a = ySort[i];  // 현재 체크포인트 y 좌표를 담고있는 인덱스 
		int b = ySort[i + 1]; // 다음 체크포인트 y 좌표를 담고있는 인덱스
		pq.push({ abs(coord[a].first - coord[b].first), {a, b} }); // y좌표 차이와 인덱스 저장
	}

	for (int i = 0; i < N - 1; i++){
		int a = xSort[i]; // 현재 체크포인트 y 좌표를 담고있는 인덱스 
		int b = xSort[i + 1]; // 다음 체크포인트 x 좌표를 담고있는 인덱스
		pq.push({ abs(coord[a].second - coord[b].second), {a, b} }); // x좌표 차이와 인덱스 저장
	}



	
	
	//쿼리를 {{가중치, {A, B}}, 쿼리의 번호}로 저장
	vector<pair<pair<int, pair<int, int>>, int>> query;

	for (int i = 0; i < Q; i++){
		int a, b, c;
		cin >> a >> b >> c;
		query.push_back({ {c, {a - 1, b - 1}}, i });
	}

	//가중치의 오름차순으로 정렬
	sort(query.begin(), query.end());

	for (int i = 0; i < query.size(); i++){
		pair<int, pair<int, int>> temp = query[i].first;
		int c = temp.first;
		int a = temp.second.first;
		int b = temp.second.second;

		//큐에서 현재 가중치보다 작거나 같은 간선이 있으면
		//꺼내서 합쳐준다
		while (!pq.empty()){
			int curC = pq.top().first;
			if (curC > c)
				break;

			unionParent(pq.top().second.first, pq.top().second.second);
			pq.pop();
		}
		answer[query[i].second] = (getParent(a) == getParent(b));
	}

	for (int i = 0; i < Q; i++)
		if (answer[i])
			cout << "YES\n";
		else
			cout << "NO\n";

	return 0;
}

