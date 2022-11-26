#include "AskFmUt.h"



vector<string> ReadFile(const string& folderName)
{

ifstream ifs(folderName);

string lines{};

vector<string> vs;

while (getline(ifs, lines))
{
	if (!lines.empty())vs.push_back(lines);

}

ifs.close();
return vs;


}


vector<string>SplitString(string& line)
{
	vector<string> v;

	if (!line.empty())
	{
		string str;
		for (string::iterator it = line.begin(); it != line.end(); it++)
		{


			if (*it == ',')
			{
				v.push_back(str);
				str = "";


			}
			else
			{
				str += *it;

			}
			if (it == line.end() - 1 && *it != ',')
			{
				str += *it;
				v.push_back(str);
			}

		}


	}

	return v;
}

int stringToInt(const string& str)
{
	int a;
	istringstream iss(str);
	iss >> a;
	return a;

}


