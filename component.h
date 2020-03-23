#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <string>
#include "game_object.h"

class Component{
private:
	std::string name;
public:
	GameObject* obj;
	virtual ~Component() = 0;
};


Component:: ~Component(){};


#endif
