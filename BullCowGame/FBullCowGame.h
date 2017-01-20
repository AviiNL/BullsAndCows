#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <ctime>

#define TMap std::map
#define TSet std::vector

using FString = std::string;
using int32 = int;

struct FWord {
    FWord() {
        Word = "";
        MaxTries = 0;
    }

    FWord(FString word, int32 maxTries) {
        Word = word;
        MaxTries = maxTries;
    }

    FString Word;
    int32 MaxTries;
};

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EWordStatus {
    OK,
    Not_Isogram,
    Empty_Value,
    Not_Lowercase,
    Invalid_Length
};

class FBullCowGame {
public:
    FBullCowGame();
    void Reset();
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetWordLength() const;
    bool IsGameWon() const;
    EWordStatus CheckGuessValidity(FString) const;
    FBullCowCount SubmitGuess(FString);

private:
    FWord MyWord;
    int MyMaxTries;
    int MyCurrentTry;
    bool bGameWon;
    TSet<FWord> Words;
    FWord GetRandomWord();
};

