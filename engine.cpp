#include <iostream>
#include <map>
#include <vector>
#include <string>
#include<SFML/Graphics.hpp>



class GameObject;
class Component;
class RenderController;
class Renderer;


class DataStorage{
public:
	bool createObject(GameObject game_object);
	bool deleteObject(std::string object_name);
	GameObject* getObject(std::string object_name);
private:
	std::vector<GameObject> objects;
};



class RenderController{
public:
	sf::RenderWindow window;
	void drawAll();
	void appendObject(GameObject* obj);
	void removeObject(GameObject* obj);
	void makeWindow();
private:
	float size_x = 800;
	float size_y = 600;
	std::vector<GameObject*> rend_objects;

};



class Singleton_R_C{
private:
	static Singleton_R_C* instance;
	Singleton_R_C(){};
	Singleton_R_C(const Singleton_R_C&){};
	Singleton_R_C& operator=( Singleton_R_C& ){};
public:
	RenderController render_controller;
	static Singleton_R_C* getInstance();
	static void deleteInstance();
};

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

Singleton_R_C* Singleton_R_C::instance = 0;

	

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

template<typename T>
void GameObject:: addComponent(){
	if (this->components.find(typeid(T).name()) == this->components.end()){
		T* new_component = new T;
		new_component->obj = this;
		this->components[typeid(T).name()] = new_component;
		if (typeid(Renderer).name() == typeid(T).name())
			Singleton_R_C::getInstance()->render_controller.appendObject(this);
	}
}

template<typename T>
void GameObject:: removeComponent(){
	if (this->components.find(typeid(T).name()) != this->components.end()){
		std::vector<GameObject*>::iterator beg, end, it_rm_obj;
		if (typeid(Renderer).name() == typeid(T).name())
			Singleton_R_C::getInstance()->render_controller.removeObject(this);
		delete this->components[typeid(T).name()];
		this->components.erase(typeid(T).name());
	}
}
	
template<typename T>
T* GameObject::getComponent(){
	std::map<std::string, Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++)
		if (it->first == typeid(T).name())
			return static_cast<T*>(it->second);
	return nullptr;
}



class Component{
private:
	std::string name;
public:
	GameObject* obj;
	virtual ~Component() = 0;
};

Component:: ~Component(){};



class Collider :public Component{
public:
	~Collider() override;
};

Collider:: ~Collider(){};



class Renderer :public Component{
private:
	sf::Texture texture;
	sf::Image image;
	sf::Sprite sprite;
public:
	void makeSprite(std::string file_name);
	void setPosOfSprite(sf::Vector2f vec);
	sf::Sprite getSprite();
	~Renderer() override;
};

Renderer:: ~Renderer(){
	delete this->texture;
	delete this->image;
	delete this->sprite;
};

void Renderer::makeSprite(std::string file_name){
	if(!this->image.loadFromFile(file_name)){
		std::cout << "Ошибка" << std::endl;
	}
	this->texture.loadFromImage(image);
	this->sprite.setTexture(this->texture);
	sf::Vector2f origin (sprite.getTexture()->getSize().x * sprite.getScale().x, sprite.getTexture()->getSize().y * sprite.getScale().y);
	origin *= 0.5f;
	this->sprite.setOrigin(origin);
}

void Renderer::setPosOfSprite(sf::Vector2f vec){
	this->sprite.setPosition(vec);
}

sf::Sprite Renderer::getSprite(){
	return this->sprite;
}
	


void RenderController::drawAll(){
	float x,y;
	auto beg = this->rend_objects.begin();
	auto end = this->rend_objects.end();
	for (auto it = beg; it != end; it++){
		x = this->size_x/2 + (*it)->x;
		y = this->size_y/2 - (*it)->y;
		(*it)->getComponent<Renderer>()->setPosOfSprite(sf::Vector2f(x, y));
		this->window.draw((*it)->getComponent<Renderer>()->getSprite());
	}
}
	
void RenderController::appendObject(GameObject* obj){
	this->rend_objects.push_back(obj);
}

void RenderController::removeObject(GameObject* obj){
	auto beg = this->rend_objects.begin();
	auto end = this->rend_objects.end();
	auto it_rm_obj = find(beg, end, obj);
	this->rend_objects.erase(it_rm_obj);
}

void RenderController::makeWindow(){
	this->window.create(sf::VideoMode(this->size_x, this->size_y), "Works!");
}



int main(){
	GameObject obj;
	obj.addComponent<Renderer>();
	Renderer* r = new Renderer;
	r = obj.getComponent<Renderer>();
	r->makeSprite("image.jpg");
	Singleton_R_C::getInstance()->render_controller.makeWindow();
	while (Singleton_R_C::getInstance()->render_controller.window.isOpen()){        //window cтоит сделать private в Renderer и написать ф-цию getWindow
        	sf::Event event;
        	while (Singleton_R_C::getInstance()->render_controller.window.pollEvent(event)){
            		if (event.type == sf::Event::Closed)
                		Singleton_R_C::getInstance()->render_controller.window.close();
        	}

        	Singleton_R_C::getInstance()->render_controller.window.clear();
		Singleton_R_C::getInstance()->render_controller.drawAll();
        	Singleton_R_C::getInstance()->render_controller.window.display();
	}
	std::cout << typeid(r).name() << std::endl;
	Collider* c = new Collider;
	c = obj.getComponent<Collider>();
	std::cout << typeid(c).name() << std::endl;
	obj.removeComponent<Renderer>();
	obj.removeComponent<Collider>(); //При вызове delete component_name - segmenation fault!
	Singleton_R_C::deleteInstance();
	std::cout << "qwerty" << std::endl;
	return 0;
}
