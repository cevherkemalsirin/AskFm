#include"AskFmSystem.h"




	void askFmSystem::initiate()
	{

		//get users from file to memory

		Uid = 0;
		getUsersFromFile();


		menu();


	}


	void askFmSystem::menu()
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
	void askFmSystem::printUsers()
	{
		m_users.empty() ? cout << "the map is empty" << endl : cout << " map is not empty " << endl;

		for (pair<int, askfmUser> p : m_users)
		{
			p.second.print();

		}


	}
	void askFmSystem::getUsersFromFile()
	{

		v_userStrings = ReadFile("Users.txt");

		Uid = (int)v_userStrings.size();

		if (Uid > 0)AddExistigUsers();

	}

	int askFmSystem::GetExistingUser(const string& username)
	{

		for (auto& m : m_users)
		{
			if (m.second.checkUserName(username))
			{
				return m.second.getID();
			}
		}
		return -1;

	}

	void askFmSystem::AddExistigUsers()
	{
		int id; string username, password, name, email;
		bool anym;


		for (auto& v : v_userStrings)
		{
			istringstream iss(v);
			iss >> id >> username >> password >> anym >> name >> email;
			askfmUser u(id, name, username, password, email, anym);
			m_users[id] = u;

		}

	}

	void askFmSystem::login()
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
				if (currentUser.checkPassword(pass))
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
	void askFmSystem::openUserManager(askfmUser& user)
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
	bool askFmSystem::checkExistingUser(const string& username)
	{

		for (auto& m : m_users)
		{
			if (m.second.checkUserName(username))return true;

		}
		return false;

	}

	void askFmSystem::createUser()
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
	void askFmSystem::addUserToFile(const string& FileName, int id)
	{
		ofstream ofs(FileName, ios::app);
		ofs << m_users[id];
		ofs.close();
	}


