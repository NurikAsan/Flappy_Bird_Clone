#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Mvar.h"

using namespace sf;

class Pipe {
public:
	Pipe() {}
	Pipe(Texture& image);

	void update();

	void Coordinates();

	const float getDx();
	Sprite sprite[2];
	const int getY();

	void setDx(float);

	FloatRect& getPipeCoordinate();

	void setImg(Texture& image) {
		for (int i = 0; i < 2; i++)
			sprite[i].setTexture(image);

		sprite[1].setTextureRect(IntRect(0, 415, 45, -415));

		dx = 0;
		Coordinates();
	}
	void restart() {
		dx = 0;
		Coordinates();
	}
private:
	int y;
	float dx;
	FloatRect rect;
};

Pipe::Pipe(Texture& image) {
		for (int i = 0; i < 2; i++)
			sprite[i].setTexture(image);

		sprite[1].setTextureRect(IntRect(0, 415, 45, -415));

		dx = 0;
		Coordinates();
}
// Функция отвечает за появление препятствий в случайном порядке
void Pipe::Coordinates() {
	srand(time(0));

	y = rand() % 6;

	rect.left = 288;
	rect.top = 100 + 50 * y;
}
// Функция обновляет координаты препятствий, то есть двигает объекты к стороне персонажа
void Pipe::update() {
	if (play)
		rect.left += dx;

	if (rect.left < -50)
		Coordinates();

	for (int i = 0; i < 2; i++)
		sprite[i].setPosition(rect.left, rect.top - 500 * i);
}

const float Pipe::getDx() {
	return dx;
}

const int Pipe::getY() {
	return y;
}

void Pipe::setDx(float dx) {
	this->dx = dx;
}

FloatRect& Pipe::getPipeCoordinate() {
	return rect;
}