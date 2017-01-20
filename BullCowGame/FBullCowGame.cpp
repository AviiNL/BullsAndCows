#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() {

    // Fill Word List
    Words.push_back(FWord("cow", 5));
    Words.push_back(FWord("ape", 5));
    Words.push_back(FWord("ant", 5));
    Words.push_back(FWord("dog", 5));
    Words.push_back(FWord("cat", 5));

    Words.push_back(FWord("bear", 7));
    Words.push_back(FWord("lion", 7));

    Words.push_back(FWord("tiger", 8));
    Words.push_back(FWord("rhino", 8));
    Words.push_back(FWord("zebra", 8));
    Words.push_back(FWord("tapir", 8));

    Words.push_back(FWord("donkey", 10));
    Words.push_back(FWord("monkey", 10));
    Words.push_back(FWord("cougar", 10));

    Words.push_back(FWord("pelican", 12));
    Words.push_back(FWord("hamster", 12));
    Words.push_back(FWord("leopard", 12));

    Reset();
}

void FBullCowGame::Reset() {
    bGameWon = false;
    MyWord = GetRandomWord();
    MyCurrentTry = 1;
}

int32 FBullCowGame::GetMaxTries() const {
    return MyWord.MaxTries;
}

int32 FBullCowGame::GetCurrentTry() const {
    return MyCurrentTry;
}

int32 FBullCowGame::GetWordLength() const {
    return MyWord.Word.length();
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
    TMap<char, bool> LettersSeen;

    for (char Letter : Guess) {
        if (LettersSeen[Letter]) {
            return EWordStatus::Not_Isogram;
        }

        LettersSeen[Letter] = true;
    }

    // All is good
    return EWordStatus::OK;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
    ++MyCurrentTry;
    FBullCowCount BullCowCount;
    int WordLength = GetWordLength();
    int GuessLength = Guess.length();

    for (int32 i = 0; i < WordLength; i++) {
        for (int32 j = 0; j < GuessLength; j++) {
            if (MyWord.Word[i] == Guess[j]) {
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

FWord FBullCowGame::GetRandomWord() {
    srand(time(NULL));
    int32 random = rand() % Words.size();

    return Words[random];
}
