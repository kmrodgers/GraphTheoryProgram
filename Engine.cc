#include <iostream>
#include "PetersenGraphRandom.h"
#include "CompleteGraphRandom.h"
#include "Hypercube2Random.h"
#include "Hypercube3Random.h"
#include "Hypercube4Random.h"
#include "Engine.h"

#include "PetersenGraphLogical.h"
#include "CompleteGraphLogical.h"
#include "Hypercube2Logical.h"
#include "Hypercube3Logical.h"
#include "Hypercube4Logical.h"

#include <string>
#include <cstdio>
#include <ctime>
#include <fstream>

#include <vector>
#include <map>

const std::string MASTER_DATA_PATH = "output_data/master_data.txt";
const std::string PLAYER1_DATA_PATH = "output_data/player1_moves.txt";
const std::string PLAYER2_DATA_PATH = "output_data/player2_moves.txt";
//const std::string PLAYER1_LOGICAL_DATA_PATH = "output_data/player1_logical_moves.txt";
//const std::string PLAYER2_LOGICAL_DATA_PATH = "output_data/player2_logical_moves.txt";
const std::string RESULTS_DATA_PATH = "output_data/results.txt";
const std::string PLAYER1_UNIQUE_MOVES_DATA_PATH = "output_data/player1_unique_moves.txt";
const std::string PLAYER2_UNIQUE_MOVES_DATA_PATH = "output_data/player2_unique_moves.txt";

Engine::Engine()
{
	int choice = 0;
	barCount = 0;
	printIntro();
	printStartMenu();
	std::cin >> choice;
	//startMenuList(choice);
	startMenuChoices(choice);
}

void Engine::printIntro()
{
	std::cout << std::endl;
	std::cout << "Welcome to the Text-Based Graph Theory Logging Program" << std::endl;
	std::cout << std::endl;
}

void Engine::printStartMenu()
{
	std::cout << "What type of graph would you like to use?" << std::endl;
	std::cout << "1. Petersen Graph" << std::endl;
	std::cout << "2. Complete Graph" << std::endl;
	std::cout << "3. Hypercube Graph" << std::endl;
	std::cout << "9. Quit program" << std::endl;
	std::cout << "Please enter your choice: ";
}

void Engine::startMenuChoices(int choice)
{
	int subMenuChoice = 0;
    int numGamesToPlay = 0;
	int numNodes = 0;
	int edgeWeight = 0;
    bool random;
    bool watch;
	std::string watchChoice;
	if (choice == 1)
	{
		std::cout << "\nPetersen Graph" << std::endl;
        std::cout << "What type of game would you like to play?" << std::endl;
        std::cout << "1. Random Game" << std::endl;
        std::cout << "2. Logical Game" << std::endl;
        std::cout << "Please enter your choice: ";
        std::cin >> subMenuChoice;
        if (subMenuChoice == 1)
        {
            std::cout << "\nRandom Petersen Graph" << std::endl;
            random = true;
        }
        else if (subMenuChoice == 2)
        {
            std::cout << "\nLogical Petersen Graph" << std::endl;
            random = false;
        }
        std::cout << "What weight would you like to assign the edges?: ";
		std::cout << "\n\tNote: Type 0 for a random weight for each edge, between 1 and 10." << std::endl;
        std::cout << "What weight? ";
        std::cin >> edgeWeight;
        std::cout << "How many games would you like to play?: ";
        std::cin >> numGamesToPlay;
        std::cout << "Would you like to view the games as they are being played?" << std::endl;
        std::cout << "\tNote: If running more than 10 million games, or \n\tif you want a cleaner terminal, 'n' recommended." << std::endl;
        std::cout << "Watch games? (y/n): ";
        std::cin >> watchChoice;
        std::cout << std::endl;
        if (watchChoice == "y" || watchChoice == "Y")
            watch = true;
        else if (watchChoice == "n" || watchChoice == "N")
            watch = false;
        createPetersenGraph(numGamesToPlay, edgeWeight, watch, random);
	}
	else if (choice == 2)
	{
        std::cout << "\nComplete Graph" << std::endl;
        std::cout << "What type of game would you like to play?" << std::endl;
        std::cout << "1. Random Game" << std::endl;
        std::cout << "2. Logical Game" << std::endl;
        std::cout << "Please enter your choice: ";
        std::cin >> subMenuChoice;
        if (subMenuChoice == 1)
        {
            std::cout << "\nRandom Complete Graph" << std::endl;
            random = true;
        }
        else if (subMenuChoice == 2)
        {
            std::cout << "\nLogical Complete Graph" << std::endl;
            random = false;
        }
		std::cout << "How many nodes would you like in this graph?: ";
		std::cin >> numNodes;
		std::cout << "What weight would you like to assign the edges?: ";
		std::cout << "\n\tNote: Type 0 for a random weight for each edge, between 1 and 10." << std::endl;
		std::cout << "What weight? ";
		std::cin >> edgeWeight;
		std::cout << "How many games would you like to play?: ";
		std::cin >> numGamesToPlay;
		std::cout << "Would you like to view the games being played?" << std::endl;
		std::cout << "\tNote: If running over 150-200 nodes, and/or over 10 million games, or \n\tif you want a cleaner terminal, 'n' recommended." << std::endl;
		std::cout << "Watch games? (y/n): ";
		std::cin >> watchChoice;
		std::cout << std::endl;
        if (watchChoice == "y" || watchChoice == "Y")
            watch = true;
        else if (watchChoice == "n" || watchChoice == "N")
            watch = false;
		createCompleteGraph(numGamesToPlay, numNodes, edgeWeight, watch, random);
	}
	else if (choice == 3)
	{
        std::cout << "\nHypercube Graph" << std::endl;
        std::cout << "What type of game would you like to play?" << std::endl;
        std::cout << "1. Random Game" << std::endl;
        std::cout << "2. Logical Game" << std::endl;
        std::cout << "Please enter your choice: ";
        std::cin >> subMenuChoice;
        if (subMenuChoice == 1)
        {
            std::cout << "\nRandom Hypercube Graph" << std::endl;
            random = true;
        }
        else if (subMenuChoice == 2)
        {
            std::cout << "\nLogical Hypercube Graph" << std::endl;
            random = false;
        }
		int dimension = 0;
		std::cout << "What dimension would you like this graph to be? (2-4): ";
		std::cin >> dimension;
		std::cout << "What weight would you like to assign the edges?: ";
		std::cout << "\n\tNote: Type 0 for a random weight for each edge, between 1 and 10." << std::endl;
		std::cout << "What weight? ";
		std::cin >> edgeWeight;
		std::cout << "How many games would you like to play?: ";
		std::cin >> numGamesToPlay;
		std::cout << "Would you like to view the games being played?" << std::endl;
		std::cout << "\tNote: If running over 150-200 nodes, and/or over 10 million games, or \n\tif you want a cleaner terminal, 'n' recommended." << std::endl;
		std::cout << "Watch games? (y/n): ";
		std::cin >> watchChoice;
		std::cout << std::endl;
        if (watchChoice == "y" || watchChoice == "Y")
            watch = true;
        else if (watchChoice == "n" || watchChoice == "N")
            watch = false;
		createHypercubeGraph(numGamesToPlay, edgeWeight, dimension, watch, random);
	}	
    else if (choice == 9)
    {
        std::cout << "Thank you for using this program!" << std::endl;
        exit(0);
    }
}

void Engine::parseMasterData()
{
	longestGame = 0;
	p1size = 0;
	p2size = 0;
	std::ifstream master;
	std::ofstream p1;
	std::ofstream p2;
	master.open(MASTER_DATA_PATH.c_str());
	p1.open(PLAYER1_DATA_PATH.c_str(), std::ios_base::app);
	p2.open(PLAYER2_DATA_PATH.c_str(), std::ios_base::app);
	std::string parseLine;
	//std::string::iterator iter = parseLine.end();
	while (std::getline(master, parseLine))
	{
		rotateBarParse();
		std::string::iterator iter = (parseLine.end()-1);
//		std::getline(master, parseLine);
		//std::cout << parseLine << std::endl;
		//std::cout << *(parseLine.end()-1) << "*" << std::endl;
		if ((*iter) == '1')
		{
			p1size++;
            std::string p1ParseLine;
			p1ParseLine = parseLine.substr(0, parseLine.size() - 2);
            //parseLine.pop_back();
			//parseLine.pop_back();
			p1 << p1ParseLine << std::endl;
			if (p1ParseLine.size() > longestGame)
				longestGame = (int)p1ParseLine.size();
		}
		else if((*iter) == '2')
		{
			p2size++;
            std::string p2ParseLine;
			p2ParseLine = parseLine.substr(0, parseLine.size() - 2);
            //parseLine.pop_back();
			//parseLine.pop_back();
			p2 << p2ParseLine << std::endl;
			if (p2ParseLine.size() > longestGame)
				longestGame = (int)p2ParseLine.size();
		}
		master.clear();
	}
	std::cout << "\nData sorted by player successfully!" << std::endl;
	p1.close();
	p2.close();
	master.close();	
}	
/*
void Engine::parsePlayerLogicalData()
{
	std::ifstream p1;
	std::ifstream p2;
	std::ofstream p1logical;
	std::ofstream p2logical;
	p1.open(PLAYER1_DATA_PATH.c_str());
	p2.open(PLAYER2_DATA_PATH.c_str());
	//p1logical.open(PLAYER1_LOGICAL_DATA_PATH, std::ios_base::app);
	//p2logical.open(PLAYER2_LOGICAL_DATA_PATH, std::ios_base::app);
	std::string testLine;
	while (std::getline(p1, testLine))
	{
		rotateBarParsePlayer1();
		if (testLine.size() == longestGame)
			p1logical << testLine << std::endl;
	}
	std::cout << "\nLogical moves extracted from player 1 data successfully!" << std::endl;
	while (std::getline(p2, testLine))
	{
		rotateBarParsePlayer2();
		if (testLine.size() == longestGame)
			p1logical << testLine << std::endl;
	}
	std::cout << "\nLogical moves extracted from player 2 data successfully!" << std::endl;
	p1.close();
	p2.close();
	p1logical.close();
	p2logical.close();
}
*/
void Engine::dataAnalysis(int choice)
{
//	longestGame = 1;
	std::ifstream p1;
	std::ifstream p2;
	std::ofstream results;
	p1.open(PLAYER1_DATA_PATH.c_str());
	p2.open(PLAYER2_DATA_PATH.c_str());
//	p1_logical.open(player1_logical_ata_path);
//	p2_logical.open(PLAYER2_LOGICAL_DATA_PATH);
	results.open(RESULTS_DATA_PATH.c_str());
	std::string testLine;
	std::map<std::string, int> player1moves;
	std::map<std::string, int> player2moves;
	std::map<std::string, int> player1logicalmoves;
	std::map<std::string, int> player2logicalmoves;
	while (std::getline(p1, testLine))
	{
		rotateBarAnalyzeP1();
		std::map<std::string, int>::iterator it = player1moves.find(testLine);
        if (it == player1moves.end())
            player1moves[testLine] = 1;
        else
            (it->second)++;
        testLine.clear();
	}
	std::cout << "\nPlayer 1 data analyzed successfully!" << std::endl;
	while (std::getline(p2, testLine))
	{
		rotateBarAnalyzeP2();
        std::map<std::string, int>::iterator it = player2moves.find(testLine);
        if (it == player2moves.end())
            player2moves[testLine] = 1;
        else
            (it->second)++;
		testLine.clear();
	}
	std::cout << "\nPlayer 2 data analyzed successfully!" << std::endl;
	std::cout << std::endl;
	results << std::endl;
	p1.close();
	p2.close();
//	std::sort(player1moves.begin(), player1moves.end());
//	std::sort(player2moves.begin(), player2moves.end());
/*	std::ofstream p1unique;
	std::ofstream p2unique;
	p1unique.open(PLAYER1_UNIQUE_MOVES_DATA_PATH.c_str());
	p2unique.open(PLAYER2_UNIQUE_MOVES_DATA_PATH.c_str());
	for (std::vector<std::string>::iterator it = player1moves.begin(); it != player1moves.end(); it++)
		p1unique << *it << std::endl;
	for (std::vector<std::string>::iterator it = player2moves.begin(); it != player2moves.end(); it++)
		p2unique << *it << std::endl;
	p1unique.close();
	p2unique.close();
*/	int numberOfGamesPlayed = choice;
	std::cout << "-----------------------------------------------" << std::endl;
	results << "-----------------------------------------------" << std::endl;
	std::cout << "\nGame Analysis" << std::endl;
	results << "\nGame Analysis" << std::endl;
	std::cout << std::endl;
	results << std::endl;
	std::cout << "Of the " << numberOfGamesPlayed << " games played:" << std::endl;
	results << "Of the " << numberOfGamesPlayed << " games played:" << std::endl;
	std::cout << std::endl;
	results << std::endl;
	std::cout << "Player 1 won " << p1size << "." << std::endl;
	results << "Player 1 won " << p1size << "." << std::endl;
	std::cout << "Player 2 won " << p2size << "." << std::endl;
	results << "Player 2 won " << p2size << "." << std::endl;
	std::cout << std::endl;
	results << std::endl;
	std::cout << "There are " << player1moves.size() << " unique moves for Player 1." << std::endl;
	results << "There are " << player1moves.size() << " unique moves for Player 1." << std::endl;
	std::cout << "There are " << player2moves.size() << " unique moves for Player 2." << std::endl;
	results << "There are " << player2moves.size() << " unique moves for Player 2." << std::endl;
	std::cout << std::endl;
	results << std::endl;
	std::cout << "Do you want to view the unique moves?" << std::endl;
	std::cout << "\tNote: the moves will be saved to file regardless of choice." << std::endl;
	std::cout << "View moves? (y/n): ";
	std::string s;
	std::cin >> s;
	if (s == "y" || s == "y")
	{
		std::cout << "The following moves led to Player 1's victory:" << std::endl;
		results << "The following moves led to Player 1's victory:" << std::endl;
		for (std::map<std::string, int>::iterator i = player1moves.begin(); i != player1moves.end(); i++)
		{
			std::cout << i->first << " " << i->second << std::endl;
			results << i->first << " " << i->second << std::endl;
	//		if (i->size() > longestGame)
	//			longestGame = i->size();	
		}
		std::cout << std::endl;
		results << std::endl;
		std::cout << "The following moves led to Player 2's victory:" << std::endl;
		results << "The following moves led to Player 2's victory:" << std::endl;
		for (std::map<std::string, int>::iterator i = player2moves.begin(); i != player2moves.end(); i++)
		{
			std::cout << i->first << " " << i->second << std::endl;
			results << i->first << " " << i->second << std::endl;
//			if (i->size() > longestGame)
//				longestGame = i->size();
		}
		std::cout << std::endl;
		results << std::endl;
	}
	else
	{
		results << "The following moves led to Player 1's victory:" << std::endl;
		for (std::map<std::string, int>::iterator i = player1moves.begin(); i != player1moves.end(); i++)
		{
            results << i->first << " " << i->second << std::endl;
	//		if (i->size() > longestGame)
	//			longestGame = i->size();	
		}
		results << std::endl;
		results << "The following moves led to Player 2's victory:" << std::endl;
		for (std::map<std::string, int>::iterator i = player2moves.begin(); i != player2moves.end(); i++)
		{
			results << i->first << " " << i->second << std::endl;
//			if (i->size() > longestGame)
//				longestGame = i->size();
		}
		results << std::endl;
	}
	std::cout << "\nThe longest game was " << (longestGame / 4) << " moves.\n" << std::endl;
	results << "The longest game was " << (longestGame / 4) << " moves.\n" << std::endl;
	results.close();
}

void Engine::rotateBarParse()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while the data is sorted...";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while the data is sorted...";
	}
	std::cout.flush();
	return;
}

void Engine::rotateBarParsePlayer1()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 1's logical moves are extracted...";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 1's logical moves are extracted...";
	}
	std::cout.flush();
	return;
}

void Engine::rotateBarParsePlayer2()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 2's logical moves are extracted...";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 2's logical moves are extracted...";
	}
	std::cout.flush();
	return;
}

void Engine::rotateBarAnalyzeP1()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 1's data is analyzed...";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 1's data is analyzed...";
	}
	std::cout.flush();
	return;
}

void Engine::rotateBarAnalyzeP2()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 2's data is analyzed...";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 2's data is analyzed...";
	}
	std::cout.flush();
	return;
}

void Engine::createPetersenGraph(int choice, int edgeWeight, bool watch, bool random)
{
	std::clock_t startTime = clock();
	std::cout << "Number of games to play: " << choice << std::endl;
    if (random == true)
        for (int i = 1; i <= choice; i++)
        {
            PetersenGraphRandom *a = new PetersenGraphRandom(i, edgeWeight, watch, choice);
            delete a;
        }
    else if (random == false)
        for (int i = 1; i <= choice; i++)
        {
            PetersenGraphLogical *a = new PetersenGraphLogical(i, edgeWeight, watch, choice);
            delete a;
        }
	std::cout << "\n\n-----------------------------------------------\n" << std::endl;
	parseMasterData();
	dataAnalysis(choice);
	//Surface *a = new Surface(choice);
	std::clock_t endTime = clock();
	std::clock_t timeDelta = endTime - startTime;
	double timeInSeconds = timeDelta / (double)CLOCKS_PER_SEC;
	int timeInDays = timeInSeconds / (60*60*24);
	int timeInHours = (timeInSeconds / (60*60)) - (timeInDays * 24);
	int timeInMinutes = (timeInSeconds / 60) - (timeInHours * 60);
	int secondsRemaining = (int)(timeInSeconds - (timeInMinutes * 60));
	std::cout << "Benchmark:" << std::endl;
	if (secondsRemaining == 0 && timeInMinutes == 0)
	{
		std::cout << "This calculation was quite quick!" << std::endl;
		std::cout << std::endl;
	}
	else if (secondsRemaining >= 10)
	{
		std::cout << "Time to completion: " << timeInMinutes << ":" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Time to completion: " << timeInMinutes << ":0" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	std::cout << "This calculation took exactly " << timeInSeconds << " seconds." << std::endl;		
	std::cout << std::endl;
}

void Engine::createCompleteGraph(int numGames, int numNodes, int edgeWeight, bool watch, bool random)
{
	//int numberOfNodes = numNodes;
	std::clock_t startTime = clock();
	std::cout << "Number of games to play: " << numGames << std::endl;
    if (random == true)
        for (int i = 1; i <= numGames; i++)
        {
            CompleteGraphRandom *a = new CompleteGraphRandom(i, numNodes, edgeWeight, watch, numGames);
            delete a;
        }
    if (random == false)
        for (int i = 1; i <= numGames; i++)
        {
            CompleteGraphLogical *a = new CompleteGraphLogical(i, numNodes, edgeWeight, watch, numGames);
            delete a;
        }
    std::cout << "\n\n-----------------------------------------------\n" << std::endl;
	parseMasterData();
//	parsePlayerLogicalData();
	dataAnalysis(numGames);
	//Surface *a = new Surface(choice);
	std::clock_t endTime = clock();
	std::clock_t timeDelta = endTime - startTime;
	double timeInSeconds = timeDelta / (double)CLOCKS_PER_SEC;
	int timeInDays = timeInSeconds / (60*60*24);
	int timeInHours = (timeInSeconds / (60*60)) - (timeInDays * 24);
	int timeInMinutes = (timeInSeconds / 60) - (timeInHours * 60);
	int secondsRemaining = (int)(timeInSeconds - (timeInMinutes * 60));
	std::cout << "Benchmark:" << std::endl;
	if (secondsRemaining == 0 && timeInMinutes == 0)
	{
		std::cout << "This calculation was quite quick!" << std::endl;
		std::cout << std::endl;
	}
	else if (secondsRemaining >= 10)
	{
		std::cout << "Time to completion: " << timeInMinutes << ":" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Time to completion: " << timeInMinutes << ":0" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	std::cout << "This calculation took exactly " << timeInSeconds << " seconds." << std::endl;
	std::cout << std::endl;
}

void Engine::createHypercubeGraph(int numGames, int edgeWeight, int dimensions, bool watch, bool random)
{
	//int numberOfNodes = numNodes;
	std::clock_t startTime = clock();
	std::cout << "Number of games to play: " << numGames << std::endl;
	if (dimensions == 2)
    {
        if (random == true)
            for (int i = 1; i <= numGames; i++)
            {
                Hypercube2Random *a = new Hypercube2Random(i, edgeWeight, watch, numGames);
                delete a;
            }
        else if (random == false)
            for (int i = 1; i <= numGames; i++)
            {
                Hypercube2Logical *a = new Hypercube2Logical(i, edgeWeight, watch, numGames);
                delete a;
            }
    }
    else if (dimensions == 3)
    {
        if (random == true)
            for (int i = 1; i <= numGames; i++)
            {
                Hypercube3Random *a = new Hypercube3Random(i, edgeWeight, watch, numGames);
                delete a;
            }
        else if (random == false)
            for (int i = 1; i <= numGames; i++)
            {
                Hypercube3Logical *a = new Hypercube3Logical(i, edgeWeight, watch, numGames);
                delete a;
            }
    }
    else if (dimensions == 4)
    {
        if (random == true)
            for (int i = 1; i <= numGames; i++)
            {
                Hypercube4Random *a = new Hypercube4Random(i, edgeWeight, watch, numGames);
                delete a;
            }
        else if (random == false)
            for (int i = 1; i <= numGames; i++)
            {
                Hypercube4Logical *a = new Hypercube4Logical(i, edgeWeight, watch, numGames);
                delete a;
            }
    }
	std::cout << "\n\n-----------------------------------------------\n" << std::endl;
	parseMasterData();
	//parsePlayerLogicalData();
	dataAnalysis(numGames);
	//Surface *a = new Surface(choice);
	std::clock_t endTime = clock();
	std::clock_t timeDelta = endTime - startTime;
	double timeInSeconds = timeDelta / (double)CLOCKS_PER_SEC;
	int timeInDays = timeInSeconds / (60*60*24);
	int timeInHours = (timeInSeconds / (60*60)) - (timeInDays * 24);
	int timeInMinutes = (timeInSeconds / 60) - (timeInHours * 60);
	int secondsRemaining = (int)(timeInSeconds - (timeInMinutes * 60));
	std::cout << "Benchmark:" << std::endl;
	if (secondsRemaining == 0 && timeInMinutes == 0)
	{
		std::cout << "This calculation was quite quick!" << std::endl;
		std::cout << std::endl;
	}
	else if (secondsRemaining >= 10)
	{
		std::cout << "Time to completion: " << timeInMinutes << ":" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Time to completion: " << timeInMinutes << ":0" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	std::cout << "This calculation took exactly " << timeInSeconds << " seconds." << std::endl;		
	std::cout << std::endl;
}