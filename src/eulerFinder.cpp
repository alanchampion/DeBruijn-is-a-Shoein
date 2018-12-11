#include "eulerFinder.h"

void eulerFinder::getPath(deBruijnGraph graph) {
	this->graph = graph;
	DFS();
}

void eulerFinder::DFS() {
	graph.printGraph();
	printf("%s %d\n", graph.getStartNode().c_str(), graph.getNodeCount());
	string solution = "";
	#pragma omp parallel
	{
		/*#pragma omp for
		for(k = 0; k < graph.getNodeCount(); k++) {
			visited.at(k) = false;
		}*/
		#pragma omp single
		solution = visit(graph.getStartNode());
	}
	printf("%s\n", solution.c_str());
}

string eulerFinder::visit(string node) {
	string cycle = node;
	if(visited.find(node) != visited.end()) {
		// TODO cycle tracking
		return cycle;
	}
	
	#pragma omp critical
	if(visited.find(node) == visited.end()) {
		visited.insert(make_pair(node, true));
	}

	for(auto n : graph.getNodes(node.substr(1, kmerSize-1))) {
		// printf("%c, %c\n", get<0>(n), get<1>(n));
		#pragma omp task
		cycle += visit(get<0>(n)+node.substr(1, kmerSize-1));
	}

	return cycle;
}