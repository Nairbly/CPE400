#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include "string.h"

//Ben and Brian

using namespace std;

//Struct declaration
struct AdjacentListNode{

	char nodeName;
	char neighbor;
	int distance;
	struct AdjacentListNode* next;

};

//Struct declaration
struct AdjacentList{

	struct AdjacentListNode *headPtr;

};

//Struct declaration
struct Graph{

	int numberOfVertices;
	int numberOfEdges;
	AdjacentList* array;

};

//Class declaration
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

//Function declarations
AdjacentListNode* nameAdjacentListNode(char);
AdjacentListNode* newAdjacentListNode(char, int);
Graph* createGraph(int);
void addEdge(struct Graph*&, char, char, int);
void printGraph(struct Graph*);
void bellmanFord(Graph*, char);
void printBellmanFord(int[], char[], int);

//Main driver
int main(){

	Graph* graph;

	Config Save;

	Save.readConfig(graph);

    printGraph(graph);

    bellmanFord(graph, graph->array[0].headPtr->nodeName);

}

//Function implementation
AdjacentListNode* nameAdjacentListNode(char input){

	AdjacentListNode* newNode = (AdjacentListNode*) malloc(sizeof(AdjacentListNode));
	newNode->nodeName = input;

}

//Function implementation
AdjacentListNode* newAdjacentListNode(char neighbor, int distance){

	AdjacentListNode* newNode = (AdjacentListNode*) malloc(sizeof(AdjacentListNode));
	newNode->neighbor = neighbor;
	newNode->distance = distance;
	newNode->next = NULL;

}

//Function implementation
Graph* createGraph(int numberOfVertices){

	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->numberOfVertices = numberOfVertices;

	graph->array = (struct AdjacentList*) malloc(numberOfVertices * sizeof(struct AdjacentList));

	int index;
	for (int index = 0 ; index < numberOfVertices ; index++)
	{
		graph->array[index].headPtr = NULL;
	}

	graph->numberOfEdges = 0;

	return graph;
}

//Function implementation
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

    graph->numberOfEdges += 1;

}

//Function implementation
void printGraph(struct Graph* graph)
{
    int vertex;

    for (vertex = 0; vertex < graph->numberOfVertices; vertex++)
    {
        AdjacentListNode* graphOutput = graph->array[vertex].headPtr;
        
        cout << "Adjacency list of vertex " << graph->array[vertex].headPtr->nodeName << endl << "head";
        
        graphOutput = graphOutput->next;

        while (graphOutput != NULL)
        {
            cout << " -> " << graphOutput->neighbor << "-" << graphOutput->distance;
            graphOutput = graphOutput->next;
        }
        cout << endl;
    }
}

//Function implementation
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
			algorithmName = algorithm;
		}

		if (input == "Queue:")
		{
			fileIn >> delayTime;
			Queue_delay = delayTime;
		}

		if (input == "Propagation:")
		{
			fileIn >> delayTime;
			Propagation_delay = delayTime;
		}

		if (input == "Processing:")
		{
			fileIn >> delayTime;
			Processing_delay = delayTime;
		}

		if (input == "Transmission:")
		{
			fileIn >> delayTime;
			Transmission_delay = delayTime;
		}						

	}

	fileIn.close();

	if (algorithmName == 'D')
	{
		fileIn.open("graph.txt");
	}

	else if (algorithmName == 'B')
	{
		fileIn.open("graphBMF.txt");
	}

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

// Implementation of the Bellman Ford algorithm
void bellmanFord(Graph* graph, char source){

	int vertices = graph->numberOfVertices;
	int edges = graph->numberOfEdges;	
	int dist[vertices]; //integer array to hold values of distance from source
	char sourceNodes[vertices]; //character array to hold nodes' characters

	//Copy start of adjacency list into new array
	for (int i = 0 ; i < vertices ; i++)
	{
		sourceNodes[i] = graph->array[i].headPtr->nodeName;
	}

	//Set values of each node to 1000 except the one passed by parameter
	//1000 is to help indicate that distance has not been evaluated yet
	for (int i = 0 ; i < vertices ; i++)
	{
		dist[i] = 1000;
		if (sourceNodes[i] == source)
		{
			dist[i] = 0;
		}
	}

	//Declaration of variables to use
	char sourceNodeName;
	char neighborNodeName;
	int distanceBetweenNodes;
	int indexOfSource = 0;
	int indexOfNeighbor = 0;

	//Go through all the vertices
	for (int i = 0 ; i < vertices ; i++)
	{
		//Go through all the edges
		for (int j = 0 ; j < vertices ; j++)
		{
			//Create pointer to headPtr of array to prevent segmentation faults
			AdjacentListNode* bellmanPointer = graph->array[j].headPtr;

			//Store name of the node
	  		sourceNodeName = bellmanPointer->nodeName;
	  		//Move to next item in the node's adjacency list
			bellmanPointer = bellmanPointer->next;

			//While adjacency list of that node does not hit NULL
			while (bellmanPointer != NULL)
			{
				//Set neighbor name
				neighborNodeName = bellmanPointer->neighbor;
				//Set distance between the nodes
				distanceBetweenNodes = bellmanPointer->distance;

				//Find index of the node 
				while (sourceNodes[indexOfSource] != sourceNodeName)
				{
					indexOfSource++;
				}

				//Find index of its neighbor
				while (sourceNodes[indexOfNeighbor] != neighborNodeName)
				{
					indexOfNeighbor++;
				}

				//If distance has been set and the value is less than the distance of the neighbor
				if ((dist[indexOfSource] != 1000) && (((dist[indexOfSource] + distanceBetweenNodes) < dist[indexOfNeighbor])))
				{
					//Set new value of distance (shortest path possible)
					dist[indexOfNeighbor] = dist[indexOfSource] + distanceBetweenNodes;
				}

				//Move onto next item in adjacency list
				bellmanPointer = bellmanPointer->next;

				//Reset index values to be used
				indexOfSource = 0;
				indexOfNeighbor = 0;				
			}

		}
	}

	printBellmanFord(dist, sourceNodes, vertices);

}

//Function prints out the results of a Bellman-Ford algorithm
void printBellmanFord(int dist[], char sourceNodes[], int vertices){

	cout << endl << "Vertex    Distance from Source" << endl;
	for (int i = 0 ; i < vertices ; i++)
	{
		cout << sourceNodes[i] << "         " << dist[i] << endl;
	}

}