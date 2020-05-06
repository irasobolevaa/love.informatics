#include <SFML/Graphics.hpp>
#include "physics.h"
#include "game_object.h"
#include "math.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>

/*segmentCollision (sf::Vector2f A1, sf::Vector2f A2, sf::Vector2f B1, sf::Vector2f B2){
        if (B1.x <= A1.x and A1.x <= B2.x or B2.x <= A1.x and A1.x <= B1.x or B1.x <= A2.x and A2.x <= B2.x or B2.x <= A2.x and A2.x <= B1.x){
                if(B1.y <= A1.y and A1.y <= B2.y or B2.y <= A1.y and A1.y <= B1.y or B1.y <= A2.y and A2.y <= B2.y or B2.y <= A2.y and A2.y <= B1.y){
                        return true;
                }
        }
        return false;

}*/

bool segmentCollision2(std::pair<float, float> v11, std::pair<float,float> v12, std::pair<float, float> v21, std::pair<float, float> v22, std::pair<float, float> c1, std::pair<float, float> c2)
{
  v11.first+= c1.first;
  v11.second += c1.second;
  v12.first += c1.first;
  v12.second += c1.second;
  v21.first += c2.first;
  v21.second += c2.second;
  v22.first += c2.first;
  v22.second += c2.second;

  bool flag1 = ((((v12.first-v11.first)*(v21.second-v11.second)-(v21.first-v11.first)*(v12.second-v11.second))*((v12.first-v11.first)*(v22.second-v11.second)-(v12.second-v11.second)*(v22.first-v11.first))) <= 0);
  bool flag2 = ((((v21.first-v22.first)*(v11.second-v22.second)-(v21.second-v22.second)*(v11.first-v22.first))*((v21.first-v22.first)*(v12.second-v22.second)-(v21.second-v22.second)*(v12.first-v22.first))) <= 0);
  if (flag1 and flag2)
    return true;
  return false;
}

void PhysicsController::update(){
	auto beg = this->colliders.begin();
        auto end = this->colliders.end();
        for (auto it = beg; it != end; it++){
               	for (auto jt = it; jt != end; jt++){
			if(it != jt && (static_cast<Collider*>((*it)))->isCollided(static_cast<Collider*>(*jt))){
				static_cast<Collider*>(*it)->solveCollision(static_cast<Collider*>(*jt));
				static_cast<Collider*>(*it)->onCollision();
			}
        	}
		static_cast<Collider*>(*it)->obj->velocity.first -= static_cast<Collider*>(*it)->obj->accel.first;//В этих 4 строчках были +=
		static_cast<Collider*>(*it)->obj->velocity.second -= static_cast<Collider*>(*it)->obj->accel.second;
		static_cast<Collider*>(*it)->obj->x -= static_cast<Collider*>(*it)->obj->velocity.first;
		static_cast<Collider*>(*it)->obj->y -= static_cast<Collider*>(*it)->obj->velocity.second;
	}
}

void solveInelasticCollision(std::pair<float, float> norm, Collider* source, Collider* obj2){
	float module = sqrt(pow(norm.first, 2) + pow(norm.second, 2));
  	norm.first = norm.first/module;
  	norm.second = norm.second/module;
  	std::pair<float, float> tau = {-norm.second, norm.first};

  	float v1n = source->obj->velocity.first * norm.first + source->obj->velocity.second * norm.second;
  	float v2n = obj2->obj->velocity.first * norm.first + obj2->obj->velocity.second * norm.second;
  	float v1t = source->obj->velocity.first * tau.first + source->obj->velocity.second * tau.second;
  	float v2t = obj2->obj->velocity.first * tau.first + obj2->obj->velocity.second * tau.second;
  	float vn = (source->mass * v1n + obj2->mass * v2n)/(source->mass + obj2->mass);
  	if ((obj2->moveable == false) and (source->moveable == true)){
    		source->obj->velocity.first = (v2n) *norm.first + v1t*tau.first;
    		source->obj->velocity.second = (v2n) *norm.second + v1t*tau.second;
  	}	

  	if ((obj2->moveable == true) and (source->moveable == false)){
		obj2->obj->velocity.first = (v1n) *norm.first + v2t*tau.first;
    		obj2->obj->velocity.second = (v1n) *norm.second + v2t*tau.second;
  	}	

  	if ((obj2->moveable == true) and (source->moveable == true))
  	{
   		source->obj->velocity.first = vn * norm.first + v1t*tau.first;
    		source->obj->velocity.second = vn * norm.second + v1t*tau.first;
    		obj2->obj->velocity.first = vn * norm.first + v2t*tau.first;
    		obj2->obj->velocity.second = vn * norm.second + v2t*tau.first;
  	}
}

void solveElasticCollision(std::pair<float, float> norm, Collider* source, Collider* obj2){
	float module = sqrt(pow(norm.first, 2) + pow(norm.second, 2));
  	norm.first = norm.first/module;
  	norm.second = norm.second/module;
  	std::pair<float, float> tau = {-norm.second, norm.first};

  	float v1n = source->obj->velocity.first * norm.first + source->obj->velocity.second * norm.second;
  	float v2n = obj2->obj->velocity.first * norm.first + obj2->obj->velocity.second * norm.second;
  	float v1t = source->obj->velocity.first * tau.first + source->obj->velocity.second * tau.second;
  	float v2t = obj2->obj->velocity.first * tau.first + obj2->obj->velocity.second * tau.second;

  	float k = source->mass / obj2->mass;
  	if (obj2->moveable == false)
    		k = 0;

  	float a = k+1;
  	float b = -2*v2n - 2*k*v1n;
  	float c = (k-1)*v1n*v1n + 2*v1n*v2n;

  	if ( (source->moveable == true)){
    		if (pow(b, 2) - 4*a*c < 0){
      			std::cout << "discriminant in elasticCollision < 0" << '\n';
      			return;
	       	}
    		float v1n_ = (-b + sqrt(pow(b, 2) - 4*a*c))/(2*a);
    		float v2n_ = k*(v1n - v1n_) + v2n;
    		source->obj->velocity.first = v1n_*norm.first + v1t*tau.first;
    		source->obj->velocity.second = v1n_*norm.second + v1t*tau.second;

    		obj2->obj->velocity.first = v2n_*norm.first + v2t*tau.first;
    		obj2->obj->velocity.second = v2n_*norm.second + v2t*tau.second;
  	}

  	if (source->moveable == false){
    		obj2->obj->velocity.first = 2*(v1n) *norm.first + v2t*tau.first;
    		obj2->obj->velocity.second = 2*(v1n) *norm.second + v2t*tau.second;
  	}
}


void Collider::elasticCollision(Collider* source, Collider* obj2){
	if ((obj2->moveable == false) and (source->moveable == false))
    		return;
  	std::pair<float, float> V = {this->obj->velocity.first - obj2->obj->velocity.first, this->obj->velocity.second - obj2->obj->velocity.second};
	sf::ConvexShape vert1 = this->getModel();
	sf::ConvexShape vert2 = obj2->getModel();
  	std::pair<float, float> c1 = {this->obj->x, this->obj->y};
  	std::pair<float, float> c2 = {obj2->obj->x, obj2->obj->y};
  
  	for (int i = 0; i < vert1.getPointCount() - 1; i++){
    		for (int j = 0; j < vert2.getPointCount() - 1; j++){
			std::pair<float, float> point_1i = {vert1.getPoint(i).x, vert1.getPoint(i).y};
			std::pair<float, float> point_1iplus = {vert1.getPoint(i+1).x, vert1.getPoint(i+1).y};
			std::pair<float, float> point_2j = {vert2.getPoint(j).x, vert2.getPoint(j).y};
			std::pair<float, float> point_2jplus = {vert2.getPoint(j+1).x, vert2.getPoint(j+1).y};
      			if (segmentCollision2(point_1i, point_1iplus, point_2j, point_2jplus, c1, c2))
      			{		
        			std::pair<float, float> norm = {-vert2.getPoint(j+1).y + vert2.getPoint(j).y, vert2.getPoint(j+1).x - vert2.getPoint(j).x};
        			if (((norm.first)*(-vert2.getPoint(j).x)+(norm.second)*(-vert2.getPoint(j).y)) > 0){	
          				norm.first = -norm.first;
          				norm.second = -norm.second;
        			}
        			if ((((norm.first)*(-vert2.getPoint(j).x)+(norm.second)*(-vert2.getPoint(j).y))*((norm.first)*(V.first)+(norm.second)*(V.second))) > 0) 
          				solveElasticCollision(norm, source, obj2); 
				
      			}
		}
	}	
 }

void Collider::inelasticCollision(Collider* source, Collider* obj2){

	if ((obj2->moveable == false) and (source->moveable == false))
    		return;
  	std::pair<float, float> V = {this->obj->velocity.first - obj2->obj->velocity.first, this->obj->velocity.second - obj2->obj->velocity.second};

	sf::ConvexShape vert1 = this->getModel();
	sf::ConvexShape vert2 = obj2->getModel();
  	std::pair<float, float> c1 = {this->obj->x, this->obj->y};
  	std::pair<float, float> c2 = {obj2->obj->x, obj2->obj->y};

	for (int i = 0; i < vert1.getPointCount() - 1; i++){
    		for (int j = 0; j < vert2.getPointCount() - 1; j++){
      			std::pair<float, float> point_1i = {vert1.getPoint(i).x, vert1.getPoint(i).y};
                        std::pair<float, float> point_1iplus = {vert1.getPoint(i+1).x, vert1.getPoint(i+1).y};
                        std::pair<float, float> point_2j = {vert2.getPoint(j).x, vert2.getPoint(j).y};
                        std::pair<float, float> point_2jplus = {vert2.getPoint(j+1).x, vert2.getPoint(j+1).y};
                        if (segmentCollision2(point_1i, point_1iplus, point_2j, point_2jplus, c1, c2)){
        			std::pair<float, float> norm = {-vert2.getPoint(j+1).y + vert2.getPoint(j).y, vert2.getPoint(j+1).x - vert2.getPoint(j).x};
        			if (((norm.first)*(-vert2.getPoint(j).x)+(norm.second)*(-vert2.getPoint(j).y)) > 0){
          				norm.first = -norm.first;
         				norm.second = -norm.second;
        			}
        			if ((((norm.first)*(-vert2.getPoint(j).x)+(norm.first)*(-vert2.getPoint(j).y))*((norm.first)*(V.first)+(norm.second)*(V.second))) > 0)
          				solveInelasticCollision(norm, source, obj2);
			}
		}
	}
}

void Collider::solveCollision(Collider* obj2){
	if ((obj2->elastic == true) and (this->elastic == true))
        	this -> elasticCollision(this, obj2);
      	else
        	this -> inelasticCollision(this, obj2);
}


void PhysicsController::appendCollider(Component* col){
	this->colliders.push_back(col);
}

void PhysicsController::removeCollider(Component* col){
	auto beg = this->colliders.begin();
	auto end = this->colliders.end();
	auto it_rm_col = find(beg, end, col);
	if(it_rm_col != end)
		this->colliders.erase(it_rm_col);
}

bool Collider::isCollided(Collider* sample){
	if (sample->phys_model.getPointCount() == 0 or this->phys_model.getPointCount() == 0){
		return false;
	}

	std::pair<float, float> c1 = {this->obj->x, this->obj->y};
        std::pair<float, float> c2 = {sample->obj->x, sample->obj->y};


	for (int i = 0; i < this->phys_model.getPointCount() - 1; i++){
                for (int j = 0; j < sample->phys_model.getPointCount() - 1; j++){
			auto a = sample->phys_model.getPoint(0);
			
			std::pair<float, float> point_1i = {this->phys_model.getPoint(i).x, this->phys_model.getPoint(i).y};
                        std::pair<float, float> point_1iplus = {this->phys_model.getPoint(i+1).x, this->phys_model.getPoint(i+1).y};
			std::pair<float, float> point_2j = {sample->phys_model.getPoint(j).x, sample->phys_model.getPoint(j).y};
			std::pair<float, float> point_2jplus = {sample->phys_model.getPoint(j+1).x, sample->phys_model.getPoint(j+1).y};

                        if (segmentCollision2(point_1i, point_1iplus, point_2j, point_2jplus, c1, c2)){
				return true;
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

void Collider::setName(std::string name){
	this->name = name;
}

void Collider::setMov(bool flag){
	this->moveable = flag;
}

void Collider::setVisible(bool flag){
	this->visible = flag;
}
