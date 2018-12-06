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
		void addEdge(string, string);
	public:
		deBruijnGraph();
		void readRead(string);
		void setKmerSize(int);
		void printGraph();
};