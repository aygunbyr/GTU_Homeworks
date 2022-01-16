#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Player {
    public:
        virtual int getGuess() {return 0;}
};

class HumanPlayer : public Player {
    public:
        virtual int getGuess()
        {
            int guess;
            cout << "Enter guess number:";
            cin >> guess;
            return guess;
        }
};

class ComputerPlayer : public Player {
    public:
        virtual int getGuess(){return rand() % 100;}
};

bool checkForWin(int guess, int answer);
void play(Player &player1, Player &player2);

int main() {
    srand(time(NULL));
    ComputerPlayer cpu1, cpu2;
    HumanPlayer human1, human2;

    cout << "###### HUMAN VERSUS HUMAN ###### " << endl;
    play(human1, human2);

    cout << "###### HUMAN VERSUS COMPUTER ###### " << endl;
    play(human1, cpu1);

    cout << "###### COMPUTER VERSUS COMPUTER #1 ###### " << endl;
    play(cpu1, cpu2);

    cout << "###### COMPUTER VERSUS COMPUTER #2 ###### " << endl;
    play(cpu1, cpu2);
    
    return 0;
}

bool checkForWin(int guess, int answer)
{
    if(answer == guess)
    {
        cout << "You're right! You win!" << endl;
        return true;
    }
    else if(answer < guess)
        cout << "Your guess is too high." << endl;
    else
        cout << "Your guess is too low." << endl;
    return false;
}

void play(Player &player1, Player &player2)
{
    int answer = 0, guess = 0;
    answer = rand( ) % 100;
    bool win = false;
    while (!win)
    {
        cout << "Player 1's turn to guess." << endl;
        guess = player1.getGuess( );
        win = checkForWin(guess, answer);
        if (win) return;

        cout << "Player 2's turn to guess." << endl;
        guess = player2.getGuess( );
        win = checkForWin(guess, answer);
    }
}
