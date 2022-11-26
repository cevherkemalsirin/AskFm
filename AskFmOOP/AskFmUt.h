#pragma once
#include <fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<stack>
#include<vector>
#include<algorithm>
#include<map>


using namespace std;



// get Lines from file and put in vector
vector<string> ReadFile(const string& folderName);

// take question lines with coma and split them into vector
vector<string>SplitString(string& line);

//take string as input and output int
int stringToInt(const string& str);







