#ifndef __DATASTORAGE__
#define __DATASTORAGE__


class DataStorage{
public:
	bool createObject(std::string object_name);
	bool deleteObject(std::string object_name);
	GameObject* getObject(std::string object_name);
private:
	std::vector<GameObject*> objects;
};


#endif //__DATASTORAGE__
