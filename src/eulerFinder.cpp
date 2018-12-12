#include "eulerFinder.h"

void eulerFinder::getPath(deBruijnGraph graph) {
	this->graph = graph;
	DFS();
}

void eulerFinder::DFS() {
	graph.printGraph();
	// printf("%s %d\n", graph.getStartNode().c_str(), graph.getNodeCount());
	string solution = "";
	printf("Begin DFS\n");
	double start = omp_get_wtime();
	#pragma omp parallel
	{
		/*#pragma omp for
		for(k = 0; k < graph.getNodeCount(); k++) {
			visited.at(k) = false;
		}*/
		#pragma omp single
		solution = visit(graph.getStartNode(), "");
	}
	double stop = omp_get_wtime();
	double time = stop - start;
	// printf("%s\n", solution.c_str());
	/*for(auto v : cycles) {
		printf("=========== Cycle ===========\n");
		for(auto c : v) {
			printf("%s\n", c.c_str());
		}
		printf("\n");
	}*/
	printf("DFS took %.3f seconds and created %lu cycles\n", time, cycles.size());
	printf("Begin Merging\n");
	start = omp_get_wtime();
	// #pragma omp parallel
	{
		/*for(int i = 0; i < int(cycles.size()); i++) {
			for(int j = 0; j < int(cycles.size()); j++) {
				if(i != j){
					#pragma omp task
					compare(cycles.at(i), cycles.at(j));
				}
			}
		}*/
		/*#pragma omp for
		for(int i = 0; i < int(cycles.size()-1); i++) {
			vector<string> mergedVector;
			merge(cycles.at(i), cycles.at(i+1),mergedVector);
		}*/
		int i = 0;
		int j = 1;
		bool noMergesLeft = false;
		bool doubleCheckMerges = false;
		int previousCyclesSize = cycles.size();
		while(cycles.size() > 1) {
			if(i >= int(cycles.size()-j)) {
				// printf("i too big\n");
				i = 0;
				++j;
				if(j >= int(cycles.size())) {
					// printf("j too big too\n");
					if(previousCyclesSize == int(cycles.size()) && noMergesLeft) {
						doubleCheckMerges = true;
					}
					if(previousCyclesSize == int(cycles.size())) {
						noMergesLeft = true;
					}
					previousCyclesSize = cycles.size();
					j = 1;
				}
			}
			// printf("i: %d\nj: %d\nCycles size: %lu\n", i, j, cycles.size());
			vector<string> mergedVector;
			bool mergeSuccess = merge(cycles.at(i), cycles.at(i+j), mergedVector);
			if(mergeSuccess) {
				// cycles.erase(cycles.begin() + i);
				cycles[i] = mergedVector;
				cycles.erase(cycles.begin() + i+j);
				// cycles.push_back(mergedVector);
			} else {
				++i;
			}

			if(noMergesLeft && doubleCheckMerges) {
				break;
			}
		}
	}
	stop = omp_get_wtime();
    time = stop - start;
    printf("Merging took %.3f seconds\n", time);

    printf("\nCycles size: %lu\n\n", cycles.size());
	for(auto cycle : cycles) {
		printf("====================== CYCLE ======================\n");
		for(auto node : cycle) {
			printf("%c", node[0]);
		}
		printf("\n\n");
	}
	printf("\n");
}

bool eulerFinder::merge(vector<string> cycle1, vector<string> cycle2, vector<string>& mergedVector) {
	// printf("Start merge\n");
	int match1 = -1;
	int match2 = -1;
	int count = 0;
	bool exitFor = false;

	for(int i = 0; i < int(cycle1.size()); ++i) {
		// printf("Cycle 1 size: %lu\nCycle 2 size: %lu\n", cycle1.size(), cycle2.size());
		for(int j = 0; j < int(cycle2.size()); ++j) {
			// printf("Cycle 1 size: %lu\nCycle 2 size: %lu\n", cycle1.size(), cycle2.size());
			// kprintf("i: %d\nj: %d\n", i, j);
			// printf("%s and %s\n", node1.c_str(), node2.c_str());
			if(cycle1.at(i) == cycle2.at(j)) {
				if(count == 0) {
					match1 = i;
					match2 = j;
				}
				count++;
			}
			// printf("Cycle1: %s\nCycle2: %s\n", cycle1.at(i).c_str(), cycle2.at(j).c_str());
			if(count > 0 && cycle1.at(i) != cycle2.at(j)){
				// printf("We breaking out, boys\n");
				exitFor = true;
				break;
			}
			if(count > 0) {
				++i;
				if(i >= int(cycle1.size())) {
					i = 0;
				}
			}
		}
		if(exitFor) {
			// printf("Let's get out of here\n");
			break;
		}
	}

	if(count > int(cycle1.size())) {
		count = cycle1.size();
	} else if(count > int(cycle2.size())) {
		count = cycle2.size();
	}

	if(count == 0) {
		// printf("Finished merge\n");
		return false;
	} else if(count == 1) {
		// printf("===== COUNT IS 0 =====\n");
		/*printf("Merging vector one: \n");
		for(auto a : cycle1) {
			printf("%s\n", a.c_str());
		}
		printf("Merging vector two: \n");
		for(auto a : cycle2) {
			printf("%s\n", a.c_str());
		}*/
		// printf("One is size %lu. Two is size %lu\n", cycle1.size(), cycle2.size());
		// printf("Merging one on %d. Merging two on %d.\n", match1, match2);
		mergedVector.insert(mergedVector.end(), cycle1.begin()+match1+1, cycle1.end());
		mergedVector.insert(mergedVector.end(), cycle1.begin(), cycle1.begin()+match1+1);
		mergedVector.insert(mergedVector.end(), cycle2.begin()+match2+1, cycle2.end());
		mergedVector.insert(mergedVector.end(), cycle2.begin(), cycle2.begin()+match2);
		/*printf("Merged vector\n");
		for(auto a : mergedVector) {
			printf("%s\n", a.c_str());
		}
		printf("Done\n");*/
	} else {
		// printf("===== COUNT IS %d =====\n", count);
		/*printf("Merging vector one: \n");
		for(auto a : cycle1) {
			printf("%s\n", a.c_str());
		}
		printf("Merging vector two: \n");
		for(auto a : cycle2) {
			printf("%s\n", a.c_str());
		}*/
		// printf("One is size %lu. Two is size %lu\n", cycle1.size(), cycle2.size());
		// printf("Merging one on %d. Merging two on %d.\n", match1, match2);
		if(match1+count > int(cycle1.size())) {
			int start = match1-(cycle1.size()-count);
			mergedVector.insert(mergedVector.end(), cycle1.begin()+start, cycle1.begin()+match1);
			mergedVector.insert(mergedVector.end(), cycle1.begin()+match1, cycle1.end());
			mergedVector.insert(mergedVector.end(), cycle1.begin(), cycle1.begin()+start);
			mergedVector.insert(mergedVector.end(), cycle2.begin()+match2+count, cycle2.end());
			mergedVector.insert(mergedVector.end(), cycle2.begin(), cycle2.begin()+match2);
		} else if(match2+count > int(cycle2.size())) {
			int start = match2-(cycle2.size()-count);
			mergedVector.insert(mergedVector.end(), cycle1.begin()+match1+count, cycle1.end());
			mergedVector.insert(mergedVector.end(), cycle1.begin(), cycle1.begin()+match1+count);
			mergedVector.insert(mergedVector.end(), cycle2.begin()+start, cycle2.begin()+match2);
			// mergedVector.insert(mergedVector.end(), cycle2.begin()+match2, cycle2.end());
			// mergedVector.insert(mergedVector.end(), cycle2.begin(), cycle2.begin()+start);
		} else if(match1 == count) {
			mergedVector.insert(mergedVector.end(), cycle2.begin(), cycle2.end());
		} else if(match2 == count) {
			mergedVector.insert(mergedVector.end(), cycle1.begin(), cycle1.end());
		} else {
			mergedVector.insert(mergedVector.end(), cycle1.begin()+match1+count, cycle1.end());
			mergedVector.insert(mergedVector.end(), cycle1.begin(), cycle1.begin()+match1+count);
			mergedVector.insert(mergedVector.end(), cycle2.begin()+match2+count, cycle2.end());
			mergedVector.insert(mergedVector.end(), cycle2.begin(), cycle2.begin()+match2);
		}
		/*printf("Merged vector\n");
		for(auto a : mergedVector) {
			printf("%s\n", a.c_str());
		}
		printf("Done\n");*/
	}
	// printf("Finished merge\n");
	return true;
}

string eulerFinder::visit(string node, string parent) {
	// printf("Calling visit on %s with parent %s\n", node.c_str(), parent.c_str());
	string cycle = node.substr(kmerSize-1, 1);
	if(visited.find(node) != visited.end()) {
		// TODO cycle tracking
		// printf("Found a already visited\n");
		#pragma omp critical
		{
			vector<string> readBack = vector<string>();
			readBack.push_back(node);
			bool findingCycle = true;
			while(findingCycle) {
				readBack.push_back(parent);
				if(visited.find(parent) != visited.end()) {
					parent = visited.at(parent);
					if(find(readBack.begin(), readBack.end(), parent) != readBack.end()) {
						findingCycle = false;
					}
				} else {
					findingCycle = false;
				}
				// printf("%s\n", parent.c_str());
			}
			if(parent == node) {
				reverse(readBack.begin(), readBack.end());
				cycles.push_back(readBack);
			}
		}
		return cycle;
	}
	
	#pragma omp critical
	if(node.substr(kmerSize-1, 1) != "$"){
		if(visited.find(node) == visited.end()) {
			if(parent != "") {
				visited.insert(make_pair(node, parent));
			}
		}
	}
	else {
		visited.erase(parent);
	}

	if(node.substr(kmerSize-1, 1) != "$"){
		for(auto n : graph.getNodes(node.substr(1, kmerSize-1))) {
			// printf("%c, %c\n", get<0>(n), get<1>(n));
			#pragma omp task
			cycle += visit(node.substr(1, kmerSize-1)+get<1>(n), node);
		}
	}

	return cycle;
}