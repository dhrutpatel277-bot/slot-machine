//*******************************************************************************
//  
//  Program 3 Fall 2024
//  DCPankratz  &  B McVey-Pankratz(All Rights reserved)
//  Dhrut Patel
//  Programmers: BMVP, DCP and Dhrut    
//
//  Honor Code Signature: _______________________
//
//  Randomally show pictures and accumulate points
//  based on a set of rules. The game ends when you run 
//  out of money or you choose to stop.
//
//  Assistance:
//
//********************************************************************************

#include "DarkGDK.h"
#include "sncIOstream.h"
using namespace std;

//Global colors can be used by any function
const unsigned int BLACK = dbRGB(0, 0, 0);
const unsigned int WHITE = dbRGB(255, 255, 255);
const unsigned int DARKGREY = dbRGB(50, 50, 50);

// Global constants used to draw the slot machine images
const int slotX = 60; const int slotY = 150;
const int slotWIDTH = 35; const int slotHEIGHT = 35;
const int slotPICWIDTH = 128;
const int MAXPIC = 4; //total number of images

//prototypes
bool loadwheels();
void spinwheels(int& leftw, int& middlew, int& rightw);
void checkResult(int leftw, int middlew, int rightw, int& prize, string& result);
void display(int prize, const string& result, int money);

bool askToPlayAgain(int& money);

void DarkGDK() {
	int leftw, middlew, rightw; // image ids for the three wheels
	int prize;                  // Points earned based on result
	string result;              // Result string for the spin
	int money;                  // Player's money

	cout << "Enter the amount of money you want to start with: "<<endl;
	cin >> money;

	dbRandomize(dbTimer()); // Pick the seed based on the time in milliseconds

	if (!loadwheels()) {
		cout << "Press a Key.." << endl;
		dbWaitKey();
		return; // End the program if loading fails
	}

	do {
		dbCLS(DARKGREY);  // Clear the screen with dark grey

		// Draw slot machine box
		dbInk(WHITE, 0);
		dbBox(slotX, slotY, slotX + 520, slotY + 2 * slotHEIGHT + slotPICWIDTH);
		dbInk(BLACK, 0);
		dbBox(slotX + 5, slotY + 5, slotX + 520 - 5, slotY + 2 * slotHEIGHT + slotPICWIDTH - 5);

		// Spin the wheels and show the images
		spinwheels(leftw, middlew, rightw);

		// Check the result and calculate the prize
		checkResult(leftw, middlew, rightw, prize, result);

		// Update money based on the prize
		money += prize;

		// Display the prize, result, and money
		display(prize, result, money);

		// Ask if player wants to play again or if they run out of money
	} while (askToPlayAgain(money) && money >=0);

	cout << "Game over! You have no more money left." << endl;
	dbWaitKey(); // Wait for a key press before exiting
}

void spinwheels(int& leftw, int& middlew, int& rightw)
///////////////////////////////////////////////////////
//  Purpose: display random images for each wheel with
//  a spinning effect before landing on final images.
///////////////////////////////////////////////////////
{
	const int SPIN_DURATION = 20; // Number of spins
	const int TIMESLICE = 15;     // Wait time between each frame (15 ms)

	// Simulate spinning effect with loop
	for (int i = 0; i < SPIN_DURATION; ++i) {
		// Randomly choose images during each spin iteration
		/*leftw = dbRND(MAXPIC - 1) + 1;
		middlew = dbRND(MAXPIC - 1) + 1;
		rightw = dbRND(MAXPIC - 1) + 1;*/
		leftw = dbRND(4);
		middlew = dbRND(4);
		rightw = dbRND(4);

		// Display each image in the appropriate slot
		dbPasteImage(leftw, slotX + slotWIDTH, slotY + slotHEIGHT);
		dbPasteImage(middlew, slotX + 2 * slotWIDTH + slotPICWIDTH, slotY + slotHEIGHT);
		dbPasteImage(rightw, slotX + 3 * slotWIDTH + 2 * slotPICWIDTH, slotY + slotHEIGHT);

		// Wait to create the spinning effect
		dbWait(TIMESLICE); // Pause briefly between spins
	}

	// The wheels stop and final values are displayed
	leftw = dbRND(MAXPIC - 1) + 1;
	middlew = dbRND(MAXPIC - 1) + 1;
	rightw = dbRND(MAXPIC - 1) + 1;

	// Display the final wheel images
	dbPasteImage(leftw, slotX + slotWIDTH, slotY + slotHEIGHT);
	dbPasteImage(middlew, slotX + 2 * slotWIDTH + slotPICWIDTH, slotY + slotHEIGHT);
	dbPasteImage(rightw, slotX + 3 * slotWIDTH + 2 * slotPICWIDTH, slotY + slotHEIGHT);
}

void display(int prize, const string& result, int money)
///////////////////////////////////////////////////////
//  Purpose: display the prize, result, and money left
///////////////////////////////////////////////////////
{
	cout << result << endl;
	cout << "Prize: " << prize << " points" << endl;
	cout << "Money left: $" << money << endl;

	sncCenterText(520, 10, "rules");
	sncCenterText(480, 20, "1. Spin the wheels and try to match images.");
	sncCenterText(480, 30, "2. Three of a kind = 6 points.             ");
	sncCenterText(480, 40, "3. Three of you = 10 points.               ");
	sncCenterText(480, 50, "4. A pair = 3 points.                      ");
	sncCenterText(480, 60, "5. Bad image = -2 points.                  ");
	sncCenterText(480, 70, "6. No match = -1 point.                    ");
	sncCenterText(480, 80, "7. Game ends when you run out of money.    ");
}



bool loadwheels()
/////////////////////////////////////////////////
//  purpose: load the images, assign ids, and check for success
//  sent to fcn: nothing
//  sent back: true or false
////////////////////////////////////////////////
{
	bool OK = true;
	dbLoadImage("me.jpg", 1);
	if (!dbImageExist(1)) {
		cout << "Cannot open me.jpg" << endl;
		OK = false;
	}
	dbLoadImage("talvar.jpg", 2);
	if (!dbImageExist(2)) {
		cout << "Cannot open talvar.jpg" << endl;
		OK = false;
	}
	dbLoadImage("7.jpg", 3);
	if (!dbImageExist(3)) {
		cout << "Cannot open cherries.bmp" << endl;
		OK = false;
	}
	dbLoadImage("Skull.jpg", 4);
	if (!dbImageExist(4)) {
		cout << "Cannot open Skull.jpg" << endl;
		OK = false;
	}
	return OK;
}
 
void checkResult(int leftw, int middlew, int rightw, int& prize, string& result)
///////////////////////////////////////////////////////
//  Purpose: determine the prize based on the wheel values
///////////////////////////////////////////////////////
{
	if (leftw == 4 || middlew == 4 || rightw == 4) {
		prize = -2;
		result = "You hit a bad image!" ;
	}
	else if (leftw == 1 && middlew == 1 && rightw == 1) {
		prize = 10;
		result = "Three of me! Jackpot!";
	}
	else if (leftw == middlew && middlew == rightw) {
		prize = 6;
		result = "Three of a kind!";
	}
	else if (leftw == middlew || middlew == rightw || leftw == rightw) {
		prize = 3;
		result = "You have a pair!";
	}
	else {
		prize = -1;
		result = "No prize this time.";

	}
	cout << result << endl;
}
bool askToPlayAgain(int& money)
///////////////////////////////////////////////////////
//  Purpose: ask the player if they want to continue playing
///////////////////////////////////////////////////////
{
	if (money <= 0) {
		return false; // Stop playing if out of money
	}

	char choice;
	cout << "Do you want to play again? (y/n): " << endl;
	cin >> choice;

	return (choice == 'y' || choice == 'Y');
}
