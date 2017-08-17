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
#include "Obstacle.hpp"
#include "InGame.hpp"

unsigned int Obstacle::max_quantity = 0;
unsigned int Obstacle::quantity = 0;

Obstacle::Obstacle()
{
    ID = ++max_quantity;
    ++quantity;
    std::cout << "    Obstacle["<< ID <<"] has been created. \n";
}

Obstacle::~Obstacle()
{
    --quantity;
    std::cout << "    Obstacle["<< ID <<"] has been destroyed. \n";
}

void Obstacle::create( bool reset )
{
    sprite.setTexture( InGame::getTexture( InGame::TexName::OBSTACLE ) );
    if( reset )
        health = 100;
}

unsigned int Obstacle::getID() const
{
    return ID;
}
