#include<iostream>
#include "AskFmUt.h"


using namespace std;

#pragma once
class Question
{
private:
	int id;
	int AskerID;
	int toID;
	string questionText;
	string answer;
	bool hasAnswer;

public:
	Question();
    Question(int id, int AskerID, int toID, const string& questionText, bool hasAnswer, const string& answer);
	Question(const vector<string>& vstr);
    friend ofstream& operator<<(ofstream& ofs, const Question& q);
	void print()const;
	int getQuestionID() const;
	void initializeQuestion(int id, int AskerID, int toID, const string& questionText, bool hasAnswer, const string& answer);

	void setAnswer(const string& answer);
	void setHasAnswer(bool HasAnswer);
	string GetAnswer() const;
	bool GetHasAnswer() const;
	int getAskerID() const;
	int getToID() const;


};

