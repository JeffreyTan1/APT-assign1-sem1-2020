#include "Node.h"
#include <iostream>
#include <string>

Node::Node(int row, int col, int dist_traveled) : row(row),
                                                  col(col),
                                                  dist_traveled(dist_traveled)
{
}

Node::~Node()
{
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
    //Estimated distance to goal is defined as
    //distance_travelled plus Manhattan distance to goal
    return dist_traveled + abs(col - goal->getCol()) + abs(row - goal->getRow());
}

bool Node::isSamePosition(Node *checkNode)
{
    if (col == checkNode->getCol() && row == checkNode->getRow())
    {

        return true;
    }

    return false;
}

bool Node::isAbove(Node *node)
{
    if (this->row == node->getRow() - 1)
    {
        return true;
    }
    return false;
}

bool Node::isBelow(Node *node)
{
    if (this->row == node->getRow() + 1)
    {
        return true;
    }
    return false;
}
bool Node::isToLeft(Node *node)
{
    if (this->col == node->getCol() - 1)
    {
        return true;
    }
    return false;
}
bool Node::isToRight(Node *node)
{
    if (this->col == node->getCol() + 1)
    {
        return true;
    }
    return false;
}

//--------------------------------