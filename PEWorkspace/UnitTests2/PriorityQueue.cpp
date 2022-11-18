#include "PriorityQueue.h"

namespace CharacterControl {
	namespace Components {

		navCell* PriorityQueue::pop()
		{
			navCell* returnVal = queue.front().second;

			queue[0] = queue[queue.size() - 1];

			queue.pop_back();

			for (int i = 0; (2 * i) + 1 < queue.size(); )
			{
				std::pair<signed int, navCell*> temp;

				// Both children exist
				if ((2 * i) + 1 < queue.size() && (2 * i) + 2 < queue.size())
				{
					// Left child is smaller
					if (queue[(2 * i) + 1].first < queue[(2 * i) + 1].first)
					{
						// Temp store the left child
						temp = queue[(2 * i) + 1];
						queue[(2 * i) + 1] = queue[i];
						queue[i] = temp;

						i = (2 * i) + 1;
					}
					// Right child is smaller
					else
					{
						// Temp store the right child
						temp = queue[(2 * i) + 2];
						queue[(2 * i) + 2] = queue[i];
						queue[i] = temp;

						i = (2 * i) + 2;
					}
				}
				// Only the left child exists
				else if ((2 * i) + 1 < queue.size())
				{
					// Temp store the left child
					temp = queue[(2 * i) + 1];
					queue[(2 * i) + 1] = queue[i];
					queue[i] = temp;

					i = (2 * i) + 1;
				}
				// Only the right child exists
				else if ((2 * i) + 2 < queue.size())
				{
					// Temp store the right child
					temp = queue[(2 * i) + 2];
					queue[(2 * i) + 2] = queue[i];
					queue[i] = temp;

					i = (2 * i) + 2;
				}
				// No child exists
				// This should never actually be executed if the loop condition is correct
				else
				{
					break;
				}
			}

			return returnVal;
		}
		void PriorityQueue::push(navCell* n, signed int distance)
		{
			std::pair<signed int, navCell*> p(distance, n);
			queue.push_back(p);

			// Add new element to end and swap to its position in the heap
			for (int i = queue.size() - 1; i > 0 && p.first < queue[floor(i / 2)].first; i = floor(i / 2))
			{
				// Temporary copy of the parent
				std::pair<signed int, navCell*> temp = queue[floor(i / 2)];

				queue[floor(i / 2)] = p;
				queue[i] = temp;
			}
		}

		void PriorityQueue::clear()
		{
			queue.clear();
		}


		unsigned int PriorityQueue::size()
		{
			return queue.size();
		}

		bool PriorityQueue::isEmpty()
		{
			return queue.empty();
		}

		navCell* PriorityQueue::top()
		{
			return queue.front().second;
		}
	}
}