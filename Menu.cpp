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
#include "App.hpp"
#include "Menu.hpp"
#include "InGame.hpp"

#include <iostream>

Menu * Menu::p_this = nullptr;

bool Menu::init( )
{
    p_this = new Menu;
    if( !p_this )
    {
        std::cout << "Menu::init > Creating Menu failed.\n";
        return false;
    }

    // Creating the buttons and title

    p_this->title.create(       "SHOOTER",      1.3f,   sf::Vector2f(  0.0f, -4.3f ),    sf::Color( 0, 180, 0 ), App::getFont(), SimpleText::Origin::CENTER  );
    p_this->new_game.create(    "new game",     0.7f,   sf::Vector2f( -3.0f, -2.0 ),     sf::Color::White,       App::getFont(), Button::Origin::TOPLEFT );
    p_this->load_game.create(   "load game",    0.7,    sf::Vector2f( -3.0f, -0.5 ),     sf::Color::White,       App::getFont(), Button::Origin::TOPLEFT );
    p_this->highscores.create(  "highscores",   0.7,    sf::Vector2f( -3.0f,  1.0 ),     sf::Color( 100, 100, 100),       App::getFont(), Button::Origin::TOPLEFT );
    p_this->exit.create(        "exit",         0.7,    sf::Vector2f( -3.0f,  2.5 ),     sf::Color::White,       App::getFont(), Button::Origin::TOPLEFT );

    // Setting status

    p_this->status = NEWGAME;
    p_this->new_game.switchStatus( true );

    return true;
}

void Menu::draw()
{
    App::draw( p_this->title );
    p_this->new_game.draw();
    p_this->load_game.draw();
    p_this->highscores.draw();
    p_this->exit.draw();
}

void Menu::logic()
{
    // Change the title of the new_game button if game is paused

    if( InGame::isPaused() && (p_this->new_game.getTitle() != "resume") )
        p_this->new_game.setTitle( "resume" );
    else if( !InGame::isPaused() && (p_this->new_game.getTitle() == "resume" ) )
        p_this->new_game.setTitle( "new game" );

    // Switch between buttons

    if( App::isKeyReleased( sf::Keyboard::Down ) )
    {
        if( p_this->status == NEWGAME )
        {
            p_this->new_game.switchStatus();
            p_this->load_game.switchStatus();
            p_this->status = LOADGAME;
        }
        else if( p_this->status == LOADGAME )
        {
            p_this->load_game.switchStatus();
            p_this->exit.switchStatus();
            p_this->status = EXIT;
        }
        else if( p_this->status == EXIT )
        {
            p_this->exit.switchStatus();
            p_this->new_game.switchStatus();
            p_this->status = NEWGAME;
        }
        /*else if( p_this->status == HIGHSCORES )
        {
            p_this->highscores.switchStatus();
            p_this->exit.switchStatus();
            p_this->status = EXIT;
        }*/
    }
    if( App::isKeyReleased( sf::Keyboard::Up ) )
    {
        if( p_this->status == LOADGAME )
        {
            p_this->load_game.switchStatus();
            p_this->new_game.switchStatus();
            p_this->status = NEWGAME;
        }
        /*else if( p_this->status == HIGHSCORES )
        {
            p_this->highscores.switchStatus();
            p_this->load_game.switchStatus();
            p_this->status = LOADGAME;
        }*/
        else if( p_this->status == NEWGAME )
        {
            p_this->new_game.switchStatus();
            p_this->exit.switchStatus();
            p_this->status = EXIT;
        }
        else if( p_this->status == EXIT )
        {
            p_this->exit.switchStatus();
            p_this->load_game.switchStatus();
            p_this->status = LOADGAME;
        }
    }

    // Checking if button is pressed

    if( App::isKeyReleased( sf::Keyboard::Return ) )
    {
        if( p_this->status == EXIT )
            App::setStatus( App::EXIT );
        else if( p_this->status == NEWGAME )
        {
            App::setStatus( App::INGAME );

        }
        else if( p_this->status == LOADGAME )
        {
            p_this->status = NEWGAME;
            p_this->new_game.switchStatus();
            p_this->load_game.switchStatus();

            App::setStatus( App::INGAME );

            SaveLoad::Load();
        }
    }
}

void Menu::close()
{
    if( p_this )
        delete p_this;
    p_this = nullptr;
}
