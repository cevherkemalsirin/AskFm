#include"askFmUserManager.h"



 class askFmSystem
{
private:
	map<int, askfmUser> m_users;
	vector<string> v_userStrings;
	askfmUser currentUser;
	int Uid;

public:
	void initiate();


private:
	void menu();

	void printUsers();

	void getUsersFromFile();

	int GetExistingUser(const string& username);

	void AddExistigUsers();

	void login();

	void openUserManager(askfmUser& user);
	

	bool checkExistingUser(const string& username);

	void createUser();
	
	void addUserToFile(const string& FileName, int id);
	

};