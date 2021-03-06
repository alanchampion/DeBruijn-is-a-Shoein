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
	if(startNode == "") {
		startNode = from;
		startNodeSize = 1;
	}

	updateNodeCount(from);
	updateNodeCount(to);

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

	if(from != "" && to != "") {
		// printf("Adding to edge %s tuple (%c, %c)\n", edge.c_str(), from[0], to[kmerSize-1]);
		auto e = begin(graph.at(edge));

		while(e != end(graph.at(edge))) {
			if(get<0>(*e) == FRONT) {
				graph.at(edge).insert(tuple<char, char>(from[0], get<1>(*e)));
				e = graph.at(edge).erase(e);
			} else if(get<1>(*e) == BACK) {
				graph.at(edge).insert(tuple<char, char>(get<0>(*e), to[kmerSize-1]));
				e = graph.at(edge).erase(e);
			} else {
				graph.at(edge).insert(tuple<char, char>(from[0], get<1>(*e)));
				graph.at(edge).insert(tuple<char, char>(get<0>(*e), to[kmerSize-1]));
			}
			++e;
		}
		graph.at(edge).insert(tuple<char, char>(from[0], to[kmerSize-1]));
		edgeCount++;
	} 
	if(from == "") {
		auto e = begin(graph.at(edge));
		bool add = true;

		while(e != end(graph.at(edge))) {
			if(get<1>(*e) == BACK) {
				graph.at(edge).insert(tuple<char, char>(get<0>(*e), to[kmerSize-1]));
				add = false;
				e = graph.at(edge).erase(e);
			} else if(get<0>(*e) != FRONT) {
				add = false;
				graph.at(edge).insert(tuple<char, char>(get<0>(*e), to[kmerSize-1]));
			}
			++e;
		}
		if(add) {
			graph.at(edge).insert(tuple<char, char>(FRONT, to[kmerSize-1]));
		}
	}
	if(to == "") {
		auto e = begin(graph.at(edge));
		bool add = true;

		while(e != end(graph.at(edge))) {
			if(get<0>(*e) == FRONT) {
				graph.at(edge).insert(tuple<char, char>(from[0], get<1>(*e)));
				add = false;
				e = graph.at(edge).erase(e);
			} else if(get<1>(*e) != BACK) {
				graph.at(edge).insert(tuple<char, char>(from[0], get<1>(*e)));
				add = false;
			}
			++e;
		}
		if(add) {
			graph.at(edge).insert(tuple<char, char>(from[0], BACK));
		}
	}
	if(int(graph.at(edge).size()) > startNodeSize && edge[0] != 'N') {
		startNodeSize = graph.at(edge).size();
		startNode = from;
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

void deBruijnGraph::updateNodeCount(string node) {
	if(node == "") {
		return;
	}

	string front = node.substr(0, kmerSize-1);
	string back = node.substr(1, kmerSize-1);
	nodeCount++;

	if(graph.find(front) != graph.end()) {
		for(auto p : graph.at(front)) {
			if(front+get<1>(p) == node) {
				nodeCount--;
				return;
			}
		}
	}
	if(graph.find(back) != graph.end()) {
		for(auto p : graph.at(back)) {
			if(get<0>(p)+back == node) {
				nodeCount--;
				return;
			}
		}
	}
}

int deBruijnGraph::getNodeCount() {
	return nodeCount;
}

int deBruijnGraph::getEdgeCount() {
	return edgeCount;
}

string deBruijnGraph::getStartNode() {
	return startNode;
}

set<tuple<char, char>> deBruijnGraph::getNodes(string edge) {
	return graph.at(edge);
}