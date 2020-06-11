#include <cstring>
#include <iostream>
using namespace std;

class pair_info {
public:
	int parent_x;
	int parent_y;
	string dir;
	pair_info(int parent_x, int parent_y, string dir);
	pair_info();
};

class graph {
public:
	int x; //��
	int y; //��
	string** adjGraph; //2�����迭 �����Ҵ�
	pair_info** wayTrace;
	graph(int x, int y);
	~graph();
	void addVertex(int x, int y, char item);
	string solution(int start_x , int start_y);
	void bfs(int start_x, int start_y , int&res_x, int&res_y, string goal);
};