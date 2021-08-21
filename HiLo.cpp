
#include <iostream>
#include <random> // for std::mt19937

namespace constants {
    constexpr int minRand = 1;
    constexpr int maxRand = 100;
    constexpr int maxGuesses = 7;
}

using namespace std;
using namespace constants;

void invalidEntry() {
    cout << "INVALID ENTRY. TRY AGAIN\n";
}

int getInput() {
    int input;
    cin >> input;
    while (cin.fail()) { // validation
        cin.clear();
        cin.ignore(32767, '\n');
        invalidEntry();
        cin >> input;
    }
    cin.ignore(32767, '\n'); //get rid of extraneous input
    return input;
}

bool evalGuess(int target, int guess) {
    if (guess == target) {
        cout << "Correct\n";
        return true;
    }
    if (guess > target) cout << "Too High\n";
    else cout << "Too Low\n";
    return false;
}

void playHiLo(int target) {
    int guessCount = 0;
    int currentGuess;
    bool correct = false;

    cout << "Hi-Lo Game Initiated. " << "Target: " << target << "\n";

    while ((maxGuesses > guessCount) && !correct) {
        cout << "Guess# " << guessCount + 1 << " - Enter guess between " << minRand << " and " << maxRand << "\n";

        currentGuess = getInput();
        if ((currentGuess <= maxRand) && (currentGuess >= minRand)) {
            guessCount++;
            correct = evalGuess(target, currentGuess);
        }
        else invalidEntry();
    }
    !correct ? cout << "You lose\n" : cout << "You won in " << guessCount << " guesses.\n";
}

bool playAgain() {
    int input;
    cout << "Play Again? (0)-No, (1)-Yes\n";
    while (1) {
        input = getInput();
        if (input == 1) return true;
        else if (input == 0) return false;
        else invalidEntry();
    }
}

int main() {
    bool running = true;

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(minRand, maxRand);

    while (running) {
        playHiLo(dist6(rng));
        running = playAgain();
    }
    return 0;
}