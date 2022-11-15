#ifndef _CHARACTER_CONTROL_NAVCELL_
#define _CHARACTER_CONTROL_NAVCELL_

#include <vector>
#include <unordered_set>
#include "PrimeEngine/Math/Vector3.h"

class navCell {
public:

	navCell(unsigned int ID, std::string SHAPE, signed int VALUE);

	unsigned int getID();

	std::string getShape();

	const std::vector<Vector3>& getCorners();

	Vector3 getCenter();

	const std::unordered_set<unsigned int>& getNeighbors();

	signed int getValue();

	bool hasNeighbor(unsigned int ID);

	bool isBlocked();

	bool block();

	bool unBlock();

	double getStartDist();

	void setStartDist(double val);

	void setParent(navCell* n);

	navCell* getParent();


private:

	unsigned int id;
	std::string shape;
	std::vector<Vector3> cornerPoints;
	Vector3 center;
	std::unordered_set<unsigned int> neighbors;
	signed int value;
	bool blocked = false;
	double distFromStart;
	navCell* parent = nullptr;
};


#endif

