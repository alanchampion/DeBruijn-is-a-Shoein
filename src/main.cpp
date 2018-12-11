#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "deBruijnGraph.h"
#include "eulerFinder.h"
#include "omp.h"

std::string graphIn;
int kmerSize;
deBruijnGraph graph = deBruijnGraph();


//prototypes
void createGraph();

int main(int argc, char* argv[]) {
	if(argc < 3) {
		printf("Not enough arguments to run program.\n");
		printf("Example: ./shoein fastq/SP1.fq 6\n");
		exit(1);
	}

	graphIn = argv[1];
	kmerSize = atoi(argv[2]);

	graph.setKmerSize(kmerSize);

	double start = omp_get_wtime();
	createGraph();
	double stop = omp_get_wtime();
    double time = stop - start;
    printf("Created graph in %.3f seconds\n", time);

	// createGraph();

	// graph.printGraph();

	return(0);
};


void createGraph() {
	printf("Reading in graph\n");

	std::ifstream inFile;
	inFile.open(graphIn);
	if(!inFile) {
		printf("Unable to open fastq file!\n");
		exit(1);
	}

	std::string line;
	bool wasAt = false;

	while(getline(inFile, line)) {
		if(wasAt && line[0] != '@') {
			wasAt = false;
			graph.readRead(line);
		}
		if(line[0] == '@') {
			wasAt = true;
		}
	}
	
	inFile.close();

	printf("Finished reading in file\n");
}
