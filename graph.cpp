#include "graph.h"
#include "queue.h"
/*
to do : is corner �Լ� ����
        bfs ��ø ���� 
		record trace ����  
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

	// �ڽ����� ���� parent�κ����� one way �϶� 
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
		set peek = queue.poll(); //ť���� ������ 
		int nx = peek.x;
		int ny = peek.y;
		if (adjGraph[nx][ny].compare(goal)==0) { //goal �� �����ߴٸ� 
			(*res_x) = nx; //goal ��ġ ���� 
			(*res_y) = ny;
			if (goal.compare("T") == 0) {  //goal�� T��� 
				(*res_x) = wayTrace[nx][ny].parent_x;
				(*res_y) = wayTrace[nx][ny].parent_y;
				answer.append(record_trace(start_x,start_y,nx,ny)); //T������ trace �߰��س��� 
				return true; }
			int x3=-1;
			int y3=-1;
			bool flag=false;
			if (goal.compare("B")==0) { //goal�� B��� 
				answer=record_trace(start_x, start_y, nx, ny); 
				 // B���� ������ trace �����ϱ�
				int px = wayTrace[nx][ny].parent_x;
				int py = wayTrace[nx][ny].parent_y;
				flag = bfs(answer,px, py, &x3, &y3, "T"); // T ã�Ҵ��� ?  ã�Ҵٸ� True ��ã�Ҵٸ� False 
				if (is_corner(nx, ny) == false && flag && (x3 != -1 && y3 != -1)) { //�ڳʰ� �ƴϰ�, T�� ã�Ҵٸ� 
					(*res_x) = x3; //T ã�� ��ġ ������ 
					(*res_y) = y3;
					return true; //��ȯ 
				}
				else if(flag==false || x3==-1 || y3==-1) return false; // T�� ��ã�Ҵٸ� false 
				adjGraph[x3][y3] = "B"; //�׿�.. �ڳʿ� ���� ��� T�� �ٷ� ���ڸ��� F�� �ٲٰ�, B�ڸ��� '.'���� �ٲپ��ش�.
				adjGraph[nx][ny] = "#";
				start_x = wayTrace[nx][ny].parent_x; //start������ nx ny �ڸ��� �ٲپ��ش�. �ڽ��� �� �ڸ���.. 
				start_y = wayTrace[nx][ny].parent_y; //�ڽ��� �� �ڸ���..���� �ʴ´� .
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
			//���� 
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
