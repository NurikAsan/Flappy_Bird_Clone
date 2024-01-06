#include <SFML/Audio.hpp>
#pragma once

using namespace sf;

class setSound {
public:
	SoundBuffer s1, s2, s3;
	Sound jump, bonus, fail;

	setSound() {
		s1.loadFromFile("sound/jump.ogg");
		s2.loadFromFile("sound/bonus.ogg");
		s3.loadFromFile("sound/fail.ogg");

		jump.setBuffer(s1);
		bonus.setBuffer(s2);
		fail.setBuffer(s3);
	}
};

setSound sound;