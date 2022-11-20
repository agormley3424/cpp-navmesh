#ifndef _CHARACTER_CONTROL_PAYWOINT_NPC_
#define _CHARACTER_CONTROL_PAYWOINT_NPC_

#include <string>
#include "PrimeEngine/Math/Vector3.h"


namespace CharacterControl {
	namespace Components {

		struct PayWoint
		{
			PayWoint(Vector3 pos, std::string name);

			std::string m_name;
			Vector3 m_pos;

		};
	}; // namespace Components
}; // namespace CharacterControl
#endif

