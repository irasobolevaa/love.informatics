#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <SFML/Graphics.hpp>
#include <string>
#include "component.h"


class Collider :public Component{
private:
        sf::ConvexShape phys_model;
public:
	std::string name;
        void makeModel(sf::ConvexShape sample);
	void setName(std::string name);
	sf::ConvexShape getModel();
	bool isCollided(Collider* sample);
	virtual void onCollision() = 0;
};


class PhysicsController{
public:
        void update();
        void appendCollider(Component* col, std::string name);
        void removeCollider(std::string name);
	template <typename T>
	Collider* getCollider();
private:
        std::map<std::string, Component*> colliders;

};


template <typename T>
Collider* PhysicsController::getCollider(){
	auto beg = this->colliders.begin();
	auto end = this->colliders.end();
	for (auto i = beg; i != end; i++){
	       if (i->first == typeid(T).name())
			return static_cast<T*>(i->second);
	return nullptr;
	}
}	



#endif
