// #include <iostream>
#include <fstream>
#include <vector>
// #include <stack>
// #include <thrust/device_vector>
#define FIN "test/ciclueuler.in"
#define FOUT "ciclueuler.out"
#define NMAX 100005
#define MMAX 700005

using namespace std;

vector<int> V1V2;
// stack<int> STACK;

// int degree[ NMAX ];

// int sol[ MMAX ],

int num_nodes, 

    num_edges,

    i,

    x,

    y,

    a,

    b;

//prototypes
void read();
// int solve();
// __global__ euler();
 
int main() {

    read();

    // solve();

    return(0);
};

void read() {
	printf("Starting read");
    freopen(FIN, "r", stdin);

    scanf("%d %d", &num_nodes, &num_edges);

    V1V2.resize(num_edges+num_edges, -1);
    // int temp[num_edges+num_edges];

    for(i = 0; i < num_edges; i++) {

          scanf("%d %d", &x, &y);

          // G[ x ].push_back( y );
          // G[ y ].push_back( x );
          // printf("%d", i);
          V1V2.insert(V1V2.begin()+i, x);
          V1V2.insert(V1V2.begin()+i+num_edges, y);
          // temp[i] = x;
          // temp[i+num_edges] = y;
 
          // degree[ x ]++;
          // degree[ y ]++;
    }     

    fclose( stdin ); 
};

/*__global__ void add(int *a, int *b, int *c) {
	int tID = blockIdx.x;
	printf("blockIdx.x = %d\n", blockIdx.x);
	if (tID < N) {
		c[tID] = a[tID] + b[tID];
		printf("tID = %d\n", tID);
	}
}*/

/*__global__ euler() {


    for(i = 1; i <= num_nodes; i++) {

        if(degree[ i ] & 1) {

           return 0; 
        }
    }

    return 1;
}*/

/*int solve() {

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
}; */