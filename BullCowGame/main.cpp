#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame("ant", 5);

// the entry point for our application
int main() {
    do {
        PrintIntro();
        PlayGame();
    } while (AskToPlayAgain());

    return 0; // exit the application
}

// introduce the game
void PrintIntro() {
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << BCGame.GetWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

void PlayGame() {
    BCGame.Reset("ant", 5);

    int32 MaxTries = BCGame.GetMaxTries();

    std::cout << "You have " << MaxTries << " attempts" << std::endl;

    // loop for the number of turns asking for guesses
    do {
        FText Guess = GetValidGuess();
        std::cout << "Your guess was: " << Guess << std::endl;

        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
        std::cout << "You got " << BullCowCount.Bulls << " Bulls and " << BullCowCount.Cows << " cows" << std::endl;

        if (BCGame.IsGameWon()) {
            std::cout << "You Win!" << std::endl << std::endl;
            return;
        }

        std::cout << std::endl;
    } while (BCGame.GetCurrentTry() <= BCGame.GetMaxTries());

    std::cout << "You lose, there are no more attempts left." << std::endl << std::endl;
}

FText GetValidGuess() {
    FText Guess;
    EWordStatus Status;

    do {
        std::cout << "Attempt " << BCGame.GetCurrentTry();
        if (BCGame.GetCurrentTry() == 1) {
            std::cout << ". Enter your guess: ";
        } else {
            std::cout << ": ";
        }

        std::getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);

        switch (Status) {
            case EWordStatus::Empty_Value:
                std::cout << "The guess can not be nothing" << std::endl << std::endl;
                break;
            case EWordStatus::Not_Isogram:
                std::cout << "The guess is not an isogram" << std::endl << std::endl;
                break;
            case EWordStatus::Not_Lowercase:
                std::cout << "The guess can only contain lowercast characters" << std::endl << std::endl;
                break;
            case EWordStatus::Invalid_Length:
                std::cout << "The guess has an invalid length" << std::endl << std::endl;
                break;
        }

    } while (Status != EWordStatus::OK);

    return Guess;

}

bool AskToPlayAgain() {
    FText response;
    std::cout << "Do you want to play again (y/n)? ";
    std::getline(std::cin, response);
    if (response[0] == 'y' || response[0] == 'Y') {
        return true;
    } else if (response[0] == 'n' || response[0] == 'N') {
        return false;
    }
    return AskToPlayAgain();
}
