/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   main.cpp
* Author: aquilla-ubuntu
*
* Created on 11 March, 2017, 11:58 AM
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

/*Author :Aishik Pyne
* Date  :11th March 2017
*/
typedef struct point {
	int i;
	int j;
	point(int i=0, int j=0) :i(i),j(j) {
	}
}point;


void read(vector< vector<int> >& map) {

	fstream file;
	file.open("input.txt",ios::in);
	string row;
	if (!file) {
		cout << "Can't Open File" << endl;
	}
	while (file>>row) {
		vector<int> v;
  		for (unsigned i=0; i<row.length(); ++i)
  		{
			if (row.at(i) == '#') {				
				v.push_back(0);
			}
			else if (row.at(i) == '.') {
				v.push_back(1);
			}
		}
		map.push_back(v);
	}
	file.close();
}


int bfs(vector<vector<int> >& map, vector<vector<int> >& path, point start) {
	queue<point> q;
	queue<int> count;
	int max_count = 0;
	q.push(start);
	count.push(0);
	while (!q.empty()) {
		point temp = q.front();q.pop();
		int count_temp = count.front();   count.pop();
		if (count_temp>max_count)max_count = count_temp;
		map[temp.i][temp.j] = 0;//VISITING THE POINT
		path[temp.i][temp.j] = count_temp;

		//LOOK DOWN
		if (temp.i - 1 >= 0) {
			if (map[temp.i - 1][temp.j] == 1) {
				point p;
				p.i = temp.i - 1;
				p.j = temp.j;
				q.push(p);
				count.push(count_temp + 1);
			}
		}		
		//LOOK RIGHT
		if (temp.j + 1 < map[temp.i].size()) {
			if (map[temp.i][temp.j + 1] == 1) {
				point p;
				p.i = temp.i;
				p.j = temp.j + 1;
				q.push(p);
				count.push(count_temp + 1);
			}
		}
		//LOOK LEFT
		if (temp.j - 1 > 0) {
			if (map[temp.i][temp.j - 1] == 1) {
				point p;
				p.i = temp.i;
				p.j = temp.j - 1;
				q.push(p);
				count.push(count_temp + 1);
			}
		}		
		//LOOK UP
		if (temp.i + 1 < map.size()) {
			if (map[temp.i + 1][temp.j] == 1) {
				point p;
				p.i = temp.i + 1;
				p.j = temp.j;
				q.push(p);
				count.push(count_temp + 1);
			}
		}
		
	}
	return max_count;
}


void reset_path(vector<vector<int> >& path) 	{
	for(int i=0;i!=path.size();i++)
		fill(path[i].begin(), path[i].end(), 0);
}


int main() {
	vector<vector<int> > Map;
	read(Map);
	int rows = Map.size();
	int cols = Map[0].size();
	vector<vector<int> > Path(rows, vector<int>(cols,0) );
	vector<vector<int> > Max_Path(rows, vector<int>(cols, 0));int max_count=0;
	point Max_Point;
	vector<vector<int> > Copy_Map = Map;
	
	for (int i = 0;i!=Map.size();i++) {
		for (int j = 0;j!=Map[i].size();j++) {
			if (Map[i][j] == 1) {
				reset_path(Path);
				point p(i,j);
				int count = bfs(Map, Path, p);

				if (count > max_count) {
					max_count = count;
					Max_Path = Path;
					Max_Point = p;
					/*for (int k = 0;k != Path.size();k++) {
						for (int l = 0;l != Path[k].size();l++) {
							Max_Path[k][l] = Path[k][l];
						}
					}*/					
				}
			}
		}
	}
	for (int k = 0;k != Path.size();k++) {
		for (int l = 0;l != Path[k].size();l++) {
			if (Max_Point.i == k && Max_Point.j == l) {
				cout << 0 << " ";
			}
			else if (Max_Path[k][l] > 0) {
				cout << Max_Path[k][l] << " ";
			}
			else {
				 (Copy_Map[k][l] == 0) ? cout << '#' << " " : cout << '.' << " ";
			}

		}cout << endl;
	}
    cout<<"Press Enter key to exit..."<<endl;
	getchar();
	return 0;
}


