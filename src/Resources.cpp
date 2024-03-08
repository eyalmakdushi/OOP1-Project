#include "Resources.h"

Resources::Resources()
{
	for (auto i = 0; i < NUM_OF_TEXTURES; ++i)
	{
		if (!m_textures[i].loadFromFile(m_texturesFilenames[i]))
			exit(EXIT_FAILURE);
	}

	for (auto i = 0; i < NUM_OF_SOUNDS; ++i)
	{
		if (!m_buffers[i].loadFromFile(m_soundsFilenames[i]))
			exit(EXIT_FAILURE);

		m_sounds[i].setBuffer(m_buffers[i]);
	}

	if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
		exit(EXIT_FAILURE);

	if (!m_gameMusic.openFromFile("Dragons.ogg"))
		exit(EXIT_FAILURE);
	m_gameMusic.setLoop(true);
	
	if (!m_menuMusic.openFromFile("V-Pop.ogg"))
		exit(EXIT_FAILURE);
	m_menuMusic.setLoop(true);
	m_menuMusic.setVolume(20);
}

Resources& Resources::instance() 
{
	static auto resources = Resources();
	return resources;
}

const sf::Texture& Resources::getTexture(const int index) const
{
	return m_textures[index];
}

const sf::Font& Resources::getFont() const
{
	return m_font;
}

void Resources::playGameMusic()
{
	m_gameMusic.play();
}

void Resources::stopGameMusic()
{
	m_gameMusic.stop();
}

void Resources::playMenuMusic()
{
	m_menuMusic.play();
}

void Resources::stopMenuMusic()
{
	m_menuMusic.stop();
}

void Resources::playSound(const int index)
{
	m_sounds[index].play();
}