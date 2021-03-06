/*	Author: Kyle Rodgers
 *	Date: 6/12/2014
 */

#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "Token.h"
#include "Node.h"
#include "CompleteGraphLogical.h"
#include "RandomEngine.h"

//	This is the .cc file for the CompleteGraphLogical object.
const std::string MATRIX_RESULTS = "output_data/matrix_results.txt";
/*	
 *  Constructor for the CompleteGraphLogical. Takes three ints: i, numNodes, weight,
 *	and a bool b and assigns initial values.
 */
CompleteGraphLogical::CompleteGraphLogical(int i, int numNodes, int weight, bool b, int k)
{
	edgeWeight = weight;
	gameNumber = i;
	totalGames = k;
	watch = b;
	nodeNameCount = 0;
	createInitialNodes(numNodes);
	createInitialEdges();
	game();
}

//	Destructor for the CompleteGraphLogical object
CompleteGraphLogical::~CompleteGraphLogical()
{
	while(!nodeList.empty()) {
		delete nodeList.front();
		nodeList.pop_front();
	}
	nodeList.clear();
	//player1.clear();
	//player2.clear();
}

//	Creates the initial edges
void CompleteGraphLogical::createInitialEdges()
{	if (edgeWeight == 0)
	{
    	int randomEdgeValue = 0;
	    for (std::list<Node*>::iterator iter1 = nodeList.begin(); iter1 != nodeList.end(); iter1++)
    	{
        	for (std::list<Node*>::iterator iter2 = nodeList.begin(); iter2 != nodeList.end(); iter2++)
	        {
    	        
        	    if ((iter1) != (iter2) && !((*iter1)->edgeExists(*iter2)))
            	{
                	randomEdgeValue = getRandomEdge(10);
	                (*iter1)->setEdge(*iter2, randomEdgeValue);
    	            (*iter2)->setEdge(*iter1, randomEdgeValue);
        	    }
	        }
    	}
	}
	else	
	{	
	    for (std::list<Node*>::iterator iter1 = nodeList.begin(); iter1 != nodeList.end(); iter1++)
		{
			for (std::list<Node*>::iterator iter2 = nodeList.begin(); iter2 != nodeList.end(); iter2++)
			{
				if ((iter1) != (iter2))
				{
					(*iter1)->setEdge(*iter2, edgeWeight);
				}
			}
		}
	}
	int matrix[nodeList.size()][nodeList.size()];
	for (std::list<Node*>::iterator iter1 = nodeList.begin(); iter1 != nodeList.end(); iter1++)
    {
        for (std::list<Node*>::iterator iter2 = nodeList.begin(); iter2 != nodeList.end(); iter2++)
	    {
	        if ((*iter1)->edgeExists(*iter2))
	        {
	        	matrix[((*iter1)->getName())-1][((*iter2)->getName())-1] = (*iter1)->getWeight(*iter2);
	        	matrix[((*iter2)->getName())-1][((*iter1)->getName())-1] = (*iter1)->getWeight(*iter2);
	        }
	        else
	        {
	        	matrix[((*iter1)->getName())-1][((*iter2)->getName())-1] = 0;
	        	matrix[((*iter2)->getName())-1][((*iter1)->getName())-1] = 0;
	        }
	    }
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::ofstream matrix_output;
	matrix_output.open(MATRIX_RESULTS.c_str(), std::ios_base::app);
	matrix_output << "Game: " << gameNumber << std::endl;
	std::cout << "Game " << gameNumber << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < nodeList.size(); i++)
	{
		for (int j = 0; j < nodeList.size(); j++)
		{
			if (matrix[i][j] < 10)
			{
				std::cout << matrix[i][j] << "  ";
				matrix_output << matrix[i][j] << "  ";
			}
			else
			{
				std::cout << matrix[i][j] << " ";
				matrix_output << matrix[i][j] << " ";
			}
		}
		std::cout << std::endl;
		matrix_output << std::endl;
	}	
}

//Desc: Creates the initial Nodes
//Input: int i, which is the name of the Node
void CompleteGraphLogical::createInitialNodes(int nodes)
{
	for (int i = 1; i <= nodes; i++)
    {
        Node *n = new Node(i);
        nodeList.push_back(n);
    }
}

void CompleteGraphLogical::removeEdge()
{
	int n1 = 0;
	int n2 = 0;
	std::cout << "Please enter the nodes you would like to remove the edge between (x y): ";
	std::cin >> n1;
	std::cin >> n2;
	std::list<Node*>::iterator iter1;
	std::list<Node*>::iterator iter2;
	for (iter1 = nodeList.begin(); iter1 != nodeList.end(); iter1++)
	{
		if ((*iter1)->getName() == n1)
		{
			for (iter2 = nodeList.begin(); iter2 != nodeList.end(); iter2++)
			{
				if ((*iter2)->getName() == n2)
				{
					(*iter1)->destroyEdge(*iter2);
					(*iter2)->destroyEdge(*iter1);
				}
			}
		}
	}
}

//Desc: Prints out the current version of the program the user is running
void CompleteGraphLogical::printVersion()
{
	std::cout << std::endl;
	std::cout << "Version: 0.2 Beta" << std::endl;
	std::cout << "Author: Kyle Rodgers" << std::endl;
	std::cout << "Date of Last Revision: 5/4/14 23:30" << std::endl;
}

void CompleteGraphLogical::print()
{
	std::cout << "This surface contains the following nodes and edges: " << std::endl;
	std::list<Node*>::iterator iter;
	for (iter = nodeList.begin(); iter != nodeList.end(); iter++)
	{
		(*iter)->printEdges();
	}
}

int CompleteGraphLogical::getRandomNumber(int size)
{
	
	RandomEngine *rand = RandomEngine::instance();
	double r = rand->getRandom();
	int randNum = (int)(r * size);
	return randNum;
}

int CompleteGraphLogical::getRandomEdge(int size)
{
	
	RandomEngine *rand = RandomEngine::instance();
	double r = rand->getRandom();
	int randNum = (int)((r * size)+1);
	return randNum;
}

void CompleteGraphLogical::rotateBar()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while the games are played. Game: " << gameNumber << " " << (int)(((double)gameNumber/totalGames)*100.0) << "% complete";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while the games are played. Game: " << gameNumber << " " << (int)(((double)gameNumber/totalGames)*100.0) << "% complete";
	}
	std::cout.flush();
	return;
}

void CompleteGraphLogical::game()
{
//    std::cout << edgeWeight << std::endl;
//	for (std::list<Node*>::iterator iter = nodeList.begin(); iter != nodeList.end(); iter++)
//        std::cout << (*iter)->getDegree() << std::endl;
    std::ofstream master_data;
	//master_data.open("logs/log.txt");
	
	
	//std::string moves;
//	std::string gameName = std::to_string(i) + ".txt";
	std::string master_data_path = "output_data/master_data.txt";
	std::ofstream matrix_data;
//	master_data.open(path+gameName);
	master_data.open(master_data_path.c_str(), std::ios_base::app);
	matrix_data.open(MATRIX_RESULTS.c_str(), std::ios_base::app);
	std::list<Node*>::iterator iter1 = nodeList.begin();
	Node* nextMoveNode;
	Token* t = new Token(*iter1);
	int nextRandomWeight = 0;
	int edgeSize = 0;
	int nextMove = 0;
	if (watch == true)
	{
		master_data << (t->getTokenLocation())->getName() << "-";
		while (true)
		{
            
            if (t->getCurrentPlayerTurn() == 2)
            {
                nextMove = getRandomNumber(t->getTokenLocation()->getEdgeListSize());
                nextMoveNode = t->getTokenLocation()->getNodeAtElement(nextMove);
                edgeSize = t->getTokenLocation()->getWeight(nextMoveNode);
                nextRandomWeight = getRandomEdge(edgeSize);
            }
            else
            {
                nextMoveNode = t->getTokenLocation()->getMinimalDegreeNode();
                nextRandomWeight = t->getTokenLocation()->getWeight(nextMoveNode);
    	    }
            if (nextRandomWeight > 0)
        	{
        		
        		master_data << nextRandomWeight << "-";
        		(t->getTokenLocation())->removeEdgeWeight(nextMoveNode, nextRandomWeight);
	        	(nextMoveNode)->removeEdgeWeight(t->getTokenLocation(), nextRandomWeight);
    		    std::cout << "Player " << t->getCurrentPlayerTurn() << " removed edge " << (t->getTokenLocation())->getName() << " - " << nextRandomWeight << " - " << (nextMoveNode)->getName() << std::endl;
    		    matrix_data << "Player " << t->getCurrentPlayerTurn() << " removed edge " << (t->getTokenLocation())->getName() << " - " << nextRandomWeight << " - " << (nextMoveNode)->getName() << std::endl;
    		    t->setPlayerTurn();
	        	t->setTokenLocation(nextMoveNode);
       			master_data << (t->getTokenLocation())->getName() << "-";
/*        		
        		master_data << nextRandomWeight << "-";
        		(t->getTokenLocation())->setEdge(nextMoveNode, nextMoveNode->getWeight(t->getTokenLocation()) - nextRandomWeight);
		        (nextMoveNode)->setEdge(t->getTokenLocation(), t->getTokenLocation()->getWeight(nextMoveNode) - nextRandomWeight);
    		    std::cout << "Player " << t->getCurrentPlayerTurn() << " removed edge " << (t->getTokenLocation())->getName() << " - " << nextRandomWeight << " - " << (nextMoveNode)->getName() << std::endl;
	    	    //master_data << "Player " << t->getCurrentPlayerTurn() << " removed edge " << (t->getTokenLocation())->getName() << " - " << (nextMoveNode)->getName() << std::endl;
    	    	t->setPlayerTurn();
		        t->setTokenLocation(nextMoveNode);
		        master_data << (t->getTokenLocation())->getName() << "-";
*/		    }
    	    if (t->getTokenLocation()->getEdgeListSize() == 0)
			{
				//moves += std::to_string((t->getTokenLocation())->getName());
				t->setPlayerTurn();
				std::cout << std::endl;
				//master_data << "Player " << t->getCurrentPlayerTurn() << " wins!\n";
				master_data << t->getCurrentPlayerTurn() << std::endl;		
				std::cout << "Player " << t->getCurrentPlayerTurn() << " wins!" << std::endl;
				std::cout << std::endl;
				matrix_data << "Player" << t->getCurrentPlayerTurn() << " wins!\n" << std::endl;
                delete t;
				break;
			}
		}
	}
	else
	{
		master_data << (t->getTokenLocation())->getName() << "-";
		while (true)
		{
			rotateBar();
            for (std::list<Node*>::iterator iter = nodeList.begin(); iter != nodeList.end(); iter++)
                (*iter)->setDegree();
//            for (std::list<Node*>::iterator iter = nodeList.begin(); iter != nodeList.end(); iter++)
//                std::cout << "Node: " << (*iter)->getName() << " Degree: " << (*iter)->getDegree() << std::endl;
            if (t->getCurrentPlayerTurn() == 2)
            {
                nextMove = getRandomNumber(t->getTokenLocation()->getEdgeListSize());
                nextMoveNode = t->getTokenLocation()->getNodeAtElement(nextMove);
                edgeSize = t->getTokenLocation()->getWeight(nextMoveNode);
                nextRandomWeight = getRandomEdge(edgeSize);
            }
            else
            {
                nextMoveNode = t->getTokenLocation()->getMinimalDegreeNode();
                nextRandomWeight = t->getTokenLocation()->getWeight(nextMoveNode);
    	    }
            if (nextRandomWeight > 0)
    	    {
    	    	master_data << nextRandomWeight << "-";
        		(t->getTokenLocation())->removeEdgeWeight(nextMoveNode, nextRandomWeight);
	        	(nextMoveNode)->removeEdgeWeight(t->getTokenLocation(), nextRandomWeight);
	        	matrix_data << "Player " << t->getCurrentPlayerTurn() << " removed edge " << (t->getTokenLocation())->getName() << " - " << nextRandomWeight << " - " << (nextMoveNode)->getName() << std::endl;
    		    t->setPlayerTurn();
	        	t->setTokenLocation(nextMoveNode);
       			master_data << (t->getTokenLocation())->getName() << "-";
	    	}
/*            else if (nextRandomWeight == 0)
		    {
	    		t->getTokenLocation()->destroyEdge(nextMoveNode);
	    		nextMoveNode->destroyEdge(t->getTokenLocation());
		    }
*/    	    if (t->getTokenLocation()->getEdgeListSize() == 0)
			{
				//moves += std::to_string((t->getTokenLocation())->getName());
				t->setPlayerTurn();
//				std::cout << std::endl;
				matrix_data << t->getCurrentPlayerTurn() << std::endl;		
				//master_data << "Player " << t->getCurrentPlayerTurn() << " wins!\n";
				master_data << t->getCurrentPlayerTurn() << std::endl;		
				matrix_data << "Player " << t->getCurrentPlayerTurn() << " wins!\n" << std::endl;
//				std::cout << std::endl;
                delete t;
				break;
            }
        }
        master_data.close();
    }
}