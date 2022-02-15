#include "ECS.h"


int BaseComponent::nextID{};

// Registry Iplementations

const Entity Registry::createEntity()
{
	int entity_ID = numEntities++;

	if (entity_ID >= entitySignatures.size()) { entitySignatures.resize(entity_ID + 1); }

	Entity e1(entity_ID);
	
	e1.entityregistryptr = this;

	entitycreationQueue.push_back(e1);

	if (entity_ID >= entitySignatures.size()) { entitySignatures.resize(entity_ID + 1); }

	Logger::sLog("Entity ID " + std::to_string(entity_ID) + " created");

	return e1;
}

void Registry::addEntitytoSystem(const Entity &e1)
{
	const unsigned int entityUID = e1.getID();
	for (const auto& x: systemsRegister)
	{
		if (entitySignatures[entityUID] == x.second->getComponentSignature())
		{
			x.second->addEntiitytoSystem(e1);
		}

	}

}

void Registry::registryUpdate()
{
	for (const auto& entity : entitycreationQueue)
	{
		addEntitytoSystem(entity);
	}

	entitycreationQueue.clear();

}



// Entity Implemenations
unsigned int Entity::getID() const 
{
	return id;
}


// System Implementations

void System::addEntiitytoSystem(const Entity &e1)
{
	// Considering it's passed the requirements
	systemEntities.push_back(e1);
	Logger::Log("Entity added to System");

}

void System::removeEntityfromSystem(const Entity &e2)
{
	const auto r_ID = e2.getID();

	for (int i = 0; i < systemEntities.size(); i++) 
	{
		if (r_ID == systemEntities[i].getID()) 
		{
			systemEntities.erase(systemEntities.begin() + i);
			Logger::Log("Entity removed");
			return;
		}
	}

	Logger::Error("Entity not found");
	
}

const Signature& System::getComponentSignature() const
{
	return ComponentSignature;
}

std::vector<Entity> System::getEntityList()
{
	return systemEntities;

}


// Component Implementations








