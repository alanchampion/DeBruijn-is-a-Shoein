#include <iostream>
#include <string>
#include <fstream>
#include <vector> // for EULER
#include <stack>  //for EULER
#define FIN "ciclueuler.in"  //for EULER
#define FOUT "ciclueuler.out"  //for EULER
#define NMAX 100005  //for EULER
#define MMAX 700005  //for EULER

using namespace std;

/*
*	Base Case Implementation of De Bruijn Graph creation and finding Eulerian cycle.
*	De Bruijn Graph construction done using BCALM, which utilizes the GATB library.
*	Eulerian cycle is found in a naive fashion.
*/

vector<int> G[ NMAX ];  //for EULER
stack<int> STACK;  //for EULER

int degree[ NMAX ],  //for EULER

    sol[ MMAX ],  //for EULER

    num_nodes,   //for EULER

    num_edges,  //for EULER

    i,  //for EULER

    x,  //for EULER

    y,  //for EULER

    a,  //for EULER

    b;  //for EULER

//prototypes
    // for EULER
void read();
int solve();
int euler();
string GetStdoutFromCommand(string cmd);

int main(){
	/*
		Here are the variables that may be modified from run to run.
	*/
	// input fastq file
	string infile = "hg00096.fastq";
	// size of kmers -- can't be multiple of 4 due to GATB bug 
	string k = "30";
	// abundance minimum, so we can ignore possible errors
	char min = '2';
	//output fasta file
	string output = "hg00096.unitigs.fa";
	//modified output
	string mod = "output.txt";
	//edge info
	string edges = "edges.txt";

	//construct the BCALM call command
	string cmd = "./bcalm/build/bcalm -in " + infile + " -kmer-size " + k + " -abundance-min " + min;

	//construct De Bruijn graph
	system(cmd.c_str()); 

	//count number of lines in output so we can figure out how many nodes there are
	cmd = "wc -l " + output + " | awk \'{print $1}\'";
	string lines_str = GetStdoutFromCommand(cmd);
	int num_lines = atoi(lines_str.c_str());
	int num_nodes = (num_lines-2)/2;

	//construct grep call command
	//grab all edges from output file
	cmd = "grep -Eohn \"L:.:[0-9]+:.\" \'" + output + "\'";
	//get rid of unnecessary colons
	cmd += " | tr \':\' \' \'";
	//get rid of unecessary L character
	cmd += " | sed \'s/[L]//g\'";
	//send to txt file
	cmd += " > ";
	cmd += mod;

	//grab all edges from fasta file
	system(cmd.c_str());

	//CONSTRAINING TO UNDIRECTED GRAPHS currently 
	//Now, we need to construct a new txt file containing only the important info
	//PARSE Modified output HERE
//	ifstream in (mod);
	ifstream in;
	in.open(mod);
//	ofstream out (edges);
	ofstream out;
	out.open(edges);
	int first = 0;
	int second = 0;
	char dir1 = ' ';
	char dir2 = ' ';
	int num_edges = 0;
	while(in >> first >> dir1 >> second >> dir2){
		first = (first-1)/2;
		out << 	first << ' ' << second << endl;
		in.ignore();
		num_edges++;
	}
	in.close();
	//out now contains all edges
	out.close();

	//create file that will be read by euler functions
	out.open("ciclueuler.in");
	out << num_nodes << ' ' << num_edges << endl;
	// copy in all edges
	cmd = "cat " + edges + " >> ciclueuler.in";

	//create euler input file
	system(cmd.c_str());

	read(); // for EULER

   	solve();     // for EULER

    return(0);
}



void read() { // for EULER

    freopen(FIN, "r", stdin);

    scanf("%d %d", &num_nodes, &num_edges);

    for(i = 1; i <= num_edges; i++) {

          scanf("%d %d", &x, &y);

          G[ x ].push_back( y );  
          G[ y ].push_back( x );
 
          degree[ x ]++;
          degree[ y ]++;
    }     

    fclose( stdin ); 
};

int euler() { // for EULER

    for(i = 1; i <= num_nodes; i++) {

        if(degree[ i ] & 1) {

           return 0; 
        }
    }

    return 1;
}

int solve() { // for EULER

    freopen(FOUT, "w", stdout);

    if( !euler() ) {

           printf("-1");

           return 0;
    }

    STACK.push( 1 );

    while(!STACK.empty()) {

           a = STACK.top();

           if(!degree[ a ]) {

               sol[++sol[0]] = a;

               STACK.pop();

               continue;  
           }

           b = G[ a ].back();

           G[ a ].pop_back();           

           degree[ a ]--;

           degree[ b ]--;

           STACK.push( b ); 

           for(vector<int>::iterator it = G[ b ].begin(); it != G[ b ].end(); ++it) {

               if(*it == a) {

                   G[ b ].erase( it );

                   break;
               }   
           } 
    }

    for(i = 1; i <= num_edges; i++) printf("%d ", sol[ i ]); 

    fclose( stdout );
  
    return 1;
};



string GetStdoutFromCommand(string cmd) {

string data;
FILE * stream;
const int max_buffer = 256;
char buffer[max_buffer];
cmd.append(" 2>&1");

stream = popen(cmd.c_str(), "r");
if (stream) {
while (!feof(stream))
if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
pclose(stream);
}
return data;
}