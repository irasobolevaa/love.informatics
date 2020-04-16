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

bool segmentCollision2(std::vector<float> v11, std::vector<float> v12, std::vector<float> v21, std::vector<float> v22, std::vector<float> c1, std::vector<float> c2)
{
  v11[0] += c1[0];
  v11[1] += c1[1];
  v12[0] += c1[0];
  v12[1] += c1[1];
  v21[0] += c2[0];
  v21[1] += c2[1];
  v22[0] += c2[0];
  v22[1] += c2[1];

  bool flag1 = ((((v12[0]-v11[0])*(v21[1]-v11[1])-(v21[0]-v11[0])*(v12[1]-v11[1]))*((v12[0]-v11[0])*(v22[1]-v11[1])-(v12[1]-v11[1])*(v22[0]-v11[0]))) <= 0);
  bool flag2 = ((((v21[0]-v22[0])*(v11[1]-v22[1])-(v21[1]-v22[1])*(v11[0]-v22[0]))*((v21[0]-v22[0])*(v12[1]-v22[1])-(v21[1]-v22[1])*(v12[0]-v22[0]))) <= 0);
  if (flag1 and flag2)
    return true;
  return false;
}

void PhysicsController::update(){
	auto beg = this->colliders.begin();
        auto end = this->colliders.end();
        for (auto it = beg; it != end; it++){
               	for (auto jt = it; jt != end; jt++){
			if((it != jt) && (static_cast<Collider*>((*it)))->isCollided(static_cast<Collider*>(*jt))){
				static_cast<Collider*>(*it)->solveCollision(static_cast<Collider*>(*jt));
				static_cast<Collider*>(*it)->onCollision();
			}
        	}
		static_cast<Collider*>(*it)->obj->velocity[0] += static_cast<Collider*>(*it)->obj->accel[0];
		static_cast<Collider*>(*it)->obj->velocity[1] += static_cast<Collider*>(*it)->obj->accel[1];
		static_cast<Collider*>(*it)->obj->x += static_cast<Collider*>(*it)->obj->velocity[0];
		static_cast<Collider*>(*it)->obj->y += static_cast<Collider*>(*it)->obj->velocity[1];
	}
}

void solveInelasticCollision(std::vector<float> norm, Collider* source, Collider* obj2){
	float module = sqrt(pow(norm[0], 2) + pow(norm[1], 2));
  	norm[0] = norm[0]/module;
  	norm[1] = norm[1]/module;
  	std::vector<float> tau = {-norm[1], norm[0]};

  	float v1n = source->obj->velocity[0] * norm[0] + source->obj->velocity[1] * norm[1];
  	float v2n = obj2->obj->velocity[0] * norm[0] + obj2->obj->velocity[1] * norm[1];
  	float v1t = source->obj->velocity[0] * tau[0] + source->obj->velocity[1] * tau[1];
  	float v2t = obj2->obj->velocity[0] * tau[0] + obj2->obj->velocity[1] * tau[1];
  	float vn = (source->mass * v1n + obj2->mass * v2n)/(source->mass + obj2->mass);
  	if ((obj2->moveable == false) and (source->moveable == true)){
    		source->obj->velocity[0] = (v2n) *norm[0] + v1t*tau[0];
    		source->obj->velocity[1] = (v2n) *norm[1] + v1t*tau[1];
  	}	

  	if ((obj2->moveable == true) and (source->moveable == false)){
		obj2->obj->velocity[0] = (v1n) *norm[0] + v2t*tau[0];
    		obj2->obj->velocity[1] = (v1n) *norm[1] + v2t*tau[1];
  	}	

  	if ((obj2->moveable == true) and (source->moveable == true))
  	{
   		source->obj->velocity[0] = vn * norm[0] + v1t*tau[0];
    		source->obj->velocity[1] = vn * norm[1] + v1t*tau[0];
    		obj2->obj->velocity[0] = vn * norm[0] + v2t*tau[0];
    		obj2->obj->velocity[1] = vn * norm[1] + v2t*tau[0];
  	}
}

void solveElasticCollision(std::vector<float> norm, Collider* source, Collider* obj2){
	float module = sqrt(pow(norm[0], 2) + pow(norm[1], 2));
  	norm[0] = norm[0]/module;
  	norm[1] = norm[1]/module;

  	std::vector<float> tau = {-norm[1], norm[0]};

  	float v1n = source->obj->velocity[0] * norm[0] + source->obj->velocity[1] * norm[1];
  	float v2n = obj2->obj->velocity[0] * norm[0] + obj2->obj->velocity[1] * norm[1];
  	float v1t = source->obj->velocity[0] * tau[0] + source->obj->velocity[1] * tau[1];
  	float v2t = obj2->obj->velocity[0] * tau[0] + obj2->obj->velocity[1] * tau[1];

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
    		source->obj->velocity[0] = v1n_*norm[0] + v1t*tau[0];
    		source->obj->velocity[1] = v1n_*norm[1] + v1t*tau[1];

    		obj2->obj->velocity[0] = v2n_*norm[0] + v2t*tau[0];
    		obj2->obj->velocity[1] = v2n_*norm[1] + v2t*tau[1];
  	}

  	if (source->moveable == false){
    		obj2->obj->velocity[0] = 2*(v1n) *norm[0] + v2t*tau[0];
    		obj2->obj->velocity[1] = 2*(v1n) *norm[1] + v2t*tau[1];
  	}
}


void Collider::elasticCollision(Collider* source, Collider* obj2){
	if ((obj2->moveable == false) and (source->moveable == false))
    		return;
  	std::vector<float> V = {this->obj->velocity[0] - obj2->obj->velocity[0], this->obj->velocity[1] - obj2->obj->velocity[1]};
	sf::ConvexShape vert1 = this->getModel();
	sf::ConvexShape vert2 = obj2->getModel();
  	std::vector<float> c1 = {this->obj->x, this->obj->y};
  	std::vector<float> c2 = {obj2->obj->x, obj2->obj->y};
  
  	for (int i = 0; i < vert1.getPointCount() - 1; i++){
    		for (int j = 0; j < vert2.getPointCount() - 1; j++){
			std::vector<float> point_1i = {vert1.getPoint(i).x, vert1.getPoint(i).y};
			std::vector<float> point_1iplus = {vert1.getPoint(i+1).x, vert1.getPoint(i+1).y};
			std::vector<float> point_2j = {vert2.getPoint(j).x, vert2.getPoint(j).y};
			std::vector<float> point_2jplus = {vert2.getPoint(j+1).x, vert2.getPoint(j+1).y};
      			if (segmentCollision2(point_1i, point_1iplus, point_2j, point_2jplus, c1, c2))
      			{		
        			std::vector<float> norm = {-vert2.getPoint(j+1).y + vert2.getPoint(j).y, vert2.getPoint(j+1).x - vert2.getPoint(j).x};
        			if (((norm[0])*(-vert2.getPoint(j).x)+(norm[1])*(-vert2.getPoint(j).y)) > 0){	
          				norm[0] = -norm[0];
          				norm[1] = -norm[1];
        			}
        			if ((((norm[0])*(-vert2.getPoint(j).x)+(norm[1])*(-vert2.getPoint(j).y))*((norm[0])*(V[0])+(norm[1])*(V[1]))) > 0) 
          				solveElasticCollision(norm, source, obj2);
      			}
		}
	}	
 }

void Collider::inelasticCollision(Collider* source, Collider* obj2){

	if ((obj2->moveable == false) and (source->moveable == false))
    		return;
  	std::vector<float> V = {this->obj->velocity[0] - obj2->obj->velocity[0], this->obj->velocity[1] - obj2->obj->velocity[1]};

	sf::ConvexShape vert1 = this->getModel();
	sf::ConvexShape vert2 = obj2->getModel();
  	std::vector<float> c1 = {this->obj->x, this->obj->y};
  	std::vector<float> c2 = {obj2->obj->x, obj2->obj->y};

	for (int i = 0; i < vert1.getPointCount() - 1; i++){
    		for (int j = 0; j < vert2.getPointCount() - 1; j++){
      			std::vector<float> point_1i = {vert1.getPoint(i).x, vert1.getPoint(i).y};
                        std::vector<float> point_1iplus = {vert1.getPoint(i+1).x, vert1.getPoint(i+1).y};
                        std::vector<float> point_2j = {vert2.getPoint(j).x, vert2.getPoint(j).y};
                        std::vector<float> point_2jplus = {vert2.getPoint(j+1).x, vert2.getPoint(j+1).y};
                        if (segmentCollision2(point_1i, point_1iplus, point_2j, point_2jplus, c1, c2)){
        			std::vector<float> norm = {-vert2.getPoint(j+1).y + vert2.getPoint(j).y, vert2.getPoint(j+1).x - vert2.getPoint(j).x};
        			if (((norm[0])*(-vert2.getPoint(j).x)+(norm[1])*(-vert2.getPoint(j).y)) > 0){
          				norm[0] = -norm[0];
         				norm[1] = -norm[1];
        			}
        			if ((((norm[0])*(-vert2.getPoint(j).x)+(norm[1])*(-vert2.getPoint(j).y))*((norm[0])*(V[0])+(norm[1])*(V[1]))) > 0)
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

	std::vector<float> c1 = {this->obj->x, this->obj->y};
        std::vector<float> c2 = {sample->obj->x, sample->obj->y};


	for (int i = 0; i < this->phys_model.getPointCount() - 1; i++){
                for (int j = 0; j < sample->phys_model.getPointCount() - 1; j++){
			auto a = sample->phys_model.getPoint(0);
			
			std::vector<float> point_1i = {this->phys_model.getPoint(i).x, this->phys_model.getPoint(i).y};
                        std::vector<float> point_1iplus = {this->phys_model.getPoint(i+1).x, this->phys_model.getPoint(i+1).y};
			std::vector<float> point_2j = {sample->phys_model.getPoint(j).x, sample->phys_model.getPoint(j).y};
			std::vector<float> point_2jplus = {sample->phys_model.getPoint(j+1).x, sample->phys_model.getPoint(j+1).y};

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
