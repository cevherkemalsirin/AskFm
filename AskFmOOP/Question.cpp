#include "Question.h"



Question::Question() = default;

 Question::Question(int id, int AskerID, int toID, const string& questionText, bool hasAnswer, const string& answer = " ")
{
	this->id = id;
	this->AskerID = AskerID;
	this->toID = toID;
	this->questionText = questionText;
	this->hasAnswer = hasAnswer;
	this->answer = answer;

}
Question::Question(const vector<string>& vstr)
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
 ofstream& operator<<(ofstream& ofs, const Question& q)
{
	ofs << q.id << "," << q.AskerID << "," << q.toID << "," << q.questionText << "," << q.answer;

	return ofs;

}

void Question::print()const 
{
	cout << id << " " << " " << AskerID << " " << toID << " Question: " << questionText << endl;
	cout << " Answer: " << answer << endl;

}

int	Question::getQuestionID() const
{
	return id;
}
void Question::initializeQuestion(int id, int AskerID, int toID, const string& questionText, bool hasAnswer, const string& answer = " ")
{
	this->id = id;
	this->AskerID = AskerID;
	this->toID = toID;
	this->questionText = questionText;
	this->hasAnswer = hasAnswer;
	this->answer = answer;

}
void Question::setAnswer(const string& answer)
{
	this->answer = answer;
}
void Question::setHasAnswer(bool HasAnswer)
{
	this->hasAnswer = HasAnswer;
}

string Question::GetAnswer() const
{
	return this->answer;
}
bool Question::GetHasAnswer() const
{
	return this->hasAnswer;
}

int Question::getAskerID() const
{
	return this->AskerID;
}
int Question::getToID() const
{
	return this->toID;
}
