#pragma once
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring> 
#include <parallel/algorithm>
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
		unordered_map<string, string> visited;
		int kmerSize;
		vector<vector<string>> cycles;
		void DFS();
		string visit(string, string);
		bool merge(vector<string>, vector<string>, vector<string>&);
};