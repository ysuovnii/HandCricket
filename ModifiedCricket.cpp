#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int userScore = 0, compScore = 0;

// Toss function
bool tossWin() {
    int userChoice, tossNum, tossResult;
    cout << "TOSS TIME!\nChoose Odd(1) or Even(2): ";
    cin >> userChoice;
    if (userChoice != 1 && userChoice != 2) {
        cout << "Invalid choice. Defaulting to Even.\n";
        userChoice = 2;
    }

    int userNum;
    cout << "Enter your toss number (1-6): ";
    cin >> userNum;
    tossNum = rand() % 6 + 1;
    cout << "Computer chose: " << tossNum << endl;

    tossResult = userNum + tossNum;
    cout << "Sum: " << tossResult << " => " << ((tossResult % 2 == 0) ? "Even" : "Odd") << endl;

    if ((tossResult % 2 == 0 && userChoice == 2) || (tossResult % 2 != 0 && userChoice == 1)) {
        cout << "You won the toss!\n";
        return true;
    } else {
        cout << "Computer won the toss.\n";
        return false;
    }
}

// Batting function
int batting(bool isUserBatting) {
    int score = 0;
    int userInput, compInput;

    while (true) {
        if (isUserBatting) {
            cout << "Your shot (1-6): ";
            cin >> userInput;
            if (userInput < 1 || userInput > 6) {
                cout << "Invalid input! Enter between 1-6.\n";
                continue;
            }
            compInput = rand() % 6 + 1;
            cout << "Computer bowled: " << compInput << endl;
        } else {
            compInput = rand() % 6 + 1;
            cout << "Your bowl (1-6): ";
            cin >> userInput;
            if (userInput < 1 || userInput > 6) {
                cout << "Invalid input! Enter between 1-6.\n";
                continue;
            }
            cout << "Computer played: " << compInput << endl;
        }

        if (userInput == compInput) {
            cout << "OUT!\n";
            break;
        } else {
            score += (isUserBatting ? userInput : compInput);
            cout << "Score: " << score << endl;
        }
    }
    return score;
}

int main() {
    srand(time(0));
    cout << "----- HAND CRICKET GAME -----\n";

    bool userWonToss = tossWin();
    bool userBatsFirst;

    if (userWonToss) {
        int choice;
        cout << "Choose:\n1. Bat\n2. Bowl\nYour choice: ";
        cin >> choice;
        userBatsFirst = (choice == 1);
    } else {
        userBatsFirst = rand() % 2 == 0;
        cout << "Computer chose to " << (userBatsFirst ? "bowl" : "bat") << " first.\n";
    }

    // First Innings
    if (userBatsFirst) {
        cout << "\n--- Your Batting ---\n";
        userScore = batting(true);
        cout << "\nYour total score: " << userScore << "\n\n";

        cout << "--- Computer Batting ---\n";
        compScore = 0;
        while (compScore <= userScore) {
            int run = batting(false);
            compScore = run;
            break;
        }
    } else {
        cout << "\n--- Computer Batting ---\n";
        compScore = batting(false);
        cout << "\nComputer total score: " << compScore << "\n\n";

        cout << "--- Your Batting ---\n";
        userScore = 0;
        while (userScore <= compScore) {
            int run = batting(true);
            userScore = run;
            break;
        }
    }

    // Result
    cout << "\n--- MATCH RESULT ---\n";
    cout << "Your Score: " << userScore << "\n";
    cout << "Computer Score: " << compScore << "\n";

    if (userScore > compScore)
        cout << "You Win!\n";
    else if (userScore < compScore)
        cout << "Computer Wins.\n";
    else
        cout << "It's a Tie!\n";

    return 0;
}
