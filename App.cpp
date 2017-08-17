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
#include "Gameover.hpp"
#include "Statistics.hpp"
#include "SimpleText.hpp"
#include <iostream>
#include <string>
#include <time.h>

App * App::p_this = nullptr;

////////////////////////////////////////////////////////////
/// STATUS
///
////////////////////////////////////////////////////////////
void App::setStatus( const App::Status& status )
{
    p_this->status = status;
}

App::Status App::getStatus()
{
    return p_this->status;
}

////////////////////////////////////////////////////////////
/// FONT
///
////////////////////////////////////////////////////////////

const sf::Font& App::getFont()
{
    return p_this->font;
}

////////////////////////////////////////////////////////////
/// isRun()
///
////////////////////////////////////////////////////////////

bool App::isRun()
{
    if( p_this->status == EXIT )
        return false;

    return true;
}

////////////////////////////////////////////////////////////
/// WINDOW
///
////////////////////////////////////////////////////////////

sf::Vector2u App::getWindowSize()
{
    return p_this->window.getSize();
}

const float& App::getResFactor()
{
    return p_this->res_factor;
}

const sf::Int32& App::getElapsedTime()
{
    return p_this->elapsed_time;
}
////////////////////////////////////////////////////////////
/// DRAW
///
////////////////////////////////////////////////////////////

void App::draw( const sf::Drawable & drawable )
{
    p_this->window.draw( drawable );
}
////////////////////////////////////////////////////////////
/// RUN
///
////////////////////////////////////////////////////////////

void App::run()
{
    // Setting status
    p_this->status = MENU;

    // Restarting clocks
    p_this->trigger.restart();
    p_this->clock.restart();

    while( App::isRun() )
    {
        // Checking events
        App::checkEvents();

        /// LOGIC
        if( p_this->status == MENU )
            Menu::logic();
        else if( p_this->status == INGAME )
            InGame::logic();
        else if( p_this->status == GAMEOVER )
            Gameover::logic();

        /// DRAWING
        //if( p_this->fps_counter%2 == 0 )
        {
            // Clearing the screen
            p_this->window.clear( sf::Color::Black );

            // Executing proper run module
            if( p_this->status == MENU )
                Menu::draw();
            else if( p_this->status == INGAME )
                InGame::draw();
            else if( p_this->status == GAMEOVER )
                Gameover::draw();

            // Drawing ammount of FPS
            if( p_this->f_FPS_display )
                draw(p_this->fps);

            // Displaying what we have drawn
            p_this->window.display();
        }

        p_this->fps_counter++;
        // Updating FPS text
        if( p_this->trigger.getElapsedTime().asSeconds() > 1.0 )
        {
            //Statistics::addTimePlayed( 1000000 );
            p_this->fps.setString( std::to_string(p_this->fps_counter)+" FPS\n" );
            p_this->fps_counter = 0;
            p_this->trigger.restart();
        }

        // Updating elapsed time
        p_this->elapsed_time = p_this->clock.getElapsedTime().asMilliseconds();
        p_this->clock.restart();
    }

    // Closing application
    App::close();
}

////////////////////////////////////////////////////////////
/// EVENTS
///
////////////////////////////////////////////////////////////

void App::checkEvents()
{
    for( int i = sf::Keyboard::Key::KeyCount - 1; i >= 0; --i )
        p_this->f_released_key[i] = false;

    sf::Event event;

    while( p_this->window.pollEvent( event ) )
    {
        // Order to close the window (by X button for example)
        if( event.type == sf::Event::Closed )
        {
            p_this->status = EXIT;
        }

        // Checking which keys were pressed and now they are realeased
        if( event.type == sf::Event::KeyReleased )
        {
            p_this->f_released_key[ event.key.code ] = true;

            if( event.key.code == sf::Keyboard::F1 )
            {
                p_this->f_FPS_display = !(p_this->f_FPS_display);
            }
        }
    }
}

bool App::isKeyReleased( sf::Keyboard::Key key )
{
    return p_this->f_released_key[ key ];
}

////////////////////////////////////////////////////////////
/// INTITIALIZATION
///
////////////////////////////////////////////////////////////

bool App::init()
{
    srand( std::time(NULL) );
    // Blocking using this method more then once
    static bool f_init = false;
    if( f_init )
    {
        std::cout << "App:init > Error. Initialization cannot be use more then once.\n";
        return false;
    }
    f_init = true;

    // Creating the only object of App
    p_this = new App;
    if( !p_this )
    {
        std::cout << "App::init > Creating App object failed.\n";
        return false;
    }

    p_this->status = INIT; // Setting status

    if( !Statistics::init() )
    {
        std::cout << "Statistics::init > Initializing Statistics failed.\n";
    }

    p_this->elapsed_time = 0;

    p_this->fps_counter = 0;
    p_this->f_FPS_display = false;

    // Creating and setting the window

    p_this->window.create( sf::VideoMode::getFullscreenModes()[0],
        "Shooter", sf::Style::Fullscreen );

    //p_this->window.create( sf::VideoMode(1280,720),
    //    "Shooter", sf::Style::None );

    //p_this->window.create( sf::VideoMode(1280,720),
    //    "Shooter", sf::Style::Default );

    if( !p_this->window.isOpen() )
    {
        std::cout << "App::init >Creating window failed.\n";
        return false;
    }

    p_this->window.setPosition( sf::Vector2i(0,0) );

    // Setting the camera
    // We want coordinates to be in range:
    // 0.0 <= x <= 16.0 && 0.0 <= y <= 9.0
    sf::View view;
    view.reset( sf::FloatRect( 0.0f, 0.0f, 16.0f, 9.0f ) );
    view.setCenter( 0.0f, 0.0f );
    p_this->window.setView( view );

    //p_this->window.setFramerateLimit(30);
    p_this->window.setVerticalSyncEnabled( true );

    // Setting the resolution fator for scaling on any resolution
    p_this->res_factor = p_this->window.getSize().y / 9.0f;

    // Loading the font
    if( !p_this->font.loadFromFile("Fonts/FreeSerifBold.ttf") )
    {
        std::cout << "App::init >Loading font failed.\n";
        return false;
    }

    // Hiding the mouse cursor
    p_this->window.setMouseCursorVisible( false );

    // Initializing Menu
    if( !Menu::init() )
    {
        std::cout << "App::init > Initializing Menu failed.\n";
        return false;
    }

    // Initializing InGame
    if( !InGame::init() )
    {
        std::cout << "App::init > Initializing InGame failed.\n";
        return false;
    }

    // Creat the FPS text
    p_this->fps.create( "", 0.25f, sf::Vector2f(-7.9f,-4.5f), sf::Color::Red, App::getFont(), SimpleText::Origin::TOPLEFT );

    App::run();

    return true;
}

////////////////////////////////////////////////////////////
/// CLOSE
///
////////////////////////////////////////////////////////////

void App::close()
{
    // Closing everything
    // Releasing reserved memory

    InGame::close();
    Menu::close();

    if( p_this->window.isOpen() )
        p_this->window.close();

    if( p_this )
        delete p_this;
    p_this = nullptr;
}

