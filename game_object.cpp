#include "game_object.h"
#include "singleton.h"
#include "renderer.h"


template<typename T>
void GameObject:: addComponent(){
	if (this->components.find(typeid(T).name()) == this->components.end()){
		T* new_component = new T;
		new_component->obj = this;
		this->components[typeid(T).name()] = new_component;
		if (typeid(Renderer).name() == typeid(T).name())
			Singleton_R_C::getInstance()->render_controller.appendObject(this);
		//if (std::is_base_of<Script, T>::value){
	//		Singleton_R_C::getInstance()->script_controller.appendScript(new_component);
		//}
	}
}

template<typename T>
void GameObject:: removeComponent(){
	if (this->components.find(typeid(T).name()) != this->components.end()){
		if (typeid(Renderer).name() == typeid(T).name())
			Singleton_R_C::getInstance()->render_controller.removeObject(this);
	//	if (std::is_base_of<Script, T>::value)
	//		Singleton_R_C::getInstance()->script_controller.removeScript(static_cast<T*>(this->components.find(typeid(T).name())->second));
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
