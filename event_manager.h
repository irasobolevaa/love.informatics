#ifndef __EVENT_MANAGER.H__
#define __EVENT_MANAGER.H__

#include <SFML/Graphics.hpp>

class Scaner{
public:
	Scaner(sf::RenderWindow* window);
	bool scan();
	sf::Event getEvent();
private:
	sf::Event event;
	sf::RenderWindow* window;
}
