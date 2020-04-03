#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <type_traits>
#include "singleton.h"
int main(){
	Singleton_R_C::getInstance()->data_storage.createObject("qwerty");
	return 0;
}

