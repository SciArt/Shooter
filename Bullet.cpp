////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#include "Bullet.hpp"
#include "InGame.hpp"
#include "App.hpp"
#include <iostream>

#include <algorithm>
# define M_PI           3.14159265358979323846  /* pi */

unsigned int Bullet::max_quantity = 0;
unsigned int Bullet::quantity = 0;

Bullet::Bullet()
{
    ID = ++max_quantity;
    ++quantity;
    std::cout << "Bullet["<< ID <<"] has been created. \n";

    owner_ID = -1;
    angle = 0.0f;
}
Bullet::~Bullet()
{
    --quantity;
    std::cout << "Bullet["<< ID <<"] has been destroyed. \n";
}

void Bullet::create( bool reset )
{
    sprite.setTexture( InGame::getTexture( InGame::TexName::BULLET ) );
}

void Bullet::create( float velocity, float pos_x, float pos_y )
{
    this->velocity = velocity;
    sprite.setTexture( InGame::getTexture( InGame::TexName::BULLET ) );
    //sprite.setPosition( pos_x - getWidth()/2.0f, pos_y - getHeight() );

    updateTrackID();
}

void Bullet::logic()
{
    sprite.move
    (
        (App::getElapsedTime()/1000.0)*velocity*std::sin( angle * M_PI/180.0 ),
        -(App::getElapsedTime()/1000.0)*velocity*std::cos( angle * M_PI/180.0 )
    );
    updateTrackID();
}

void Bullet::setRotation( float angle )
{
    this->angle = angle;
    sprite.setRotation( angle );
}

void Bullet::setOwner( Moveable* moveable )
{
    owner_ID = moveable->getID();
}

bool Bullet::checkCollision( Moveable* moveable )
{
    if( static_cast<int>(moveable->getID()) != owner_ID )
       return this->Moveable::checkCollision( moveable );
    return false;
}
