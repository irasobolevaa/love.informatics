#include <SFML/Graphics.hpp>
#include "physics.h"
#include "game_object.h"

bool segmentCollision (sf::Vector2f A1, sf::Vector2f A2, sf::Vector2f B1, sf::Vector2f B2){
        if (B1.x <= A1.x and A1.x <= B2.x or B2.x <= A1.x and A1.x <= B1.x or B1.x <= A2.x and A2.x <= B2.x or B2.x <= A2.x and A2.x <= B1.x){
                if(B1.y <= A1.y and A1.y <= B2.y or B2.y <= A1.y and A1.y <= B1.y or B1.y <= A2.y and A2.y <= B2.y or B2.y <= A2.y and A2.y <= B1.y){
                        return true;
                }
        }
        return false;

}

void PhysicsController::update(){
	auto beg = this->phys_objects.begin();
        auto end = this->phys_objects.end();
        for (auto it = beg; it != end; it++){
                for (auto jt = it; jt != end; jt++){
                	if((*it)->getComponent<Collider>()->isCollided(*jt)){
				onCollision();
			}
        	}
	}
}

void PhysicsController::appendObject(GameObject* obj){
        this->phys_objects.push_back(obj);
}

void PhysicsController::removeObject(GameObject* obj){
        auto beg = this->phys_objects.begin();
        auto end = this->phys_objects.end();
        auto it_rm_obj = find(beg, end, obj);
        this->phys_objects.erase(it_rm_obj);


bool Collider::isCollided(GameObject* sample){
	for (int i = 0; i < this->phys_model.getPointCount() - 1; i++){
                for (int j = 0; j < sample->getComponent<Collider>()->phys_model.getPointCount() - 1; j++){
                        if (segmentCollision(this->phys_model.getPoint(i),this->phys_model.getPoint(i+1),sample->getComponent<Collider>()->phys_model.getPoint(j),sample->getComponent<Collider>()->phys_model.getPoint(j+1))){
                                return true;
                                break;
                        }
                }
        }
        return false;
}

void Collider::makeModel(sf::CovexShape sample){
	this->phys_model = sample;
}

sf::ConvexShape Collider::getModel(){
	return this->phys_model;
}
