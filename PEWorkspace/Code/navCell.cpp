#include "navCell.h"
#include "PrimeEngine/Events/Component.h"
#include <iostream>

using namespace PE;
using namespace PE::Components;
using namespace CharacterControl::Events;

namespace CharacterControl {
	namespace Components {

		PE_IMPLEMENT_CLASS1(navCell, Component);

		//navCell::navCell(unsigned int ID, std::string SHAPE, signed int VALUE)
		//{
		//	id = ID;
		//	shape = SHAPE;
		//	value = VALUE;
		//}

		unsigned int navCell::getID()
		{
			return id;
		}

		std::string navCell::getShape()
		{
			return shape;
		}

		const std::vector<Vector3>& navCell::getCorners()
		{
			return cornerPoints;
		}

		Vector3 navCell::getCenter()
		{
			return center;
		}

		signed int navCell::getValue()
		{
			return value;
		}

		const std::unordered_set<unsigned int>& navCell::getNeighbors()
		{
			return neighbors;
		}

		bool navCell::hasNeighbor(unsigned int ID)
		{
			return neighbors.find(ID) != neighbors.end();
		}

		bool navCell::isBlocked()
		{
			return blocked;
		}

		void navCell::block()
		{
			blocked = true;;
		}

		void navCell::unBlock()
		{
			blocked = false;
		}

		double navCell::getStartDist()
		{
			return distFromStart;
		}

		void navCell::setStartDist(double val)
		{
			distFromStart = val;
		}

		void navCell::setParent(navCell* n)
		{
			parent = n;
		}

		navCell* navCell::getParent()
		{
			return parent;
		}



		navCell::navCell(PE::GameContext& context, PE::MemoryArena arena, PE::Handle hMyself, const Events::Event_CREATE_NAVCELL* pEvt)
			: Component(context, arena, hMyself)
		{
			id = pEvt->m_id;

			for (auto i = pEvt->m_neighbors.begin(); i != pEvt->m_neighbors.end(); i++)
			{
				neighbors.insert(*i);
			}

			m_base = pEvt->m_base;

			shape = pEvt->m_shape;

			value = pEvt->m_value;
		}

		//navCell::navCell()
		//{
		//	std::cerr << "The default constructor for navCell is being called. This shouldn't be happening!\n";
		//}

		void navCell::addDefaultComponents()
		{
			Component::addDefaultComponents();

			// custom methods of this component
		}

	}
	namespace Events {

		PE_IMPLEMENT_CLASS1(Event_CREATE_NAVCELL, PE::Events::Event);

		void Event_CREATE_NAVCELL::SetLuaFunctions(PE::Components::LuaEnvironment* pLuaEnv, lua_State* luaVM)
		{
			static const struct luaL_Reg l_Event_CREATE_NAVMESH[] = {
			{"Construct", l_Construct},
			{NULL, NULL} // sentinel
			};

			// register the functions in current lua table which is the table for Event_CreateSoldierNPC
			luaL_register(luaVM, 0, l_Event_CREATE_NAVMESH);
		}

		int Event_CREATE_NAVCELL::l_Construct(lua_State* luaVM)
		{
			PE::Handle h("EVENT", sizeof(Event_CREATE_NAVCELL));
			Event_CREATE_NAVCELL* pEvt = new(h) Event_CREATE_NAVCELL;

			// get arguments from stack
			int numArgs, numArgsConst;
			numArgs = numArgsConst = 20;

			pEvt->m_shape = lua_tostring(luaVM, -numArgs--);

			float positionFactor = 1.0f / 100.0f;

			pEvt->m_id = (unsigned int)lua_tonumber(luaVM, -numArgs--) * positionFactor;

			for (int i = 0; i < 4; ++i)
			{
				signed int n = (signed int)lua_tonumber(luaVM, -numArgs--) * positionFactor;

				if (n >= 0)
				{
					pEvt->m_neighbors.insert(n);
				}
			}

			pEvt->m_value = (signed int)lua_tonumber(luaVM, -numArgs--) * positionFactor;

			Vector3 pos, u, v, n;
			pos.m_x =
				pos.m_y = (float)lua_tonumber(luaVM, -numArgs--) * positionFactor;
			pos.m_z = (float)lua_tonumber(luaVM, -numArgs--) * positionFactor;

			u.m_x = (float)lua_tonumber(luaVM, -numArgs--); u.m_y = (float)lua_tonumber(luaVM, -numArgs--); u.m_z = (float)lua_tonumber(luaVM, -numArgs--);
			v.m_x = (float)lua_tonumber(luaVM, -numArgs--); v.m_y = (float)lua_tonumber(luaVM, -numArgs--); v.m_z = (float)lua_tonumber(luaVM, -numArgs--);
			n.m_x = (float)lua_tonumber(luaVM, -numArgs--); n.m_y = (float)lua_tonumber(luaVM, -numArgs--); n.m_z = (float)lua_tonumber(luaVM, -numArgs--);

			pEvt->m_peuuid = LuaGlue::readPEUUID(luaVM, -numArgs--);

			lua_pop(luaVM, numArgsConst); //Second arg is a count of how many to pop

			pEvt->m_base.loadIdentity();
			pEvt->m_base.setPos(pos);
			pEvt->m_base.setU(u);
			pEvt->m_base.setV(v);
			pEvt->m_base.setN(n);

			LuaGlue::pushTableBuiltFromHandle(luaVM, h);

			return 1;
		}
	};
};