#include "PayWoint.h"
#include "PrimeEngine/Math/Vector3.h"
#include <string>


namespace CharacterControl {
	namespace Components {

		PayWoint::PayWoint(Vector3 pos, std::string name)
		{
			m_pos = pos;
			m_name = name;
		}

	}; // namespace Components
}; // namespace CharacterControl
