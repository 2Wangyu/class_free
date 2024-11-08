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
//        return ""; // È«²¿×Ö·û¶¼Æ¥Åä£¬·µ»Ø¿Õ×Ö·û´®  
//    }
//    else if (pos == pattern.length()) {
//        return str.substr(pos); // Æ¥Åäµ½str½áÎ²£¬·µ»ØÊ£Óà×Ö·û´®  
//    }
//    else if (pos == pattern.length()) {
//        return ""; // Æ¥Åäµ½pattern½áÎ²£¬·µ»Ø¿Õ×Ö·û´®  
//    }
//    else {
//        return str.substr(pos); // ²»Æ¥Åä£¬·µ»ØÊ£Óà×Ö·û´®  
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