#pragma once
#include <string>
#include <fstream>
#include "deBruijnGraph.h"
#include "omp.h"

using namespace std;

class eulerFinder {
	public:
		void getPath(deBruijnGraph);
		eulerFinder(int kmerSize) {
			this->kmerSize = kmerSize;
		}
	private:
		deBruijnGraph graph;
		unordered_map<string, bool> visited;
		int kmerSize;
		void DFS();
		string visit(string);
};