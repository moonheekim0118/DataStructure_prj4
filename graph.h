#include <cstring>
#include <iostream>
using namespace std;

class pair {
public:
	int parent_x;
	int parent_y;
	//string dir;
	pair() {}
};

class graph {
public:
	int x; //��
	int y; //��
	string** adjGraph; //2�����迭 �����Ҵ�
	graph(int x, int y);
	~graph();
	void addVertex(int x, int y, char item);
};