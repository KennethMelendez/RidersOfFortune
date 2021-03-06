﻿// App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

void displayMap(int);
void userOptions();

int diceRoll();
int monsters();

int playerWeaponsAndSettingAttackPoints(int);
int playerFound;


int silentProtagonistEXPCount(int,bool, bool);
int monstersInMapCounter();
int randomizingMonster(int);
int attackPoints;
int gameSpaces = 27;	//Using this variable in order to set/loop through the array and for clarity
int lastGameSpace = gameSpaces;
int setPlayerEXP = 0;
int setAttackPointsForPlayer = 0;


int main()
{

	string player;

	// Story
	
	//adding player username input
	cout << Please enter your name. << endl;
	cin >> player;
	
	//if user does not fill out form name will default to the story protagonist name
	if(player == ""){
		player == "Yarra";
	}
	
	cout << "You play " << player << ", a young horseman in search of the of the illustrious Chalice of Knowledge, an artifact that will bring you everlasting wisdom.\n";
	cout << "The Chalice can only be found in dragon dungeon after defeating the dragon.\n\n";


	// MAP
	int playersCurrentPosition = 0;


	//GAME LOGIC/GAMEBOARD (ALL LOGIC WILL BE INSIDE LOOP)

	for (int playersSteps = 0; playersSteps < lastGameSpace; playersSteps++) {
		int monsterSpawner = randomizingMonster(gameSpaces);
		displayMap(playersSteps);

		//Test monster randomizer
		//cout << "Monster appeared in space.." << monsterSpawner << endl;
		cout << "You are in space .." << playersSteps << endl;

		// display user options
		userOptions();

		//created a prompt for the user
		int prompt;
		cin >> prompt;
		if (prompt == 1)
		{
			// user travels to another space on the board
			playersSteps += diceRoll();

			cout << "a six-sided die will be rolled and you must move to that space." << endl;

		}
		//Dismount and explore current area
		else if (prompt == 2)
		{
			cout << "You explored the current area and ... " << endl;

			// randomizes outcomes
			int outcome = rand() % 2;

			// Test outcome randomizer
			//cout << " This is the outcome # : " << outcome << endl;

			// outcome 1 (Monsters)



				//will decriment and keep track of monsters
			monstersInMapCounter();
			//if the player steps equals to where the monster spawned AND theres WILL CHECK IF THERES A MONSTER
			//the monster will proceed to attack

			//trying to improve outcome of finding a monster
			if (monsterSpawner < playersSteps) {
				monsterSpawner = playersSteps;
			}

			if (playersSteps == monsterSpawner && monstersInMapCounter() >= 0) {
				cout << "Oh no! A monster attacked!" << endl;
				cout << "Monster's HP: " << monsters() << endl;

				// === outcomes of winning or lossing battle ===
				// Dice Roll for monster attack

				setAttackPointsForPlayer = setAttackPointsForPlayer + diceRoll();

				if (monsters() >= setAttackPointsForPlayer) {
					// cout << "You have died!" << endl;
					
					break;
				}
				else if (setAttackPointsForPlayer >= monsters()) {
					cout << "Congrats! You have won, please proceed!" << endl;

					// Monster XP
					setPlayerEXP = silentProtagonistEXPCount(setPlayerEXP, true, false);
					cout << "You have gained: " << setPlayerEXP << endl;
				}
			}
			else {

				if (outcome == 0) {
					// outcome 2 (Weapons)

					setAttackPointsForPlayer = playerWeaponsAndSettingAttackPoints(setAttackPointsForPlayer);
					cout << "Your current attack points: " << setAttackPointsForPlayer << endl;
				}
				else if (outcome == 1) {
					// outcome 3 (Nothing happened)

					cout << "There is nothing for you to do, so you reflect upon your adventures thus far. You take the time to train and enhance your reflexes." << endl;
				
					// Travel EXP
					setPlayerEXP = silentProtagonistEXPCount(setPlayerEXP, false, true);
					cout << "You have gained " << setPlayerEXP << "!" << endl;
				}
			}
		}
		else if (prompt != 1 || prompt != 2)
		{
			cout << "Please only enter available options from the menu!" << endl;
			break;
		}


		// Dice
		cout << "The dice rolled: " << diceRoll() << endl;

		// Your current EXP
		setPlayerEXP = silentProtagonistEXPCount(setPlayerEXP, false, false);
		cout << "Your current EXP: " << setPlayerEXP << endl;
		
	}
	// End of Map Dragon
	int dragonEXP = 5;
	int dragon = 10;
	if (setPlayerEXP > dragonEXP && setPlayerEXP >= dragon) {

		cout << "Due to your cunning and experience, you have defeated the deadly dragon. Your quest has ended good sir. You’ve obtained the Chalice of knowledge and all of earth’s mysteries are revealed." << endl;
	} 
	else if (setPlayerEXP < dragonEXP) {

		cout << "Alas, the dragon’s eyes stare at you and places you under his spell. You try to move but fail to do so and find yourself torched by the dragon’s fire. If only you had more experience, you could have seen it coming" << endl;
	}

    return 0;
}


void displayMap( int playersPosition) {
	/*=========================================================
	Map logic
	MAP generator
	==========================================================*/

	//number of spaces in game
	
	const int gameSpacesForArray = 27;	//Using this variable in order to set the game space (Example this game will have 27 spaces)

	string theGameBoard[gameSpacesForArray];
	//for loop will add to each game space untill the end of the array
	for (int x = 0; x < gameSpaces; x++) {
		//DRY dont repeat yourself made variables for players position so we know it will change
		int lastSpace = size(theGameBoard) - 1;


		if (theGameBoard[x] == theGameBoard[playersPosition]) {
			theGameBoard[playersPosition] = "P";
		}
		else if (theGameBoard[x] == theGameBoard[lastSpace]) {
			theGameBoard[lastSpace] = "D";
		}
		else if (theGameBoard[x] != "P" || theGameBoard[x] != "D"){
			theGameBoard[x] = "*";
		}

		
	}

	/*=========================================================
	Map logic
	Display Map
	==========================================================*/

	//displays map
	for (int n = 0; n < gameSpaces; n++) {
		cout << theGameBoard[n];
	}
	//making a space
	cout << "" << endl;

}

//When calling this function
//if put (true,false) adds +2 exp
//if put (false, true) adds +1 exp
//if put (false,false) the function returns the current exp without changes
int silentProtagonistEXPCount(int exp ,bool foundMonsterAndWon,bool exploring) {
	

	if (foundMonsterAndWon == true) {
		exp += 2;
		return exp;
	}
	else if (exploring == true) {
		exp++;
		return exp;
	}
	else {
		return exp;
	}
}

int diceRoll() {
	int sixDice = 1 + (rand() % 6);
	return sixDice;
}

void userOptions() {
	cout << "Press 1 to Travel to another space on the board" << endl;
	cout << "Press 2 to Dismount and explore the current space" << endl;
}



int playerWeaponsAndSettingAttackPoints(int currentAttackPoints) {

	//int currentAttackPoints = 0;

	//make randomizer here for weapon
		srand(time(0));
		int weapon = 1 + (rand() % 5);

		// Test the randomizer

		//cout << "The dice for the weapon is : " << weapon << endl;
		
		
	

	if (weapon == 1 && currentAttackPoints <= 3 && currentAttackPoints != 3) {
		currentAttackPoints += 3;
		cout << " You found a Crossbow!" << endl;
		cout << "attack points raised to " << currentAttackPoints << endl;
		
	}else if (weapon == 2 && currentAttackPoints <= 4 && currentAttackPoints != 4) {
		currentAttackPoints += 4;
		cout << " You found a Flail!" << endl;
		cout << "attack points raised to " << currentAttackPoints << endl;
	
	}else if (weapon == 3 && currentAttackPoints <= 5 && currentAttackPoints != 5) {
		currentAttackPoints += 5;
		cout << " You found a Broad Sword!" << endl;
		cout << "attack points raised to " << currentAttackPoints << endl;
		
	}else if (weapon == 4 && currentAttackPoints <= 6 && currentAttackPoints != 6) {
		currentAttackPoints += 6;
		cout << " You found a Dragon Slayer!" << endl;
		cout << "attack points raised to " << currentAttackPoints << endl;
		
	}
	else if (weapon == 5 && currentAttackPoints <= 7 && currentAttackPoints != 7) {
		currentAttackPoints += 7;
		cout << " You found a Spell of the Gods!" << endl;
		cout << "attack points raised to " << currentAttackPoints << endl;

	}
	else {

		cout << "Weapon was found but already had a better weapon..." << endl;
		return currentAttackPoints;
	}
	return currentAttackPoints;
}


int monsters() {
	int monsterHP = 3 + (rand() % 7);
	return monsterHP;
}


//using this function to keep count of the monsters 
int monstersInMapCounter() {
	int numberOfMonsters = 14;
	
	//when calling this function it will keep count of the monsters
	//call this function when you encounter a monster (function will activate and reduce count by 1 if true)
	
		numberOfMonsters--;
	
		return numberOfMonsters;

}


// length of spaces / THE ARRAY < - will randomize in the array
int randomizingMonster(int lengthOfSpaces) {
	// the int will return a random number
	//i will use that number to set the monster into the array
	return 1 + (rand() % lengthOfSpaces);
}


