#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <getopt.h>
#include <ctype.h>
#include "utils.h"
#include "struct.h"

// Utility function for string duplication
char* my_strdup(const char* s) {
    char* d = malloc(strlen(s) + 1);
    if (d) {
        strcpy(d, s);
    }
    return d;
}

// Function to create a new graph
Graph* createGraph(const char* name) {
    Graph* graph = malloc(sizeof(Graph));
    if (!graph) {
        perror("Failed to allocate memory for graph");
        return NULL;
    }
    graph->nodes = NULL;
    graph->nodeCount = 0;
    graph->edgeCount = 0;
    graph->name = my_strdup(name);
    if (!graph->name) {
        free(graph);
        perror("Failed to duplicate graph name");
        return NULL;
    }
    return graph;
}

// Function to delete a graph and free all associated memory
void deleteGraph(Graph* graph) {
    if (!graph) return;

    for (int i = 0; i < graph->nodeCount; i++) {
        Node* node = graph->nodes[i];
        free(node->name);
        free(node->outEdges);
        free(node->inEdges);
        free(node);
    }
    free(graph->nodes);
    free(graph->name);
    free(graph);
}

// Function to create a new node or find an existing one
// Helper function to trim whitespace from a string
char* trimWhitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

Node* findOrCreateNode(Graph* graph, char* nodeName) {
    nodeName = trimWhitespace(nodeName);  // Trim the node name before using it

    for (int i = 0; i < graph->nodeCount; i++) {
        if (strcmp(graph->nodes[i]->name, nodeName) == 0) {
            printf("Existing node found: %s\n", nodeName);  // Debugging output
            return graph->nodes[i];
        }
    }

    Node* node = malloc(sizeof(Node));
    if (!node) {
        perror("Failed to allocate memory for node");
        return NULL;
    }

    node->name = my_strdup(nodeName);
    if (!node->name) {
        free(node);
        perror("Failed to duplicate node name");
        return NULL;
    }
    node->outEdges = NULL;
    node->inEdges = NULL;
    node->outCount = 0;
    node->inCount = 0;

    Node** temp = realloc(graph->nodes, (graph->nodeCount + 1) * sizeof(Node*));
    if (!temp) {
        free(node->name);
        free(node);
        perror("Failed to expand nodes array");
        return NULL;
    }

    graph->nodes = temp;
    graph->nodes[graph->nodeCount++] = node;
    printf("New node created: %s\n", node->name);  // Debugging output

    return node;
}

// Function to add an edge between two nodes
int addEdge(Graph* graph, Node* from, Node* to) {
    from->outEdges = realloc(from->outEdges, (from->outCount + 1) * sizeof(Node*));
    to->inEdges = realloc(to->inEdges, (to->inCount + 1) * sizeof(Node*));
    if (!from->outEdges || !to->inEdges) {
        perror("Failed to expand edge arrays");
        return -1;
    }
    from->outEdges[from->outCount++] = to;
    to->inEdges[to->inCount++] = from;
    graph->edgeCount++;
    return 0;
}

// Function to read a graph from a DOT file
Graph* readDotFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    char type[10], identifier[256];
    // Read and check the graph type and name
    if (fscanf(file, "%s %s {", type, identifier) != 2 || strcmp(type, "digraph") != 0) {
        fprintf(stderr, "File format error: Expected 'digraph <name> {'\n");
        fclose(file);
        return NULL;
    }

    Graph* graph = createGraph(identifier);
    if (!graph) {
        fclose(file);
        return NULL;
    }

    char from[256], to[256];
    // Read node connections
    while (fscanf(file, "%255s -> %255s", from, to) == 2) {
        // Automatically strip the semicolon from the end of the 'to' node name
        size_t to_len = strlen(to);
        if (to[to_len - 1] == ';') {
            to[to_len - 1] = '\0'; // Remove the semicolon
        }

        Node* nodeFrom = findOrCreateNode(graph, from);
        Node* nodeTo = findOrCreateNode(graph, to);
        if (!nodeFrom || !nodeTo || addEdge(graph, nodeFrom, nodeTo) != 0) {
            fprintf(stderr, "Failed to add edge from %s to %s\n", from, to);
        }
    }
    fclose(file);
    return graph;
}

//debug functions
void printNode(const Node* node) {
    if (node == NULL) {
        printf("Node is NULL\n");
        return;
    }
    printf("Node Name: %s\n", node->name);
    printf("Out-degree: %d, In-degree: %d\n", node->outCount, node->inCount);
    printf("Outgoing Edges: ");
    for (int i = 0; i < node->outCount; i++) {
        if (node->outEdges[i]) {
            printf("%s ", node->outEdges[i]->name);
        }
    }
    printf("\nIncoming Edges: ");
    for (int i = 0; i < node->inCount; i++) {
        if (node->inEdges[i]) {
            printf("%s ", node->inEdges[i]->name);
        }
    }
    printf("\n");
    printf("\n");
}

void printGraph(const Graph* graph) {
    if (graph == NULL) {
        printf("Graph is NULL\n");
        return;
    }
    printf("Graph Name: %s\n", graph->name);
    printf("Total Nodes: %d, Total Edges: %d\n", graph->nodeCount, graph->edgeCount);
    for (int i = 0; i < graph->nodeCount; i++) {
        printf("Node %d:\n", i + 1);
        printNode(graph->nodes[i]);
    }
}
