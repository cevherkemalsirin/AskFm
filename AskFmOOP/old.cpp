#include <fstream>
#include<iostream>
#include<sstream>;
#include<string>;
#include<stack>
#include<vector>
#include<algorithm>
#include<map>

/*
using namespace std;


//lets read file with the help of function that returns string lines as vector


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
//----------------------------------------Done


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


//----------------------------------------Done


int stringToInt(string& str)
{
	int a;
	istringstream iss(str);
	iss >> a;
	return a;
}

//------------------------------------------Done

//template <typename T>
//void WriteFile(const string & fileName,const T& questionMap,int loop=1)
//{
//	ofstream ofs(fileName,trunc);
//
//	for(int i=0;i<loop;i++)
//	ofs << questionMap;
//
//	ofs.close();
//	
//
//}
struct askfmUser
{
	int id{};

	string name{};
	string userName{};
	string password{};
	string email{};
	bool allowAQ{};

	askfmUser()
	{

	}
	askfmUser(const int id, const string& name, const string& userName, const string& password, const string& email, bool allowAQ)
	{
		this->id = id;
		this->name = name;
		this->userName = userName;
		this->password = password;
		this->email = email;
		this->allowAQ = allowAQ;


	}


	// overload << operator
	friend ofstream& operator<<(ofstream& ofs, const askfmUser& u)
	{
		ofs << u.id << " " << u.userName << " " << u.password << " " << u.allowAQ << " " << u.name << " " << u.email << endl;

		return ofs;

	}

	friend ifstream& operator>> (ifstream& ifs, askfmUser& u)
	{
		ifs >> u.id;
		ifs >> u.userName;
		ifs >> u.password;
		ifs >> u.allowAQ;
		ifs >> u.name;
		ifs >> u.email;


		return ifs;
	}
	void print()
	{
		cout << this->id << " " << this->userName << " " << this->password << " " << allowAQ << " " << this->name << " " << this->email << endl;
	}
};

//------------------------------------------Done

// ask fm project
struct Question
{
	int id{};
	int AskerID{};
	int toID{};
	string questionText{};
	string answer{};
	bool hasAnswer{};

	Question()
	{

	}
	Question(vector<string>& vstr)
	{
		if (vstr.size() == 5)
		{
			id = stringToInt(vstr[0]);
			AskerID = stringToInt(vstr[1]);
			toID = stringToInt(vstr[2]);
			questionText = vstr[3];
			answer = vstr[4];
			hasAnswer = true;


		}
		else if (vstr.size() == 4)
		{

			id = stringToInt(vstr[0]);
			AskerID = stringToInt(vstr[1]);
			toID = stringToInt(vstr[2]);
			questionText = vstr[3];
			hasAnswer = false;
		}

	}
	friend ofstream& operator<<(ofstream& ofs, Question& q)
	{
		ofs << q.id << "," << q.AskerID << "," << q.toID << "," << q.questionText << "," << q.answer;

		return ofs;

	}

	void print()
	{
		cout << id << " " << " " << AskerID << " " << toID << " Question: " << questionText << endl;
		cout << " Answer: " << answer << endl;

	}



};

void WriteFile(const string& fileName, const map<int, vector<Question>> questionMap)
{
	ofstream ofs(fileName, ios::trunc);

	for (auto& m : questionMap)
	{
		for (Question q : m.second)
			ofs << q << endl;
	}

	ofs.close();
}

//------------------------------------------Done

struct questionManager
{
	map<int, vector<Question>> m_allQuestions;
	int QID{};


	void GetAllQuestions()
	{

		//int Qid, userId, toId; string question, answer;
		m_allQuestions.clear();
		vector<string> takenQuestions;
		vector<string> splittedString;
		takenQuestions = ReadFile("Questions.txt");
		QID = (int)takenQuestions.size();

		for (auto& v : takenQuestions)
		{

			splittedString = SplitString(v);

			Question q(splittedString);

			m_allQuestions[q.id].push_back(q);


		}

	}

	void reWriteAllquestions()
	{
		WriteFile("Questions.txt", m_allQuestions);


	}
	void printAll()
	{
		for (auto& m : m_allQuestions)
		{
			for (auto& v : m.second)
			{
				v.print();

			}
		}


	}


};

//------------------------------------------Done


struct askFmUserManager
{
	askfmUser CurrentSystemUser{};
	vector<Question> askedQuestions{};
	vector<Question> askedToQuestions{};
	questionManager questionM{};


	askFmUserManager(askfmUser& CurrentSystemUser)
	{
		this->CurrentSystemUser = CurrentSystemUser;
		retriveQuestions();
	}

	void retriveQuestions()
	{
		questionM.GetAllQuestions();

		for (auto& m : questionM.m_allQuestions)
		{
			for (Question& q : m.second)
			{
				if (q.toID == CurrentSystemUser.id)
				{
					askedQuestions.push_back(q);
				}
				else if (q.AskerID == CurrentSystemUser.id)
				{
					askedToQuestions.push_back(q);
				}
			}

		}


	}
	void refreshPage()
	{
		askedQuestions.clear();
		askedToQuestions.clear();
		retriveQuestions();

	}
	void PrintQuestionsToMe()
	{

		refreshPage();
		int a = 0;
		for (auto& v : askedQuestions)
		{
			a++;
			cout << "Question " << a << "): " << endl;
			v.print();

		}

	}

	void PrintQuestionsFromMe()
	{
		refreshPage();
		int a = 0;
		for (auto& v : askedToQuestions)
		{
			a++;
			cout << "Question " << a << "): " << endl;
			v.print();

		}
	}

	void AnswerQuestion()
	{

		while (true)
		{
			int qid;
			cout << "Please Enter a Question ID: " << endl;
			cin >> qid;
			int FetchedId = FetchQuestionById(qid, false);

			if (FetchedId != -1)
			{
				askedQuestions[FetchedId].print();
				if (askedQuestions[FetchedId].hasAnswer)
				{
					cout << " Warning question has an answer, Do you want to override it ? (0-1)" << endl;
					bool choice;  cin >> choice;
					if (choice)
					{
						string answerT;
						cout << "Enter Answer: " << endl;
						cin.ignore();
						getline(cin, answerT);
						askedQuestions[FetchedId].answer = answerT;
						updateQManagerAnswer(qid, FetchedId);
						refreshPage();
						break;
					}
					else
					{
						break;
					}

				}
				else
				{
					string answerT;
					cout << "Enter Answer: " << endl;
					cin.ignore();
					getline(cin, answerT);
					askedQuestions[FetchedId].answer = answerT;
					askedQuestions[FetchedId].hasAnswer = true;
					updateQManagerAnswer(qid, FetchedId);
					refreshPage();
					break;
				}
			}
			else
			{
				cout << " There is no question with this ID to answer! " << endl;
			}
		}


	}

	void updateQManagerAnswer(int id, int fetchedId)
	{
		for (auto& v : questionM.m_allQuestions[id])
		{
			if (v.id == id)
			{

				v.answer = askedQuestions[fetchedId].answer;
				v.hasAnswer = askedQuestions[fetchedId].hasAnswer;

			}

		}

		questionM.reWriteAllquestions();

	}

	void askQuestion(const map<int, askfmUser>& allUsers)
	{
		while (true)
		{

			Question newQuestion{};
			int toUserId;
			cout << "Please enter a userId to ask a question " << endl;
			cin >> toUserId;

			if (allUsers.count(toUserId))
			{
				//ask here if thread question or not
				string qText{}; cin.ignore();
				cout << "Please enter a question! " << endl;
				getline(cin, qText);
				newQuestion.id = ++questionM.QID;
				newQuestion.AskerID = CurrentSystemUser.id;
				newQuestion.toID = toUserId;
				newQuestion.questionText = qText;
				newQuestion.hasAnswer = false;
				questionM.m_allQuestions[newQuestion.id].push_back(newQuestion);
				questionM.reWriteAllquestions();
				refreshPage();
				break;
			}
			else
			{
				cout << "No users with this id check it again ! " << endl;
			}
		}
	}

	void deleteQuestion()
	{
		while (true)
		{
			cout << "(-1 to cancel) Please enter question Id to Delete: " << endl;
			int delId{}; cin >> delId;
			if (delId == -1)break;
			int asked = FetchQuestionById(delId, false);
			int toAsked = FetchQuestionById(delId, true);
			if (asked != -1)
			{
				int questionId = askedQuestions[asked].id;
				cout << "a" << endl;
				questionM.m_allQuestions.erase(questionId);

				questionM.reWriteAllquestions();
				break;

			}
			else if (toAsked != -1)
			{
				int questionId = askedToQuestions[toAsked].id;
				questionM.m_allQuestions.erase(questionId);

				questionM.reWriteAllquestions();
				break;
			}
			else
			{
				cout << "There is no such question or you have no authorize " << endl;
			}

		}
	}

	int FetchQuestionById(int id, bool didIask)
	{
		if (didIask)
		{
			for (int i = 0; i < (int)askedToQuestions.size(); i++)
			{
				if (id == askedToQuestions[i].id) return i;
			}
			return -1;
		}
		else
		{
			for (int i = 0; i < (int)askedQuestions.size(); i++)
			{
				if (id == askedQuestions[i].id) return i;
			}
			return -1;
		}
	}

	void printAllQuestions()
	{
		questionM.printAll();
	}

};


struct askFmSystem
{
	map<int, askfmUser> m_users;
	vector<string> v_userStrings;
	askfmUser currentUser;
	int Uid{};


	void initiate()
	{

		//get users from file to memory


		getUsersFromFile();


		menu();


	}


	void menu()
	{

		while (true)
		{
			//system("CLS");
			int choice;
			cout << "Please Enter 1 or 2: " << endl;

			cout << endl << endl;
			cout << "1) Log-In" << endl;
			cout << "2) Sign-Up" << endl;

			cin >> choice;

			if (choice == 1)
			{
				login();
				break;
			}
			else if (choice == 2)
			{
				createUser();
				break;
			}

			else

			{
				cout << " Please Enter 1 or 2 " << endl;

			}

		}



	}
	void printUsers()
	{
		m_users.empty() ? cout << "the map is empty" << endl : cout << " map is not empty " << endl;

		for (pair<int, askfmUser> p : m_users)
		{
			p.second.print();

		}


	}
	void getUsersFromFile()
	{

		v_userStrings = ReadFile("Users.txt");

		Uid = (int)v_userStrings.size();

		if (Uid > 0)AddExistigUsers();

	}

	int GetExistingUser(const string& username)
	{

		for (auto& m : m_users)
		{
			if (m.second.userName == username)
			{
				return m.second.id;
			}
		}

	}

	void AddExistigUsers()
	{
		int id; string username, password, name, email;
		bool anym;
		askfmUser u;
		for (auto& v : v_userStrings)
		{
			istringstream iss(v);
			iss >> id >> username >> password >> anym >> name >> email;

			u.id = id; u.userName = username; u.password = password; u.allowAQ = anym; u.name = name; u.email = email;

			m_users[id] = u;

		}

	}

	void login()
	{
		while (true)
		{
			cout << "Please enter a UserName: " << endl;
			string givenUname{}; cin >> givenUname;
			if (checkExistingUser(givenUname))
			{
				int id = GetExistingUser(givenUname);
				currentUser = m_users[id];
				cout << "Please enter a Password: " << endl;
				string pass; cin >> pass;
				if (currentUser.password == pass)
				{

					openUserManager(currentUser);
					break;


				}
				else
				{
					cout << "Password does not match try again " << endl;
				}

			}
			else
			{
				cout << "This user does not exist enter again " << endl;
			}
		}
	}
	void openUserManager(askfmUser& user)
	{
		askFmUserManager um(user);
		int choice;
		system("CLS");
		cout << "Entered to the system: " << endl;

		while (true)
		{

			cout << "Menu: " << endl;
			cout << "1: Print Question To Me " << endl;
			cout << "2: Print Question From Me " << endl;
			cout << "3: Answer a Question " << endl;
			cout << "4: Delete a Question " << endl;
			cout << "5: Ask a Question " << endl;
			cout << "6: List System Users " << endl;
			cout << "7: Feed " << endl;
			cout << "8: Logout " << endl;

			cout << "Enter number in range 1-8: ";

			cin >> choice;
			cout << endl;
			if (choice > 8 || choice < 1)
			{
				cout << choice << " is Invalid choice, please enter 1-8: " << endl;
				continue;
			}
			else
			{
				system("CLS");
				if (choice == 1)
				{
					um.PrintQuestionsToMe();
				}
				else if (choice == 2)
				{
					um.PrintQuestionsFromMe();

				}
				else if (choice == 3)
				{
					um.AnswerQuestion();
				}
				else if (choice == 4)
				{
					um.deleteQuestion();
				}
				else if (choice == 5)
				{
					um.askQuestion(m_users);
				}
				else if (choice == 6)
				{
					printUsers();

				}
				else if (choice == 7)
				{
					um.printAllQuestions();
				}
				else if (choice == 8)
				{

					break;
				}

			}

		}
		menu();


	}
	bool checkExistingUser(const string& username)
	{
		string userName;
		for (auto &m : m_users)
		{
			if (m.second.userName == username)return true;

		}
		return false;

	}

	void createUser()
	{
		while (true)
		{
			string name, password, email, username;
			bool anymQA{};
			cout << "Please enter a name: " << endl;
			cin >> name;
			cout << "Please Enter a username" << endl;
			cin >> username;
			cout << " Please enter a password " << endl;
			cin >> password;
			cout << " Please enter a email " << endl;
			cin >> email;
			cout << " Please enter allow Anymous Questions or not! (1-0)" << endl;
			cin >> anymQA;
			if (!checkExistingUser(username))
			{
				++Uid;

				askfmUser u{ Uid, name,username,password,email,anymQA };
				m_users[Uid] = u;
				break;
			}
			else cout << "Existing UserName Please choose a different UserName," << endl;
		}



		addUserToFile("Users.txt", Uid);

	}
	void addUserToFile(const string& FileName, int id)
	{
		ofstream ofs(FileName, ios::app);
		ofs << m_users[id];
		ofs.close();
	}


};

int main()
{
	/*questionManager qm;

	qm.GetAllQuestions();

	for(auto &m: qm.m_allQuestions)
	{
		cout << m.first << endl;
		m.second[0].print();
	}
	

	askFmSystem s;
	s.initiate();

}

*/