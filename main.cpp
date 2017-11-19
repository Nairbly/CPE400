#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "string.h"

using namespace std;

struct AdjacentListNode{

	int destination;
	struct AdjacentListNode* next;

};

struct AdjacentList{

	struct AdjacentListNode *head;

};

struct Graph{

	int numberOfVertices;
	struct AdjacentList* array;

};

struct AdjacentListNode* newAdjacentListNode(int destination){

	struct AdjacentListNode* newNode = (AdjacentListNode*) malloc(sizeof(AdjacentListNode));
	newNode->destination = destination;
	newNode->next = NULL;

}

struct Graph* createGraph(int numberOfVertices){

	struct Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->numberOfVertices = numberOfVertices;

	graph->array = (struct AdjacentList*) malloc(numberOfVertices * sizeof(struct AdjacentList));

	int index;
	for (int index = 0 ; index < numberOfVertices ; index++)
	{
		graph->array[index].head = NULL;
	}

	return graph;
}

void addEdge(struct Graph* graph, int source, int destination){

    struct AdjacentListNode* newNode = newAdjacentListNode(destination);
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;
 
    newNode = newAdjacentListNode(source);
    newNode->next = graph->array[destination].head;
    graph->array[destination].head = newNode;

}

void printGraph(struct Graph* graph)
{
    int vertex;
    for (vertex = 0; vertex < graph->numberOfVertices; ++vertex)
    {
        struct AdjacentListNode* graphOutput = graph->array[vertex].head;
        cout << endl << "Adjacency list of vertex " << vertex << endl << "head";
        while (graphOutput)
        {
            cout << "->" << graphOutput->destination;
            graphOutput = graphOutput->next;
        }
        cout << endl;
    }
}

int main(){

    // create the graph given in above fugure
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
 
    // print the adjacency list representation of the above graph
    printGraph(graph);

/*
	ifstream fileIn.open("Config.conf"); 
	string input;
	char algorithmName;
	int delayTime;

	while (!fileIn.eof())
	{
		fileIn >> input;

		if (input == "Algorithm:")
		{
			fileIn >> algorithmName;
			//store in class 
		}

		if (input == "Queue:")
		{
			fileIn >> delayTime;
			//store in class
		}

		if (input == "Propagation:")
		{
			fileIn >> delayTime;
			//store in class
		}

		if (input == "Processing:")
		{
			fileIn >> delayTime;
			//store in class
		}

		if (input == "Transmission:")
		{
			fileIn >> delayTime;
			//store in class
		}						

		if (input == "Graph:")
		{
			fileIn >> input;
			//store in class
		}	
	}

	fileIn.close();

	ifstream.fileIn("INSERT CLASS VARIABLE WITH GRAPH NAME");

	int numberOfNodes;
	char nodeStart;
	char nodeEnd;
	int nodeDistance;

	fileIn >> numberOfNodes;

	while (!fileIn.eof())
	{
		fileIn >> nodeStart;
		fileIn >> nodeEnd;
		fileIn >> nodeDistance;
	}

	fileIn.close();

*/
}