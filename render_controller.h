#ifndef __RENFER_CONTROLLER_H__
#define __RENDER_CONTROLLER_H__

#include "component.h"
#include <SFML/Graphics.hpp>
#include "game_object.h"


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


#endif
