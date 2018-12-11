#pragma once
#include <string>
#include <unordered_map>
#include <tuple>
#include <set>
#define BACK '$'
#define FRONT '^'

using namespace std;

class deBruijnGraph {
	private:
		int kmerSize;
		unordered_map<string, set<tuple<char, char>>> graph;
		int nodeCount;
		string startNode;
		void addEdge(string, string);
		void updateNodeCount(string);
	public:
		deBruijnGraph();
		void readRead(string);
		void setKmerSize(int);
		void printGraph();
		int getNodeCount();
		string getStartNode();
		set<tuple<char, char>> getNodes(string);
};
