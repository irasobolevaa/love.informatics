#include "user_api.h"

void ge::runApplication(){
	Singleton_R_C::runApplication();
}

bool ge::makeSprite(GameObject* obj, std::string file_name){
	if (obj->getComponent<Renderer>() != nullptr){
		obj->getComponent<Renderer>()->makeSprite(file_name);
		return true;
	}
	else return false;
}

void ge::createObject(std::string object_name){
	Singleton_R_C::getInstance()->data_storage.createObject(object_name);
}

void ge::deleteObject(std::string object_name){
	Singleton_R_C::getInstance()->data_storage.deleteObject(object_name);
}

GameObject* ge::getObject(std::string object_name){
	return Singleton_R_C::getInstance()->data_storage.getObject(object_name);
}

void ge::setWindowSize(float x, float y){
	Singleton_R_C::getInstance()->render_controller.setWindowSize(x, y);
}

void ge::setWindowTitle(std::string title){
	Singleton_R_C::getInstance()->render_controller.setTitle(title);
}

void ge::Vertex::Vertex(std::vector<int> coordinates){
	for (auto i = coordinates.begin(); i != coordinates.end(); i++){
		auto j = i;
		j++;
		this->vertex.push_back(sf::Vector2f(*i, *j));
		i++;
	}
}





