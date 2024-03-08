#include "StaticObject.h"

StaticObject::StaticObject(const sf::Texture& texture, float scaleRatio, sf::Vector2f position)
    : BaseObject(texture, scaleRatio, position)
{}

bool StaticObject::isDisposed() const
{
    return m_isDisposed;
}

void StaticObject::dispose()
{
    setDisposed();
}

void StaticObject::setDisposed()
{
    m_isDisposed = true;
}