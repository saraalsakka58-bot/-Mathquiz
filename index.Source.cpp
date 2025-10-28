#include<iostream>
#include<cstdlib>
#include<cmath>
#include<ctime>
using namespace std;
enum enquestionlevel {
	easylevel = 1, middlevel = 2, hardlevel = 3, mixlevel = 4
};
enum enoperationtype {
	add = 1, sub = 2, mult = 3, Div=4,mix=5
};
int randomnumber(int from,int to) {
	return rand() % (to - from + 1) + from;
}
string getoperationtype(enoperationtype op) {
	switch (op) {
	case enoperationtype::add:
			return"+";
	case enoperationtype::Div:
		return "/";
	case enoperationtype::sub:
		return "-";
	case enoperationtype::mult:
		return "*";
	case enoperationtype::mix: {
		enoperationtype randop = (enoperationtype)randomnumber(1,4);
		return getoperationtype(randop);
	}
		
	}
}
enoperationtype getrandomoperationtype() {
	return (enoperationtype)randomnumber(1, 4);
}
string getquestionleveltext(enquestionlevel questionlevel) {
	string arrquestionlevel[4] = { "easy","mid","hard","mix" };
	return arrquestionlevel[questionlevel - 1];
}
void setscreencolor(bool right) {
	if (right)
		system("color 2F");
	else {
		system("color 4F");
		cout << "\a";
	}
}
	int simplecalculator(int num1, int num2, enoperationtype op) {
		switch (op) {
		case enoperationtype::add:
			return num1 + num2;
		case enoperationtype::sub:
			return num1 - num2;
		case enoperationtype::mult:
			return num1 * num2;
		case enoperationtype::Div: 
			 return (num2 != 0) ? (num1 / num2) : 0; 
		default :
			return num1 + num2;
		}
	}
	struct stquestion {
		int num1 = 0;
		int num2 = 0;
		enoperationtype operationtype;
		enquestionlevel questionlevel;
		int correctanswer = 0;
		int playeranswer = 0;
		bool answerresut = false;
	};
	struct stquiz {
		stquestion questionlist[100];
		short numberofquestion;
		enoperationtype operationtype;
		enquestionlevel questionlevel;
		short numberofwronganswer=0;
		short numberofrightanswer=0;
		bool ispass=false;
	};
	stquestion generatequestion(enquestionlevel questionlevel,enoperationtype opt) {
		stquestion question;
		if (questionlevel == enquestionlevel::mixlevel)
			questionlevel = (enquestionlevel)randomnumber(1, 3);
		if (opt == enoperationtype::mix)
			opt = getrandomoperationtype();
		question.operationtype = opt;
		switch (questionlevel) {
		case enquestionlevel::easylevel:
			question.num1 = randomnumber(1, 10);
			question.num2 = randomnumber(1, 10);
			break;

		case enquestionlevel::middlevel:
			question.num1 = randomnumber(10, 50);
			question.num2 = randomnumber(10, 50);
			break;
		case enquestionlevel::hardlevel:
			question.num1 = randomnumber(50, 100);
			question.num2 = randomnumber(50, 100);
			break;
		}
		question.correctanswer = simplecalculator(question.num1, question.num2, question.operationtype);
		question.questionlevel = questionlevel;
		return question;
 }
	void askandcorrectquestion(stquiz &quiz) {
		for (short questionnumber = 0; questionnumber < quiz.numberofquestion; questionnumber++) {
			cout << "\nquestion[" << questionnumber + 1 << "/" << quiz.numberofquestion << "]: "<<endl;
			cout << quiz.questionlist[questionnumber].num1 << endl;
			cout << getoperationtype(quiz.questionlist[questionnumber].operationtype) << " ";
			cout << quiz.questionlist[questionnumber].num2 << " ";
			cin >> quiz.questionlist[questionnumber].playeranswer;
			if (quiz.questionlist[questionnumber].playeranswer == quiz.questionlist[questionnumber].correctanswer) {
				cout << "correct answer" << endl;
				quiz.questionlist[questionnumber].answerresut = true;
				quiz.numberofrightanswer++;
			}
			else {
				cout << "wrong answer,the right answer:" <<quiz.questionlist[questionnumber].correctanswer<< endl;
				quiz.numberofwronganswer++;
			}
			setscreencolor(quiz.questionlist[questionnumber].answerresut);
		}
	}
	void playmathgame() {
		stquiz quiz;
		quiz.numberofquestion = 5;
		quiz.questionlevel = enquestionlevel::easylevel;
		quiz.operationtype = enoperationtype::mix;
		for (short questionumber = 0; questionumber < quiz.numberofquestion; questionumber++) {
			quiz.questionlist[questionumber] = generatequestion(quiz.questionlevel, quiz.operationtype);
		}
		askandcorrectquestion(quiz);
		cout << "\nquiz complete! rightanswers:" << quiz.numberofrightanswer << "wrong answer:" << quiz.numberofwronganswer << endl;
		cout << quiz.ispass ? "you passed the quiz!\n" : "ypu failed the quiz!\n):";
	}
	int main() {
		srand((unsigned)time(NULL));
		playmathgame();
			return 0;
	}
