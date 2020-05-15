#ifndef __CLIENT.H__
#define __CLIENT.H__

#include <iostream>
#include "game_object.h"
#include "data_storage.h"
//Нужно дописать получение данных с сервера об отрисовываемых объектах.
//Приложение-клиент отправляет на сервер данные о событиях
//(нажатие клавишь клавиатуры).
//Получение данных о положении курсора мыши надо дописать.
class Client{
private:
	static Client* instance;  //Singleton
	Client(){};
	Client(const Client&){};
	Client& operator=(Client&){};
	void deleteInstance();

	DataStorage data_storage; //Данные для отображения на экране
	RenderController render_controller;
	Scaner scaner;
	std::string name;

	sf::TcpSocket socket;  //Сеть
	sf::Packet events_pack;
	void makePack();
	void connect();
	void send();
public:
	static client* getInstance();
	void setName(std::string name);
	void runApp();
};
	

#endif
