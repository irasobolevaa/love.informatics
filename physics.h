#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <SFML/Graphics.hpp>
#include <string>
#include "component.h"


class Collider :public Component{
private:
        sf::ConvexShape phys_model;
public:
        void makeModel(sf::ConvexShape sample);
	sf::ConvexShape getModel();
	bool isCollided(Collider* sample);
	virtual void onCollision();
        ~Collider() override;
};


class PhysicsController{
public:
        void update();
        void appendCollider(Collider* col);
        void removeCollider(Collider* col);
	template <typename T>
	Collider* getCollider();
private:
        std::vector<Collider*> colliders;

};


template <typename T>
Collider* PhysicsController::getCollider(){
	auto beg = this->colliders.begin();
	auto end = this->colliders.end();
	for (auto i = beg; i != end;){
	       if (typeid(*i).name == typeid(T).name)
			return *i
	return nullptr;
	}
}	



#endif
