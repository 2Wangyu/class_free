//#include <iostream>
//#include <vector>
//#include <queue>
//
//using namespace std;
//
//// ����ڵ�ṹ�壬��������Ͳ���
//struct Node {
//    int x, y, steps;
//    Node(int _x, int _y, int _steps) : x(_x), y(_y), steps(_steps) {}
//};
//
//int shortestPath(vector<vector<int>>& maze, pair<int, int> start, pair<int, int> destination) {
//    // �����ĸ������ƫ�������ֱ��ʾ�ϡ��¡�����
//    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
//
//    // ��ȡ�Թ�������������
//    int rows = maze.size();
//    int cols = maze[0].size();
//
//    // ����һ����������BFS
//    queue<Node> q;
//
//    // �����������
//    q.push(Node(start.first, start.second, 0));
//
//    // ����һ����ά�������ڼ�¼�Ƿ���ʹ�ĳ��λ��
//    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
//    visited[start.first][start.second] = true;
//
//    // BFS�㷨
//    while (!q.empty()) {
//        Node curr = q.front();
//        q.pop();
// 
//        // �ж��Ƿ񵽴��յ�
//        if (curr.x == destination.first && curr.y == destination.second) {
//            return curr.steps;
//        }
//
//        // �����ĸ�����
//        for (int i = 0; i < 4; ++i) {
//            int nx = curr.x;
//            int ny = curr.y;
//            int steps = curr.steps;
//
//            nx += directions[i][0];
//            ny += directions[i][1];
//            ++steps;
//
//            // �����ص�ǰ�����ƶ���ֱ������ǽ�ڻ�߽�
//            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0 && !visited[nx][ny]) {
//                // �����λ��û�б����ʹ����������
//                visited[nx][ny] = true;
//                q.push(Node(nx, ny, steps));
//
//            }
//            // ����һ��
//            nx -= directions[i][0];
//            ny -= directions[i][1];
//            --steps;
//        }
//    }
//
//    // �������Ϊ����δ�ҵ��յ㣬˵��û�пɴ�·��
//    return -1;
//
//}
//
//int main() {
//    vector<vector<int>> maze = {
//        {0, 0, 1, 0, 0},
//        {0, 0, 0, 0, 0},
//        {0, 0, 1, 0, 0},
//        {0, 1, 1, 1, 0},
//        {0, 0, 0, 0, 0}
//    };
//
//    pair<int, int> start = make_pair(0, 0);
//    pair<int, int> destination = make_pair(4,4);
//
//    int result = shortestPath(maze, start, destination);
//    cout << "Shortest path length: " << result << endl;
//
//    return 0;
//}
