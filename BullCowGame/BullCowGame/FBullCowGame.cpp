#pragma once
#include "FBullCowGame.h"
#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame(){ Reset();}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "BLUNT";
	MyHiddenWord = HIDDEN_WORD;

	for (std::string::size_type i = 0; i < MyHiddenWord.length(); ++i)
		MyHiddenWord[i] = tolower(MyHiddenWord[i]);

	MyCurrentTry = 1;
	NoOfBulls = 0;
	return;
}

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,16},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry;}

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}

bool FBullCowGame::IsGameWon() const
{
	if (NoOfBulls == MyHiddenWord.length())
	{
		return true;
	}
	return false;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString guess)
{
	int32 HiddeWordLength = guess.length();

	// Check if length mismatch
	if (guess.length() != MyHiddenWord.length())
	{
		return EWordStatus::Length_Mismatch;
	}

	// Check for case
	if (!IsLowercase(guess))
	{
		return EWordStatus::Not_Lowercase;
	}

	// Check if guess is an isogram
	if (!IsIsogram(guess))
	{
		return EWordStatus::Not_Isogram;
	}

	return EWordStatus::OK;
}

// Receive a VALID Guess, increaments count and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	// compare letters against the hidden word
	int32 HiddeWordLength = guess.length();

	for (int32 n = 0; n < HiddeWordLength; n++)
	{
		int32 index = MyHiddenWord.find(guess[n]);
		if (index == n)
		{
			BullCowCount.Bulls++;
		}
		else if (index != -1)
		{
			BullCowCount.Cows++;
		}
	}

	NoOfBulls = BullCowCount.Bulls;
	return BullCowCount;
}

bool FBullCowGame::IsLowercase(FString guess) const
{
	for (auto Letter : guess)
	{
		if (Letter < 'a' || Letter > 'z')
		{
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsIsogram(FString guess) const
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : guess)
	{
		if (LetterSeen[Letter])
			return false;
		LetterSeen[Letter] = true;
	}
	return true;
}
