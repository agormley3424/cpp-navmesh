#ifndef _CHARACTER_CONTROL_SOLDIER_NPC_
#define _CHARACTER_CONTROL_SOLDIER_NPC_

#include "PrimeEngine/Events/Component.h"


#include "../Events/Events.h"

namespace CharacterControl{

namespace Components {

struct SoldierNPC : public PE::Components::Component
{
	PE_DECLARE_CLASS(SoldierNPC);

	SoldierNPC(PE::GameContext &context, PE::MemoryArena arena, PE::Handle hMyself, Events::Event_CreateSoldierNPC *pEvt);

	virtual void addDefaultComponents();

	int lastWayPoint = -1;
	int currentWayPoint = -1;

	signed int startCell;
	signed int endCell;
	bool cycle;
	bool outside = true;
	Vector3 targetPos;
	std::string hostility;
};
}; // namespace Components
}; // namespace CharacterControl
#endif

