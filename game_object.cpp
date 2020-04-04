#include "game_object.h"

GameObject::~GameObject(){
	for (auto i = this->components.begin(); i != this->components.end(); i++)
		delete i->second;
}
