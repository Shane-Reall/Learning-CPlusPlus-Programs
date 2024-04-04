// Name: SHANE REALL
// File Name: prog4.cpp
// Date: 15 March, 2023
// Program Description: A Minesweeper game Making use of Recusion

#include <iostream>
#include <cstring>
#include <fstream>

void load(int grid[][6], char *fileName); //Prototype for load function
int play(int grid[][6], int locationY, int locationX); //Prototype for play function
void print(int grid[][6], int &winCheck, int returned); //Prototype for print function

const int gridLength = 6; //Constants required for this project
const int gridWidth = 6;

using namespace std;

int main()
{
    int grid[6][6]; //Array that holds the grid for the game
    char fileName[10] = "mines.txt"; //Saves the name of the file holding the data for the grid
    bool endGame; //Boolean that checks for the end of the game
    int locationX; //The X axis on the Grid
    int locationY; //The Y axis on the Grid
    int returned = -1; //Holds the returned value of the play function
    int winCheck = 0; //Checks to see if the game was one

    load(grid, fileName); //load function is passed the grid and fileName to pull the data from the fileName and load it into the grid array

    endGame = false;

    while (endGame == 0) //loops the information below till the game is over
    {
        cout << "Enter tile location: ";
        cin >> locationY >> locationX; //Gets the X and Y values from the user

        winCheck = 0;
        
        returned = play(grid, locationX, locationY); //Sets the returned value to the return of the play function, which is passed the grid and loactions 

        print(grid, winCheck, returned); //passes the grid, winCheck and returned variables to print function

        if (returned == 0) //Checks to see if the player had lost
        {
            endGame = true;
            cout << "Bomb Hit! You Lost!" << endl;
        }
        if (winCheck == 0) // Checks to see if the player had won
        {
            endGame = true;
            cout << "YOU WIN!!!" << endl;
        }
    }
}

void load(int grid[][6], char *fileName) //This function takes the information feed to it, to create the grid array
{
    char gridHold; //Holds a single chracter at the time and loads it into the array
    int counter = 0; //Is used to count when to go to the next line of the array

    ifstream inFile(fileName); //Opens the File

    for (int i = 0; i < 41; i++) //loops through the entire file
    {
        inFile.get(gridHold); //Grabs the next character of the file

        if (gridHold == '-') //Compares the current character to -
        {
            grid[counter][i % 7] = -1; //loads the current character into its place
            cout << "-"; //sets the visual grid to show only -
        }
        else if (gridHold == 'x') //Compares the current character to x
        {
            grid[counter][i % 7] = -2; //loads the current character into its place
            cout << "-"; //sets the visual grid to show only -
        }
        else
        {
            counter++; //tells the loop to load the next characters into the next lines
            cout << endl; //Skips to the next line when displaying the grid
        }
    }

    cout << endl;

    inFile.close(); //Closes the File
}

int play(int grid[][6], int locationX, int locationY) //This function takes the information and begins changing the grid array to reflect what the player is doing
{
    int counter = 0; //Used to count the number of Bombs tounching the current square 

    if (locationX <= 5 && locationX >= 0 && locationY <= 5 && locationY >= 0) //Checks to see if player's values are within the range of the grid 
    {
        if (grid[locationY][locationX] == -2) //Checks to see if the current selected array section is a bomb
        {
            grid[locationY][locationX] = 9; //Sets the bomb to a value that cannot be used for the counter variable
            return 0; //Ends function
        }
        grid[locationY][locationX] = 0; //Sets current grid location to 0

        if (grid[locationY + 1][locationX] == -2) //Checks Lower for a Bomb
        {
            if (locationY + 1 <= 5) //Makes sure current checked loaction is within the grid
            {
                counter++;
            }
        }
        if (grid[locationY + 1][locationX + 1] == -2) //Checks Lower Right for a Bomb
        {
            if (locationY + 1 <= 5 && locationX + 1 <= 5) //Makes sure current checked loaction is within the grid
            {
                counter++;
            }
        }
        if (grid[locationY][locationX + 1] == -2) //Checks Right for a Bomb
        {
            if (locationX + 1 <= 5) //Makes sure current checked loaction is within the grid
            {
                counter++;
            }
        }
        if (grid[locationY - 1][locationX + 1] == -2) //Checks Upper Right for a Bomb
        {
            if (locationY - 1 >= 0 && locationX + 1 <= 5) //Makes sure current checked loaction is within the grid
            {
                counter++;
            }
        }
        if (grid[locationY - 1][locationX] == -2) //Checks Upper for a Bomb
        {
            if (locationY - 1 >= 0) //Makes sure current checked loaction is within the grid
            {
                counter++;
            }
        }
        if (grid[locationY - 1][locationX - 1] == -2) //Checks Upper Left for a Bomb
        {
            if (locationY - 1 >= 0 && locationX - 1 >= 0) //Makes sure current checked loaction is within the grid
            {
                counter++;
            }
        }
        if (grid[locationY][locationX - 1] == -2) //Checks Left for a Bomb
        {
            if (locationX - 1 >= 0) //Makes sure current checked loaction is within the grid
            {
                counter++;
            }
        }
        if (grid[locationY + 1][locationX - 1] == -2) //Checks Lower Left for a Bomb
        {
            if (locationY + 1 <= 5 && locationX - 1 >= 0) //Makes sure current checked loaction is within the grid
            {
                counter++;
            }
        }

        grid[locationY][locationX] = counter; //Sets current grid loaction to the number of surrounding bombs

        if (grid[locationY][locationX] == 0) //Checks to make sure current location is zero to make sure the recursion spots if its not
        {
            if (locationX + 1 <= 5) //Moves to Right
            {
                play(grid, locationX + 1, locationY); //Recersion of play with the loaction to the right
            }
            if (locationX + 1 <= 5 && locationY - 1 >= 0) //Moves to Upper Right
            {
                play(grid, locationX + 1, locationY - 1); //Recersion of play with the loaction to the upper right
            }
            if (locationY - 1 >= 0) //Moves to Upper
            {
                play(grid, locationX, locationY - 1); //Recersion of play with the loaction to the above loaction
            }
            if (locationX - 1 >= 0 && locationY - 1 >= 0) //Moves to Upper Left
            {
                play(grid, locationX - 1, locationY - 1); //Recersion of play with the loaction to the upper left
            }

            if (locationX - 1 >= 0) //Moves to Left
            {
                if (grid[locationY][locationX - 1] == -1) //Checks to see if the next grid location has been checked yet
                {
                    play(grid, locationX - 1, locationY);  //Recersion of play with the loaction to the left
                }
            }
            if (locationY + 1 <= 5 && locationX - 1 >= 0) //Moves to Lower Left
            {
                if (grid[locationY + 1][locationX - 1] == -1) //Checks to see if the next grid location has been checked yet
                {
                    play(grid, locationX - 1, locationY + 1);  //Recersion of play with the loaction to the lower left
                }
            }
            if (locationY + 1 <= 5) //Moves to Lower
            {
                if (grid[locationY + 1][locationX] == -1) //Checks to see if the next grid location has been checked yet
                {
                    play(grid, locationX, locationY + 1);  //Recersion of play with the loaction to the lower square
                }
            }
            if (locationX + 1 <= 5 && locationY + 1 <= 5) //Moves to Lower Right
            {
                if (grid[locationY + 1][locationX + 1] == -1) //Checks to see if the next grid location has been checked yet
                {
                    play(grid, locationX + 1, locationY + 1);  //Recersion of play with the loaction to the lower right
                }
            }
        }
    }
    
    return 1; // Ends function without telling main the game has ended
}

void print(int grid[][6], int &winCheck, int returned) //This function takes the given information and visualizes it in the console log
{
    for (int i = 0; i < 6; i++) //Grid's X-Axis
    {
        for (int t = 0; t < 6; t++) //Grid's Y-Axis
        {
            if (grid[i][t] == -1) //Sets all non-bomb spots to '-' & increases the winCheck
            {
                cout << "-";
                winCheck++;
            }
            else if (grid[i][t] == -2) //Sets all bomb spots to '-' or 'x' depending on if the game has been lost
            {
                if (returned != 0) //Checks to see if Game has Ended
                {
                    cout << "-";
                }
                else
                {
                    cout << "x";
                }
            }
            else if (grid[i][t] == 9) //Checks to see if a bomb tile has been seleted by the player
            {
                cout << "x";
            }
            else //Every other option that could be sent throught here, specificly the number of surrounding bombs
            {
                cout << grid[i][t];
            }
        }
        cout << endl;
    }
}