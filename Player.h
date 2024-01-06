#pragma once
#include <SFML/Graphics.hpp>
#include "Mvar.h"

using namespace sf;

class Player {
public:
	Player() {}
	Player(Texture& image);

	~Player();

    void update(float time);

	FloatRect& getPlayerCoordinate();
	const Sprite& getSpritePlayer();
	const bool getonGround();
	const float getcurFrame();
	const float getDx();
	const float getDy();

	void setDx(float dx);
	void setDy(float dy);
	void setImg(Texture& image) {
		sprite.setTexture(image);
		sprite.setTextureRect(IntRect(0, 0, 38, 25));

		rect.left = 125;
		rect.top = 100;

		dx = dy = 0;
		curFrame = 0;
	}
	void restart() {
		rect.left = 125;
		rect.top = 100;

		dx = dy = 0;
		curFrame = 0;
	}
private:
	float dx, dy;  // движение персонажа
	FloatRect rect; // координаты персонажа
	float curFrame; // фрейм
	Sprite sprite; // спрайт
	bool onGround; // прыжок
};

/*
* Данный конструктор принимает текстуру и назначет его спрайту.
* Также инициализирует начальные координаты игрока, движение  и фрейм
*/
Player::Player(Texture& image) {
	sprite.setTexture(image);
	sprite.setTextureRect(IntRect(0, 0, 38, 25));

	rect.left = 125;
	rect.top = 100;

	dx = dy = 0;
	curFrame = 0;
}

/*
* Данный метод принимет время от начало подсчета таймером,
* Осуществляет анимацию персонажа
* Также данный метод позволят осуществлять прыжок
*/
void Player::update(float time) {
	rect.left += dx * time;

	// если игрок не на земле и в режиме игры, то  двигается по у
	if (!onGround && (play || over))
		dy += 0.0005 * time;

	rect.top += dy * time;

	onGround = false;

	// Условие для проверки что игрок упал
	if (rect.top > 480) {
		rect.top = 480;
		dy = 0;

		onGround = true;
	}

	// анимация персонажа
	if (!over) {
		curFrame += 0.005 * time;
		if (curFrame > 3)
			curFrame -= 3;

		sprite.setTextureRect(IntRect(38 * int(curFrame), 0, 38, 25));
	}

	sprite.setPosition(rect.left, rect.top);

	dx = 0;
}

// Деструктор класса
Player::~Player() {}

// Возвращает спрайт
const Sprite& Player::getSpritePlayer()
{
	return sprite;
}

// возваращает переменную, которая отвечает за прыжок
const bool Player::getonGround()
{
	return onGround;
}
//возвращает фрейм
const float Player::getcurFrame()
{
	return curFrame;
}
// Возвращает координаты игрока
FloatRect& Player::getPlayerCoordinate() {
	return rect;
}
// Возвращает Скорость персонажа по х
const float Player::getDx() {
	return dx;
}
// Возвращает Скорость персонажа по у
const float Player::getDy() {
	return dy;
}
// Сеттер для скорости персонажа по х
void Player::setDx(float dx) {
	this->dx = dx;
}
// Сеттер для скорости персонажа по у
void Player::setDy(float dy) {
	this->dy = dy;
}