#pragma once
#include "../ECS/ECS.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/ObjTransformComponent.h"
#include "../Components/SpriteComponent.h"

class MovementSystem : public System
{
public:
	MovementSystem()
	{
		addComponentRequirement<ObjTransformComponent>();
		addComponentRequirement<RigidBodyComponent>();
		addComponentRequirement<SpriteComponent>();
	}

	
	void update(float dt)
	{
		for (auto& x: getEntityList())
		{
			ObjTransformComponent& transformComponent = x.getComponent<ObjTransformComponent>();
			const RigidBodyComponent rbComponent = x.getComponent<RigidBodyComponent>();

			transformComponent.pos.x += (rbComponent.objVelocity.x * dt);
			transformComponent.pos.y += (rbComponent.objVelocity.y * dt);

			//Logger::sLog("Entity ID: " + std::to_string(x.getID()) + " moved to " + std::to_string(transformComponent.pos.x) + " " + std::to_string(transformComponent.pos.y));

		}
	}

};
