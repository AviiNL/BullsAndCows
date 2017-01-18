#pragma once

#include <iostream>
#include <algorithm>
#include <string>

using FString = std::string;
using int32 = int;

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
    FBullCowGame(FString, int32);
    void Reset(FString, int32);
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetWordLength() const;
    bool IsGameWon() const;
    EWordStatus CheckGuessValidity(FString) const;
    FBullCowCount SubmitGuess(FString);

private:
    FString MyWord;
    int MyMaxTries;
    int MyCurrentTry;
    bool bGameWon;
};

