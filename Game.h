#pragma once
#include "Player.h"
#include "Tap.h"
#include "Pipe.h"
#include "Score.h"
#include "Sound.h"

class Game {
public:
	Game();
	~Game();
	void run();

private:
	void processEvents();
	void update(float time);
	void render();
	sf::RenderWindow m_window;
	Texture Picture;
	Texture f;
	Texture tp;
	Texture pi;
	Texture sc;
	Texture go;
	Texture res;
	Sprite fon;
	Sprite gameover;
	Sprite restart;
	Player p;
	Tap tap;
	Pipe pipe;
	Score score;

};

// Загружаем необходимые картинки
Game::Game() :m_window(sf::VideoMode(288, 512), "Flappy Bird"), Picture(), f(), tp(), pi(), sc(), go(), fon(), gameover()
{
	f.loadFromFile("images/background.png");
	Picture.loadFromFile("images/player.png");
	tp.loadFromFile("images/tap.png");
	pi.loadFromFile("images/pipe.png");
	sc.loadFromFile("images/score.png");
	go.loadFromFile("images/gameover.png");
	res.loadFromFile("images/restart.png");
	fon.setTexture(f);
	p.setImg(Picture);
	tap.setImg(tp);
	pipe.setImg(pi);
	score.setImg(sc);
	gameover.setTexture(go);
	gameover.setPosition(30, 200);
	restart.setTexture(res);
	restart.setScale(0.2, 0.2);
}

Game::~Game(){}

// Функция запуска игры
void Game::run()
{
	sf::Clock clock;
	while (m_window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		processEvents();
		update(time);
		render();
	}
}
// Функция для отслеживания событий пользователем
void Game::processEvents()
{

	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == Event::Closed)
			m_window.close();

		if (event.type == Event::MouseButtonPressed) {
			// Если нажата мышка то началась игра, изменяем режим ожидание и старт игры
			if (event.key.code == Mouse::Left) {
				if (start) {
					start = false;
					play = true;
				}

				if (play) {
					p.setDy(-0.2);

					sound.jump.play();
				}
			}
			// для кнопки рестарт
			if (over) {

				if (event.mouseButton.button == sf::Mouse::Left) {
					// Получение позиции клика мыши
					sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
					sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

					// Проверка, был ли клик мыши внутри кнопки
					if (restart.getGlobalBounds().contains(mousePosF)) {
						start = true;
						play = false;
						over = false;
						p.restart();
						pipe.restart();
						score.restart();
						tap.restart();
					}
				}
			}
		}
	}
}
// Функция обновляет данные на каждой новой итерации
void Game::update(float time)
{
	// Если игра началось
	if (play) {

		if (p.getPlayerCoordinate().left > 10)
			p.setDx(-0.2);
		else
			p.setDx(0);

		pipe.setDx(-0.05);
		// Если трубы уходят за границу экрана, обновляем счетчик
		if (pipe.getPipeCoordinate().left < 0 && score.add) {
			score.c++;

			score.add = false;

			sound.bonus.play();
		}
		else if (pipe.getPipeCoordinate().left > 200)
			score.add = true;

		for (int i = 0; i < 2; i++)
			if (p.getSpritePlayer().getGlobalBounds().intersects(pipe.sprite[i].getGlobalBounds()) || p.getonGround()) {
				play = false;
				over = true;

				sound.fail.play();
			}
	}

	p.update(time);
	if (start)
		tap.update();
	pipe.update();
	score.update();
}
// Функция для отрисовки данных
void Game::render()
{
	m_window.clear(Color::White);
	m_window.draw(fon);
	m_window.draw(p.getSpritePlayer());
	if (tap.getVid() && start)
		m_window.draw(tap.getSprite());
	for (int i = 0; i < 2; i++)
		m_window.draw(pipe.sprite[i]);
	for (int i = 0; i < 3; i++)
		if (score.vid[i])
			m_window.draw(score.sec[i]);
	if (over) {
		m_window.draw(gameover);
		m_window.draw(restart);
	}
	m_window.display();
}