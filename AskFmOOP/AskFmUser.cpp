#include "AskFmUser.h"


	askfmUser::askfmUser()
	{
		this->id = 0;
	}
	
	askfmUser::askfmUser(const int id, const string& name, const string& userName, const string& password, const string& email, bool allowAQ)
	{
		this->id = id;
		this->name = name;
		this->userName = userName;
		this->password = password;
		this->email = email;
		this->allowAQ = allowAQ;


	}
	// overload << operator
	 ofstream& operator<<(ofstream& ofs, const askfmUser& u)
	{
		ofs << u.id << " " << u.userName << " " << u.password << " " << u.allowAQ << " " << u.name << " " << u.email << endl;

		return ofs;

	}

	 ifstream& operator>> (ifstream& ifs, askfmUser& u)
	{
		ifs >> u.id;
		ifs >> u.userName;
		ifs >> u.password;
		ifs >> u.allowAQ;
		ifs >> u.name;
		ifs >> u.email;


		return ifs;
	}
	void askfmUser::print() const
	{
		cout << this->id << " " << this->userName << " " << this->password << " " << allowAQ << " " << this->name << " " << this->email << endl;
	}

	int askfmUser::getID()const
	{
		return id;
	}

	bool  askfmUser::checkUserName(const string& givenUsername)
	{
		if (this->userName == givenUsername) return true;

		return false;
	}

	bool  askfmUser::checkPassword(const string& givenPassword)
	{
		if (this->password == givenPassword) return true;

		return false;
	}



