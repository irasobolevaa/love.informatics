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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		this->obj->y +=0.3;
		this->obj->remove();
	}
}


class CustomCollider:public Collider{
	void onCollision() override{
		//std::cout << "Collision!" << std::endl;
	}
	~CustomCollider(){};
};



int main(){
	ge::createObject("rock");
	ge::createObject("ball");
	ge::createObject("rock_1");
	ge::setWindowTitle("Works!");
	ge::setWindowSize(800, 600);
	ge::addComponent<Renderer>("rock");
	ge::addComponent<Renderer>("ball");
	ge::makeSprite("rock", "rock.png");
	ge::makeAnimation("rock", 0, 0, 64, 64, 16, 0.005);
	ge::addComponent<Renderer>("rock_1");
	ge::makeSprite("rock_1", "rock.png");
	ge::makeAnimation("rock_1", 0, 0, 64, 64, 16, 0.005);
	ge::makeAnimation("rock_1", 0, 0, 64, 64, 16, 0.01);
	ge::makeSprite("ball", "image_2.png");
	ge::addComponent<MoveByKeys>("rock");
	ge::addComponent<MoveByKeys>("ball");
	ge::setLayer("rock_1", 2);
	ge::setLayer("ball", 3);
	ge::runApplication();
	return 0;
}
