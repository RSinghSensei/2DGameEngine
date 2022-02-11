#pragma once
#include "../ECS/ECS.h"
#include "../Components/ObjTransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem : public System
{
public:
	MovementSystem()
	{
		addComponentRequirement<ObjTransformComponent>();
	}

	~MovementSystem() {}
	
	void updateMS()
	{
		//for (auto& x: getEntityList())
		//{
		//	ObjTransformComponent transformComponent = x.getComponent<ObjTransformComponent>();
		//	RigidBodyComponent rbComponent = x.getComponent<RigidBodyComponent>();

		//	transformComponent.pos.x += (rbComponent.velocity.x); // times delta time
		//	transformComponent.pos.y += (rbComponent.velocity.y); // times delta time

		//	Logger::sLog("Entity ID: " + std::to_string(x.getID()) + " moved to " + std::to_string(transformComponent.pos.x) + " " + std::to_string(transformComponent.pos.y));

		//}
	}

};
