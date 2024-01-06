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
	float dx, dy;  // �������� ���������
	FloatRect rect; // ���������� ���������
	float curFrame; // �����
	Sprite sprite; // ������
	bool onGround; // ������
};

/*
* ������ ����������� ��������� �������� � �������� ��� �������.
* ����� �������������� ��������� ���������� ������, ��������  � �����
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
* ������ ����� �������� ����� �� ������ �������� ��������,
* ������������ �������� ���������
* ����� ������ ����� �������� ������������ ������
*/
void Player::update(float time) {
	rect.left += dx * time;

	// ���� ����� �� �� ����� � � ������ ����, ��  ��������� �� �
	if (!onGround && (play || over))
		dy += 0.0005 * time;

	rect.top += dy * time;

	onGround = false;

	// ������� ��� �������� ��� ����� ����
	if (rect.top > 480) {
		rect.top = 480;
		dy = 0;

		onGround = true;
	}

	// �������� ���������
	if (!over) {
		curFrame += 0.005 * time;
		if (curFrame > 3)
			curFrame -= 3;

		sprite.setTextureRect(IntRect(38 * int(curFrame), 0, 38, 25));
	}

	sprite.setPosition(rect.left, rect.top);

	dx = 0;
}

// ���������� ������
Player::~Player() {}

// ���������� ������
const Sprite& Player::getSpritePlayer()
{
	return sprite;
}

// ����������� ����������, ������� �������� �� ������
const bool Player::getonGround()
{
	return onGround;
}
//���������� �����
const float Player::getcurFrame()
{
	return curFrame;
}
// ���������� ���������� ������
FloatRect& Player::getPlayerCoordinate() {
	return rect;
}
// ���������� �������� ��������� �� �
const float Player::getDx() {
	return dx;
}
// ���������� �������� ��������� �� �
const float Player::getDy() {
	return dy;
}
// ������ ��� �������� ��������� �� �
void Player::setDx(float dx) {
	this->dx = dx;
}
// ������ ��� �������� ��������� �� �
void Player::setDy(float dy) {
	this->dy = dy;
}