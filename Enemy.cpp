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
#include "Enemy.hpp"
#include "InGame.hpp"
#include "App.hpp"
#include "time.h"

unsigned int Enemy::max_quantity = 0;
unsigned int Enemy::quantity = 0;

Enemy::Enemy()
{
    ID = ++max_quantity;
    ++quantity;
    velocity = 0.5f;
    std::cout << "    Enemy["<< ID <<"] has been created. \n";
}

Enemy::~Enemy()
{
    --quantity;
    std::cout << "    Enemy["<< ID <<"] has been destroyed. \n";
}

void Enemy::create( bool reset )
{
    sprite.setTexture( InGame::getTexture( InGame::TexName::ENEMY ) );
}

void Enemy::logic()
{

    if( rand()/static_cast<float>(RAND_MAX) > 0.98 )
        velocity = -velocity;

    sprite.move( velocity*App::getElapsedTime()/1000.0f , 0.0f );

    if( sprite.getPosition().x < InGame::board_begin + InGame::track_width*track_ID )
    {
        sprite.setPosition( InGame::board_begin + (InGame::track_width*track_ID), sprite.getPosition().y );
        velocity = -velocity;
    }
    if( sprite.getPosition().x + getWidth()  > InGame::board_begin + InGame::track_width*(track_ID+1) )
    {
        sprite.setPosition( InGame::board_begin + (InGame::track_width*(track_ID+1)) - getWidth(), sprite.getPosition().y );
        velocity = -velocity;
    }
}

unsigned int Enemy::getID() const
{
    return ID;
}
