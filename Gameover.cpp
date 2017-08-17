////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#include "Gameover.hpp"
#include <iostream>
#include <string>
#include "Statistics.hpp"

Gameover * Gameover::p_this = nullptr;

bool Gameover::init( )
{
    p_this = new Gameover;
    if( !p_this )
    {
        std::cout << "Gameover::init > Creating Gameover failed.\n";
        return false;
    }

    p_this->summary.create( "SUMMARY",
        0.7f, sf::Vector2f( 0.0 , -4.3 ), sf::Color::Yellow, App::getFont(), Button::CENTER );

    p_this->scores.create(              "scores: " + std::to_string( Statistics::getScores() ),
        0.4f, sf::Vector2f( -2.5 , -3.2 ), sf::Color::White, App::getFont() );
    p_this->moveables_destroyed.create(   "moveables destroyed: " + std::to_string( Statistics::getMoveablesDestroyed() ),
        0.4f, sf::Vector2f( -2.5 , -2.5 ), sf::Color::White, App::getFont()  );
    p_this->bullets_shooted.create(   "bullets shooted: " + std::to_string( Statistics::getBulletsShooted() ),
        0.4f, sf::Vector2f( -2.5 , -1.7 ), sf::Color::White, App::getFont() );
    p_this->time_played.create(         "time played: " + std::to_string( Statistics::getTimePlayed()) + "sec",
        0.4f, sf::Vector2f( -2.5 , -1.0 ), sf::Color::White, App::getFont() );


    p_this->info.create( "press ESC to return\nto the main menu",
        0.4f, sf::Vector2f( -2.5 , 0.0 ), sf::Color::White, App::getFont() );
    return true;
}

void Gameover::draw()
{
    p_this->summary.draw();
    p_this->scores.draw();
    p_this->moveables_destroyed.draw();
    p_this->bullets_shooted.draw();
    p_this->time_played.draw();
    p_this->info.draw();
}

void Gameover::logic()
{
    if( App::isKeyReleased( sf::Keyboard::Escape ) )
    {
        Statistics::reset();
        Gameover::close();
    }
}

void Gameover::close()
{
    delete p_this;
    App::setStatus( App::Status::MENU );
}
