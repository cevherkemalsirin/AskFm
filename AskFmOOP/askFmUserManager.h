#include "Question.h"
#include "AskFmUser.h"
#include "questionManager.h"
class askFmUserManager
{
private:
	askfmUser CurrentSystemUser;
	vector<Question> askedQuestions;
	vector<Question> askedToQuestions;
	questionManager questionM;

public:
	askFmUserManager(const askfmUser& CurrentSystemUser);
	void retriveQuestions();
	void refreshPage();
	void PrintQuestionsToMe();
	

	void PrintQuestionsFromMe();
	

	void AnswerQuestion();

	void updateQManagerAnswer(int id, int fetchedId);

	void askQuestion(const map<int, askfmUser>& allUsers);

	void deleteQuestion();

	int FetchQuestionById(int id, bool didIask);

	void printAllQuestions()const;
};
