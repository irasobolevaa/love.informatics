#include "graphics.h"
#include "game_object.h"

void RenderController::drawAll(){
	float x,y;
	auto beg = this->rend_objects.begin();
	auto end = this->rend_objects.end();
	for (auto it = beg; it != end; it++){
		x = this->size_x/2 + (*it)->x;
		y = this->size_y/2 + (*it)->y;
		(*it)->getComponent<Renderer>()->setPosOfSprite(sf::Vector2f(x, y));
		this->window.draw((*it)->getComponent<Renderer>()->getSprite());
	}
}
	
void RenderController::appendObject(GameObject* obj){
	this->rend_objects.push_back(obj);
}

void RenderController::removeObject(GameObject* obj){
	auto beg = this->rend_objects.begin();
	auto end = this->rend_objects.end();
	auto it_rm_obj = find(beg, end, obj);
	this->rend_objects.erase(it_rm_obj);
}

void RenderController::makeWindow(){
	this->window.create(sf::VideoMode(this->size_x, this->size_y), this->title);
}



Renderer:: ~Renderer(){};

void Renderer::makeSprite(std::string file_name){
	if(!this->image.loadFromFile(file_name)){
		std::cout << "Ошибка" << std::endl;
	}
	this->texture.loadFromImage(image);
	this->sprite.setTexture(this->texture);
	sf::Vector2f origin (sprite.getTexture()->getSize().x * sprite.getScale().x, sprite.getTexture()->getSize().y * sprite.getScale().y);
	origin *= 0.5f;
	this->sprite.setOrigin(origin);
}

void Renderer::setPosOfSprite(sf::Vector2f vec){
	this->sprite.setPosition(vec);
}

sf::Sprite Renderer::getSprite(){
	return this->sprite;
}

void RenderController::setWindowSize(float x, float y){
	this->size_x = x;
	this->size_y = y;
}

void RenderController::setTitle(std::string title){
	this->title = title;
}
