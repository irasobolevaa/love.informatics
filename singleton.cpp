#include "singleton.h"

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
