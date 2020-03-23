#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SFML/Graphics.hpp>
#include <string>
#include "component.h"
#include "game_object.h"


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
