//#include<iostream>
//using namespace std;
//#include<string>
//#include<cmath>
//
//static int num = 0;
//
//
//struct AMGraph {
//	int vertex[1000];
//	double edge[1000][1000];
//    int vertices ;
//	int edges;
//};
//
//struct Eset {
//	int start;
//	int end;
//	double weight;
//
//};
//void InitEset(Eset* E, AMGraph* G) {
//	int k = 0;
//	//因为是无向矩阵，所以遍历上三角就可以了
//	for (int i = 0; i < G->vertices; ++i) {
//		for (int j = i + 1; j < G->vertices; ++j) {
//			if (G->edge[i][j] > 0) {
//				E[k].start = i;
//				E[k].end = j;
//				E[k].weight = G->edge[i][j];
//				k++;
//			}
//		}
//	}
//
//}
////冒泡排序
//void Sort_Eset(Eset* E, int length) {
//	bool flag = true;
//	for (int i = 0; i < length - 1 && flag; i++) {//如果没有发生交换则代表有序
//		flag = false;
//		for (int var = 0; var < length - 1; ++var) {
//			if (E[var].weight > E[var + 1].weight) {
//				flag = true;
//				Eset temp = E[var];
//				E[var] = E[var + 1];
//				E[var + 1] = temp;
//			}
//		}
//	}
//}
//
//void Krusal(AMGraph* G,bool flag,int **arr) {
//	Eset* E = new Eset[G->edges];
//	InitEset(E, G);
//	Sort_Eset(E, G->edges);
//
//	//此时E图中的边为升序
//	//建立V集合存放连通依赖点
//	int V[1000];
//	for (int var = 0; var < G->vertices; ++var) {
//		V[var] = var;
//	}//先假设每一个独立点都为自己的连通依赖点，即所有点不相互邻接
//
//	
//	double length = 0;
//
//	if (flag == true) {
//		//找到各自所属的连通分量所代表的编号
//		int component1 = V[arr[0][0]];
//		int component2 = V[arr[0][1]];
//		V[arr[0][1]] = component1;
//		length += G->edge[arr[0][0]][arr[0][1]];	
//	}
//	//依据边的信息，把点连接起来
//	for (int var = 0; var < G->edges; ++var) {
//		//找到边的两端
//		int v1 = E[var].start;
//		int v2 = E[var].end;
//
//		//找到各自所属的连通分量所代表的编号
//		int component1 = V[v1];
//		int component2 = V[v2];
//		//如果不相等，则可以连接起来
//		if (component1 != component2) {
//			//找到v2连通分量的所有点，将它的编号与v1相同
//			for (int var = 0; var < G->vertices; ++var) {
//				if (V[var] == component2) {
//					V[var] = component1;
//				}
//			}
//			length += E[var].weight;
//		}
//	}
//	delete[]E;
//	cout << length << endl;
//
//}
//
//void initedge(AMGraph* G,int **arr) {
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
//	for (int i = 1; i < G->vertices; i++) {
//		for (int j = i + 1; j < G->vertices; j++)
//		{
//			int a = abs(arr[i][0] - arr[j][0]);
//			int b = abs(arr[i][1] - arr[j][1]);
//			G->edge[i][j] = sqrt(a * a + b * b);
//
//			//
//			//cout << G->edge[i][j]<<endl;
//
//		}
//	}
//}
//void creategraph1(AMGraph *G,int **arr) {
//	G->vertices = num + 1;
//	
//	for (int i = 1; i <=( G->vertices-1); i++) {
//		G->edge[0][i] = arr[i][1];
//
//		//
//		//cout << G->edge[0][i]<<endl;
//	}
//	initedge(G,arr);
//	Krusal(G,false,arr);
//
//}
//void creategraph2(AMGraph* G, int** arr) {
//	G->vertices = num + 1;
//	for (int i = 1; i <= (G->vertices - 1); i++) {
//		G->edge[0][i] = (arr[i][1] <= arr[i][0] ? arr[i][1] :arr[i][0]) ;
//
//		//
//		//cout << G->edge[0][i]<<endl;
//	}
//	initedge(G, arr);
//	Krusal(G,false,arr);
//
//
//
//}
//void creategraph3(AMGraph* G, int** arr) {
//	G->vertices = num + 1;
//	for (int i = 1; i <= (G->vertices - 1); i++) {
//		G->edge[0][i] = (arr[i][1] <= arr[i][0] ? arr[i][1] : arr[i][0]);
//
//		//
//		//cout << G->edge[0][i]<<endl;
//	}
//	initedge(G, arr);
//	Krusal(G, true, arr);
//
//
//}
//
//int main() {
//	
//	cin >> num;
//	cout << endl;
//	int** arr = new int* [num+1];
//	for (int i = 0; i <= num; ++i) {
//		arr[i] = new int[2];
//	}
//	for (int i = 1; i <= num; i++) {
//	
//		cin >> arr[i][0] >> arr[i][1];
//
//	}
//	cout << endl;
//	cin >> arr[0][0] >> arr[0][1];
//	cout << endl;
//
//	AMGraph *G = new AMGraph;
//	creategraph1(G,arr);
//	creategraph2(G,arr);
//	creategraph3(G,arr);
//
//
//
//}