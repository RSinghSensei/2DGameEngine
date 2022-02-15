#pragma once
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <utility>
#include <deque>
#include <glm/glm.hpp>
#include <memory>
#include "../Logger/Logger.h"

typedef std::bitset<32> Signature;

class Entity{
public:
	Entity(unsigned int ID) :id(ID) {}
	unsigned int getID() const;
	class Registry* entityregistryptr = nullptr;

	template<typename T, typename ...Targs>void addComponent(Targs&& ...args);
	template<typename T>void removeComponent();
	template<typename T>bool hasComponent();
	template<typename T>T& getComponent();

private:
	unsigned int id;
};

class BaseComponent {
public:
	BaseComponent() = default;
	static int nextID;
};

class BasePool
{
public:
	virtual ~BasePool() = 0 {};

};

template<typename T>
class Component : public BaseComponent{
public:
	static unsigned int getID()
	{
		static unsigned int c_ID = nextID++;
		return c_ID;
	}

//private:
//	static unsigned int id;
};

class System {
public:
	System() = default;
	~System() = default;

	void addEntiitytoSystem(const Entity& e1);
	void removeEntityfromSystem(const Entity& e1);
	const Signature& getComponentSignature() const;
	std::vector<Entity> getEntityList();

	template<typename T> void addComponentRequirement();

private:
	Signature ComponentSignature;
	std::vector<Entity>systemEntities;

};

class Registry
{
public:
	Registry() = default;
	~Registry() = default;
	const Entity createEntity();
	void addEntitytoSystem(const Entity& e1);
	void registryUpdate();
	///void killEntity();
	// r-value references in arguments
	template<typename T, typename ...Targs> void addComponent(const Entity& e1, Targs&& ...args);
	template<typename T> void removeComponent(const Entity& e1);
	template<typename T> bool hasComponent(const Entity& e1);
	template<typename T> T& getComponent(const Entity& e1);
	
	template<typename T, typename ...Targs> void addSystem(Targs&& ...args);
	template<typename T> void removeSystem();
	template<typename T> bool hasSystem();
	template<typename T> T& getSystem();

private:

	std::deque<Entity>entitycreationQueue;
	std::deque<Entity>entitykillQueue;

	unsigned int numEntities{};
	std::vector<std::shared_ptr<BasePool>> componentPools;
	std::vector<Signature>entitySignatures;
	std::unordered_map<std::type_index, std::shared_ptr<System>>systemsRegister;
};


template<typename poolType>
class Pool : public BasePool
{
public:
	Pool() {}
	Pool(unsigned int size) { data.reserve(size); }
	virtual ~Pool() = default;
	
	bool isEmpty() const;
	unsigned int getSize() const { return data.size(); }
	void resize(unsigned int n) { data.resize(n); }
	void clear() { data.clear(); }
	void add(poolType p1) { data.push_back(p1); }
	void remove(unsigned int index) { data.erase(data.begin() + index); }
	void set(poolType p1, unsigned int index) { data[index] = p1; }
	poolType& get(unsigned int index) { return data[index]; }

	poolType& operator[](unsigned int id);


private:
	std::vector<poolType>data;


};



template<typename T>
void System::addComponentRequirement()
{	
	unsigned int componentID = Component<T>::getID();
	ComponentSignature.set(componentID);


}

template<typename T, typename ...Targs> 
void Registry::addComponent(const Entity& e1, Targs&& ...args)
{
	const unsigned int componentUID = Component<T>::getID();
	const unsigned int entityUID = e1.getID();

	if (componentUID >= componentPools.size()) { componentPools.resize(componentUID + 1, nullptr); } 
	// When we call resize, vector will place values in the newly allocated places
	// Hence why we place nullptr in the optional parameter

	if (componentPools[componentUID] == nullptr) 
	{	
		std::shared_ptr<Pool<T>> allocPool = std::make_shared<Pool<T>>();
		Logger::Log("New pool being allocated for component");
		/*Pool<T>* allocPool = new Pool<T>; */
		componentPools[componentUID] = allocPool;
	}

	// Fetch the existingPool at the position, if it wasn't there it got instatiated in the previous step
	std::shared_ptr<Pool<T>> existingPool = std::static_pointer_cast<Pool<T>>(componentPools[componentUID]);


	if (existingPool->getSize() <= entityUID) { existingPool->resize(entityUID + 1); }



	// Constructer of our component type
	// If T was objTransformComponent, this is what would get consturcted5
	// std::forward just forwards the r-value arguments we passed in
	T newComponent(std::forward<Targs>(args)...);

	existingPool->set(newComponent, entityUID);

	entitySignatures[entityUID].set(componentUID);

	Logger::sLog("Component ID: " + std::to_string(componentUID) + " added to Entity ID: " + std::to_string(entityUID));

}

template<typename T>
void Registry::removeComponent(const Entity& e1)
{
	const unsigned int entityUID = e1.getID();
	const unsigned int componentUID = Component<T>::getID();

	//if (!hasComponent(e1)) { Logger::Log("Component does not have this entity"); return; }

	//Pool<T>* existingPool = componentPools[componentUID];
	// Implement a remove function here, which removes by index, wrong function parameter as of now
	//existingPool->remove
	
	entitySignatures[entityUID].set(componentUID) = 0;

	Logger::sLog("Component ID: " + std::to_string(componentUID) + " removed from Entity ID: " + std::to_string(entityUID));
}

template<typename T>
bool Registry::hasComponent(const Entity& e1)
{
	const unsigned int entityUID = e1.getID();
	const unsigned int componentUID = Component<T>::getID();
	
	if (entitySignatures[entityUID].test(componentUID)) { return true; }
	return false;

}

template<typename T>
T& Registry::getComponent(const Entity& e1)
{
	const unsigned int componentUID = Component<T>::getID();

	std::shared_ptr<Pool<T>>toGet = std::static_pointer_cast<Pool<T>>(componentPools[componentUID]);

	return toGet->get(e1.getID());

}

template<typename T, typename ...Targs>
void Registry::addSystem(Targs&& ...args)
{
	std::shared_ptr<T>newSystem = std::make_shared<T>(std::forward<Targs>(args)...);
	systemsRegister.insert(std::make_pair(std::type_index(typeid(T)), newSystem));

}	

template<typename T>
void Registry::removeSystem()
{
	systemsRegister.erase(std::type_index(typeid(T)));

}

template<typename T>
bool Registry::hasSystem()
{
	return systemsRegister.count(std::type_index(typeid(T)));

}

template<typename T>
T& Registry::getSystem()
{	
	return *(std::static_pointer_cast<T>(systemsRegister[std::type_index(typeid(T))]));

}

template<typename T, typename ...Targs>
void Entity::addComponent(Targs&& ...args)
{

	entityregistryptr->addComponent<T>(*this, std::forward<Targs>(args)...);
	/*unsigned int componentUID = Component<T>::getID();

	if (componentUID >= entityregistryptr->componentPools) { entityregistryptr->componentPools.resize(componentUID + 1); }

	if (entityregistryptr->componentPools[componentUID] == nullptr) 
	{ 
		std::shared_ptr<Pool<T>>allocPool = std::make_shared<Pool<T>>();
		entityregistryptr->componentPools[componentUID] = allocPool;
	}

	std::shared_ptr<Pool<T>>existingPool = std::static_pointer_cast<Pool<T>>(entityregistryptr->componentPools[componentUID]);

	if (existingPool->getSize() >= id) { existingPool->resize(id + 1); }
	T newComponent(std::forward<Targs>(args)...);
	existingPool->set(newComponent, id);

	entityregistryptr->entitySignatures[id].set(componentUID);

	Logger::sLog("Entity ID: " + std::to_string(id) + " has been added to component ID: " + std::to_string(componentUID));*/


}

template<typename T>
void Entity::removeComponent()
{
	entityregistryptr->removeComponent<T>(*this);
	//const unsigned int componentUID = Component<T>::getID();

	//std::shared_ptr<Pool<T>>toRemove = std::static_pointer_cast<Pool<T>>(entityregistryptr->componentPools[componentUID]);
	//
	//toRemove->remove(id);

	//entityregistryptr->entitySignatures[id].set(componentUID, false);
}

template<typename T>
bool Entity::hasComponent()
{
	return entityregistryptr->hasComponent<T>(*this);
	//const unsigned int componentUID = Component<T>::getID();

	//return entityregistryptr->entitySignatures[id].test(componentUID);

	//std::shared_ptr<Pool<T>>toCheck = std::static_pointer_cast<Pool<T>>(entityregistryptr->componentPools[componentUID]);

	//if (toCheck->getsize() >= id) { return false; }

	//if (toCheck->operator[]())

}

template<typename T>
T& Entity::getComponent()
{
	return entityregistryptr->getComponent<T>(*this);

}


