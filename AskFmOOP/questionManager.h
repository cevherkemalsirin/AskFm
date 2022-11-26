
#include "AskFmUt.h"
#include "Question.h"

class questionManager
{
private:
	map<int, vector<Question>> m_allQuestions;
	int QID;

public:
	questionManager();

	void DataAllQuestions();

	void reWriteAllquestions();

	void printAll()const;

	map<int, vector<Question>>& getAllQuestions();

	void getQuestionFromUser( int userID, int ToID, bool hasAnswer);


private:
	void WriteFile(const string& fileName, const map<int, vector<Question>> questionMap);

};
