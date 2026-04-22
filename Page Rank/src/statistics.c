#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <limits.h>
#include "utils.h"
#include "struct.h"


void stats(Graph* graph) {
    if (graph == NULL) {
        return;  // Exit the function early
    }

    if ( graph->nodeCount == 0) {
        // Set all values to 0 if the graph is null or contains no nodes
        graph->maxOutDegree = 0;
        graph->maxInDegree = 0;
        graph->minOutDegree = 0;
        graph->minInDegree = 0;
        return;  // Exit the function early
    }
 
    // Initialize min values to a large number since we are looking for the minimum
    int maxOut = 0, maxIn = 0;
    int minOut = INT_MAX, minIn = INT_MAX;

    // Iterate through each node
    for (int i = 0; i < graph->nodeCount; i++) {
        Node* node = graph->nodes[i];
        if (node != NULL) {
            // Update maximum degrees
            if (node->outCount > maxOut) {
                maxOut = node->outCount;
            }
            if (node->inCount > maxIn) {
                maxIn = node->inCount;
            }
            
            // Update minimum degrees
            if (node->outCount < minOut) {
                minOut = node->outCount;
            }
            if (node->inCount < minIn) {
                minIn = node->inCount;
            }
        }
    }

    // Set the min values only if we found any nodes with edges
    if (minOut == INT_MAX) minOut = 0;
    if (minIn == INT_MAX) minIn = 0;

    // Save the values in the graph structure
    graph->maxOutDegree = maxOut;
    graph->maxInDegree = maxIn;
    graph->minOutDegree = minOut;
    graph->minInDegree = minIn;
}

