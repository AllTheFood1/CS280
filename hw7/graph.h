#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

// must use these structs
// they represent the vertices in our graph
struct adjCity;
struct city;
struct adjCity
{
	city *v;
	int weight;
};
struct city
{
	string key; // stores the name of the city
	vector<adjCity*> adjacent;
	bool visited; // for traversals (DFS/BFS)
	bool solved; // for Dijsktra's
	int distance; // for keeping track of distance in Dijkstra's
	city* parent; // for keeping track of parent in Dijkstra's
};

class graph {
private:
	vector<city*> vertices;
public:
	graph(); //constructor
	~graph(); //destructor
	void insertCity(string cityName); // inserts a new vertex (city)
	void insertEdge(string firstCity, string secondCity, int weight); // inserts edge with specified weight
	void printGraph(); // prints each vertex and it's adj vertices
	city* search(string cityName); // finds and returns city 
	void bft(string startCity); // prints out the vertices in a BF traversal from the starting city
	void dft(string startCity); // prints out the vertices in a DF traversal from the starting city
	city* dijkstras(string start, string end); // Dijkstra's algorithm!
	void printShortestPath(city* endV); // to be called after Dijkstra's
};


// Constructor
graph::graph() {
	cout << "Constructing." << endl;
}

// Destructor
// need to actually call delete on each struct we made with new
// Should loop through, for each city, delete all adjacent cities, then delete the city
graph::~graph()
{
	cout << "Destructing." << endl;
	for(int i = 0; i < this->vertices.size(); i++)
	{
		cout << "Something is happening in the destructor" << this->vertices[i]->key << endl;
		for(int j = 0; j < this->vertices[i]->adjacent.size(); j++)
		{
			cout << "Something else is happening in the destructor" << this->vertices[i]->adjacent[j]->v->key << endl;
			delete this->vertices[i]->adjacent[j];
		}
		// delete this->vertices[i];
	}
	for(int i = 0; i < this->vertices.size(); i++)
	{
		delete this->vertices[i];
	}
}

/*
* Method name: insertCity
* Purpose: accepts a city name, adds a new vertex
* @param cityName - the name of the city
* @return - none
* Notes - should only add if there isn't already a vertex with that key,
* if there is a vertex with that key, print out an "error message"
*/
void graph::insertCity(string cityName)
{
	cout << "Inserting " << cityName << endl;
	for(int i = 0; i < this->vertices.size(); i++)
	{
		if(cityName == this->vertices[i]->key)
		{
			cityName = cityName + "2";
			cout << "That city name already exists, adding " << cityName << endl;
			break;
		}
	}
	city * temp = new city();
	temp->key = cityName;
	this->vertices.push_back(temp);
}

/*
* Method name: insertEdge
* Purpose: adds an edge between two cities
* @param firstCity - the first city in the edge
* @param secondCity - the second city in the edge
* @param weight - the weight of the edge (useful later for searching)
* @return - none
* Notes - should, technically, add two edges. The edge: firstCity -> secondCity
* and the edge: secondCity -> firstCity.
* You can follow most of the pseudocode in the book, but will need to add some additional
* functionality to add both edges.
*/
void graph::insertEdge(string firstCity, string secondCity, int weight)
{
	cout << "Inserting edges between " << firstCity <<" and " << secondCity << " with weight " << weight << endl;
	city* city1;
	city* city2;
	for(int i = 0; i < this->vertices.size(); i++)
	{
		if(this->vertices[i]->key == firstCity)
		{
			city1 = this->vertices[i];
		}else if(this->vertices[i]->key == secondCity)
		{
			city2 = this->vertices[i];
		}
	}
	adjCity* temp1 = new adjCity;
	temp1->v = city2;
	temp1->weight = weight;
	city1->adjacent.push_back(temp1);

	adjCity* temp2 = new adjCity;
	temp2->v = city1;
	temp2->weight = weight;
	city2->adjacent.push_back(temp2);
}

void graph::printGraph()
{
	for(int i = 0; i < this->vertices.size(); i++)
	{
		cout << this->vertices[i]->key << "-->";
		for(int j = 0; j < this->vertices[i]->adjacent.size(); j++)
		{
			cout << this->vertices[i]->adjacent[j]->v->key << "(" << vertices[i]->adjacent[j]->weight << ") ";
		}
		cout << endl;
	}
}

/*
* Method name: search
* Purpose: finds a key and returns the associated city pointer
* @param cityName - the key we are searching for
* @return - the pointer to that city, return NULL if the city we want is not in the graph
*/
city* graph::search(string cityName)
{
	cout << "Searching for " << cityName << endl;
	for(int i = 0; i < this->vertices.size(); i++)
	{
		if(cityName == this->vertices[i]->key)
		{
			return this->vertices[i];
		}
	}
	return NULL;
}

/*
* Method name: bft (breadth first traversal)
* Purpose: prints out a breadth first traversal from a start vertex
* @param startCity - the city we are starting from
* @return - none
* Notes - just print each city key as you traverse it, must use a queue!
* At the end, make sure to loop back through vertices, setting visited to false for each!
*/
void graph::bft(string startCity)
{
	cout << "Running BFT starting at " << startCity << endl;
	queue<city*>* THEqueue = new queue<city*>;
	city* startVertex = search(startCity);
	startVertex->visited = true;
	THEqueue->push(startVertex);
	while(!THEqueue->empty())
	{
		city* temp = THEqueue->front();
		THEqueue->pop();
		for(int i = 0; i < temp->adjacent.size(); i++)
		{
			if(!temp->adjacent[i]->v->visited)
			{
				temp->adjacent[i]->v->visited = true;
				cout << temp->adjacent[i]->v->key << endl;
				THEqueue->push(temp->adjacent[i]->v);
			}
		}
	}
	for(int i = 0; i < this->vertices.size(); i++)
	{
		this->vertices[i]->visited = false;
	}
}

/*
* Method name: dft (depth first traversal)
* Purpose: prints out a depth first traversal from a start vertex
* @param startCity - the city we are starting from
* @return - none
* Notes - just print each city key as you traverse it, must use a stack!
* At the end, make sure to loop back through vertices, setting visited to false for each!
*/
void graph::dft(string startCity)
{
	cout << "Running DFT starting at " << startCity << endl;
	city* startVertex = search(startCity);
	startVertex->visited = true;
	stack<city*>* THEstack = new stack<city*>;
	THEstack->push(startVertex);
	while(!THEstack->empty())
	{
		city* temp = THEstack->top();
		THEstack->pop();
		cout << temp->key << endl;
		for(int i = 0; i < temp->adjacent.size(); i++)
		{
			if(!temp->adjacent[i]->v->visited)
			{
				temp->adjacent[i]->v->visited = true;
				THEstack->push(temp->adjacent[i]->v);
			}
		}
	}
	for(int i = 0; i < this->vertices.size(); i++)
	{
		this->vertices[i]->visited = false;
	}
}

/*
* Method name: printShortestPath
* Purpose: starts at end vertex, walks backwards to the start
* 	vertex, prints the path in the correct order from start to finish
* @param endV - the city that we found the shortest path to
* @return - none
* Notes - use the parent pointers, may need a data structure to store
* 	the path in the right order
*/
void graph::printShortestPath(city* endV)
{
	stack<city*> pathStack;
	pathStack.push(endV);
	city* parent = endV->parent;
	while(parent != NULL)
	{
		pathStack.push(parent);
		parent = parent->parent;
	}
	while(!pathStack.empty())
	{
		cout << pathStack.top()->key << endl;
		pathStack.pop();
	}
}

/*
* Method name: dijkstras
* Purpose: performs the book's description of Dijkstra's algorithm
* 	to find the shortest path from start to end
* @param start - the city name we are starting from
* @param end - the city name that we are searching for
* @return - the pointer to the end vertex
* Notes - use the pseudocode from the book. You can feel free to create
* 	another vector to use to keep track of solved vertices
*/
city* graph::dijkstras(string start, string end)
{
	city* startVertex = search(start);
	city* endVertex = search(end);
	startVertex->solved = true;
	startVertex->distance = 0;
	vector<city*> solved;
	solved.push_back(startVertex);
	while(!endVertex->solved)
	{
		int minDistance = INT_MAX;
		city* solvedVertex = NULL;
		city* parent = NULL;
		for(int i = 0; i < solved.size(); i++)
		{
			city* solving = solved[i];
			for(int j = 0; j < solving->adjacent.size(); j++)
			{
				// cout << "Something is happening" << endl;
				if(!solving->adjacent[j]->v->solved)
				{
					int distance = solving->distance + solving->adjacent[j]->weight;
					if(distance < minDistance)
					{
						solvedVertex = solving->adjacent[j]->v;
						minDistance = distance;
						parent = solving;
					}
				}
			}
		}
		solvedVertex->distance = minDistance;
		solvedVertex->parent = parent;
		solvedVertex->solved = true;
		solved.push_back(solvedVertex);
	}
	return endVertex;
}
#endif
