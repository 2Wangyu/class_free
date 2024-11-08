//#include<iostream>
//using namespace std;
//#include<cmath>
//#include<vector>
//#include <map>
//#include <algorithm>
//#include <climits>  
//
//static int num = 0;
//static double money = 0;
//
//struct AMGraph {
//	int vertex[1000];
//	double edge[1000][1000];
//	int vertices;
//	int edges;
//};
//
//
//
//double Prim(AMGraph* G, int** arr) {
//	vector<int> unvisit;
//	vector<int> visit;
//	visit.push_back(0);
//	for (int i = 1; i < G->vertices; i++) {
//		unvisit.push_back(i);
//	}
//
//	int minnum = 0;
//	double minpath = 100000;
//
//	for (int i = 1; i < G->vertices; i++) {
//		if (G->edge[0][i] > 0) {
//			if (G->edge[0][i] < minpath) {
//				minnum = i;
//				minpath = G->edge[0][i];
//			}
//		}
//	}
//	unvisit.erase(std::remove(unvisit.begin(), unvisit.end(), minnum), unvisit.end());
//	visit.push_back(minnum);
//
//	double pathlength[1000] = { 0 };
//	pathlength[minnum] = minpath;
//
//	int path[1000];
//	path[minnum] = 0;
//
//	double wipelength = pathlength[minnum];
//
//	int frontfarm = 0;
//	for (int i = 2; i < G->vertices; i++) {
//		double minallpath = INT_MAX;
//
//		for (vector<int>::iterator it1 = visit.begin(); it1 != visit.end(); ++it1) {
//			for (std::vector<int>::iterator it2 = unvisit.begin(); it2 != unvisit.end(); ++it2) {
//				double length = 0;
//				if (G->edge[*it1][*it2] < 0) {
//					continue;
//				}
//				if (*it1 == 0) {
//					length = G->edge[*it1][*it2];
//					if (length < minallpath) {
//						frontfarm = *it1;
//						minallpath = length;
//						minnum = *it2;
//						minpath = G->edge[*it1][*it2];
//					}
//				}
//				else {
//					int temp = *it1;
//					length = G->edge[*it1][*it2];
//			
//					double weight = money;
//					while (temp != 0) {
//						length += pathlength[temp]*weight;
//						temp = path[temp];
//						weight *= money;
//					}
//					if (length < minallpath) {
//						frontfarm = *it1;
//						minallpath = length;
//						minnum = *it2;
//						minpath = G->edge[*it1][*it2];
//					}
//				}
//
//
//			}
//
//		}
//		unvisit.erase(std::remove(unvisit.begin(), unvisit.end(), minnum), unvisit.end());
//		visit.push_back(minnum);
//		pathlength[minnum] = minpath;
//		path[minnum] = frontfarm;
//		wipelength += minallpath;
//
//		
//	}
//	return wipelength;
//}
//
//
//
//
//
//void initedge(AMGraph* G, int** arr) {
//	int tempedge = 0;
//	for (int i = G->vertices - 1; i > 0; i--) {
//
//		tempedge += i;
//	}
//	G->edges = tempedge;
//	for (int i = 0; i <= G->vertices - 1; i++)
//	{
//		G->vertex[i] = i;
//	}
//	for (int i = 0; i < G->vertices - 1; i++) {
//		for (int j = i + 1; j < G->vertices - 1; j++)
//		{
//			int a = abs(arr[i][0] - arr[j][0]);
//			int b = abs(arr[i][1] - arr[j][1]);
//			G->edge[i + 1][j + 1] = sqrt(a * a + b * b);
//			G->edge[j + 1][i + 1] = sqrt(a * a + b * b);
//
//
//		}
//	}
//	
//
//
//}
//double creategraph1(AMGraph* G, int** arr) {
//	G->vertices = num + 1;
//
//	for (int i = 0; i < (G->vertices - 1); i++) {
//		G->edge[0][i + 1] = arr[i][1];
//
//	}
//	initedge(G, arr);
//	return Prim(G, arr);
//
//}
//double creategraph2(AMGraph* G, int** arr) {
//	G->vertices = num + 1;
//	for (int i = 0; i < (G->vertices - 1); i++) {
//		G->edge[0][i + 1] = (arr[i][1] <= arr[i][0] ? arr[i][1] : arr[i][0]);
//		G->edge[i + 1][0] = (arr[i][1] <= arr[i][0] ? arr[i][1] : arr[i][0]);
//
//	}
//	initedge(G, arr);
//	return Prim(G, arr);
//
//}
//
//
//int main() {
//	
//	cin >> num>>money;
//	int** arr = new int* [num];
//	for (int i = 0; i < num; ++i) {
//		arr[i] = new int[2];
//	}
//	for (int i = 0; i < num; i++) {
//		cin >> arr[i][0] >> arr[i][1];
//	}
//
//	AMGraph* G = new AMGraph;
//	cout << creategraph1(G, arr) << endl;
//	cout << creategraph2(G, arr) << endl;
//
//
//}