//Exam Grader Program


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int numQuestions = 20;

/*
Function: getAnswers
Purpose: Reads answers from a file and stores them in an array.
Parameters:
 - filename: The name of the file to read from.
 - answers: The array to store the answers in.
 Returns: None
Preconditions: The file must exist and contain exactly numQuestions answers.
Postconditions: The answers array will be filled with the answers from the file.
 */
void getAnswers(const char* filename, char answers[]);

/*
Function: gradeExam
Purpose: Compares the correct answers with the student's answers and tracks missed questions.
Parameters:
 - correctAnswers: The array of correct answers.
 - studentAnswers: The array of student's answers.
 - missedQuestions: The array to store the missed question numbers.
 - missedAnswersData: The array to store the correct and student answers for missed questions.
Returns: The number of missed questions.
Preconditions: The correctAnswers and studentAnswers arrays must be filled with answers.
Postconditions: The missedQuestions and missedAnswersData arrays will be filled with the missed questions and answers.
*/
int gradeExam(const char correctAnswers[], const char studentAnswers[], int missedQuestions[], char missedAnswersData[][2]);
/*
Function: writeReport
Purpose: Writes the exam report to the console.
Parameters:
 - missedQuestions: The array of missed question numbers.
 - numMissed: The number of missed questions.
 - missedAnswersData: The array of correct and student answers for missed questions.
Returns: None
Preconditions: The missedQuestions and missedAnswersData arrays must be filled with the missed questions and answers.
Postconditions: The exam report will be written to the console.
*/
void writeReport(const int missedQuestions[], int numMissed, 
                 const char missedAnswersData[][2]);

int main() {
    char correctAnswers[numQuestions];
    char studentAnswers[numQuestions];
    int missedQuestions[numQuestions];
    char missedAnswersData[numQuestions][2]; 

    //Use getAnswers to read correct answers from CorrectAnswers.txt.
    getAnswers("CorrectAnswers.txt", correctAnswers);

    //Use getAnswers to read student answers from StudentAnswers.txt.
    getAnswers("StudentAnswers.txt", studentAnswers);

    //Grade the exam. The numMissed variable will hold the number of missed questions. Use the gradeExam function to determine the number of missed questions and fill the missedQuestions and missedAnswersData arrays.
    int numMissed = gradeExam(correctAnswers, studentAnswers, 
                              missedQuestions, missedAnswersData);

    //Use writeReport to print the exam report to the console. The exam report should show the number of missed questions, the missed questions and the correct answers, and the test score.
    writeReport(missedQuestions, numMissed, missedAnswersData);

    //Return 0 to indicate successful completion.
    return 0;
}

void getAnswers(const char* filename, char answers[]) {
    ifstream infile;
    infile.open(filename);

    //Ensure the file opened successfully. If not, print an error message and exit.
    if (infile.fail()) {
        cout << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    //Read the answers from the file. If the file does not contain exactly numQuestions answers, print an error message and exit.
    for (int i = 0; i < numQuestions; i++) {
        infile >> answers[i];
        if (infile.fail()) {
            cout << "Error: Could not read answer " << (i + 1) << " from file " << filename << endl;
         exit(1);
        }
    }

    infile.close();
}

int gradeExam(const char correctAnswers[], const char studentAnswers[],
              int missedQuestions[], char missedAnswersData[][2]) {
    int numMissed = 0;

    //Compare answers and track missed questions
    for (int i = 0; i < numQuestions; i++) {
        if (correctAnswers[i] != studentAnswers[i]) {
            missedQuestions[numMissed] = i + 1; // Store question number (1-based)
            missedAnswersData[numMissed][0] = correctAnswers[i]; // Correct answer
            missedAnswersData[numMissed][1] = studentAnswers[i]; // Student answer
            numMissed++;
        }
    }

    return numMissed;
}

void writeReport(const int missedQuestions[], int numMissed,
                 const char missedAnswersData[][2]) {
    cout << "Exam Report Details" << endl;
    cout << "Number Questions missed: " << numMissed << endl;

    if (numMissed > 0) {
        cout << "Missed questions and correct answers:" << endl;
        cout << "Question   Correct Answer   Your Answer" << endl;
        for (int i = 0; i < numMissed; i++) {
            cout << setw(4) << missedQuestions[i]
                 << setw(14) << missedAnswersData[i][0]
                 << setw(14) << missedAnswersData[i][1] << endl;
        }
    }

    //Calculate and display percentage
    double percentage = ((double)(numQuestions - numMissed) / numQuestions) * 100.0;
    cout << fixed << setprecision(2);
    cout << "Test score: " << percentage << "%" << endl;

    //Determine pass/fail
    if (percentage >= 70.0) {
        cout << "You passed the exam." << endl;
    } else {
        cout << "You failed the exam." << endl;
    }
}