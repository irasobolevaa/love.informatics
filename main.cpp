#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <type_traits>
#include "user_api.h"




class MoveByKeys:public Script{ void execute() override;
};

void MoveByKeys::execute(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->obj->x -=0.3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->obj->x +=0.3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->obj->y -=0.3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->obj->y +=0.3;
}


class CustomCollider:public Collider{
	void onCollision() override{
		//std::cout << "Collision!" << std::endl;
	}
	~CustomCollider(){};
};



int main(){
	ge::createObject("rock");
	ge::setWindowTitle("Works!");
	ge::setWindowSize(800, 600);
	ge::addComponent<Renderer>("rock");
	ge::makeSprite("rock", "rock.png");
	ge::makeAnimation("rock", 0, 0, 64, 64, 16, 0.005);
	std::vector<int> vec;
	vec.push_back(100);
	vec.push_back(100);
	vec.push_back(200);
	vec.push_back(100);
	vec.push_back(200);
	vec.push_back(200);
	vec.push_back(100);
	vec.push_back(200);
	ge::Vertex vert = ge::Vertex(vec);
	ge::addComponent<MoveByKeys>("rock");
	ge::runApplication();
	return 0;
}
