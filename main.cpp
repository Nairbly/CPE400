#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "string.h"

//Ben and Brian

using namespace std;

struct AdjacentListNode{

	char neighbor;
	int distance;
	struct AdjacentListNode* next;

};

struct AdjacentList{

	struct AdjacentListNode *head;

};

struct Graph{

	int numberOfVertices;
	struct AdjacentList* array;

};

class Config{
public:
	void readConfig(Graph*);
private:
	char algorithmName;
	int Queue_delay;
	int Propagation_delay;
	int Processing_delay;
	int Transmission_delay;
};

struct AdjacentListNode* newAdjacentListNode(char neighbor, int distance){

	struct AdjacentListNode* newNode = (AdjacentListNode*) malloc(sizeof(AdjacentListNode));
	newNode->neighbor = neighbor;
	newNode->distance = distance;
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

void addEdge(struct Graph* graph, char source, char neighbor, int distance){

    AdjacentListNode* newNode = newAdjacentListNode(neighbor, distance);
    int saveLocation;
    bool done = 0;
    for (int i = 0; i < graph->numberOfVertices; i++)
    {
    	cout << "huh" << endl;
    	if (graph->array[i].head->neighbor == source)
    	{
    		saveLocation = i;
    		break;
    	}
    }
    cout << "LUL" << endl;
    AdjacentListNode* pointer = graph->array[saveLocation].head;
    do{
    	cout << "fuck2" << endl;
    	if (pointer->next == NULL)
    	{
    		cout << "fuck3" << endl;
    		pointer->next = newNode;
    		done = 1;
    	}
    	cout << "fuck4" << endl;
		pointer = pointer->next;
		cout << "fuck5" << endl;
    }while(pointer->next != NULL || done != 1);
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
            cout << "->" << graphOutput->neighbor;
            graphOutput = graphOutput->next;
        }
        cout << endl;
    }
}

void Config::readConfig(Graph* graph)
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

	cout << algorithmName << endl;
	cout << Queue_delay << endl;
	cout << Propagation_delay << endl;
	cout << Processing_delay << endl;
	cout << Transmission_delay << endl;
	cout << fileName << endl;

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
		cout << "lol" << endl;
		graph->array[i].head->neighbor = nodeNames;
		cout << "ded" << endl;
		cout << graph->array[i].head->neighbor << endl;
	}

	while (!fileIn.eof())
	{
		fileIn >> nodeStart;
		fileIn >> nodeEnd;
		fileIn >> nodeDistance;
		addEdge(graph, nodeStart, nodeEnd, nodeDistance);
		cout << "fuck" << endl;
	}

	fileIn.close();

}


int main(){

	Graph* graph;

	Config Save;

	Save.readConfig(graph);

/*
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
*/

}