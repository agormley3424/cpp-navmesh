#include "navCell.h"

navCell::navCell(unsigned int ID, std::string SHAPE, signed int VALUE)
{
	id = ID;
	shape = SHAPE;
	value = VALUE;
}

unsigned int navCell::getID()
{
	return id;
}

std::string navCell::getShape()
{
	return shape;
}

const std::vector<Vector3>& navCell::getCorners()
{
	return cornerPoints;
}

Vector3 navCell::getCenter()
{
	return center;
}

signed int navCell::getValue()
{
	return value;
}

const std::unordered_set<unsigned int>& navCell::getNeighbors()
{
	return neighbors;
}

bool navCell::hasNeighbor(unsigned int ID)
{
	return neighbors.find(ID) != neighbors.end();
}

bool navCell::isBlocked()
{
	return blocked;
}

bool navCell::block()
{
	blocked = true;;
}

bool navCell::unBlock()
{
	blocked = false;
}

double navCell::getStartDist()
{
	return distFromStart;
}

double navCell::setStartDist(double val)
{
	distFromStart = val;
}