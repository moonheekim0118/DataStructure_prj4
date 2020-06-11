#include "graph.h"

graph::graph(int x, int y) { //생성자 
	this->x = x;
	this->y = y;
	adjGraph = new string * [x];
	for (int i = 0; i < x; i++)
		adjGraph[i] = new string[y];
}


graph::~graph() { //소멸자 
	for (int i = 0; i < x; i++)
		delete[] adjGraph[i];
	delete[] adjGraph;

}


void graph::addVertex(int x, int y, char item)
{
	string str;
	str += item; //char형 item string형으로 변환
	adjGraph[x][y] = str;
}
