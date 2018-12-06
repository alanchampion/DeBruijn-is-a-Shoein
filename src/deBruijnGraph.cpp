#include "deBruijnGraph.h"

deBruijnGraph::deBruijnGraph() {
	graph = unordered_map<string, set<tuple<char, char>>>();
}

void deBruijnGraph::readRead(string read) {
	// printf("%s\n", read.c_str());
	string kmer;
	string prevKmer = "";
	for(long unsigned int i = 0; i <= read.length() - kmerSize; i++) {
		kmer = read.substr(i, kmerSize);
		// printf("%s\n", kmer.c_str());
		addEdge(prevKmer, kmer);
		prevKmer = kmer;
	}
	addEdge(prevKmer, "");
}

void deBruijnGraph::setKmerSize(int kmerSize) {
	this->kmerSize = kmerSize;
}

void deBruijnGraph::addEdge(string from, string to) {
	// printf("(%s, %s)\n", from.c_str(), to.c_str());

	string edge;
	if(from == "") {
		edge = to.substr(0, kmerSize-1);
	} else {
		edge = from.substr(1, kmerSize-1);
	}

	if(graph.find(edge) == graph.end()) {
		// printf("%s\n", edge.c_str());
		graph.insert(make_pair(edge, set<tuple<char, char>>()));
	}

	// TODO Get all the possible edges. 
	if(from != "" && to != "") {
		// printf("Adding to edge %s tuple (%c, %c)\n", edge.c_str(), from[0], to[kmerSize-1]);
		graph.at(edge).insert(tuple<char, char>(from[0], to[kmerSize-1]));
	} 
	if(from == "") {
		graph.at(edge).insert(tuple<char, char>(FRONT, to[kmerSize-1]));
	}
	if(to == "") {
		graph.at(edge).insert(tuple<char, char>(from[0], BACK));
	}
}

void deBruijnGraph::printGraph() {
	for(auto elemg : graph) {
		printf("%s: ", elemg.first.c_str());
		for(auto elems : elemg.second) {
			printf("(%c, %c), ", get<0>(elems), get<1>(elems));
		}
		printf("\n");
	}
}