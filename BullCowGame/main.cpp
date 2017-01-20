#include <iostream>
#include <string>
#include <math.h>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

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

    std::cout << std::endl;

    std::cout << " ____        _ _                       _    ____" << std::endl;
    std::cout << "| __ ) _   _| | |___    __ _ _ __   __| |  / ___|_____      _____" << std::endl;
    std::cout << "|  _ \\| | | | | / __|  / _` | '_ \\ / _` | | |   / _ \\ \\ /\\ / / __|" << std::endl;
    std::cout << "| |_) | |_| | | \\__ \\ | (_| | | | | (_| | | |__| (_) \\ V  V /\\__ \\" << std::endl;
    std::cout << "|____/ \\__,_|_|_|___/  \\__,_|_| |_|\\__,_|  \\____\\___/ \\_/\\_/ |___/" << std::endl;
    std::cout << "By AviiNL as part of the Unreal Course on udemy.com" << std::endl;
    std::cout << std::endl;

    
    return;
}

void PlayGame() {
    BCGame.Reset();

    std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
    std::cout << "The game is simple, you need to guess a " << BCGame.GetWordLength() << " letter word" << std::endl;
    std::cout << "The word must have all letters different (isogram)." << std::endl;
    std::cout << "A small hint: All words are animals" << std::endl;
    std::cout << "The bulls count the number of letters that are in the correct place" << std::endl;
    std::cout << "The cows count the number of letters that are in the wrong place" << std::endl;
    std::cout << std::endl;

    int32 MaxTries = BCGame.GetMaxTries();

    std::cout << "You have " << MaxTries << " attempts. Good luck!" << std::endl << std::endl;

    // loop for the number of turns asking for guesses
    do {
        FText Guess = GetValidGuess();
        // std::cout << "Your guess was: " << Guess << std::endl;

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
            std::cout << ". Enter your guess";
        }
        std::cout << ": ";
        

        std::getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);

        switch (Status) {
            case EWordStatus::Empty_Value:
                std::cout << "Your guess can not be nothing";
                break;
            case EWordStatus::Not_Isogram:
                std::cout << "\"" << Guess << "\" is not an isogram";
                break;
            case EWordStatus::Not_Lowercase:
                std::cout << "Your guess can only contain lowercast characters";
                break;
            case EWordStatus::Invalid_Length:
                std::cout << "Your guess has an invalid length, it should be " << BCGame.GetWordLength() << " characters long";
                break;
        }

        if (Status != EWordStatus::OK) {
            std::cout << std::endl << std::endl;
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
