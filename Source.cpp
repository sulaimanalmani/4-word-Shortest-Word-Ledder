// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <iostream>
#include <limits.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Number of vertices in the graph
#define V 3807
string data[V];
vector<vector<int>> graph;

// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
	if (sptSet[v] == false && dist[v] <= min)
		min = dist[v], min_index = v;

	return min_index;
}

// Function to print shortest path from source to j
// using parent array
void printPath(int parent[], int j)
{
	// Base Case : If j is source
	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);

	printf("%s ", data[j]);
}

// A utility function to print the constructed distance
// array
void printSolution(int dist[], int src, int tar, int parent[])
{
	int i = tar;
	printf("Vertex\t  Distance\tPath");
	printf("\n%s -> %s \t\t %d\t\t%s ", data[src], data[i], dist[i], data[src]);
	printPath(parent, i);
}

// Funtion that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(int src, int tar)
{
	int dist[V];  // The output array. dist[i] will hold
	// the shortest distance from src to i

	// sptSet[i] will true if vertex i is included / in shortest
	// path tree or shortest distance from src to i is finalized
	bool sptSet[V];

	// Parent array to store shortest path tree
	int parent[V];

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
	{
		parent[i] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of
		// vertices not yet processed. u is always equal to src
		// in first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is
			// an edge from u to v, and total weight of path from
			// src to v through u is smaller than current value of
			// dist[v]
		if (!sptSet[v] && graph[u][v] &&
			dist[u] + graph[u][v] < dist[v])
		{
			parent[v] = u;
			dist[v] = dist[u] + graph[u][v];
		}
	}

	// print the constructed distance array
	printSolution(dist, src, tar, parent);
	system("pause");
}
bool DiffByOne(string s1, string s2)
{
	int diff = 0;
	if (!(s1[0] == s2[0]))
		diff++;
	if (!(s1[1] == s2[1]))
		diff++;
	if (!(s1[2] == s2[2]))
		diff++;
	if (!(s1[3] == s2[3]))
		diff++;

	if (diff == 1)
		return true;
	else return false;
}
// driver program to test above function
int main()
{
	ifstream ifile;
	ifile.open("dict.txt");
	for (int i = 0; i<3807; i++)
	{
		ifile >> data[i];
	}

	vector<vector<int>> graph;
	for (int i = 0; i<V; i++)
	{
		float percentage = float(i) / 3807 * 100;
		cout << percentage <<"%" << "\n";
		vector<int> temp;
		for (int j = 0; j<V; j++)
		{
			if (DiffByOne(data[j], data[i]))
				temp.push_back(1);
			else temp.push_back(0);
		}
		graph.push_back(temp);
	}

	while (true)
	{
		system("CLS");
		cout << "Enter Source : ";
		string sx;
		cin >> sx;
		cout << "Enter Target : ";
		string sy;
		cin >> sy;
		int x, y, c = 0;
		for (int i = 0; i<3807; i++)
		{
			if (data[i] == sx)
				x = i, c++;
			if (data[i] == sy)
				y = i, c++;
			if (c == 2)
				break;
		}
		dijkstra(x, y);
	}
	return 0;
}