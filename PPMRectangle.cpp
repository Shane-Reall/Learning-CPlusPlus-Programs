// Name: Shane Reall
// File Name: prog2.cpp
// Date: 15 Feburuary, 2023
// Program Description: A Program that will create a colored rectangle based off of a given length, width, and RGB value.

#include <iostream>
#include <fstream>

using namespace std;

typedef int RGB[3];

int getParameters(int &ulcx, int &ulcy, int &height, int &width, int* &r); // Prototype for getParameters
																		  // It is passing the ulcx, ulcy, height, and width by reference to allow for them to be changed in the function
																		 // It is also passing the pointer of r by referance to allow for the change of the values of the r array
int fillRectangle(int ulcx, int ulcy, int height, int width, int colors[], int screen[][768]); // Prototype for fillRectangle
																							  // It is passing the ulcx, ulcy, height, width, colors array, and screen array by vaule, since they do not need to be changed at this point
int writeToPPM(int screen [][768]); // Prototype for writeToPPM
								   // It is only passed the screen array

int main()
{
	int ulcx;	//Upper Left Corner X
	int ulcy;	//Upper Left Corner Y
	int height;	//Height of the Shape
	int width;	//Width of the Shape
	RGB colors;	//Array to hold the 3 Red Green & Blue Values
	int screen[256][768];	//Screen Size
							//768 is used since the array is 3 times the actual width to allow room for all of the RGB values
	int* r = colors;	//A pointer to the colors array to allow for it to be passed to the getParameters function

	getParameters(ulcx, ulcy, height, width, r);	//Calling of the getParameters
	fillRectangle(ulcx, ulcy, height, width, colors, screen);	//Calling of the fillRectangle
	writeToPPM(screen);	//Calling of the writeToPPM
}

int getParameters(int &ulcx, int &ulcy, int &height, int &width, int* &r) //This function get the parameters from the user to creat the shape.
{
	cout << "Enter the x and y coordinates of the upper left corner: ";
	cin >> ulcy;	//Obtaining the X coordinate of the upper left corner
	cin >> ulcx;	//Obtaining the Y coordinate of the upper left corner
	while (ulcx > 256 || ulcy > 256 || ulcx < 0 || ulcy < 0) //Checks to see if the X and Y values are between 0 & 256
	{
		cout << "There was an issue with your x and y coordinates, one or both were not between 0 and 256" << endl;
		cout << "Enter the x and y coordinates of the upper left corner, again: ";
		cin >> ulcy;
		cin >> ulcx;
	}
	cout << endl << ulcy << " " << ulcx << endl; //Shows the inputed X and Y Values in the Console

	cout << "Enter the height and width (in pixels): ";
	cin >> height;	//Obtaining the Height of the shape
	cin >> width;	//Obtaining the Width of the shape
	while (height < 0 || width < 0) //Checks to see if the Height and Width values are Positive
	{
		cout << "There was an issue with your height and width values, one or both were not above 0" << endl;
		cout << "Enter the height and width, again (in pixels): ";
		cin >> height;
		cin >> width;
	}
	cout << endl << height << " " << width << endl; //Shows the inputed Height and Width Values in the Console

	cout << "Enter the RGB color code (0-15): ";
	cin >> r[0];	//Obtaing the Red Value of the Shape
	cin >> r[1];	//Obtaing the Green Value of the Shape
	cin >> r[2];	//Obtaing the Blue Value of the Shape
	while (r[0] > 15 || r[1] > 15 || r[2] > 15 || r[0] < 0 || r[1] < 0 || r[2] < 0) //Checks that all values are between 0 and 15 in the array
	{
		cout << "There was an issue with your RGB values, one or more were not between 0 and 15" << endl;
		cout << "Enter the RGB color code, again (0-15): ";
		cin >> r[0];
		cin >> r[1];
		cin >> r[2];
	}
	cout << endl << r[0] << " " << r[1] << " " << r[2] << endl; //Shows the inputed colors array Values in the Console

	return 0; //Ends the function
}

int fillRectangle(int ulcx, int ulcy, int height, int width, int colors[], int screen[][768]) //This function creates the shape by loading RGB values into the 2D screen Array
{

	for (int k = 0; k < 256; k++) //Loops 256 times for the height of the PPM
	{
		for (int i = 0; i < 768; i = i + 3) //Lopps 768 times for the width of the PPM multiplied by three, this is done to allow room for the 3 RGB values need for each pixel
		{									// The i is increased by three each repeation to skip over the ending part of the RGB values and to instead jump to the begining of the next RGB value
			if (k <= (256 - ulcx) + height && k >= 256 - (ulcx)) //Checks to see if the filling in within the peremeters of the shape's x values
			{													//All of the values are subtracted from 256 due to my program showing that 0,0 is in the Upper Left Corner instead of the Lower Left Corner
				if (i >= ulcy * 3 && i <= ulcy * 3 + width * 3) //Checks to see if the filling in within the peremeters of the shape's x values
				{												//All of the values are multiplied by three to repersent the increased size of the width of the ppm
					screen[k][i] = colors[0];	//Sets the Red Value for the RGB 'strings' when it finds the correct location
					screen[k][i+1] = colors[1];	//Sets the Green Value for the RGB 'strings' when it finds the correct location
					screen[k][i+2] = colors[2];	//Sets the Blue Value for the RGB 'strings' when it finds the correct location
				}
				else
				{
					screen[k][i] = 15;		//Sets the rest of the Red Values to Max
					screen[k][i + 1] = 15;	//Sets the rest of the Green Values to Max
					screen[k][i + 2] = 15;	//Sets the rest of the Blue Values to Max
				}	//This sets the rest of the pixels to white
			}
			else
			{
				screen[k][i] = 15;		//Sets the rest of the Red Values to Max
				screen[k][i + 1] = 15;	//Sets the rest of the Green Values to Max
				screen[k][i + 2] = 15;	//Sets the rest of the Blue Values to Max
			}	//This sets the rest of the pixels to white
		}
	}

	return 0; //Ends the function
}

int writeToPPM(int screen[][768]) //This function creats the ppm file using the screen array created in the fillRectangle function
{
	ofstream outFile("image.ppm"); // Creates the 'image.ppm' file

	outFile << "P3" << endl << "256 256" << endl << "15" << endl; //Writes 'P3', '256 256', and '15' to the first three lines of the file

	for (int k = 0; k < 256; k++) //Loops 256 times for the value of the height
	{
		for (int i = 0; i < 768; i++) //Loops for 768 for the width of the file, to allow for all RGB values for each pixel
		{
			outFile << screen[k][i] << " "; //Prints the RGB values into the file, one at a time
		}
	}

	outFile.close(); //Closes the ppm file

	return 0; //Ends the function
}