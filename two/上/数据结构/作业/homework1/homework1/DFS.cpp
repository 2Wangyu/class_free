//#include<iostream>
//#include<vector>
//#include<queue>
//#include<math.h>
//#include<algorithm>
//#include<set>
//
//std::set<std::pair<int, int>> count;
//int shortestPath(std::vector<std::vector<int>>& maze, std::pair<int, int> start, std::pair<int, int>dest) {
//	int m = maze.size();
//	int n = maze[0].size();
//	int up = 1000, 
//		down = 1000, 
//		left = 1000,
//		right = 1000;
//	if (start == dest) {
//		return 0;
//	}
//	if (maze[dest.first][dest.second] == 1)
//		return 1000;
//	if (maze[dest.first][dest.second] != 1 && abs(start.first - dest.first) == 1 && start.second == dest.second)
//		return 1;
//	if (maze[dest.first][dest.second] != 1 && start.first == dest.first && abs(start.second - dest.second) == 1)
//		return 1;
//	count.insert(dest);
//	if (dest.first > 0 && count.find({ dest.first - 1,dest.second }) == count.end())
//		up = shortestPath(maze, start, std::make_pair(dest.first - 1, dest.second));
//
//	if (dest.first < m - 1 && count.find({ dest.first + 1,dest.second }) == count.end())
//		down = shortestPath(maze, start, std::make_pair(dest.first + 1, dest.second));
//
//	if (dest.second > 0 && count.find({ dest.first,dest.second - 1 }) == count.end())
//		left = shortestPath(maze, start, std::make_pair(dest.first, dest.second - 1));
//
//	if (dest.second < n - 1 && count.find({ dest.first,dest.second + 1 }) == count.end())
//		right = shortestPath(maze, start, std::make_pair(dest.first, dest.second + 1));
//
//	count.erase(dest);
//
//	if (maze[dest.first][dest.second] != 1) {
//		return std::min(std::min(up, down), std::min(left, right)) + 1;
//	}
//
//}
//int main() {
//	std::vector<std::vector<int>> test = {
//		{0,0,1,0,0},
//		{0,0,0,0,0},
//		{0,0,1,0,0},
//		{0,1,1,1,0},
//		{0,0,0,0,0}
//	};
//	std::cout << shortestPath(test, std::make_pair(0, 0), std::make_pair(2, 3));
//	return 0;
//}