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




int main(){
	ge::createObject("ball");
	ge::deleteObject("ball");
	ge::createObject("ball");
	ge::setWindowTitle("Works!");
	ge::setWindowSize(800, 600);
	ge::addComponent<Renderer>("ball");
	ge::addComponent<MoveByKeys>("ball");
	ge::makeSprite(ge::getObject("ball"), "image_2.png");
	ge::runApplication();
	return 0;
}
