// Name: SHANE REALL
// File Name: prog5.cpp
// Date: 29 March, 2023
// Program Description: program to create, play, and edit a music playlist

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

struct Node	//Structure used for node creation
{
	string song;
	string artist;
	Node* next;
};

void buildPlaylist(char*, Node*, Node*, int&);	//Prototypes for lower functions
void showPlaylist(Node*);
void playSong(Node*, int);
void removeSong(Node*&, Node*, int&);

int main()
{
	char fileName[25];	//Variable to hold File Name
	int option = 0;	//Variable to hold user selection
	int playlistLength = 0;	//Variable to hold length of the imported playlist
	bool looping = true;	//Booleon to check if a loop should continue or not

	cout << "What is File Name: ";
	cin >> fileName; //Gets file name from user

	Node* head = NULL;
	head = new Node;

	Node* tail = head;

	buildPlaylist(fileName, head, tail, playlistLength);	//Creates the playlist
	cout << "Playlist created!" << endl << endl;	//Tells user playlist was created

	while (looping == true)
	{
		cout << "1) Show the playlist" << endl << "2) Play a song" << endl << "3) Remove a song" << endl << "4) Quit" << endl << endl;	//Shows all options
		cout << "Enter your option:";
		cin >> option;	//Gets user's selected option

		if (option == 1)
		{
			showPlaylist(head); //Outs the entire playlist
		}
		else if (option == 2)
		{
			playSong(head, playlistLength);	//Plays a song in the playlist
		}
		else if (option == 3)
		{
			removeSong(head, tail, playlistLength);	//Removes a song from the playlist
		}
		else if (option == 4)
		{
			looping = false;	//Ends loop to the program
		}
		else
		{
			cout << "Invalid option, enter again!";	//Checks for invalid inputs
		}

	}
}

void buildPlaylist(char *fileName, Node* head, Node* tail, int &playlistLength) //Builds playlist
{
	#pragma warning(disable : 4996)	//Disables error message involved with Tokening

	char lineHold[50]; //Holds a line from the text file read
	char* token;	//Token used for Tokenizing
	char delimiter[3] = ":";	//What is being checked for to sperate lines
	int i = 0;	//Variable used for compairason
	int firstCheck = 0;	//Also used for compairasons

	ifstream inFile(fileName);	//Opens the file

	while (!inFile.eof())	//Checks for the end of the File
	{
		playlistLength++;	//Reads the size of the list as it is created
		inFile.getline(lineHold, 50);	//Sets a value to the 'lineHold'
		Node* pnew = new Node;	//Creates a new Node to add information into

		token = strtok(lineHold, delimiter);
		while (token != NULL)	//Loops till done
		{

			i++;

			if (firstCheck == 0)	//Checks to see if this is the first loop around
			{
				if (i == 1)
				{
					head->song = token;	//Sets head->song to token
				}
				else
				{
					head->artist = token;	//Sets head->artist to token
					head->next = NULL;	//Creates a blank space for connections later on
					i = 0; //Resets the i value for later use
					//cout << head->song << " by " << head->artist << endl << endl;
				}
			}
			else if (i == 1)//Checks to see if song or artist need to be added to the playlist
			{
				pnew->song = token;	//Adds song to playlist
			}
			else
			{
				pnew->artist = token;	//Setting the artist and tails for current values
				tail->next = pnew;
				tail = pnew;
				tail->next = NULL;
			}
			token = strtok(NULL, delimiter);	//Resets token's value
		}
		firstCheck++;
		i = 0;	
	}

	inFile.close();	//Closes file

	return;
}

void showPlaylist(Node* head)	//Outs the playlist in the console log
{
	int counter = 1;

	cout << "-------------------------------------" << endl;

	Node* walker = NULL;	//Traverses the list
	walker = head;
	while (walker != NULL)
	{
		cout << counter << ") ";	//Number of song
		cout << setw(21) << left << walker->song << setw(21) << left << walker->artist << endl; //Outs song and it's artist
		walker = walker->next;	//Moves walker to next node
		counter++;
	}

	cout << "-------------------------------------" << endl;

	return;
}

void playSong(Node* head, int playlistLength) //'Plays' a selected song
{
	int selectNumber;	//User input
	bool loopCheck = true;	//Boolean to check to continue looping

	while (loopCheck == true)	//Checks if input is between the required numbers
	{
		cout << "Enter the song number(1-" << playlistLength << ") :";	
		cin >> selectNumber;	
		if (selectNumber > 0 && selectNumber < playlistLength + 1)	
		{
			loopCheck = false;
		}
	}
	

	Node* walker = NULL;	//Traverses the list to search for selected song
	walker = head;
	for (int t = 1; t <= selectNumber; t++)
	{
		if (t == selectNumber)
		{
			cout << "Now playing \"" << walker->song << "\" by " << walker->artist << endl;
		}
		walker = walker->next;
	}
	return;
}

void removeSong(Node* &head, Node* tail, int &playlistLength) //Removes a song from the playlist
{
	int selectNumber;	//User input
	bool loopCheck = true;	//Boolean to check to continue looping

	while (loopCheck == true)	//Checks if input is between the required numbers
	{
		cout << "Enter the song number(1-" << playlistLength << ") :";
		cin >> selectNumber;
		if (selectNumber > 0 && selectNumber < playlistLength + 1)
		{
			loopCheck = false;
		}
	}

	if (selectNumber == 1) //Check to see if deleted item is the first
	{
		Node* tmp = head;
		head = head->next; //Moves the head one node forward
		cout << "removing \"" << head->song << "\" by " << head->artist << endl;
		delete tmp;
	}
	else if (selectNumber == playlistLength) //Check to see if deleted item the last
	{
		Node* pre = NULL;

		Node* walker = NULL;
		walker = head; //Traversals the list to find the selected node
		for (int t = 1; t <= selectNumber; t++)
		{
			if (t == selectNumber - 1)	//Find new end
			{
				pre = walker;
			}
			else if (t == selectNumber) //Remove old end
			{
				cout << "removing \"" << walker->song << "\" by " << walker->artist << endl;
			}
			walker = walker->next;
		}
		pre->next = NULL; //Create new end
	}
	else //Check to see if deleted item is not the last nor first
	{
		Node* pre = NULL;
		Node* cur = NULL;

		Node* walker = NULL;
		walker = head;
		for (int t = 1; t <= selectNumber; t++)	//Traversis the linked list
		{
			if (t == selectNumber - 1)
			{
				pre = walker;
			}
			else if (t == selectNumber)
			{
				cur = walker;
				cout << "removing " << cur->song << " by " << cur->artist << endl;
			}
			walker = walker->next;
		}

		pre->next = cur->next; //Links the previous node to the node after the deleted one
		delete cur; //Deletes the selected Node
		pre = cur = NULL;
	}

	playlistLength--;	//decreases the value of the playlistLength

	return;
}