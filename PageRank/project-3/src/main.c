#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <getopt.h>
#include <ctype.h>
#include "utils.h"
#include "struct.h"
#include "statistics.h"

int main(int argc, char *argv[]) {
    rand_init();
    int opt;
    int N = -1; // Number of steps (default is invalid to ensure it's set)
    int P = 10; // Default probability
    int rflag = 0, mflag = 0, hflag = 0, sflag = 0;

    while ((opt = getopt(argc, argv, "hr:m:p:s")) != -1) {
        switch (opt) {
            case 's': // Statistics flag
                sflag = 1;
                break;
            case 'h': // Help flag
                hflag = 1;
                break;
            case 'r': // Random surfer
                rflag = 1;
                N = atoi(optarg);
                if (N <= 0) {
                    fprintf(stderr, "Option -%c requires a positive integer argument.\n", opt);
                    return 1;
                }
                break;
            case 'm': // Markov chain
                mflag = 1;
                N = atoi(optarg);
                if (N <= 0) {
                    fprintf(stderr, "Option -%c requires a positive integer argument.\n", opt);
                    return 1;
                }
                break;
            case 'p': // Set probability P
                P = atoi(optarg);
                if (P < 1 || P > 100) {
                    fprintf(stderr, "Option -%c requires an integer argument between 1 and 100.\n", opt);
                    return 1;
                }
                break;
            case '?':
                if (optopt == 'r' || optopt == 'm' || optopt == 'p' || optopt == 's')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    if (hflag) {
        printf("Usage: ./pagerank [OPTIONS]... [FILENAME]\n");
        printf("Options:\n");
        printf("  -h  Show this help message and exit.\n");
        printf("  -r N  Perform N steps of the Random Surfer model and print the result.\n");
        printf("  -m N  Perform N steps of the Markov Chain model and print the result.\n");
        printf("  -p P  Set the boredom probability percent (default: 10%%, range: 1-100).\n");
        printf("  -s  Compute and print the statistics of the graph.\n");
        printf("FILENAME must be specified unless -h is used. FILENAME should be in DOT format.\n");
        return 0;
    }

    if (optind == argc) {
        fprintf(stderr, "Missing FILENAME argument.\n");
        return 1;
    }

    char *filename = argv[optind]; // File to process

    // Process the file based on flags
   // if (sflag) {
   //     printf("Running Statistics for file: %s\n", filename);
  //  }
  //  if (rflag) {
  //      printf("Running Random Surfer model for %d steps, P=%d, on file: %s\n", N, P, filename);
  //  }
  //  if (mflag) {
  //      printf("Running Markov Chain model for %d steps, P=%d, on file: %s\n", N, P, filename);
   // }

   

// read graph
Graph* graph = readDotFile(filename);

 // print statistics
 if (sflag == 1) {
stats (graph);

printf ("%s:\n" , graph->name);
printf( "- num nodes: %d\n", graph->nodeCount);
printf( "- num edges: %d\n", graph->edgeCount);
printf("- indegree: %d-%d\n" , graph->minInDegree , graph->maxInDegree);
printf("- outdegree: %d-%d\n" , graph->minOutDegree , graph->maxOutDegree);
}
printGraph (graph);
deleteGraph (graph);
return 0;
}