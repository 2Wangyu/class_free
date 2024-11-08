//#include <iostream>
//#include <vector>
//#include <queue>
//
//using namespace std;
//
//// 定义节点结构体，包含坐标和步数
//struct Node {
//    int x, y, steps;
//    Node(int _x, int _y, int _steps) : x(_x), y(_y), steps(_steps) {}
//};
//
//int shortestPath(vector<vector<int>>& maze, pair<int, int> start, pair<int, int> destination) {
//    // 定义四个方向的偏移量，分别表示上、下、左、右
//    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
//
//    // 获取迷宫的行数和列数
//    int rows = maze.size();
//    int cols = maze[0].size();
//
//    // 创建一个队列用于BFS
//    queue<Node> q;
//
//    // 将起点加入队列
//    q.push(Node(start.first, start.second, 0));
//
//    // 创建一个二维数组用于记录是否访问过某个位置
//    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
//    visited[start.first][start.second] = true;
//
//    // BFS算法
//    while (!q.empty()) {
//        Node curr = q.front();
//        q.pop();
// 
//        // 判断是否到达终点
//        if (curr.x == destination.first && curr.y == destination.second) {
//            return curr.steps;
//        }
//
//        // 遍历四个方向
//        for (int i = 0; i < 4; ++i) {
//            int nx = curr.x;
//            int ny = curr.y;
//            int steps = curr.steps;
//
//            nx += directions[i][0];
//            ny += directions[i][1];
//            ++steps;
//
//            // 继续沿当前方向移动，直到遇到墙壁或边界
//            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0 && !visited[nx][ny]) {
//                // 如果该位置没有被访问过，加入队列
//                visited[nx][ny] = true;
//                q.push(Node(nx, ny, steps));
//
//            }
//            // 回退一步
//            nx -= directions[i][0];
//            ny -= directions[i][1];
//            --steps;
//        }
//    }
//
//    // 如果队列为空仍未找到终点，说明没有可达路径
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
