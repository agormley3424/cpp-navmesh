#ifndef _CHARACTER_CONTROL_NAVMESH_
#define _CHARACTER_CONTROL_NAVMESH_

#include <vector>
#include <forward_list>
#include <unordered_map>
#include "navCell.h"
#include "CharacterControl/Characters/SoldierNPC.h"


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

			// Marks the designated cell as 'blocked'
			static void blockCell(unsigned int cellID);

			// Marks the designated cell as not 'blocked'
			static void unblockCell(unsigned int cellID);

			// Returns the center of the next navCell to be moved to
			static navCell* aStar(unsigned int start, unsigned int end, SoldierNPC* sNPC);

			// Returns the manhattan distance between two vectors
			static float manhattan(Vector3 vec1, Vector3 vec2);

			// Output the cells array
			static void printCells();

			// Output the graph
			static void printGraph();

			// Add default values for the A* execution
			static void setDefaults(unsigned int start, unsigned int end);

			// Run A* with default values
			static navCell* aStar();

			// Run A* with a soldier's beginning and end cells
			static navCell* aStar(SoldierNPC* sNPC);

			// Run A* with a default end, and a start position closest to the soldier
			static navCell* aStar(Vector3 soldierPos, bool& outside, bool debugging, SoldierNPC* sNPC);

			// Returns true if pos is equal to the position of the end mesh's center
			static bool finished(Vector3 pos);

			// Color the cells of a soldier
			static void navMesh::colorCells(bool& outside, SoldierNPC* sNPC);


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

