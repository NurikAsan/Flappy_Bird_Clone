#include <SFML/Graphics.hpp>
#pragma once

using namespace sf;

class Score {
public:
	Sprite sec[3];
	int s[3], c;
	bool vid[3], add;

	Score() {}
	Score(Texture& image);

	void update();
	void setImg(Texture& image) {
		for (int i = 0; i < 3; i++) {
			sec[i].setTexture(image);

			sec[i].setPosition(100 + 44 * i, 25);

			sec[i].setTextureRect(IntRect(0, 0, 44, 45));

			s[i] = 0;
			c = 0;
		}

		add = true;
	}
	void restart() {
		for (int i = 0; i < 3; i++) {

			sec[i].setPosition(100 + 44 * i, 25);

			sec[i].setTextureRect(IntRect(0, 0, 44, 45));

			s[i] = 0;
			c = 0;
		}
	}
};

Score::Score(Texture& image) {
	for (int i = 0; i < 3; i++) {
		sec[i].setTexture(image);

		sec[i].setPosition(100 + 44 * i, 25);

		sec[i].setTextureRect(IntRect(0, 0, 44, 45));

		s[i] = 0;
		c = 0;
	}

	add = true;
}
// ������ ������ ��������
void Score::update() {
	if (c < 10) {
		s[0] = c;

		vid[0] = true;
		vid[1] = false;
		vid[2] = false;
	}
	else if (c >= 10 && c < 100) {
		s[0] = c / 10;
		s[1] = c % 10;

		vid[0] = true;
		vid[1] = true;
		vid[2] = false;
	}
	else if (c >= 100 && c < 1000) {
		s[0] = c / 100;
		s[1] = (c / 10) % 10;
		s[2] = (c % 100) % 10;

		vid[0] = true;
		vid[1] = true;
		vid[2] = true;
	}

	for (int i = 0; i < 3; i++)
		sec[i].setTextureRect(IntRect(44 * s[i], 0, 44, 45));
}