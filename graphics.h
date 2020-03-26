#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <SFML/Graphics.hpp>
#include <string>
#include "component.h"


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


#endif
