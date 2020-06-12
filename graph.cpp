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
	if (cnt < 2 && x>=2) return true;
	else return false;
}

string graph::record_trace(int start_x, int start_y, int nx, int ny) {
	string answer = "";
	cout << "start x : " << start_x << " start_y: " << start_y << endl;
	cout << "nx : " << nx << "ny : " << ny << endl;
	int find_x = wayTrace[nx][ny].parent_x;
	int find_y = wayTrace[nx][ny].parent_y;
	answer.append(wayTrace[find_x][find_y].dir, 0, 1);
	cout << answer << endl;
	while (true){
		if ((find_x == start_x && find_y == start_y)) break;
		find_x = wayTrace[find_x][find_y].parent_x;
		find_y = wayTrace[find_x][find_y].parent_y;
		if (find_x >= x || find_x < 0 || find_y >= y || find_y < 0) break;
		answer.append(wayTrace[find_x][find_y].dir);
		cout << wayTrace[find_x][find_y].dir << endl;
	} 

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			cout << wayTrace[i][j].parent_x << " " << wayTrace[i][j].parent_y << endl;
	}
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
		set peek = queue.poll(); //큐에서 꺼내기 
		int nx = peek.x;
		int ny = peek.y;
		if (adjGraph[nx][ny].compare(goal)==0) { //goal 에 도착했다면 
			(*res_x) = nx; //goal 위치 저장 
			(*res_y) = ny;
			if (goal.compare("T") == 0) {  //goal이 T라면 
				(*res_x) = wayTrace[nx][ny].parent_x;
				(*res_y) = wayTrace[nx][ny].parent_y;
				answer.append(record_trace(start_x,start_y,nx,ny)); //T까지의 trace 추가해놓기 
				return true; }
			int x3=-1;
			int y3=-1;
			bool flag=false;
			if (goal.compare("B")==0) { //goal이 B라면 
				answer=record_trace(start_x, start_y, nx, ny); 
				 // B직전 까지의 trace 저장하기
				int px = wayTrace[nx][ny].parent_x;
				int py = wayTrace[nx][ny].parent_y;
				flag = bfs(answer,px, py, &x3, &y3, "T"); // T 찾았는지 ?  찾았다면 True 못찾았다면 False 
				if (is_corner(nx, ny) == false && flag && (x3 != -1 && y3 != -1)) { //코너가 아니고, T를 찾았다면 
					(*res_x) = x3; //T 찾은 위치 저장후 
					(*res_y) = y3;
					return true; //반환 
				}
				else if(flag==false || x3==-1 || y3==-1) return false; // T를 못찾았다면 false 
				adjGraph[x3][y3] = "B"; //그외.. 코너에 몰린 경우 T의 바로 앞자리를 F로 바꾸고, B자리를 '.'으로 바꾸어준다.
				adjGraph[nx][ny] = "#";
				start_x = wayTrace[nx][ny].parent_x; //start지점과 nx ny 자리도 바꾸어준다. 박스를 민 자리로.. 
				start_y = wayTrace[nx][ny].parent_y; //박스를 민 자리는..가지 않는다 .
				nx = start_x;
				ny = start_y;
				
				for (int i = 0; i < x; i++) {
					for (int j = 0; j < y; j++) {
						visited[i][j] = false;
					}
				}
			}
		}
		if (nx != 0 && adjGraph[nx - 1][ny].compare("#") != 0 && visited[nx - 1][ny] != true) {
			//북쪽 
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
		adjGraph[nx][ny] = ".";
	}
	return false;
}
