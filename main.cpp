#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <type_traits>
#include "user_api.h"




class MoveByKeys:public Script{ void execute() override;
};

void MoveByKeys::execute(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->obj->x -=0.3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->obj->x +=0.3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->obj->y -=0.3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		this->obj->y +=0.3;
		ge::deleteObject(this->obj->name);
	}
}

class CustomCollider:public Collider{
	void onCollision() override{
//		std::cout << "Collision!" << std::endl;
	}
	~CustomCollider(){};
};


int main(){
	ge::setWindowTitle("Works!");
	ge::setWindowSize(800, 600);

	ge::createObject("rock");
	ge::addComponent<Renderer>("rock");
	ge::makeSprite("rock", "rock.png");
	ge::makeAnimation("rock", 0, 0, 64, 64, 16, 0.005);
	ge::addComponent<CustomCollider>("rock");

	std::vector<std::pair<float, float>> vec;
	vec.push_back({-32, 32});
	vec.push_back({32, 32});
	vec.push_back({32, -32});
	vec.push_back({-32,-32});

	ge::Vertex v = ge::Vertex(vec);

	ge::makeModelOfCollider<CustomCollider>(v, "rock");
	ge::setVelocity("rock", 0.05, 0.1);

	ge::createObject("wall_1");
	ge::createObject("wall_2");
	ge::createObject("wall_3");
	ge::createObject("wall_4");

	std::vector<std::pair<float, float>> vec1, vec2, vec3, vec4;
	
	vec1.push_back({-400, 300});
	vec1.push_back({400, 300});
	vec1.push_back({400, 310});
	vec1.push_back({-400, 310});

	vec2.push_back({-399, 299});
	vec2.push_back({-410, 299});
	vec2.push_back({-410, -299});
	vec2.push_back({-399, -299});

	vec3.push_back({-400, -300});
	vec3.push_back({-400, -310});
	vec3.push_back({400, -310});
	vec3.push_back({400, -300});

	vec4.push_back({400, -299});
	vec4.push_back({410, -299});
	vec4.push_back({410, 299});
	vec4.push_back({400, 299});

	ge::Vertex v1 = ge::Vertex(vec1);
	ge::Vertex v2 = ge::Vertex(vec2);
	ge::Vertex v3 = ge::Vertex(vec3);
	ge::Vertex v4 = ge::Vertex(vec4);

	ge::addComponent<CustomCollider>("wall_1");
	ge::addComponent<CustomCollider>("wall_2");
	ge::addComponent<CustomCollider>("wall_3");
	ge::addComponent<CustomCollider>("wall_4");

	ge::makeModelOfCollider<CustomCollider>(v1, "wall_1");
	ge::makeModelOfCollider<CustomCollider>(v2, "wall_2");
	ge::makeModelOfCollider<CustomCollider>(v3, "wall_3");
	ge::makeModelOfCollider<CustomCollider>(v4, "wall_4");

	ge::setMoveable<CustomCollider>("wall_1", false);
	ge::setMoveable<CustomCollider>("wall_2", false);
	ge::setMoveable<CustomCollider>("wall_3", false);
	ge::setMoveable<CustomCollider>("wall_4", false);
	

	ge::runApplication();
	return 0;
}
