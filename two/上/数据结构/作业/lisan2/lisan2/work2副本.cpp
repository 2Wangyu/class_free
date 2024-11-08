//#include<iostream>
//using namespace std;
//#include<string>
//#include<cmath>
//#include<vector>
//#include <map>
//#include <algorithm>
//#include <climits>  
//static int num = 0;
//static int farfar = 0;
//static int farwa = 0;
//
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
//	int pathfarmnum[1000] = { 0 };
//	pathfarmnum[minnum] += 1;
//	int path[1000];
//	path[minnum] = 0;
//
//	int frontfarm = 0;
//	for (int i = 2; i < G->vertices; i++) {
//		double minallpath = INT_MAX;
//
//		for (vector<int>::iterator it1 = visit.begin(); it1 != visit.end(); ++it1) {
//			for (std::vector<int>::iterator it2 = unvisit.begin(); it2 != unvisit.end(); ++it2) {
//				double length = 0;
//				if (G->edge[*it1][*it2] <0) {
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
//					while (temp != 0) {
//						length += pathlength[temp];
//						temp = path[temp];
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
//		pathfarmnum[minnum] += 1;
//		int temp = minnum;
//		while (temp != 0) {
//			temp = path[temp];
//			pathfarmnum[temp] += 1;
//		}
//	}
//
//	double wipelength = 0;
//	for (int i = 1; i < G->vertices; i++) {
//		wipelength += pathfarmnum[i] * pathlength[i];
//	}
//	return wipelength;
//}
//
//void initedge(AMGraph* G, int** arr, int** arrfarfar, bool flag) {
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
//	if (flag == true) {
//		for (int i = 0; i < farfar; i++)
//		{
//			G->edge[arrfarfar[i][0]][arrfarfar[i][1]] = -1;
//			G->edge[arrfarfar[i][1]][arrfarfar[i][0]] = -1;
//		}
//		G->edges = tempedge - farfar - farwa;
//
//	}
//
//
//}
//double creategraph1(AMGraph* G, int** arr, int** arrfarfar, int* arrfarwa) {
//	G->vertices = num + 1;
//
//	for (int i = 0; i < (G->vertices - 1); i++) {
//		G->edge[0][i + 1] = arr[i][1];
//
//	}
//	initedge(G, arr, arrfarfar, false);
//	return Prim(G, arr);
//
//}
//double creategraph2(AMGraph* G, int** arr, int** arrfarfar, int* arrfarwa) {
//	G->vertices = num + 1;
//	for (int i = 0; i < (G->vertices - 1); i++) {
//		G->edge[0][i + 1] = (arr[i][1] <= arr[i][0] ? arr[i][1] : arr[i][0]);
//		G->edge[i + 1][0] = (arr[i][1] <= arr[i][0] ? arr[i][1] : arr[i][0]);
//
//	}
//	initedge(G, arr, arrfarfar, false);
//	return Prim(G, arr);
//
//}
//double creategraph3(AMGraph* G, int** arr, int** arrfarfar, int* arrfarwa) {
//	G->vertices = num + 1;
//	for (int i = 0; i < (G->vertices - 1); i++) {
//		G->edge[0][i + 1] = (arr[i][1] <= arr[i][0] ? arr[i][1] : arr[i][0]);
//		G->edge[i + 1][0] = (arr[i][1] <= arr[i][0] ? arr[i][1] : arr[i][0]);
//
//	}
//	for (int i = 0; i < farwa; i++) {
//		G->edge[0][arrfarwa[i]] = -1;
//		G->edge[arrfarwa[i]][0] = -1;
//	}
//	initedge(G, arr, arrfarfar, true);
//	return Prim(G, arr);
//
//
//}
//
//int main() {
//
//	cin >> num;
//	int** arr = new int* [num];
//	for (int i = 0; i < num; ++i) {
//		arr[i] = new int[2];
//	}
//	for (int i = 0; i < num; i++) {
//		cin >> arr[i][0] >> arr[i][1];
//	}
//
//	cin >> farfar;
//	int** arrfarfar = new int* [farfar];
//	for (int i = 0; i < farfar; ++i) {
//		arrfarfar[i] = new int[2];
//	}
//	for (int i = 0; i < farfar; i++) {
//		cin >> arrfarfar[i][0] >> arrfarfar[i][1];
//	}
//
//
//	cin >> farwa;
//	int* arrfarwa = new int[farwa];
//	for (int i = 0; i < farwa; i++) {
//		cin >> arrfarwa[i];
//	}
//
//	AMGraph* G = new AMGraph;
//	cout << creategraph1(G, arr, arrfarfar, arrfarwa) << endl;
//	cout << creategraph2(G, arr, arrfarfar, arrfarwa) << endl;
//	cout << creategraph3(G, arr, arrfarfar, arrfarwa) << endl;
//
//}