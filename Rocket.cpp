////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#include "Rocket.hpp"
#include <algorithm>
#include "App.hpp"
#include "InGame.hpp"

# define M_PI           3.14159265358979323846  /* pi */

unsigned int Rocket::max_quantity = 0;
unsigned int Rocket::quantity = 0;

Rocket::Rocket()
{
    ID = ++max_quantity;
    ++quantity;
    std::cout << "   Rocket["<< ID <<"] has been created. \n";

    collision_damage = 10;
}
Rocket::~Rocket()
{
    --quantity;
    std::cout << "   Rocket["<< ID <<"] has been destroyed. \n";
}

void Rocket::create( bool reset )
{
    sprite.setTexture( InGame::getTexture( InGame::TexName::ROCKET ) );
}

void Rocket::create( float velocity, float pos_x, float pos_y )
{
    this->velocity = velocity;
    sprite.setTexture( InGame::getTexture( InGame::TexName::ROCKET ) );

    updateTrackID();
}

void Rocket::logic()
{
    Moveable* target = Board::getMoveable( target_ID );

    if( target == nullptr )
    {
        // Searching for new target;
        target = Board::searchForNearestMoveable( this );
        if( target != nullptr )
        {
            target_ID = target->getID();
            target->getSprite().setColor(sf::Color(255,0,0));
        }
    }

    if( target != nullptr )
    {
        float y = getPositionCenter().x - target->getPositionCenter().x;
        float x = getPositionCenter().y - target->getPositionCenter().y;

        sprite.move
        (
            -(App::getElapsedTime()/1000.0)*velocity*std::sin( std::atan2( y, x ) ),
            -(App::getElapsedTime()/1000.0)*velocity*std::cos( std::atan2( y, x ) )
        );
        setRotation( -std::atan2( y, x ) * 180.0 / M_PI );
    }
    else
    {
        sprite.setRotation( 0.0f );
        sprite.move( 0.0f, -(App::getElapsedTime()/1000.0)*velocity );
    }
}

void Rocket::setTarget( Moveable* moveable )
{
    target_ID = moveable->getID();
}
