#include "Node.h"
#include <iostream>

Node::Node(int row, int col, int dist_traveled) : row(row),
                                                  col(col),
                                                  dist_traveled(dist_traveled)
{
}

Node::~Node()
{
    //Do nothing
}

int Node::getRow()
{
    return row;
}

int Node::getCol()
{
    return col;
}

int Node::getDistanceTraveled()
{
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node *goal)
{
    //distance_travelled + Manhattan distance from point p to G
    return dist_traveled + abs(col - goal->getCol()) + abs(row - goal->getRow());
}

bool Node::isSamePosition(Node *checkNode)
{

    if (col == checkNode->getCol() && row == checkNode->getRow())
    {
        std::cout << "isSamePosition true" << std::endl;
        return true;
    }
    std::cout << "isSamePosition false" << std::endl;
    return false;
}

bool Node::isAbove(Node *node)
{
    if (this->col == node->getCol() + 1)
    {
        return true;
    }
    return false;
}

bool Node::isBelow(Node *node)
{
    if (this->col == node->getCol() - 1)
    {
        return true;
    }
    return false;
}
bool Node::isToLeft(Node *node)
{
    if (this->row == node->getRow() - 1)
    {
        return true;
    }
    return false;
}
bool Node::isToRight(Node *node)
{
    if (this->row == node->getRow() + 1)
    {
        return true;
    }
    return false;
}

//--------------------------------