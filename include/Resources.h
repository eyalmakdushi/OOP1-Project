#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>

const int WINDOW_HEIGHT = 900;
const int WINDOW_WIDTH = 800;

const int NUM_OF_TEXTURES = 21;
const int NUM_OF_SOUNDS = 14;

class Resources
{
public:
	static Resources& instance();
	Resources(const Resources&) = delete;
	void operator = (const Resources&) = delete;

	void playGameMusic();
	void stopGameMusic();
	void playMenuMusic();
	void stopMenuMusic();
	void playSound(const int index);

	const sf::Texture& getTexture(const int index) const;
	const sf::Font& getFont() const;

private:
	Resources();

	sf::Texture m_textures[NUM_OF_TEXTURES];
	std::string m_texturesFilenames[NUM_OF_TEXTURES] =
	{ "pacman.png","demon.png","cookie.png","door.png","key.png","wall.png", "freeze.png", "time.png", "life.png", "super.png",
		"super pacman.png", "help normal.png", "help hovered.png", "play normal.png", "play hovered.png", "quit normal.png",
		"quit hovered.png", "menu background1.jpg", "information.jpg", "win.jpg", "lost.jpg" };

	sf::SoundBuffer m_buffers[NUM_OF_SOUNDS];
	std::string m_soundsFilenames[NUM_OF_SOUNDS] =
	{ "winning.ogg", "lose.ogg", "button.ogg", "key.ogg", "bump.ogg", "cookie.ogg", "demon.ogg", "life.ogg",
	 "ice.ogg", "super pacman.ogg", "time.ogg", "hooray.ogg", "time out.ogg","door.ogg"};
	sf::Sound m_sounds[NUM_OF_SOUNDS];

	sf::Music m_gameMusic;
	sf::Music m_menuMusic;

	sf::Font m_font;
};