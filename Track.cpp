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
#include "Track.hpp"
#include "App.hpp"
#include "InGame.hpp"
#include "Gameover.hpp"
#include "Statistics.hpp"
#include <iostream>

unsigned int Track::max_quantity = 0;
unsigned int Track::quantity = 0;

Track::Track()
{
    // Setting data
    speed = 2.0f;

    ID = ++max_quantity;
    ++quantity;
    std::cout << "Track["<< ID <<"] has been created.\n";
}

Track::~Track()
{
    --quantity;
    std::cout << "Track["<< ID <<"] has been destroyed.\n";
}

void Track::create( unsigned int id )
{
    // Setting track position ID
    track_pos_id = id;

    // Setting texture and appearance
    if( track_pos_id%2 == 0 )
        sprite.setTexture( InGame::getTexture(InGame::TexName::TRACK1) );
    else
        sprite.setTexture( InGame::getTexture(InGame::TexName::TRACK2) );

    sprite.setScale( 16.0/1920.0 , 16.0/1920.0 );
    sprite.setPosition( InGame::board_begin + (InGame::track_width * track_pos_id ) , -4.5f);
}

void Track::draw()
{
    // Drawing the track
    App::draw( sprite );
}

void Track::logic( Player* player, std::list<Moveable*>& moveables_list )
{
    if( player->getTrackID() == track_pos_id )
        speed = 2.0f;
    else
        speed = 1.5f;

    // Moving all moveables in track
    for( std::list<Moveable*>::iterator it=moveables_list.begin(); it != moveables_list.end(); ++it )
    {
        // Movement from the track
        if( (*it)->getTrackID() == track_pos_id )
            (*it)->setPosition( (*it)->getPosition().x ,
                (*it)->getPosition().y + (App::getElapsedTime()/1000.0 * speed) );
    }
}
