////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#include "SimpleText.hpp"
#include "App.hpp"
#include <iostream>

unsigned int SimpleText::max_quantity = 0;
unsigned int SimpleText::quantity = 0;

SimpleText::SimpleText()
{
    // Handling uniqe parameters
    ID = ++max_quantity;
    ++quantity;

    std::cout << "SimpleText["<< ID <<"] has been created. \n";
}

SimpleText::~SimpleText()
{
    --quantity;
    std::cout << "SimpleText["<< ID <<"] has been destroyed. \n";
}

SimpleText::SimpleText( const std::string &title,
        const float &height, const sf::Vector2f& position,
        const sf::Color &color, const sf::Font &font,
        const SimpleText::Origin &origin )
{
    // Handling uniqe parameters
    ID = ++max_quantity;
    ++quantity;
    std::cout << "SimpleText["<< ID <<"] has been created. \n";
    // Seting data
    setFont( font );
    setCharacterSize( App::getResFactor() * height );
    setScale( 1.0f/ App::getResFactor(), 1.0f / App::getResFactor());
    setString( title );
    setOrigin( origin );
    setPosition( position );
    setFillColor( color );
}

void SimpleText::create( const std::string &title,
        const float &height, const sf::Vector2f& position,
        const sf::Color &color, const sf::Font &font,
        const SimpleText::Origin &origin )
{
    // Seting data
    setFont( font );
    setCharacterSize( App::getResFactor() * height );
    setScale( 1.0f/ App::getResFactor(), 1.0f / App::getResFactor());
    setString( title );
    setOrigin( origin );
    setPosition( position );
    setFillColor( color );
}

void SimpleText::setOrigin( const SimpleText::Origin& origin )
{
    if( origin == SimpleText::Origin::TOPLEFT )
        sf::Text::setOrigin( 0.0f, 0.0f );
    else if( origin == SimpleText::Origin::CENTER )
        sf::Text::setOrigin( getLocalBounds().width/2.0f, 0.0f );
}
