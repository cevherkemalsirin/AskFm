#include <fstream>
#include <iostream>

using namespace std;


class askfmUser
{
private:
	int id;

	string name;
	string userName;
	string password;
	string email;
	bool allowAQ;

public:

	askfmUser();
	askfmUser(const int id, const string& name, const string& userName, const string& password, const string& email, bool allowAQ);



	// overload operator <<  >> to read and write users to/from the file

	friend ofstream& operator<<(ofstream& ofs, const askfmUser& u);
	friend ifstream& operator>> (ifstream& ifs, askfmUser& u);

	void print() const;

	int getID()const;

	bool checkUserName(const string& givenUsername);

	bool checkPassword(const string& givenPassword);
};

