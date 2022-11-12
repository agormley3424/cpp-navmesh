#ifndef _CHARACTER_CONTROL_NAVMESH_
#define _CHARACTER_CONTROL_NAVMESH_

#include <vector>
#include <forward_list>
#include <unordered_map>
#include "navCell.h"

class navMesh {
public:

	navMesh();

	const std::unordered_map<unsigned int, std::forward_list<navCell*>>& getGraph();

	const std::unordered_map<unsigned int, navCell>& getCells();

	void addCell(navCell& newCell);

	// The cell should be removed from the cells vector immediately
	// You can remove the null nodes from the graph if you want, but it'll take n+m instructions
	void removeCell(unsigned int cellID);

	// Removes the cell from the graph, but keeps it in the cells vector
	void blockCell(unsigned int cellID);

	// Restores a cell to the graph
	// If this cell is already in the graph, it should throw an error
	// If this cell isn't in the cells array, it should throw an error
	void unblockCell(unsigned int cellID);

	// Returns the next navCell to be moved to
	navCell* aStar(unsigned int start, unsigned int end);

	// Returns the manhattan distance between two vectors
	float manhattan(Vector3 vec1, Vector3 vec2)


private:
	// I could make this even more efficient by storing the graph as a forward list of forward lists, but I don't wanna deal with the iterators...
	std::unordered_map<unsigned int, std::forward_list<navCell*>> graph;
	std::unordered_map<unsigned int, navCell> cells;

	void addToGraph(navCell& newCell);
	void removeFromGraph(unsigned int ID);
};


#endif

