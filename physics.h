#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <SFML/Graphics.hpp>
#include <string>
#include "component.h"


class PhysicsController{
public:
        void update();
        void appendObject(GameObject* obj);
        void removeObject(GameObject* obj);
private:
        std::vector<GameObject*> phys_objects;

};


class Collider :public Component{
private:
        sf::ConvexShape phys_model;
public:
        void makeModel(sf::ConvexShape sample);
	sf::ConvexShape getModel();
	bool isCollided(GameObject* sample);
	virtual void onCollision() = 0;
        ~Collider() override;
};


#endif
