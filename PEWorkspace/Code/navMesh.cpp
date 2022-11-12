#include "navMesh.h"
#include <iostream>
#include <forward_list>
#include "navCell.h"
#include <queue>

const std::unordered_map<unsigned int, std::forward_list<navCell*>>& navMesh::getGraph()
{
	return graph;
}

const std::unordered_map<unsigned int, navCell>& navMesh::getCells()
{
	return cells;
}

// Add a cell to the graph
void navMesh::addToGraph(navCell& newCell)
{

}

// Remove a cell from the graph
void removeFromGraph(unsigned int ID)
{

}

void navMesh::addCell(navCell& newCell)
{
	// Return if cell is already stored
	if (cells.find(newCell.getID()) != cells.end())
	{
		std::cerr << "navMesh.cpp: addCell Error: Line 16: Attempt to add cell already stored\n";
		return;
	}

	// Else if cell isn't stored

	unsigned int newID = newCell.getID();

	cells[newID] = newCell;

	unsigned int newID = newCell.getID();

	// Check every cell in the graph for neighborship
	for (auto iter = graph.begin(); iter != graph.end(); iter++)
	{
		// The ID of the first cell in this row (one node)
		unsigned int graphID = iter->first;
		std::forward_list<navCell*>& row = iter->second;


		// If the cell has this graph cell as a neighbor, add it to its linked list
		if (newCell.hasNeighbor(graphID)) {
			row.insert_after(row.begin(), &cells[newID]);
		}
	}

	// Add a new linked list for this cell
	graph.emplace(newID, &cells[newID]);
}

// The cell should be removed from the cells vector immediately
// You can remove the null nodes from the graph if you want, but it'll take n+m instructions
void navMesh::removeCell(unsigned int cellID)
{
	// Return if cell isn't stored
	// Return if cell is already stored
	if (cells.find(cellID) == cells.end())
	{
		std::cerr << "navMesh.cpp: removeCell Error: Line 52: Attempt to remove cell not stored\n";
		return;
	}

	// else if cell is stored


	// Remove from the graph
	for (auto iter = graph.begin(); iter != graph.end(); iter++)
	{

		std::forward_list<navCell*>& row = iter->second;
		if (row.front() == &cells[cellID])
		{
			graph.erase(iter);
		}
		else {
			row.remove(&cells[cellID]);
		}
	}


	// Remove from the cells array
	cells.erase(cellID);
}

// Removes the cell from the graph, but keeps it in the cells vector
void navMesh::blockCell(unsigned int cellID)
{
	if (cells[cellID].isBlocked())
	{
		std::cerr << "navMesh.cpp: blockCell Error: Line 75: Attempt to block cell already blocked\n";
		return;
	}

	cells[cellID].block();

	// Remove from the graph
	for (auto iter = graph.begin(); iter != graph.end(); iter++)
	{

		std::forward_list<navCell*>& row = iter->second;
		if (row.front() == &cells[cellID])
		{
			graph.erase(iter);
		}
		else {
			row.remove(&cells[cellID]);
		}
	}

}

// Restores a cell to the graph
// If this cell is already in the graph, it should throw an error
// If this cell isn't in the cells array, it should throw an error
void navMesh::unblockCell(unsigned int cellID)
{
	if (cells[cellID].isBlocked())
	{
		std::cerr << "navMesh.cpp: unblockCell Error: Line 96: Attempt to unblock cell already unblocked\n";
		return;
	}

	// Else

	cells[cellID].unBlock();

	navCell& newCell = cells[cellID];
	unsigned int newID = newCell.getID();

	// Check every cell in the graph for neighborship
	for (auto iter = graph.begin(); iter != graph.end(); iter++)
	{
		// The ID of the first cell in this row (one node)
		unsigned int graphID = iter->first;
		std::forward_list<navCell*>& row = iter->second;


		// If the cell has this graph cell as a neighbor, add it to its linked list
		if (newCell.hasNeighbor(graphID)) {
			row.insert_after(row.begin(), &cells[newID]);
		}
	}

	// Add a new linked list for this cell
	graph.emplace(newID, &cells[newID]);
}

float navMesh::manhattan(Vector3 vec1, Vector3 vec2)
{
	float manSum = 0.0;
	Vector3 diffVec = vec1 - vec2;
	manSum += abs(diffVec.getX());
	manSum += abs(diffVec.getZ());

	// Not considering Y for now, I should reenable this later
	//manSum += abs(diffVec.getY());

}

// Returns the next navCell to be moved to
navCell* navMesh::aStar(unsigned int start, unsigned int end)
{
	navCell& startCell = cells[start];
	navCell& endCell = cells[end];

	// Does A* update farthest known distance from the source like Dijkstra's, or nah?
	// Doing that will necessitate modifying the fringe priority queue sometimes
	// I'm assuming that doesn't happen for the time being

	// Since C++ only has a max priority queue by default, I need to implement a min priority queue from a min heap,
	// one that allows for easy comparison and storage of navCells. Otherwise, I can use a C++ priority queue with negated values
	// and a custom comparison function of my own making

	// It's pretty dumb to have a hash table storing the adjacency list AND have each element be the first value of each row.
	// I don't need both. I should stop including the self cell for each row in the list

	// Pretty sure I need to use manhattan distance, as eucliean distance can underestimate a path length
	// How do I calculate that again? If the cells are aligned with the world axes, I can look at the x, y, and z component differences
	// If they aren't aligned, this might be trickier...

	std::priority_queue<navCell*> fringe;
	std::unordered_set<unsigned int> discovered;

	startCell.setStartDist(0);

	fringe.push(&start, startCell.getValue() + manhattan(startCell.getCenter(), endCell.getCenter()));

	while (!fringe.empty())
	{
		navCell* targetCell = fringe.top();
		fringe.pop();

		std::forward_list<navCell*> &row = graph[targetCell->getID()];

		for (auto iter = row.begin()++; iter != row.end(); iter++)
		{
			navCell* neighbor = *iter;

			// If we haven't found this node already, add it to the fringe
			if (discovered.find(neighbor->getID) == discovered.end())
			{
				// Assuming all cells are equally adjacent...for now
				neighbor->setStartDist(targetCell->getStartDist() + 1.0);
				fringe.push(neighbor);
			}
			// Else, update its value in the fringe (might not be necessary?)
			// I'll definitely need my own data structure to do this
			// Or do I...the fringe only stores pointers, nothing's stopping me from modifying the cells themselves!
			else {
				neighbor->setStartDist(min(neighbor->getStartDist(), targetCell->getStartDist() + 1.0));
			}
		}

		// I also need a way to trace back the whole path from the end...maybe it's a good time to take a break!
	}


}