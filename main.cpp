#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <type_traits>
#include "game_object.h"
//#include "graphics.h"
//#include "scripts.h"
//#include "singleton.h"




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
	GameObject obj;
	obj.addComponent<Renderer>();
	obj.addComponent<MoveByKeys>();
	Renderer* r = new Renderer;
	r = obj.getComponent<Renderer>();
	r->makeSprite("image_2.png");
	Singleton_R_C::runApplication();
	return 0;
}
