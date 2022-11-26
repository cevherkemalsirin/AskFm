#include "askFmUserManager.h"



askFmUserManager::askFmUserManager(const askfmUser& CurrentSystemUser)
	{
		this->CurrentSystemUser = CurrentSystemUser;
		retriveQuestions();
	}

	void askFmUserManager::retriveQuestions()
	{
		questionM.DataAllQuestions();

		for (auto& m : questionM.getAllQuestions())
		{
			for (Question& q : m.second)
			{
				if (q.getToID() == CurrentSystemUser.getID())
				{
					askedQuestions.push_back(q);
				}
				else if (q.getAskerID()== CurrentSystemUser.getID())
				{
					askedToQuestions.push_back(q);
				}
			}

		}


	}
	void askFmUserManager::refreshPage()
	{
		askedQuestions.clear();
		askedToQuestions.clear();
		retriveQuestions();

	}
	void askFmUserManager::PrintQuestionsToMe()
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

	void askFmUserManager::PrintQuestionsFromMe()
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

	void askFmUserManager::AnswerQuestion()
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
				if (askedQuestions[FetchedId].GetHasAnswer())
				{
					cout << " Warning question has an answer, Do you want to override it ? (0-1)" << endl;
					bool choice;  cin >> choice;
					if (choice)
					{
						string answerT;
						cout << "Enter Answer: " << endl;
						cin.ignore();
						getline(cin, answerT);
						askedQuestions[FetchedId].setAnswer(answerT);
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
					askedQuestions[FetchedId].setAnswer(answerT);
					askedQuestions[FetchedId].setHasAnswer(true);
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

	void askFmUserManager::updateQManagerAnswer(int id, int fetchedId)
	{
		for (auto& v : questionM.getAllQuestions()[id])
		{
			if (v.getQuestionID() == id)
			{

				v.setAnswer(askedQuestions[fetchedId].GetAnswer());
				v.setAnswer(askedQuestions[fetchedId].GetAnswer());

			}

		}

		questionM.reWriteAllquestions();

	}

	void askFmUserManager::askQuestion(const map<int, askfmUser>& allUsers)
	{
		int toUserId = 1;

		while (true)
		{
			cout << "Please enter a userId to ask a question, -1 to cancel " << endl;
			cin >> toUserId;

			if (allUsers.count(toUserId))
			{
				//ask here if thread question or not
				questionM.getQuestionFromUser(CurrentSystemUser.getID(), toUserId, false);
				refreshPage();
				break;
			}
			else if (toUserId == -1)
			{
				break;
			}
			else
			{
				cout << "No users with this id check it again ! " << endl;
			}
		}
	}

	void askFmUserManager::deleteQuestion()
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
				int questionId = askedQuestions[asked].getQuestionID();
				cout << "a" << endl;
				questionM.getAllQuestions().erase(questionId);

				questionM.reWriteAllquestions();
				break;

			}
			else if (toAsked != -1)
			{
				int questionId = askedToQuestions[toAsked].getQuestionID();
				questionM.getAllQuestions().erase(questionId);

				questionM.reWriteAllquestions();
				break;
			}
			else
			{
				cout << "There is no such question or you have no authorize " << endl;
			}

		}
	}

	int askFmUserManager::FetchQuestionById(int id, bool didIask)
	{
		if (didIask)
		{
			for (int i = 0; i < (int)askedToQuestions.size(); i++)
			{
				if (id == askedToQuestions[i].getQuestionID()) return i;
			}
			return -1;
		}
		else
		{
			for (int i = 0; i < (int)askedQuestions.size(); i++)
			{
				if (id == askedQuestions[i].getQuestionID()) return i;
			}
			return -1;
		}
	}

	void askFmUserManager::printAllQuestions()const
	{
		questionM.printAll();
	}
