#include "navCell.h"
#include "PrimeEngine/Events/Component.h"
#include <iostream>
#include "PrimeEngine/Scene/DebugRenderer.h"

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
			m_base = pEvt->m_base;
			center = pEvt->m_base.getPos();
			neighbors = pEvt->m_neighbors;
			shape = pEvt->m_shape;
			id = pEvt->m_id;
			value = pEvt->m_value;
			cornerPoints = { center + Vector3(-1.0, 0, -1.0), center + Vector3(1.0, 0, -1.0),
											center + Vector3(1.0, 0, -1.0), center + Vector3(1.0, 0, 1.0),
											center + Vector3(1.0, 0, 1.0), center + Vector3(-1.0, 0, 1.0),
											center + Vector3(-1.0, 0, 1.0), center + Vector3(-1.0, 0, -1.0) };
		}

		void navCell::drawCell(Vector3 color)
		{
			Vector3 linePoints[16];

			for (int i = 0, j = 0; i < 16; ++i)
			{
				if (i % 2 == 0)
				{
					linePoints[i] = cornerPoints[j];
					++j;
				}
				else
				{
					linePoints[i] = color;
				}

				int a = 1;
			}

			int b = 2;

			DebugRenderer::Instance()->createLineMesh(false, Matrix4x4(), &linePoints[0].m_x, 8, 2);
		}

		void navCell::addDefaultComponents()
		{
			Component::addDefaultComponents();

			// custom methods of this component
		}

		//navCell::navCell(unsigned int ID, std::string SHAPE, Vector3 CENTER, signed int VALUE,
		//	std::unordered_set<unsigned int> NEIGHBORS)
		//{
		//	id = ID;
		//	shape = SHAPE;
		//	center = CENTER;
		//	value = VALUE;
		//	neighbors = NEIGHBORS;
		//}

		//navCell::navCell()
		//{
		//	std::cerr << "The default constructor for navCell is being called. This shouldn't be happening!\n";
		//}

		//void navCell::addDefaultComponents()
		//{
		//	Component::addDefaultComponents();

		//	// custom methods of this component
		//}

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

			pEvt->m_shape = lua_tostring(luaVM, -numArgs--); // Arg 1

			float positionFactor = 1.0f / 100.0f;

			pEvt->m_id = (unsigned int)lua_tonumber(luaVM, -numArgs--); // Arg 2

			for (int i = 0; i < 4; ++i)
			{
				signed int n = (signed int)lua_tonumber(luaVM, -numArgs--);  // Arg 3 - 6

				if (n >= 0)
				{
					pEvt->m_neighbors.insert(n);
				}
			}

			pEvt->m_value = (signed int)lua_tonumber(luaVM, -numArgs--); // Arg 7

			Vector3 pos, u, v, n;
			pos.m_x = (float)lua_tonumber(luaVM, -numArgs--) * positionFactor; // Arg 8
			pos.m_y = (float)lua_tonumber(luaVM, -numArgs--) * positionFactor; // Arg 9
			pos.m_z = (float)lua_tonumber(luaVM, -numArgs--) * positionFactor; // Arg 10

			u.m_x = (float)lua_tonumber(luaVM, -numArgs--); u.m_y = (float)lua_tonumber(luaVM, -numArgs--); u.m_z = (float)lua_tonumber(luaVM, -numArgs--); // Arg 11 - 13
			v.m_x = (float)lua_tonumber(luaVM, -numArgs--); v.m_y = (float)lua_tonumber(luaVM, -numArgs--); v.m_z = (float)lua_tonumber(luaVM, -numArgs--); // Arg 14 - 16
			n.m_x = (float)lua_tonumber(luaVM, -numArgs--); n.m_y = (float)lua_tonumber(luaVM, -numArgs--); n.m_z = (float)lua_tonumber(luaVM, -numArgs--); // Arg 17 - 19

			pEvt->m_peuuid = LuaGlue::readPEUUID(luaVM, -numArgs--); // Arg 20

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