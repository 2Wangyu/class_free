#ifndef ALTERTABLE_H
#define ALTERTABLE_H
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

class altertable
{
public:
    altertable();
    void alter(const string& filename, const string& operation, const string& oldColumnName, const string& newColumnName, const string& newColumnType);
};

#endif // ALTERTABLE_H
