#include "graph.h"
#include <iostream>
using namespace std;
/*
 미로 찾기 게임
*/

int main()
{
    int r;
    int c;
    int mazeNum = 0;
    do {

        cin >> r;
        cin >> c;
        if (r == 0 && c == 0) break;
        graph  maze(r, c); //그래프 생성
        string str;
        int start_x = 0;
        int start_y = 0;
        for (int i = 0; i < r; i++) {
            cin >> str;
            for (int j = 0; j < c; j++) {
                maze.addVertex(i, j, str.at(j));
                if (str.at(j) == 'S') {
                    start_x = i;
                    start_y = j;
                }
            }
        }
        ++mazeNum;
        string ans;
        ans=maze.solution(start_x,start_y);
        cout << ans << endl;
        cout << "Maze #" << mazeNum << endl;
    } while (r != 0 && c != 0);
}