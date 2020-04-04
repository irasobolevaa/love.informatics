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
        void appendCollider(Component* col);
        void removeCollider(Component* col);
private:
        std::vector<Component*> colliders;

};




#endif
