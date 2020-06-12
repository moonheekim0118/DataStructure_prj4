#include "graph.h"
#include "queue.h"
/*
to do : is corner 함수 수정
        bfs 중첩 수정 
		record trace 수정  
*/

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

graph::graph(int x, int y) { //생성자 
	this->x = x;
	this->y = y;
	adjGraph = new string * [x];
	wayTrace = new pair_info * [x];
	for (int i = 0; i < x; i++) {
		adjGraph[i] = new string[y];
		wayTrace[i] = new pair_info[y];
	}
	
	
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


string graph::solution(int start_x, int start_y) {
	string ans="";
	int res_x=-1;
	int res_y=-1;
	string answer = "";
	if (bfs(answer,start_x, start_y, &res_x, &res_y, "B")) {
		if(res_x==-1 && res_y==-1) return "Impossible";
		return answer;
	}
	else return "Impossible";
}


bool graph::is_corner(int nx, int ny) { 

	int parent_x = wayTrace[nx][ny].parent_x;
	int parent_y = wayTrace[nx][ny].parent_y; 

	// 박스로의 길이 parent로부터의 one way 일때 
	int cnt = 0;
	if (parent_x != 0 && adjGraph[parent_x - 1][parent_y].compare(".") == 0) cnt++;
	if (parent_x != x-1 && adjGraph[parent_x+1][parent_y].compare(".") == 0) cnt++;
	if (parent_y != 0 && adjGraph[parent_x][parent_y-1].compare(".") == 0) cnt++;
	if (parent_y != y-1 && adjGraph[parent_x][parent_y+1].compare(".") == 0) cnt++;
	if (cnt < 2) return true;
	else return false;
}

string graph::record_trace(int start_x, int start_y, int nx, int ny) {
	string answer = "";
	cout << "start x : " << start_x << " start_y: " << start_y << endl;
	cout << "nx : " << nx << "ny : " << ny << endl;
	int find_x = wayTrace[nx][ny].parent_x;
	int find_y = wayTrace[nx][ny].parent_x;
	cout << " find_x : " << find_x << "   find_y : " << find_y << endl;
	/*do {
		answer.append(wayTrace[find_x][find_y].dir, 0, 1);
		find_x = wayTrace[find_x][find_y].parent_x;
		find_y = wayTrace[find_x][find_y].parent_y;
	} while (find_x != start_x && find_y != start_y);*/
	return answer;
}

bool graph::bfs(string& answer,int start_x, int start_y, int* res_x, int* res_y, string goal) {
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
		if (adjGraph[nx][ny].compare(goal)==0) {
			(*res_x) = nx;
			(*res_y) = ny;
			if (goal.compare("F") == 0) {
				answer.append(record_trace(start_x, start_y, nx, ny)); //F까지의 trace 추가해놓기
				return true; }
			if (goal.compare("T") == 0) { 
				answer.append(record_trace(start_x,start_y,nx,ny)); //T까지의 trace 추가해놓기 
				return true; }
			int x3=-1;
			int y3=-1;
			bool flag=false;
			if (goal.compare("B")==0) {
				answer=record_trace(start_x, start_y, nx, ny); 
				 // B직전 까지의 trace 저장하기 
				flag = bfs(answer,nx, ny, &x3, &y3, "T");
				if (is_corner(nx, ny) == false && flag && (x3 != -1 && y3 != -1)) {
					(*res_x) = x3;
					(*res_y) = y3;
					return true;
				}
				else if(flag==false || x3==-1 || y3==-1) return false;
				adjGraph[x3][y3] = "F";
				goal = "F";
				adjGraph[nx][ny] = ".";
				start_x = wayTrace[nx][ny].parent_x;
				start_x = wayTrace[nx][ny].parent_y;
			}
		}
		if (nx != 0 && adjGraph[nx - 1][ny].compare("#") != 0 && visited[nx - 1][ny] != true) {
			string dir;
			if (goal == "B") dir ="n";
			else dir ="N";
			pair_info p(nx, ny, dir);
			wayTrace[nx - 1][ny] = p;
			set s(nx - 1, ny);
			queue.add(s);
			visited[nx - 1][ny] = true;
		}
		if (ny != 0 && adjGraph[nx][ny-1].compare("#") != 0 && visited[nx][ny-1] != true) {
			string dir;
			if (goal == "B") dir = "w";
			else dir = "W";
			pair_info p(nx, ny, dir);
			wayTrace[nx][ny-1] = p;
			set s(nx, ny-1);
			queue.add(s);
			visited[nx][ny-1] = true;
		}
		if (nx != x-1 && adjGraph[nx +1 ][ny].compare("#")!=0 && visited[nx +1][ny] != true) {
			string dir;
			if (goal == "B") dir = "s";
			else dir = "S";
			pair_info p(nx, ny, dir);
			wayTrace[nx +1][ny] = p;
			set s(nx+1, ny);
			queue.add(s);
			visited[nx+1][ny] = true;
		}
		if (ny!= y-1 && adjGraph[nx][ny+1].compare("#") != 0 && visited[nx][ny+1] != true) {
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
	return false;
}
