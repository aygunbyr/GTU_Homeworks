#include <iostream>
#include <string>
using namespace std;

class Student {
    public:
    void resetClasses();
    void getUserInput();
    inline void setnumClasses(int num) {*numClasses=num;}
    inline string getName() {return *name;}
    inline int getnumClasses() {return *numClasses;}
    inline string getCourseName(int classIndex) {return classList[classIndex];}
    inline void allocateclasslist(int numClass) {classList = new string[numClass];} 
    void printInformation();
    void operator=(Student student2);
    Student() { // constructor
        name = new string;
        numClasses = new int;
        *numClasses = 0;
        classList = new string[20];
    }
    ~Student() { // destructor
        delete name;
        delete numClasses;
        delete[] classList;
    }

    private:
    string* name;
    int* numClasses; //how many courses the student is currently enrolled in
    string* classList;
};

int main() {
    int i;
    Student student, student2;

    cout << "STUDENT #1" << endl;
    student.getUserInput();
    student.printInformation();

    cout << "STUDENT #2" << endl;
    student2.getUserInput();
    student2.printInformation();

    // Reset operation
    student2.resetClasses();
    cout << "Student #2 information have been reset." << endl;
    student2.printInformation();

    // Copy course information with overloaded assign operator.
    student2=student;
    cout << "Courses of Student #1 have copied to Student #2." << endl;
    student2.printInformation();

    return 0;
}

void Student :: resetClasses() {
    *numClasses = 0;
    delete[] classList;
    classList = new string[20];
}

void Student :: getUserInput() {
    string strInput;
    cout << "Enter name of the student: ";
    getline(cin >> ws, *name);

    cout << "Youre going to enter courses students enrolled, enter \"-1\" to stop." << endl;
    do {
        cout << "Enter name of the course: ";
        getline(cin >> ws, strInput);
        if(strInput != "-1")
        {
            classList[*numClasses] = strInput;
            (*numClasses)++;
        }
    } while(strInput != "-1");
}

void Student :: printInformation() {
    int i;
    cout << "Student name: " << *name << endl;
    cout << "Number of courses: " << *numClasses << endl;
    for(i=0; i<*numClasses; i++)
        cout << i+1 << ". " << classList[i] << endl;
}

void Student::operator=(Student student2) {
    int i;
    // Copy information of classes
    *numClasses = student2.getnumClasses();
    classList = new string[*numClasses];
    for(i=0; i<*numClasses; i++)
        classList[i] = student2.getCourseName(i);
}
