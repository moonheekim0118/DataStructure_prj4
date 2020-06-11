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
	int x; //행
	int y; //열
	string** adjGraph; //2차원배열 동적할당
	graph(int x, int y);
	~graph();
	void addVertex(int x, int y, char item);
};