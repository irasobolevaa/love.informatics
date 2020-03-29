#include "data_storage.h"
#include "game_object.h"

#include<iostream>
#include<string>

void createObject(std::string object_name)
{
    if (getObject(object_name) == nullptr)
    {
        GameObject* obj = new GameObject(object_name);
        obj.name = object_name;
        this->objects.push_back(obj);
    }
}

void deleteObject(std::string object_name)
{
    GameObject* obj = getObject(object_name);
    if(obj != )
    {
        objects.erase(obj);
        delete obj;
    }
}   

GameObject* getObject(std::string object_name)
{
	for (auto i = this->objects.begin(); i != this->objects.end(); i++)
		if ((*i)->name == object_name) 
			return *it
}
