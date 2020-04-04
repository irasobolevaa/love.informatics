#include "singleton.h"

Singleton_R_C* Singleton_R_C::getInstance(){
	if (!instance){
		instance = new Singleton_R_C();
		return instance;
	}
	return instance;
}

void Singleton_R_C::deleteInstance(){
	if (instance){
		delete instance;
		instance = 0;
	}
}

void Singleton_R_C::runApplication(){
	Singleton_R_C::getInstance()->render_controller.makeWindow();
	while (Singleton_R_C::getInstance()->render_controller.window.isOpen()){        //window cтоит сделать private в Renderer и написать ф-цию getWindow
        	sf::Event event;
        	while (Singleton_R_C::getInstance()->render_controller.window.pollEvent(event)){
            		if (event.type == sf::Event::Closed)
                		Singleton_R_C::getInstance()->render_controller.window.close();
        	}

        	Singleton_R_C::getInstance()->render_controller.window.clear();
		Singleton_R_C::getInstance()->render_controller.drawAll();
		Singleton_R_C::getInstance()->script_controller.update();
		Singleton_R_C::getInstance()->physics_controller.update();
        	Singleton_R_C::getInstance()->render_controller.window.display();
	}
	Singleton_R_C::deleteInstance();
}


Singleton_R_C* Singleton_R_C::instance = 0;
