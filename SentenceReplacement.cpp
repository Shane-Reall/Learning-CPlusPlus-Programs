// Name: SHANE REALL
// File Name: prog3.cpp
// Date: 01 March, 2023
// Program Description: A search and replace program for .txt files.

#include <iostream>
#include <cstring>
#include <fstream>

int length(char*); //Prototype for the length function
char* read(char*, char*); //Prototype for the read function
char* replace(char*, char*, char*); //Prototype for the replace function

using namespace std;

int main()
{
	char fileName[100]; //Char array used to hold fileName, size is set to 100 to account for most possible file name sizes
	char *pointer; //Char pointer used to point toward the fileName
	char *characters = NULL; //Char pointer to point toward the entire write text inside of the file
	char searchWord[100]; //Char array used to hold the word to be searched, size is set to 100 to account for most possible searchable word sizes
	char replaceWord[100]; //Char array used to hold the word to be replaced with, size is set to 100 to account for most possible word sizes
	char *searchPointer = NULL; //Char pointers that point toward the searchWord char array
	char *replacePointer = NULL; //Char pointers that point toward the replaceWord char array

	int fileLength; //An int of the total length of the text inside of the file

	cout << "Enter the filename: "; //Requesting and recieving the filename, search word, and replace word
	cin.getline(fileName, 100);
	cout << "Enter the search word: ";
	cin >> searchWord;
	cout << "Enter the replace word: ";
	cin >> replaceWord;

	pointer = fileName; //setting the filename to a pointer so it can be passed into a function

	fileLength = length(pointer); //valuing the fileLength by calling the length function with pointer

	characters = new char[fileLength * 2]; //using new to create the size of the characters array to allow the complete text to fit inside of it.

	characters = read(pointer, characters); //valuing the character array by calling the read function and passing it the pointer and the empty characters array.

	cout << "Original content:" << endl; //Out putting the original content of the file
	cout << characters << endl << endl << endl;

	replacePointer = replaceWord; //converting the replaceWord and searchWord values into pointers to be passed to a function
	searchPointer = searchWord;

	replace(characters, searchPointer, replacePointer); //Calling the replace function by passing it the characters array, searchPointer, and replacePointer

	delete [] characters; //deleteing the new created on line 39

}

int length(char *fileName) //Length function is used to find the total length of the text inside of the file
{
	char fileText[10000]; //creating an array to hold a massive amount of characters
	int pos = 0; // a counter used to track the number of characters
	
	ifstream inFile(fileName); //opening the file
	
	inFile.get(fileText, 10000); //reading the entire file into the fileText string

	pos = strlen(fileText); //reading the lenght of the fileText string

	inFile.close(); //closing the file

	return pos; //returning the count of the length
}

char* read(char *fileName, char *fileContent) //function used to read the contents of the file into an char array
{
	int length = strlen(fileContent); //finding the lenght of the file text

	ifstream inFile(fileName); //opening the file

	inFile.get(fileContent, length*2); //geting the entire context of the file

	inFile.close(); //closing the file

	return fileContent; //returning the context of the file
}

char* replace(char* fileContent, char* oldWord, char* newWord) //function that reads through the file to find and replace words
{
	#pragma warning(disable : 4996) //Code will not work without this due to Visual Studios not allowing the use of strtok due to it being "unsafe"

	char* token; //used to tokenize the fileContent by space
	char delimiter[3] = " "; //what's being tokenized by
	char passFile[10000] = ""; //what the fileContent is being loaded into as it is tokenized
	int oldLength = strlen(oldWord); //orignal length of the fileContent
	int newLength = strlen(newWord); //new length of the passFile
	char holdingP[100] = ""; //char strings used to hold a version of the oldWord with a period at the end
	char holdingC[100] = ""; //char strings used to hold a version of the oldWord with a comma at the end
	int fileSize = strlen(fileContent); //finding the current file length of the fileContent
	

	strncpy(holdingP, oldWord, oldLength); //copies the oldWord and creates two version with a period and comma ending the word
	strcat(holdingP, ".");
	strncpy(holdingC, oldWord, newLength);
	strcat(holdingC, ",");

	token = strtok(fileContent, delimiter); //begining of tokenizing the fileContent
	while (token != NULL) //looping till the end is found
	{
		if (!strcmp(token, oldWord)) //checks for a match between the oldWord and token
		{
			token = newWord; //changes oldWord to newWord
		}
		else if (!strcmp(token, holdingP)) //checks for a match between the holdingP and token
		{
			token = strcat(newWord, "."); //changes holdingP to newWord
		}
		else if (!strcmp(token, holdingC)) //checks for a match between the holdingC and token
		{
			token = strcat(newWord, ","); //changes holdingC to newWord
		}
		strcat(passFile, token); //moves curent word to the passFile array
		strcat(passFile, " "); //puts a space after each word loaded into the passFile array
		token = strtok(NULL, delimiter); //resets the token for next run of loop
	}

	cout << "Modified content:" << endl << passFile << endl; //outing the modified text

	return 0; //returning nothing
}