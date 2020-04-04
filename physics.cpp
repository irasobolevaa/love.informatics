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
	auto beg = this->colliders.begin();
        auto end = this->colliders.end();
        for (auto it = beg; it != end; it++){
                for (auto jt = it; jt != end; jt++){
			if((*it)->isCollided(*jt)){
				(*it)->onCollision();
			}
        	}
	}
}

void PhysicsController::appendCollider(Collider* col){
        this->colliders.push_back(col);
}

void PhysicsController::removeCollider(Collider* col){
        auto beg = this->colliders.begin();
        auto end = this->colliders.end();
        auto it_rm_col = find(beg, end, col);
        this->colliders.erase(it_rm_col);
}

bool Collider::isCollided(Collider* sample){
	for (int i = 0; i < this->phys_model.getPointCount() - 1; i++){
                for (int j = 0; j < sample->phys_model.getPointCount() - 1; j++){
                        if (segmentCollision(this->phys_model.getPoint(i),this->phys_model.getPoint(i+1),sample->phys_model.getPoint(j),sample->phys_model.getPoint(j+1))){
                                return true;
                                break;
                        }
                }
        }
        return false;
}

void Collider::makeModel(sf::ConvexShape sample){
	this->phys_model = sample;
}

sf::ConvexShape Collider::getModel(){
	return this->phys_model;
}
