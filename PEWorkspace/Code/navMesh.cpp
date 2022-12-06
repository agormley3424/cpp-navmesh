#include "navMesh.h"
#include <iostream>
#include <forward_list>
#include "navCell.h"
#include <queue>
#include "PriorityQueue.h"
#include "CharacterControl/Characters/SoldierNPC.h"

namespace CharacterControl {
	namespace Components {

		std::unordered_map<unsigned int, std::forward_list<navCell*>> navMesh::graph = {};
		std::unordered_map<unsigned int, navCell> navMesh::cells = {};
		unsigned int* navMesh::defaultStart = new unsigned int(1);
		unsigned int* navMesh::defaultEnd = new unsigned int(4);

		const std::unordered_map<unsigned int, std::forward_list<navCell*>>& navMesh::getGraph()
		{
			return graph;
		}

		const std::unordered_map<unsigned int, navCell>& navMesh::getCells()
		{
			return cells;
		}

		// Add a cell to the graph (Helper function to be added later)
		void navMesh::addToGraph(navCell& newCell)
		{

		}

		// Remove a cell from the graph (Helper function to be added later)
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

			cells.insert({ newID, newCell });
			auto iter = cells.find(newID);
			navCell* newAddress = &(iter->second);

			// Add a new linked list for this cell
			std::forward_list<navCell*> newRow;
			newRow.push_front(newAddress);
			graph.insert({newID, newRow});

			for (auto iter = graph.begin(); iter != graph.end(); iter++)
			{
				unsigned int graphID = iter->first;

				if (newCell.hasNeighbor(graphID))
				{
					std::forward_list<navCell*>& row = iter->second;

					// Insert the new cell into the neighbor's row
					row.insert_after(row.begin(), newAddress);

					// Insert the neighbor into the new cell's row
					graph[newID].insert_after(graph[newID].begin(), row.front());
				}
			}
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

			// Remove from the graph
			// Remove from the graph
			// It's more efficient to compare IDs than whole objects
			// Oh wait, I can totally overload the compare operator! I'll do that

			graph.erase(cellID);

			auto iter = cells.find(cellID);
			navCell* cellAddress = &(iter->second);

			for (auto row = graph.begin(); row != graph.end(); row++)
			{
				std::forward_list<navCell*>& listProxy = row->second;
				for (auto col = listProxy.begin(); col != listProxy.end(); col++)
				{
					auto future = col;
					future++;
					if (future != listProxy.end() && *future == cellAddress)
					{
						listProxy.erase_after(col);

						// A particular node should only ever be a neighbor of another node once, so I can break early
						break;
					}
				}
			}


			// Remove from the cells array
			cells.erase(cellID);
		}

		// Removes the cell from the graph, but keeps it in the cells vector
		// It might be more efficient to just check if a cell is blocked or not, rather than remove it from the entire graph...
		void navMesh::blockCell(unsigned int cellID)
		{
			auto iter = cells.find(cellID);
			navCell* cellAddress = &(iter->second);
			navCell& cellProxy = iter->second;

			if (cellProxy.isBlocked())
			{
				std::cerr << "navMesh.cpp: blockCell Error: Line 75: Attempt to block cell already blocked\n";
				return;
			}

			cellProxy.block();

			// Remove from the graph
			// It's more efficient to compare IDs than whole objects
			// Oh wait, I can totally overload the compare operator! I'll do that

			graph.erase(cellID);



			for (auto row = graph.begin(); row != graph.end(); row++)
			{
				std::forward_list<navCell*>& listProxy = row->second;
				for (auto col = listProxy.begin(); col != listProxy.end(); col++)
				{
					auto future = col;
					future++;
					if (future != listProxy.end() && *future == cellAddress)
					{
						listProxy.erase_after(col);

						// A particular node should only ever be a neighbor of another node once, so I can break early
						break;
					}
				}
			}
		}

		// Restores a cell to the graph
		// If this cell is already in the graph, it should throw an error
		// If this cell isn't in the cells array, it should throw an error
		void navMesh::unblockCell(unsigned int cellID)
		{
			if (cells.find(cellID) == cells.end())
			{
				std::cerr << "navMesh.cpp: unblockCell Error: Line 163: Attempt to unblock cell not currently stored\n";
				return;
			}

			auto iter = cells.find(cellID);
			navCell* cellAddress = &(iter->second);
			navCell& cellProxy = iter->second;

			if (cellProxy.isBlocked())
			{
				std::cerr << "navMesh.cpp: unblockCell Error: Line 96: Attempt to unblock cell already unblocked\n";
				return;
			}

			// Else

			cellProxy.unBlock();

			unsigned int newID = cellProxy.getID();

			// Add a new linked list for this cell
			std::forward_list<navCell*> newRow;
			newRow.push_front(cellAddress);
			graph.insert({ newID, newRow });

			for (auto iter = graph.begin(); iter != graph.end(); iter++)
			{
				unsigned int graphID = iter->first;

				if (cellProxy.hasNeighbor(graphID))
				{
					std::forward_list<navCell*>& row = iter->second;

					// Insert the new cell into the neighbor's row
					row.insert_after(row.begin(), cellAddress);

					// Insert the neighbor into the new cell's row
					graph[newID].insert_after(graph[newID].begin(), row.front());
				}
			}
		}

		float navMesh::manhattan(Vector3 vec1, Vector3 vec2)
		{
			float manSum = 0.0;
			Vector3 diffVec = vec1 - vec2;
			manSum += abs(diffVec.getX());
			manSum += abs(diffVec.getZ());

			// Not considering Y for now, I should reenable this later
			//manSum += abs(diffVec.getY());

			return manSum;
		}

		void navMesh::printCells()
		{
			for (auto iter = cells.begin(); iter != cells.end(); iter++)
			{
				std::cerr << iter->second.getID() << ", ";
			}

			std::cerr << std::endl;
		}

		void navMesh::printGraph()
		{
			for (auto row = graph.begin(); row != graph.end(); row++)
			{
				for (auto col = row->second.begin(); col != row->second.end(); col++)
				{
					std::cerr << (*col)->getID() << ", ";
				}
				std::cerr << std::endl;
			}
		}

		void navMesh::setDefaults(unsigned int start, unsigned int end)
		{
			*defaultStart = start;
			*defaultEnd = end;
		}

		// Returns true if pos is equal to the position of the end mesh's center
		bool navMesh::finished(Vector3 pos)
		{
			navCell& endCell = cells.find(*defaultEnd)->second;

			return endCell.getCenter() == pos;
		}

		Vector3 navMesh::aStar()
		{
			return aStar(*defaultStart, *defaultEnd);
		}

		//Vector3 navMesh::aStar(Vector3 soldierPos, bool outside, SoldierNPC* sNPC)
		//{
		//	if (outside)
		//	{
		//		return cells.find(sNPC->startCell)->second.getCenter();
		//	}
		//	// else

		//	navCell* nearest = nullptr;
		//	double minDist = std::numeric_limits<double>::max();
		//	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		//	{
		//		double tempDist = (soldierPos - (iter->second.getCenter())).length();
		//		if (tempDist - minDist < std::numeric_limits<double>::epsilon())
		//		{
		//			nearest = &(iter->second);
		//			minDist = tempDist;
		//		}
		//	}

		//	assert(nearest != nullptr);

		//	if (minDist - 1 > std::numeric_limits<double>::epsilon())
		//	{
		//		return aStar(sNPC->startCell, sNPC->endCell);
		//	}
		//	else
		//	{
		//		return aStar(nearest->getID(), sNPC->endCell);
		//	}
		//}

		Vector3 navMesh::aStar(Vector3 soldierPos, bool& outside, SoldierNPC* sNPC)
		{
			if (outside)
			{
				navCell* nearest = nullptr;
				double minDist = std::numeric_limits<double>::max();
				for (auto iter = cells.begin(); iter != cells.end(); iter++)
				{
					double tempDist = (soldierPos - (iter->second.getCenter())).length();
					if (tempDist - minDist < std::numeric_limits<double>::epsilon())
					{
						nearest = &(iter->second);
						minDist = tempDist;
					}
				}

				assert(nearest != nullptr);

				if (abs(minDist - 1) > std::numeric_limits<double>::epsilon())
				{
					outside = false;
					sNPC->startCell = nearest->getID();
					return aStar(sNPC->startCell, sNPC->endCell);
				}
				else
				{
					return aStar(nearest->getID(), nearest->getID());
				}
			}
			else
			{
				return aStar(sNPC->startCell, sNPC->endCell);
			}
		}

		// Returns the next navCell to be moved to
		Vector3 navMesh::aStar(unsigned int start, unsigned int end)
		{
			navCell& startCell = cells.find(start)->second;
			navCell* startAddress = &startCell;
			navCell& endCell = cells.find(end)->second;
			navCell* endAddress = &endCell;

			if (start == end)
			{
				return startCell.getCenter();
			}

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

			PriorityQueue fringe;
			std::unordered_set<unsigned int> discovered;

			startCell.setStartDist(0);

			fringe.push(startAddress, startCell.getValue() + manhattan(startCell.getCenter(), endCell.getCenter()));
			discovered.insert(start);

			while (!fringe.isEmpty())
			{
				navCell* targetCell = fringe.top();
				fringe.pop();

				if (targetCell->getID() == end)
				{
					while (targetCell->getParent() != startAddress)
					{
						targetCell = targetCell->getParent();
					}

					return targetCell->getCenter();
				}

				std::forward_list<navCell*>* row;
				row = &(graph.find(targetCell->getID())->second);
				auto iter = row->begin();
				iter++;

				for (; iter != row->end(); iter++)
				{
					navCell* neighbor = *iter;

					// If we haven't found this node already, add it to the fringe
					if (discovered.find(neighbor->getID()) == discovered.end())
					{
						// Assuming all cells are equally adjacent...for now
						neighbor->setStartDist(targetCell->getStartDist() + 1.0);
						fringe.push(neighbor, neighbor->getValue() + manhattan(neighbor->getCenter(), endCell.getCenter()));

						neighbor->setParent(targetCell);
						discovered.insert(neighbor->getID());
					}
					// Else, update its value in the fringe (might not be necessary?)
					// I'll definitely need my own data structure to do this
					// Or do I...the fringe only stores pointers, nothing's stopping me from modifying the cells themselves!
					else {
						if ((targetCell->getStartDist() + 1.0 - neighbor->getStartDist() < std::numeric_limits<double>::epsilon()))
						{
							neighbor->setStartDist(targetCell->getStartDist() + 1.0);
							neighbor->setParent(targetCell);
						}
					}
				}
			}

			// If nothing has been returned yet, something has gone wrong
			return Vector3(-1, -1, -1);
		}
	}
}
