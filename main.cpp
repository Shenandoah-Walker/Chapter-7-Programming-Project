//World Series Champions Program


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*
Function: getTeams
Purpose: Read teams from file into vector
Parameters:
 - filename: name of file to read from
 - teams: vector to store teams
Returns: None
Preconditions: None
Postconditions: teams vector is populated with teams from file
*/
void getTeams(string filename, vector<string>& teams);

/*
Function: findWinner
Purpose: Find the number of wins for a specific team
Parameters:
 - teamName: name of team to find wins for
 - winners: vector of winners
Returns: Number of wins for specified team
Preconditions: None
Postconditions: None
*/
int findWinner(string teamName, const vector<string>& winners);

int main() {
    vector<string> teams;
    vector<string> winners;
    string teamName;

    // Read teams from file
    getTeams("Teams.txt", teams);

    //Read winners from file.
    getTeams("WorldSeriesWinners.txt", winners);

    //Display the list of teams.
    cout << "World Series Teams:" << endl;
    for (const string& team : teams) {
        cout << team << endl;
    }
    cout << endl;

    //Prompt user for team name and display number of wins.
    while (true) {
        cout << "Enter a team name (or 'quit' to exit): ";
        getline(cin, teamName);

        
        //Check if user wants to quit using teamName as a sentinel.
        if (teamName == "quit") {
            break;

        }

        int winCount = findWinner(teamName, winners);
        // Display the number of wins for the specified team. If the team has won once, write "time" instead of "times".
        if (winCount == 1) {
            cout << teamName << " won the World Series " << winCount << " time." << endl << endl;
        }
        else {
            cout << teamName << " won the World Series " << winCount << " times." << endl << endl;
        }
    }

    return 0;
}

//Use getTeams to read the teams from the file into the vector.
void getTeams(string filename, vector<string>& teams) {
    ifstream infile;
    infile.open(filename);

    if (infile.fail()) {
        cout << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    string teamName;
    while (getline(infile, teamName)) {
        teams.push_back(teamName);
    }

    infile.close();
}

//Use findWinner to find the number of wins for a specific team.
int findWinner(string teamName, const vector<string>& winners) {
    int count = 0;

    //Use a range-based for loop to iterate through winners.
    for (const string& winner : winners) {
        if (winner == teamName) {
            count++;
        }
    }

    return count;
}
