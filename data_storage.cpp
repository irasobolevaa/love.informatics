#include "data_storage.h"
#include "game_object.h"

#include<iostream>
#include<string>

void DataStorage::createObject(std::string object_name)
{
    if (getObject(object_name) == nullptr)
    {
        GameObject* obj = new GameObject;
	obj = nullptr;
	std::cout << "qwerty_1" << std::endl;
        obj->name = object_name;
	std::cout << "qwerty_2" << std::endl;
        this->objects.push_back(obj);
    }
}

void DataStorage::deleteObject(std::string object_name)
{
    GameObject* obj = getObject(object_name);
    if(obj != nullptr)
    {
	auto beg = this->objects.begin();
	auto end = this->objects.end();
	auto it_rm_obj = find(beg, end, obj);
        this->objects.erase(it_rm_obj);
        delete obj;
    }
}   

GameObject* DataStorage::getObject(std::string object_name)
{	
	std::cout << "from get obj" << std::endl;
	for (auto i = this->objects.begin(); i != this->objects.end(); i++)
		if ((*i)->name == object_name)
			return *i;
	return nullptr;
}
