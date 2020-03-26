#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "graphics.h"
#include "scripts.h"

class Singleton_R_C{
private:
	static Singleton_R_C* instance;
	Singleton_R_C(){};
	Singleton_R_C(const Singleton_R_C&){};
	Singleton_R_C& operator=( Singleton_R_C& ){};
public:
	RenderController render_controller;
	ScriptController script_controller;
	static Singleton_R_C* getInstance();
	static void deleteInstance();
	static void runApplication();
};

#endif
