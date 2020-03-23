#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include "component.h"
#include <map>


class GameObject{
public:
	std::string name;
	template<typename T>
	void addComponent();
	template<typename T>
	void removeComponent();
	template<typename T>
	T* getComponent();
	float x = 0;
	float y = 0;
private:
	std::map<std::string, Component*> components;
};

#endif
