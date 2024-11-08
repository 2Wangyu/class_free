//#include <iostream>  
//#include <string>  
//
//using namespace std;
//
//string extractUnmatchedString(const string& str, const string& pattern) {
//    size_t pos = 0;
//    while (pos < str.length() && pos < pattern.length() && str[pos] == pattern[pos]) {
//        ++pos;
//    }
//
//    if (pos == str.length() && pos == pattern.length()) {
//        return ""; // ȫ���ַ���ƥ�䣬���ؿ��ַ���  
//    }
//    else if (pos == pattern.length()) {
//        return str.substr(pos); // ƥ�䵽str��β������ʣ���ַ���  
//    }
//    else if (pos == pattern.length()) {
//        return ""; // ƥ�䵽pattern��β�����ؿ��ַ���  
//    }
//    else {
//        return str.substr(pos); // ��ƥ�䣬����ʣ���ַ���  
//    }
//}
//
//int main() {
//    string str = "Hello, world!";
//    string pattern = "Hel";
//    string unmatched = extractUnmatchedString(str,pattern);
//    cout << "Unmatched string: " << unmatched << endl;
//    return 0;
//}