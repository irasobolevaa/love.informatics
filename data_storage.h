#ifndef __DATASTORAGE__
#define __DATASTORAGE__
#include <vector>
#include <string>
class GameObject;

class DataStorage{
public:
	void createObject(std::string object_name);
	void deleteObject(std::string object_name);
	GameObject* getObject(std::string object_name);
	~DataStorage();
private:
	std::vector<GameObject*> objects;
};


#endif //__DATASTORAGE__
