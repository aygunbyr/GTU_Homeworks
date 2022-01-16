#include <iostream>
using namespace std;

struct student {
    int quiz1, quiz2;
    int midterm;
    int final_exam;
    double avg;
    char letter_grade;       
    void calculateAvg();
    void calculateLetterGrade();
};

void student::calculateAvg() {
    double quizAvg;
    quizAvg = (quiz1+quiz2)*0.5;
    avg = (0.5*final_exam)+(0.25*midterm)+10*(0.25*quizAvg);
}

void student::calculateLetterGrade() {
    if(avg <= 100.0 && avg >= 90.0)
        letter_grade = 'A';
    else if(avg >= 80.0)
        letter_grade = 'B';
    else if(avg >= 70.0)
        letter_grade = 'C';
    else if(avg >= 60.0)
        letter_grade = 'D';
    else if(avg >= 0.0)
        letter_grade = 'F';
}

int main() {
    int input;
    student student1;
    cout << "Enter quiz #1 grade: ";
    cin >> student1.quiz1;
    cout << "Enter quiz #2 grade: ";
    cin >> student1.quiz2;
    cout << "Enter midterm grade: ";
    cin >> student1.midterm;
    cout << "Enter final exam grade: ";
    cin >> student1.final_exam;
    student1.calculateAvg();
    student1.calculateLetterGrade();
    cout << "RESULTS" << endl;
    cout << "Average: "  << student1.avg << endl;
    cout << "Letter Grade: " << student1.letter_grade << endl;

    
    return 0;
}