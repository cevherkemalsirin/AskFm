#include "questionManager.h"




	questionManager::questionManager()
	{
		QID = 0;
	}
	void questionManager::DataAllQuestions()
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

			m_allQuestions[q.getQuestionID()].push_back(q);


		}

	}

	void  questionManager::reWriteAllquestions()
	{
		WriteFile("Questions.txt", m_allQuestions);


	}
	void questionManager:: printAll()const
	{
		for (auto& m : m_allQuestions)
		{
			for (auto& v : m.second)
			{
				v.print();

			}
		}


	}
	map<int, vector<Question>>& questionManager::getAllQuestions() 
	{
		return m_allQuestions;

	}
	void questionManager::WriteFile(const string& fileName, const map<int, vector<Question>> questionMap)
	{
		ofstream ofs(fileName, ios::trunc);

		for (auto& m : questionMap)
		{
			for (Question q : m.second)
				ofs << q << endl;
		}

		ofs.close();

	}
	void questionManager::getQuestionFromUser(int userID,int ToID,bool hasAnswer)
	{
		string qText{}; cin.ignore();
		cout << "Please enter a question! " << endl;
		getline(cin, qText);

		Question newQuestion(++QID, userID, ToID, qText, hasAnswer,"");

		getAllQuestions()[newQuestion.getQuestionID()].push_back(newQuestion);
		reWriteAllquestions();
	}
