#ifndef __USER_API_H__
#define __USER_API_H__

#include "game_object.h"

namespace ge{
	void runApplication();
	bool makeSprite(GameObject* obj, std::string file_name);
	void createObject(std::string object_name);
	void deleteObject(std::string object_name);
	GameObject* getObject(std::string object_name);
	template <typename T>
	void addComponent(std::string object_name);
	template <typename T>
	void removeComponent(std::string object_name);
	void setWindowTitle(std::string title);
	void setWindowSize(float x, float y);
	template <typename T>
	void makeModelOfCollider(Vertex vert);
	class Vertex{
	public:
		std::vector<sf::Vector2f> vertex;
		Vertex(std::vector<float> cordinates);
	}


	
}

template <typename T>
void ge::addComponent(std::string object_name){
	GameObject* obj;
	obj = Singleton_R_C::getInstance()->data_storage.getObject(object_name);
	obj->addComponent<T>();
}

template <typename T>
void ge::removeComponent(std::string object_name){
	GameObject* obj;
	obj = Singleton_R_C::getInstance()->data_storage.getObject(object_name);
	obj->removeComponent<T>();
}

template <typename T>
void ge::makeModelOfCollider(Vertex vert){
	sf::ConvexShape* convex = new ConvexShape;
	convex->setPointCount(vert.size());
	int j = 0;
	for (auto i = vert.begin(); i != vert.end(); i++){
		convex.setPoint(j, *i);
		j++;
	}
	Singleton_R_C::getInstance()->phisic_controller.getCollider<T>->makeModel(convex);
}




#endif
