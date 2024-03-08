#pragma once
#include "BaseObject.h"
#include "DynamicObject.h"

class StaticObject : public BaseObject
{
public:
    virtual ~StaticObject() = default;
    virtual bool isDisposed() const;
    virtual void dispose();

protected:
    StaticObject(const sf::Texture& texture, float scaleRatio, sf::Vector2f position);
    void setDisposed();

private:
    bool m_isDisposed = false;
};
