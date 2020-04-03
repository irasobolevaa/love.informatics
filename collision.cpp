#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

bool segmentCollision (sf::Vector2f A1, sf::Vector2f A2, sf::Vector2f B1, sf::Vector2f B2){
	if (B1.x <= A1.x and A1.x <= B2.x or B2.x <= A1.x and A1.x <= B1.x or B1.x <= A2.x and A2.x <= B2.x or B2.x <= A2.x and A2.x <= B1.x){
		if(B1.y <= A1.y and A1.y <= B2.y or B2.y <= A1.y and A1.y <= B1.y or B1.y <= A2.y and A2.y <= B2.y or B2.y <= A2.y and A2.y <= B1.y){
			return true;
		}
	}
	return false;

}

bool collisionCheck (sf::ConvexShape obj1, sf::ConvexShape obj2){
	for (int i = 0; i < obj1.getPointCount() - 1; i++){
		for (int j = 0; j < obj2.getPointCount() - 1; j++){
			if (segmentCollision(obj1.getPoint(i),obj1.getPoint(i+1),obj2.getPoint(j),obj2.getPoint(j+1))){
				return true;
				break;
			}
		}
	}
	return false;
}

int main()
{	

	sf::ConvexShape obj1(3);
        obj1.setPoint(0, sf::Vector2f(100, 100));
        obj1.setPoint(1, sf::Vector2f(100, 150));
        obj1.setPoint(2, sf::Vector2f(150, 150));

        sf::ConvexShape obj2(4);
        obj2.setPoint(0, sf::Vector2f(100, 100));
        obj2.setPoint(1, sf::Vector2f(500, 600));
        obj2.setPoint(2, sf::Vector2f(600, 600));
        obj2.setPoint(3, sf::Vector2f(600, 500));

	bool check = collisionCheck(obj1, obj2);
	std::cout << check << std::endl;

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "GO");
	while (window.isOpen())
    	{
                sf::Event event;
        	while (window.pollEvent(event))
		{
            		if (event.type == sf::Event::Closed)
                	window.close();
        	}
		window.clear();
	
		window.draw(obj1);
		window.draw(obj2);
	
		window.display();
	}
}
