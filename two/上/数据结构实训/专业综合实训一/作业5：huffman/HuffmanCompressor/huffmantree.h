#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include<iostream>
#include<queue>
#include<vector>
#include<map>
using namespace std;
// 自定义比较函数，用于根据 map 中的值进行比较
struct Compare {
    bool operator()(const std::pair<char, int>& a, const std::pair<char, int>& b) {
        return a.second > b.second;  // 使用值进行比较（降序排列）
    }
};

struct TreeNode{
    char val;//代表字符
    int freq;//字符的频率
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x):val(x),freq(0),left(NULL),right(){};
    TreeNode(char x,int f):val(x),freq(f),left(NULL),right(){};//每个节点读取后的节点

};
struct Comparenode {
    bool operator()(TreeNode* node1,TreeNode* node2) {
        return node1->freq>node2->freq;  // 使用值进行比较（降序排列）
    }
};
class HuffmanTree
{
public:
    //构建哈夫曼树
    HuffmanTree( map<char, int> freq );
    //HuffmanTree(std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>,Compare> pq);
    TreeNode* root_;
    //求出哈夫曼编码
    void printHuffmanCode(TreeNode* root, string str, map<char, string>& huffmanCode);
    //外部获取哈夫曼编码
    map<char,string> getHuffmanCodeString();
    //储存哈夫曼编码
    map<char, string> huffmanCode;

};

#endif // HUFFMANTREE_H
