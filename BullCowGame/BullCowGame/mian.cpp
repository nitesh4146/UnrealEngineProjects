/*
This is the console executable that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
bool AskToPlayGame();

FBullCowGame BCGame;	// Instantiate a new game

int32 main()
{
	//std::cout << BCGame.GetMaxTries() << std::endl;
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayGame());
	
	return 0;
}

void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	FBullCowCount BC_count;

	// Loops for the number of turns asking for guesses
	FText Guess = "";

	// loop asking for guesses while the game is NOT won
	// abd there are still tries remianing
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Guess = GetValidGuess();

		// Submit valid guess to the game
		BC_count = BCGame.SubmitGuess(Guess);

		// Print number of bulls and cows
		std::cout << "Bulls: " << BC_count.Bulls << " Cows: " << BC_count.Cows << std::endl << std::endl;
	}
	PrintGameSummary();
}

void PrintIntro()
{
	// introduce the game
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You Won!!\n******************************************\n";
	}
	else
	{
		std::cout << "Better luck next time.\n\n";
	}
}


FText GetValidGuess()
{
	EWordStatus Status = EWordStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 Current_Try = BCGame.GetCurrentTry();
		// get a guess from the player
		std::cout << "Try " << Current_Try << " of "<< BCGame.GetMaxTries() << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		// Check for valid guess
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Length_Mismatch:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase word.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EWordStatus::OK);
	
	return Guess;
}

bool AskToPlayGame()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	if (Response[0] == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}
