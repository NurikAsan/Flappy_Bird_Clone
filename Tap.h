#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Tap {
public:
	Tap() {}
	Tap(Texture& image);

	~Tap();
	void update(); 

	const Sprite& getSprite();
	const bool getVid();
	const int getTime();
	void setImg(Texture& image) {
		sprite.setTexture(image);
		sprite.setPosition(120, 200);

		vid = true;
		time = 2000;
	}
	void restart() {
		sprite.setPosition(120, 200);

		vid = true;
		time = 2000;
	}
private:
	Sprite sprite;
	bool vid; // ���������� �������� �� ���������
	int time; // ������ ����� ��� ��������

};
// �����������
Tap::Tap(Texture& image) {
		sprite.setTexture(image);
		sprite.setPosition(120, 200);

		vid = true;
		time = 2000;
}

Tap::~Tap(){}
/*
* � ������ ������� ���������� time ������ ��� ����������������,
* � ������ ��� ����� ��������� �������� 0, �� ���������� ������ �������� ����
*/
void Tap::update(){
		time--;

		if (time < 1000) {
			vid = false;
			if (time == 0) {
				time = 2000;
				vid = true;
			}
		}
}

const Sprite& Tap::getSprite() {
	return sprite;
}

const bool Tap::getVid() {
	return vid;
}

const int Tap::getTime() {
	return time;
}