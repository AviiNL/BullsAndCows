#include "FBullCowGame.h"

FBullCowGame::FBullCowGame(FString Word, int32 MaxTries) {
    Reset(Word, MaxTries);
}

void FBullCowGame::Reset(FString Word, int32 MaxTries) {
    bGameWon = false;
    MyWord = Word;
    MyMaxTries = MaxTries;
    MyCurrentTry = 1;
}

int32 FBullCowGame::GetMaxTries() const {
    return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const {
    return MyCurrentTry;
}

int32 FBullCowGame::GetWordLength() const {
    return MyWord.length();
}

bool FBullCowGame::IsGameWon() const {
    return bGameWon;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const {

    // Check if the Guess is empty
    if (Guess.length() == 0) {
        return EWordStatus::Empty_Value;
    }

    // Check if the Guess has an invalid length
    if (Guess.length() != GetWordLength()) {
        return EWordStatus::Invalid_Length;
    }

    // Check if the Guess has uppercase characters
    if (std::any_of(Guess.begin(), Guess.end(), [](char c) {
        return isupper(c);
    })) {
        return EWordStatus::Not_Lowercase;
    };

    // Check if the Guess not an isogram
    std::sort(Guess.begin(), Guess.end());
    if (std::adjacent_find(Guess.begin(), Guess.end()) != Guess.end()) {
        return EWordStatus::Not_Isogram;
    }

    // All is good
    return EWordStatus::OK;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
    ++MyCurrentTry;
    FBullCowCount BullCowCount;
    int WordLength = MyWord.length();
    int GuessLength = Guess.length();

    for (int32 i = 0; i < WordLength; i++) {
        for (int32 j = 0; j < GuessLength; j++) {
            if (MyWord[i] == Guess[j]) {
                if (i == j) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }
        }
    }

    if (BullCowCount.Bulls == GuessLength) {
        // It's a full match
        bGameWon = true;
    }

    return BullCowCount;
}
