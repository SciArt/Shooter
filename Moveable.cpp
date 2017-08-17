////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Moveable.hpp"
#include "App.hpp"
#include "InGame.hpp"

unsigned int Moveable::max_quantity = 0;
unsigned int Moveable::quantity = 0;

Moveable::Moveable()
{
    // Set scale of the sprite
    // From the 1920p (texture resolution) to 16.0f (game resolution)
    sprite.setScale( 16.0f/1920.0f , 16.0f/1920.0f );

    collision_damage = 1;
    health = 1;
    //pos_x = 0.0f; pos_y = 0.0f;
    ID = ++max_quantity;
    ++quantity;
    std::cout << "  Movable["<< ID <<"] has been created. \n";
}

Moveable::~Moveable()
{
    --quantity;
    std::cout << "  Moveable["<< ID <<"] has been destroyed. \n";
}

sf::Sprite& Moveable::getSprite()
{
    return sprite;
}

sf::Vector2f Moveable::getPosition() const
{
    return sprite.getPosition();
}
sf::Vector2f Moveable::getPositionCenter() const
{
    return sf::Vector2f(sprite.getPosition().x + getWidth()/2, sprite.getPosition().y + getHeight()/2);
}
sf::Vector2f Moveable::getPositionTopCenter() const
{
    return sf::Vector2f(sprite.getPosition().x + getWidth()/2, sprite.getPosition().y);
}
sf::Vector2f Moveable::getPositionCenterRelative() const
{
    return sf::Vector2f(sprite.getLocalBounds().width/2.0, sprite.getLocalBounds().height/2.0);
}

void Moveable::setPosition( const sf::Vector2f& position )
{
    sprite.setPosition( position );
}

void Moveable::setPosition( const float x, const float y )
{
    sprite.setPosition( x, y );
}

bool Moveable::checkCollision( const float position_y ) const
{
    // NOT WORK IF THERE IS NO TEXTURE

    // When the moveable is not in collision with another moveable
    if( ( (position_y + getHeight()) <= sprite.getPosition().y ) ||
        (sprite.getPosition().y + getHeight()) <= position_y )
        return false;
    return true;
}

bool Moveable::checkCollision( Moveable* moveable )
{
    // NOT WORK IF THERE IS NO TEXTURE
    return sprite.getGlobalBounds().intersects( moveable->getSprite().getGlobalBounds() );
    /*
    if( this->getPosition().y >= moveable->getPosition().y + moveable->getHeight() ||
        this->getPosition().x + this->getWidth() <= moveable->getPosition().x ||
        this->getPosition().x >= moveable->getPosition().x + moveable->getWidth() ||
        this->getPosition().y + this->getHeight() <= moveable->getPosition().y )
    {
        return false;
    }
    return true;*/
}

float Moveable::getWidth() const
{
    if( sprite.getTexture() )
        return sprite.getTexture()->getSize().x * 16.0/1920.0;
    return -1;
}

float Moveable::getHeight() const
{
    if( sprite.getTexture() )
        return sprite.getTexture()->getSize().y * 16.0/1920.0;
    return -1;
}

void Moveable::updateTrackID()
{
    track_ID = static_cast<int>( (getPosition().x + (getWidth()/2.0f) - InGame::board_begin) / InGame::track_width  );
    if( track_ID > 4 )
        track_ID = 4;
    if( track_ID < 0 )
        track_ID = 0;
}

unsigned int Moveable::getID() const
{
    return ID;
}
