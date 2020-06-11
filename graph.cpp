#include "graph.h"

graph::graph(int x, int y) { //������ 
	this->x = x;
	this->y = y;
	adjGraph = new string * [x];
	for (int i = 0; i < x; i++)
		adjGraph[i] = new string[y];
}


graph::~graph() { //�Ҹ��� 
	for (int i = 0; i < x; i++)
		delete[] adjGraph[i];
	delete[] adjGraph;

}


void graph::addVertex(int x, int y, char item)
{
	string str;
	str += item; //char�� item string������ ��ȯ
	adjGraph[x][y] = str;
}
