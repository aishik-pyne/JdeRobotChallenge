
/* 
 * File:   main.cpp
 * Author: Aishik Pyne
 *
 * Created on 17 March, 2017, 8:09 PM
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <string>
using namespace std;

/*A vector of alive points is maintained
 * since all life/death activity occour around the living cells it's okay to check activity 
 * in the neightbourhood only. It saves a lot of time
 *
 */
typedef struct point {
	int i;
	int j;
	point(int i=0, int j=0) :i(i),j(j) {
	}
}point;

//Initailly reads the PATTERN from the input.txt file
point read(vector< point >& v) {
	fstream file;
	file.open("input.txt", ios::in);
	string row;
	if (!file) {
		cout << "Can't Open File" << endl;
	}
	int r = 0;
	while (file >> row) {
		for (unsigned i = 0; i<row.length(); ++i) {
			if (row.at(i) == 'O') {
				point p(r, i);
				v.push_back(p);
			}
		}
		r++;
	}
	file.close();
	point size(r, row.size());
	return size;
}

//Returns number of alive neightbours
int aliveNeighbours(point p,vector<vector<int>> grid){
    int count=0;
	int rs = max(0, p.i - 1);
	int cs = max(0, p.j - 1);
	int re = min((int)grid.size() -1, p.i + 1);
	int ce = min((int)grid[0].size() - 1, p.j + 1);
    for(int r=rs; r<=re; r++){
        for(int c=cs; c<= ce; c++){
			if (p.i == r && p.j == c)continue;
            if(grid[r][c]==1){
                count++;
            }
        }
    }
    return count;
}

//Checks if the point is already declared alive 
bool newPoint(vector<point> v,point p){
    for(int i=0;i<v.size();i++){
        if(v[i].i==p.i && v[i].j==p.j){
            return false;
        }
    }
    return true;
}

//The iterator function produces the new set of points and repalces the previous one
vector<point> iterate(vector<point> v,vector<vector<int>> grid){
    vector<point> newV;
    for(int i=0;i<v.size();i++){
        int an=aliveNeighbours(v[i],grid);
        if((an==2 || an==3) && newPoint(newV, v[i])){
            newV.push_back(v[i]);
        }
		int rs = max(0, v[i].i - 1);
		int cs = max(0, v[i].j - 1);
		int re = min((int)grid.size() - 1   , v[i].i + 1);
		int ce = min((int)grid[0].size() - 1, v[i].j + 1);
        for(int r=rs;r<=re;r++){
            for(int c=cs;c<=ce;c++){
                point q(r,c);
                an=aliveNeighbours(q,grid);
                if(an==3 && newPoint(newV,q)){
                    newV.push_back(q);
                }
            }
        }
    }
    return newV;
}

//The grid is reset and the new pattern is generated
void renderGrid(vector<vector<int>> &grid,vector<point> livingCells){
    for(int i=0;i!=grid.size();i++)
        fill(grid[i].begin(), grid[i].end(), 0);
    for(int k=0;k<livingCells.size();k++){
        grid[livingCells[k].i][livingCells[k].j]=1;
    }
}

//Rewrites the output.txt file (Crude Logic and Very Slow and large grids)
void displayGrid(vector<vector<int>> grid){
    fstream f;
    f.open("output.txt",ios::out);
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
			if(grid[i][j]==0)
				f<<'.';
			else
				f <<'O';
        }f<<endl;
    }
	f.close();
}
void delay(int seconds)
{
    time_t start, current;

    time(&start);

    do
    {
        time(&current);
    }
    while ((current - start) < seconds);
}
int main() {
    vector<point> livingCells;
	point size=read(livingCells);
    vector< vector<int> > grid(size.i,vector<int>(size.j,0));
    int c=50;//MAX_ITERATIONS (Change to desired value)
    while(c--!=0){
        renderGrid(grid,livingCells);
        displayGrid(grid);

		livingCells = iterate(livingCells, grid);
        cout.flush();
		delay(1);
    }
    return 0;
}

