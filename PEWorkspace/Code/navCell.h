#ifndef _CHARACTER_CONTROL_NAVCELL_
#define _CHARACTER_CONTROL_NAVCELL_

#include <vector>
#include <unordered_set>
#include "PrimeEngine/Math/Vector3.h"
#include "PrimeEngine/APIAbstraction/APIAbstractionDefines.h"
#include "PrimeEngine/Lua/LuaEnvironment.h"
#include "PrimeEngine/Lua/EventGlue/EventDataCreators.h"
#include <string>
#include "PrimeEngine/Math/Matrix4x4.h"
#include "PrimeEngine/Events/Component.h"

namespace CharacterControl {
namespace Components {

	struct navCell : public PE::Components::Component  {
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

		navCell(PE::GameContext& context, PE::MemoryArena arena, PE::Handle hMyself, const CharacterControl::Events::Event_CREATE_NAVCELL* pEvt);

	private:

		unsigned int id;
		std::string shape;
		std::vector<Vector3> cornerPoints;
		Vector3 center;
		std::unordered_set<unsigned int> neighbors;
		signed int value;
		bool blocked = false;
		double distFromStart = std::numeric_limits<double>::max();
		navCell* parent = nullptr;
		Matrix4x4 m_base;
	};
}

	namespace Events {
		struct Event_CREATE_NAVCELL : public PE::Events::Event
		{
			PE_DECLARE_CLASS(Event_CREATE_NAVCELL);

			virtual void addDefaultComponents();

			// override SetLuaFunctions() since we are adding custom Lua interface
			static void SetLuaFunctions(PE::Components::LuaEnvironment* pLuaEnv, lua_State* luaVM);

			// Lua interface prefixed with l_
			static int l_Construct(lua_State* luaVM);

			Matrix4x4 m_base;
			unsigned int m_id;
			std::unordered_set<signed int> m_neighbors;
			signed int m_value;
			std::string m_shape;


			PEUUID m_peuuid; // unique object id
		};
	}
}

#endif

