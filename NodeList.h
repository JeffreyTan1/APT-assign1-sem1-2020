#ifndef COSC_ASSIGN_ONE_NODELIST
#define COSC_ASSIGN_ONE_NODELIST

#include "Types.h"
#include "Node.h"

class NodeList
{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Desctructor
    NodeList();
    ~NodeList();

    // Copy Constructor
    // Produces a DEEP COPY of the NodeList
    NodeList(NodeList &other);

    // Number of elements in the NodeList
    int getLength();

    // Add a COPY node element to the BACK of the nodelist.
    void addElement(Node *newNode);

    // Get a pointer to the ith node in the node list
    Node *getNode(int i);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    //Contructor that is used for creating neighbor nodelist
    //Using this we can limit the array size to 4, and not take up maxSize
    NodeList(int size);

    //True if the checknode has the same col and row as a node in the list
    bool isIncluded(Node *checkNode);

    //Called on openlist.
    //Node in openlist with smallest estimated dist to goal
    //and not in closedlist.
    Node *getSmallestEstDistNode(Node *goalNode, NodeList *nodesExplored);

    //Called on closedlist.
    //Node in the neighbors list that is -1 distance from the current node
    Node *searchPathNeighbors4LeastDist(Node *currentNode, NodeList *neighbors);

    //Called on path.
    //Reverses the list
    void reverseList();

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // NodeList: list of node objects
    // You may assume a fixed size for M1, M2, M3
    Node **nodes;

    // Number of nodes currently in the NodeList
    int length;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
};

#endif //COSC_ASSIGN_ONE_NODELIST