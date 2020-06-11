#include "graph.h"
#include "queue.h"

pair_info::pair_info(int parent_x, int parent_y, string dir) {
	this->parent_x = parent_x;
	this->parent_y = parent_y;
	this->dir = dir;
}

pair_info::pair_info() {
	parent_x = -1;
	parent_y = -1;
	this->dir = "";
}

graph::graph(int x, int y) { //������ 
	this->x = x;
	this->y = y;
	adjGraph = new string * [x];
	wayTrace = new pair_info * [x];
	for (int i = 0; i < x; i++) {
		adjGraph[i] = new string[y];
		wayTrace[i] = new pair_info[y];
	}
	
	
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


string graph::solution(int start_x, int start_y) {
	string ans="";
	int res_x;
	int res_y;
	bfs(start_x, start_y, res_x,res_y,"B");
	return ans;
}


void graph::bfs(int start_x, int start_y, int& res_x, int& res_y, string goal) {

	bool** visited = new bool * [x];
	for (int i = 0; i < x; i++)
		visited[i] = new bool[y];
	Queue queue;
	set push(start_x, start_y);
	queue.add(push);
	visited[start_x][start_y] = true;
	while (!queue.is_Empty()) {
		set peek = queue.poll();
		int nx = peek.x;
		int ny = peek.y;
		if (adjGraph[nx][ny] == goal) {
			res_x = x;
			res_y = y;
			return;
		}
		if (nx != 0 && adjGraph[nx - 1][ny] != "#" && visited[nx - 1][ny] != true) {
			string dir;
			if (goal == "B") dir = "n";
			else dir = "N";
			pair_info p(nx, ny, dir);
			wayTrace[nx - 1][ny] = p;
			set s(nx - 1, ny);
			queue.add(s);
			visited[nx - 1][ny] = true;
		}
		if (ny != 0 && adjGraph[nx][ny-1] != "#" && visited[nx][ny-1] != true) {
			string dir;
			if (goal == "B") dir = "w";
			else dir = "W";
			pair_info p(nx, ny, dir);
			wayTrace[nx][ny-1] = p;
			set s(nx, ny-1);
			queue.add(s);
			visited[nx][ny-1] = true;
		}
		if (nx != x-1 && adjGraph[nx +1 ][ny] != "#" && visited[nx +1][ny] != true) {
			string dir;
			if (goal == "B") dir = "s";
			else dir = "S";
			pair_info p(nx, ny, dir);
			wayTrace[nx +1][ny] = p;
			set s(nx+1, ny);
			queue.add(s);
			visited[nx+1][ny] = true;
		}
		if (ny!= y-1 && adjGraph[nx][ny+1] != "#" && visited[nx][ny+1] != true) {
			string dir;
			if (goal == "B") dir = "e";
			else dir = "E";
			pair_info p(nx, ny, dir);
			wayTrace[nx][ny+1] = p;
			set s(nx, ny+1);
			queue.add(s);
			visited[nx][ny+1] = true;
		}
	}
}
