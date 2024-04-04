// Name: SHANE REALL
// File Name: prog6.cpp
// Date: 19 April, 2023
// Program Description: a C++ program to compute some statistics about the 2022 - 23 Flacon Hoops season.You should define a structure type called Player and compute some player statistics.Specifically, for each player, it should compute field goal percentage, three pointer percentage, free throw percentage, and average points per game.It should read the data from an input file, perform the calculations, and display the result to the screen.Your program should also allow one to search a particular playerand display his numbers.The expected execution trace for the correct program is shown in Sample Execution.The data file will contain each player’s records.The file will be formatted as follows

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

struct Player //Player Structure
{
	string name;
	float gamesPlayed;
	float fieldGoalsMade;
	float fieldGoalsAttempt;
	float threePointersMade;
	float threePointersAttempt;
	float freeThrowsMade;
	float freeThrowsAttempt; //After is mathed
	float fieldGoalsPercent;
	float threePointersPercent;
	float freeThrowsPercent;
	float averagePointsPerGame;
};

typedef Player playType[50];

//Prototypes
int readData(playType);		
void calculateStats(playType, int);
void sortPlayers(playType, int);
void displayStats(playType, int);
void searchPlayer(playType, string, int);

int main()
{
	playType player;	//Variables
	bool looping = true;
	string letter;
	string playerName;
	string *pointer;
	int playersCount = 0;

	playersCount = readData(player); //Reading in Data size using readData Function

	calculateStats(player, playersCount);	//Calculating the Percentages
	sortPlayers(player, playersCount);		//Sorting the Players by there Averages per game
	displayStats(player, playersCount);		//Displaying the data for the user

	while (looping == true)	//Loop to check for when the user wishes to end the program
	{
		cout << "Do you want to search any player? (y/n)";
		cin >> letter;
		if (letter == "y")	//Checks to see if user selcted yes
		{
			cout << "Enter the player name: ";
			cin.ignore();
			getline(cin, playerName);
			searchPlayer(player, playerName, playersCount);	//Searches for the wanted Player
		}
		else if (letter == "n")	//Checks to see if user selcted no
		{
			cout << "Bye!";
			looping = false; //Ends the loop
		}
		else //Checks to see if user entered anything besides yes or no
		{
			cout << "That is not a possible response to the question.";
		}
	}

}

int readData(playType player) //Reads the Data from the .txt File
{
	char fileName[25];
	string line;
	int total = 0; //Tracks the amount of players

	cout << "What is the Name of the File: ";
	cin.getline(fileName, 25);

	ifstream indata;
	indata.open(fileName); //Opens File

	if (!indata) //Checks for File's Existaence
	{
		cout << "Error opening file. \n";
		cout << "It may not exist where indicated" << endl;

		return 1;
	}

	while (indata) //Loops till file ends
	{
		getline(indata, line, ':');

		player[total].name = line;

		indata >> player[total].gamesPlayed;	//Reads in the data
		indata >> player[total].fieldGoalsMade;
		indata >> player[total].fieldGoalsAttempt;
		indata >> player[total].threePointersMade;
		indata >> player[total].threePointersAttempt;
		indata >> player[total].freeThrowsMade;
		indata >> player[total].freeThrowsAttempt;

		total++;
		indata.ignore(); //Skips over the /n at the end of lines
	}

	return total - 1;
}

void calculateStats(playType player, int total) //Calculates Percentages
{
	//Variables used to make writing out equations easier
	float fgm = 0.0;
	float fga = 0.0;
	float tpm = 0.0;
	float tpa = 0.0;
	float ftm = 0.0;
	float fta = 0.0;
	float gp = 0.0;
	for (int i = 0; i < total; i++) //Loop to both read in infor to variable & Compleate Equations
	{
		player[i].fieldGoalsPercent = 0;
		player[i].threePointersPercent = 0;
		player[i].freeThrowsPercent = 0;
		player[i].averagePointsPerGame = 0;

		fgm = player[i].fieldGoalsMade;
		fga = player[i].fieldGoalsAttempt;
		tpm = player[i].threePointersMade;
		tpa = player[i].threePointersAttempt;
		ftm = player[i].freeThrowsMade;
		fta = player[i].freeThrowsAttempt;
		gp = player[i].gamesPlayed;

		if (player[i].fieldGoalsMade == 0 || player[i].fieldGoalsAttempt == 0) //Done to aviod Divide by Zero Issues
		{
			player[i].fieldGoalsPercent = 0.00;
		}
		else
		{
			player[i].fieldGoalsPercent = fgm / fga;
		}

		if (player[i].threePointersMade == 0 || player[i].threePointersAttempt == 0) //Done to aviod Divide by Zero Issues
		{
			player[i].threePointersPercent = 0.00;
		}
		else
		{
			player[i].threePointersPercent = tpm / tpa;
		}

		if (player[i].freeThrowsMade == 0 || player[i].freeThrowsAttempt == 0) //Done to aviod Divide by Zero Issues
		{
			player[i].freeThrowsPercent = 0.00;
		}
		else
		{
			player[i].freeThrowsPercent = ftm / fta;
		}

		if (player[i].fieldGoalsMade + player[i].freeThrowsMade == 0) //Done to aviod Divide by Zero Issues
		{
			player[i].averagePointsPerGame = 0.00;
		}
		else
		{
			player[i].averagePointsPerGame = (((fgm - tpm) * 2.0) + (tpm * 3.0) + (ftm)) / (gp);
		}
	}

	return;
}

void sortPlayers(playType player, int total) //Sorts the Players by there Average Points Per Game
{
	int i, j;
	for (i = 0; i < total - 1; i++) //Bubble Sorting
	{
		for (j = 0; j < total - i - 1; j++)
		{
			if (player[j].averagePointsPerGame < player[j + 1].averagePointsPerGame)
				swap(player[j], player[j + 1]);
		}
	}

	return;
}

void displayStats(playType player, int total) //Display Data
{
	cout << setw(20) << left << "Name" << setw(7) << "FG%" << setw(7) << "TP%" << setw(7) << "FT%" << setw(7) << "Average" << endl; //Formating Titles
	cout << "---------------------------------------------------" << endl;
	for (int i = 0; i < total; i++) //Formatting the Data with the Titles
	{
		cout << setw(20) << left << player[i].name;
		cout << setw(7) << fixed << setprecision(2) << player[i].fieldGoalsPercent;
		cout << setw(7) << fixed << setprecision(2) << player[i].threePointersPercent;
		cout << setw(7) << fixed << setprecision(2) << player[i].freeThrowsPercent;
		cout << setw(7) << fixed << setprecision(2) << player[i].averagePointsPerGame;
		if (i != total - 1)//Done to aviod blank line between last entry and bottom dashed line
		{
			cout << endl;
		}
	}
	cout << endl << "---------------------------------------------------" << endl;

	return;
}

void searchPlayer(playType player, string playerName, int total) //Searches for the requested Player
{
	int requestedPlayer = -1;

	for (int i = 0; i < total; i++) //Loops till requested player is found or till end of data
	{
		if (player[i].name == playerName)
		{
			requestedPlayer = i;
			i = total;
		}
	}

	if (requestedPlayer != -1) //Checks to see if Player was found
	{
		//Displays the Requested Player's Data
		cout << "Number of games played: " << player[requestedPlayer].gamesPlayed << endl;
		cout << "Field goal %: " << player[requestedPlayer].fieldGoalsPercent << endl;
		cout << "Three pointer %: " << player[requestedPlayer].threePointersPercent << endl;
		cout << "Free throw %: " << player[requestedPlayer].freeThrowsPercent << endl;
		cout << "Average points per game: " << player[requestedPlayer].averagePointsPerGame << endl;
	}
	else //Incase the player is not found
	{
		cout << "Player was not found!" << endl;
	}

	return;
}