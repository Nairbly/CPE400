#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "string.h"

//Ben and Brian

using namespace std;

struct AdjacentListNode{

	char nodeName;
	char neighbor;
	int distance;
	struct AdjacentListNode* next;

};

struct AdjacentList{

	struct AdjacentListNode *headPtr;

};

struct Graph{

	int numberOfVertices;
	struct AdjacentList* array;

};

class Config{
public:
	void readConfig(Graph*&);

private:
	char algorithmName;
	int Queue_delay;
	int Propagation_delay;
	int Processing_delay;
	int Transmission_delay;
};

AdjacentListNode* nameAdjacentListNode(char);
AdjacentListNode* newAdjacentListNode(char, int);
Graph* createGraph(int);
void addEdge(struct Graph*&, char, char, int);
void printGraph(struct Graph*);

int main(){

	Graph* graph;

	Config Save;

	Save.readConfig(graph);

    printGraph(graph);


}

AdjacentListNode* nameAdjacentListNode(char input){

	AdjacentListNode* newNode = (AdjacentListNode*) malloc(sizeof(AdjacentListNode));
	newNode->nodeName = input;

}

AdjacentListNode* newAdjacentListNode(char neighbor, int distance){

	AdjacentListNode* newNode = (AdjacentListNode*) malloc(sizeof(AdjacentListNode));
	newNode->neighbor = neighbor;
	newNode->distance = distance;
	newNode->next = NULL;

}

Graph* createGraph(int numberOfVertices){

	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->numberOfVertices = numberOfVertices;

	graph->array = (struct AdjacentList*) malloc(numberOfVertices * sizeof(struct AdjacentList));

	int index;
	for (int index = 0 ; index < numberOfVertices ; index++)
	{
		graph->array[index].headPtr = NULL;
	}

	return graph;
}

void addEdge(struct Graph*& graph, char source, char neighbor, int distance){

    AdjacentListNode* newNode = newAdjacentListNode(neighbor, distance);
    int saveLocation;
    bool done = 0;

    for (int i = 0; i < graph->numberOfVertices; i++)
    {
    	if (graph->array[i].headPtr->nodeName == source)
    	{
    		saveLocation = i;
    		break;
    	}
    }

    AdjacentListNode* pointer = graph->array[saveLocation].headPtr;

    if (pointer == NULL)
    {
    	pointer = newNode;
    }

    else
    {
	    while (pointer->next != NULL)
	    {
	    	pointer = pointer->next;
	    }    	
	    pointer->next = newNode;
    }

}

void printGraph(struct Graph* graph)
{
    int vertex;

    for (vertex = 0; vertex < graph->numberOfVertices; vertex++)
    {
        struct AdjacentListNode* graphOutput = graph->array[vertex].headPtr;
        
        cout << endl << "Adjacency list of vertex " << graph->array[vertex].headPtr->nodeName << endl << "head";
        
        graphOutput = graphOutput->next;

        while (graphOutput != NULL)
        {
            cout << " -> " << graphOutput->neighbor;
            graphOutput = graphOutput->next;
        }
        cout << endl;
    }
}

void Config::readConfig(Graph*& graph)
{

	ifstream fileIn;
	fileIn.open("Config.conf"); 
	string input;
	char algorithm;
	int delayTime;

	while (!fileIn.eof())
	{
		fileIn >> input;

		if (input == "Algorithm:")
		{
			fileIn >> algorithm;
			//store in class 
			algorithmName = algorithm;
		}

		if (input == "Queue:")
		{
			fileIn >> delayTime;
			//store in class
			Queue_delay = delayTime;
		}

		if (input == "Propagation:")
		{
			fileIn >> delayTime;
			//store in class
			Propagation_delay = delayTime;
		}

		if (input == "Processing:")
		{
			fileIn >> delayTime;
			//store in class
			Processing_delay = delayTime;
		}

		if (input == "Transmission:")
		{
			fileIn >> delayTime;
			//store in class
			Transmission_delay = delayTime;
		}						

	}

	fileIn.close();

	//Used to test if read-in is done properly
/*
	cout << algorithmName << endl;
	cout << Queue_delay << endl;
	cout << Propagation_delay << endl;
	cout << Processing_delay << endl;
	cout << Transmission_delay << endl;
*/
	fileIn.open("graph.txt");

	int numberOfNodes;
	char nodeNames;
	char nodeStart;
	char nodeEnd;
	int nodeDistance;

	fileIn >> numberOfNodes;

	graph = createGraph(numberOfNodes);

	for (int i = 0 ; i < numberOfNodes ; i++)
	{
		fileIn >> nodeNames;
    	AdjacentListNode* newNode = nameAdjacentListNode(nodeNames);		
		graph->array[i].headPtr = newNode;
	}

	while (!fileIn.eof())
	{
		fileIn >> nodeStart;
		fileIn >> nodeEnd;
		fileIn >> nodeDistance;
		addEdge(graph, nodeStart, nodeEnd, nodeDistance);
	}

	fileIn.close();

}