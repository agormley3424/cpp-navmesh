#ifndef _CHARACTER_CONTROL_PRIORITYQUEUE_
#define _CHARACTER_CONTROL_PRIORITYQUEUE

#include <vector>
#include "navCell.h"

namespace CharacterControl {
	namespace Components {
		class PriorityQueue
		{
		public:
			navCell* pop();
			void push(navCell* n, signed int distance);
			void clear();
			unsigned int size();
			bool isEmpty();
			navCell* top();
		private:
			std::vector<std::pair<signed int, navCell*>> queue;
		};
	}
}

#endif