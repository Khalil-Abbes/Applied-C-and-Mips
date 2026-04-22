#ifndef STRUCT_H
#define STRUCT_H

typedef struct Node {
    char* name;            // Node identifier
    struct Node** outEdges; // Array of pointers to outgoing edges
    struct Node** inEdges;  // Array of pointers to incoming edges
    int outCount;         // Number of outgoing edges
    int inCount;          // Number of incoming edges
} Node;

typedef struct Graph {
    char* name;
    Node** nodes;         // Array of pointers to nodes
    int nodeCount;        // Number of nodes
    int edgeCount;        // Number of edges
    int maxOutDegree;     // Maximum outgoing connections
    int maxInDegree;      // Maximum incoming connections
    int minOutDegree;     // Minimum outgoing connections
    int minInDegree;      // Minimum incoming connections
} Graph;

char *my_strdup(const char *s);
Graph* createGraph(const char* name);
void deleteGraph(Graph* graph);
Node* findOrCreateNode(Graph* graph,  char* nodeName);
char* trimWhitespace(char* str);
int addEdge(Graph* graph , Node* from, Node* to);
Graph* readDotFile(const char* filename);
//debug
void printNode(const Node* node);
void printGraph(const Graph* graph);
#endif