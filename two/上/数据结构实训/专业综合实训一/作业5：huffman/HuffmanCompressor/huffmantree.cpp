#include "huffmantree.h"
#include <iostream>
#include <queue>
#include <map>
#include <string>

HuffmanTree::HuffmanTree( map<char, int> freq)
{
    priority_queue<TreeNode*, vector<TreeNode*>, Comparenode> pq_;
        for (auto& p : freq) {
            pq_.push(new TreeNode(p.first, p.second));
        }
    while (pq_.size() > 1) {
              //TreeNode* left = new TreeNode(pq_.top().first,pq_.top().second);
              TreeNode* left = pq_.top();
              pq_.pop();
              //TreeNode* right =new  TreeNode(pq_.top().first,pq_.top().second);
              TreeNode* right = pq_.top();
              pq_.pop();
              //TreeNode* parent = new TreeNode('\0', left->freq + right->freq);
              TreeNode* parent = new TreeNode('\0', left->freq + right->freq);
              parent->left = left;
              parent->right = right;
              pq_.push(parent);
//              parent->left = left;
//              parent->right = right;
//              pq_.push(make_pair(parent->val,parent->freq));


          }
          root_ = pq_.top();

};
// 写出Huffman 编码表
void HuffmanTree::printHuffmanCode(TreeNode* root, string str, map<char, string>& huffmanCode) {
    if (root== NULL) {
        return;
    }

    if (root->val != '\0') {
        huffmanCode[root->val] = str;
    }
    printHuffmanCode(root->left, str + "0", huffmanCode);
    printHuffmanCode(root->right, str + "1", huffmanCode);

}

// 获取 Huffman 编码字符串
map<char,string> HuffmanTree::getHuffmanCodeString() {

    printHuffmanCode(root_, "", huffmanCode);
//    用于测试
//    string result = "";
//    for (auto& p : huffmanCode) {
//        result += p.second + " " + to_string(p.first) + "\n";
//    }
    return huffmanCode;
}
