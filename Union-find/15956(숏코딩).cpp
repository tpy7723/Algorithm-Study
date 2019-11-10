#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>

using namespace std;

const int MAX = 1000000;

string input;
int parent[MAX]; // 부모 저장
vector<string> group[MAX];
bool hasNumber[MAX];

// 재귀를 이용하여 부모 찾기
int getParent(int x) {
	if (parent[x] == x) return x;
	return parent[x] = getParent(parent[x]);
}

// 작은 값을 부모로 하여 합침
void unionParent(int a, int b) {
	a = getParent(a);
	b = getParent(b);
	if (a < b) parent[b] = a;
	else parent[a] = b;
}

int main(void) {
	// 부모 배열 초기화
	for (int i = 0; i < MAX; i++) {
		parent[i] = i;
	}

	cin >> input;
	input += "&&";

	map<string, int> str2int; //변수에 임의의 번호
	vector<string> int2str; //번호를 변수로

	vector<pair<int, int>> same; //==으로 연결된 변수
	vector<pair<int, int>> diff; //!=으로 연결된 변수

	string tempS[2]; //파싱중인 절에 들어가는 두 변수를 임의의로 저장

	bool isbackward = 0; //현재 파싱중인 절의 앞/뒤를 표시
	bool isDifferent; //현재 파싱중인 절이 ==인지 !=인지 표시

	for (int i = 0; i < input.size(); i++) {
		//변수 구성 문자
		if (input[i] != '=' &&input[i] != '&' && input[i] != '!') { 
			tempS[isbackward].push_back(input[i]);
		}
		else if (isbackward == 0) { //절의 첫 번째 변수가 완성됐을 경우
			isDifferent = (input[i] == '!');
			isbackward = 1;
			i++; // 두칸 건너뛰는 효과
		}
		else { //절의 두 번째 변수가 완성됬을 경우
			int a, b; // 변수에 해당하는 번호를 찾아내거나 새로 매긴다

			if (str2int.count(tempS[0])) { // 이미 확인한 변수이면
				a = str2int[tempS[0]]; // 해당 변수 인덱스 저장
			}
			else {
				str2int[tempS[0]] = int2str.size(); // 새로운 인덱스 부여
				a = int2str.size(); // 해당 변수 인덱스 저장
				int2str.push_back(tempS[0]); // 해당 인덱스에 변수 저장
			}

			if (str2int.count(tempS[1])) { // 이미 확인한 변수이면
				b = str2int[tempS[1]]; // 해당 변수 인덱스 저장 
			}
			else{
				str2int[tempS[1]] = int2str.size(); // 새로운 인덱스 부여
				b = int2str.size(); // 해당 변수 인덱스 저장
				int2str.push_back(tempS[1]); // 해당 인덱스에 변수 저장
			}

			//==면 same, !=면 diff
			if (isDifferent)
				diff.push_back({ a, b });
			else
				same.push_back({ a, b });
				
			// 변수 초기화
			tempS[0] = tempS[1] = "";
			isbackward = 0;
			i++;
		}
	}

	string answer;

	//==끼리 연결된 컴포턴트끼리 전부 합친다 Union find
	for (int i = 0; i < same.size(); i++) 
		unionParent(same[i].first, same[i].second);

	// 같은 집합끼리 묶어서 group에 저장
	for (int i = 0; i < int2str.size(); i++)
		group[getParent(i)].push_back(int2str[i]);

	//각 그룹을 순회하면서 답을 구성
	for (int i = 0; i < int2str.size(); i++){
		//이 그룹에 상수가 2개 이상 있다면 항상 거짓
		int cntNumber = 0;

		for (int j = 0; j < group[i].size(); j++)
			cntNumber += (isdigit(group[i][j][0]) || (group[i][j][0] == '-'));

		if (cntNumber >= 2){
			cout << "0==1";
			return 0;
		}

		//상수가 있는 절은 나중에 필요하므로 표시
		if (cntNumber == 1)
			hasNumber[i] = true;

		//그룹의 원소가 3 이상이면, 답에 포함되어야 한다
		if (group[i].size() < 2)
			continue;

		//이 그룹에서 가장 길이가 짧은 변수를 찾아낸다
		int minLength = group[i][0].size(), minIdx = 0;
		for (int j = 1; j < group[i].size(); j++){
			if (group[i][j].size() < minLength)	{
				minLength = group[i][j].size();
				minIdx = j;
			}
		}

		string temp = group[i][minIdx];

		for (int j = 0; j < group[i].size(); j++){
			if (j == minIdx)
				continue;
			answer += group[i][j] + "==" + temp + "&&";
		}
		//길이가 가장 짧은 원소는 맨 앞에 놔둔다
		swap(group[i][0], group[i][minIdx]);
	}

	//!=로 연결되는 그룹의 쌍을 저장
	//set을 사용하고 항상 {작은 값, 큰 값}으로 저장하여 중복을 없앤다

	set<pair<int, int>> diffZip;
	for (int i = 0; i < diff.size(); i++){
		int a = getParent(diff[i].first);
		int b = getParent(diff[i].second);

		//같은 그룹끼리 다르다 = 무조건 거짓
		if (a == b){
			cout << "a!=a";
			return 0;
		}

		//둘 다 숫자를 가지고 있으면 다르다고 표시할 필요가 없다
		if (hasNumber[a] && hasNumber[b])
			continue;

		diffZip.insert({ min(a, b), max(a, b) });
	}

	//두 그룹의 가장 짧은 변수를 골라 !=로 연결한다
	for (set<pair<int, int>>::iterator it = diffZip.begin(); it != diffZip.end(); it++){
		answer += group[(*it).first][0] + "!=" + group[(*it).second][0] + "&&";

	}

	//항상 참인 절만 있었다면 답이 비어있을 수 있다
	if (answer.empty()){
		cout << "1==1";

		return 0;
	}

	//불필요하게 들어간 &&를 없애고 출력
	for (int i = 0; i < 2; i++)
		answer.pop_back();

	cout << answer << "\n";

	return 0;
}