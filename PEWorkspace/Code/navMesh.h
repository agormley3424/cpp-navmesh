#ifndef _CHARACTER_CONTROL_NAVMESH_
#define _CHARACTER_CONTROL_NAVMESH_

#include <vector>
#include <forward_list>
#include <unordered_map>
#include "navCell.h"

namespace CharacterControl {
	namespace Components {

		class navMesh {
		public:

			//navMesh();

			static const std::unordered_map<unsigned int, std::forward_list<navCell*>>& getGraph();

			static const std::unordered_map<unsigned int, navCell>& getCells();

			static void addCell(navCell& newCell);

			// The cell should be removed from the cells vector immediately
			// You can remove the null nodes from the graph if you want, but it'll take n+m instructions
			static void removeCell(unsigned int cellID);

			// Removes the cell from the graph, but keeps it in the cells vector
			static void blockCell(unsigned int cellID);

			// Restores a cell to the graph
			// If this cell is already in the graph, it should throw an error
			// If this cell isn't in the cells array, it should throw an error
			static void unblockCell(unsigned int cellID);

			// Returns the center of the next navCell to be moved to
			static Vector3 aStar(unsigned int start, unsigned int end);

			// Returns the manhattan distance between two vectors
			static float manhattan(Vector3 vec1, Vector3 vec2);

			// Output the cells array
			static void printCells();

			// Output the graph
			static void printGraph();

			// Add default values for the A* execution
			static void setDefaults(unsigned int start, unsigned int end);

			// Run A* with default values
			static Vector3 aStar();

			// Run A* with a default end, and a start position closest to the soldier
			static Vector3 aStar(Vector3 soldierPos, bool outside);


		private:
			// I could make this even more efficient by storing the graph as a forward list of forward lists, but I don't wanna deal with the iterators...
			static std::unordered_map<unsigned int, std::forward_list<navCell*>> graph;
			static std::unordered_map<unsigned int, navCell> cells;

			static void addToGraph(navCell& newCell);
			static void removeFromGraph(unsigned int ID);
			static unsigned int* defaultStart;
			static unsigned int* defaultEnd;
		};
	}
}
#endif

