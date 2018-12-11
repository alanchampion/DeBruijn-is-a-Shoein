#pragma once
#include <string>
#include <fstream>
#include "deBruijnGraph.h"
#include "omp.h"

using namespace std;

void getPath(deBruijnGraph graph) {
	graph.printGraph();
}