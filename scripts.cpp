#include "scripts.h"
#include <algorithm>

void ScriptController::update(){
	auto beg = this->scripts.begin();
	auto end = this->scripts.end();
	for (auto it = beg; it != end; it++){
		static_cast<Script*>((*it))->execute();
	}
}

void ScriptController::appendScript(Component* script){
	this->scripts.push_back(script);
}

void ScriptController::removeScript(Component* script){
	auto beg = this->scripts.begin();
	auto end = this->scripts.end();
	auto it_rm_sc = find(beg, end, script);
	this->scripts.erase(it_rm_sc);
}

