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

#include "Button.hpp"
#include "App.hpp"
#include <iostream>

unsigned int Button::max_quantity = 0;
unsigned int Button::quantity = 0;

Button::Button()
{
    // Handling uniqe parameters
    ID = ++max_quantity;
    ++quantity;
    std::cout << "Button["<< ID <<"] has been created. \n";

    // Reseting data
    height = 0.0f;
    refreshTextActive();
    f_active = false;
}

Button::Button( const std::string &title,
        const float &height, const sf::Vector2f& position,
        const sf::Color &color, const sf::Font &font,
        const Button::Origin &origin )
{
    // Handling uniqe parameters
    ID = ++max_quantity;
    ++quantity;
    std::cout << "Button["<< ID <<"] has been created. \n";

    // Setting data
    setFont( font );
    setHeight( height );
    setTitle( title );
    setOrigin( origin );
    setPos( position );
    setColor( color );

    refreshTextActive();
    f_active = false;
}

void Button::create( const std::string &title,
        const float &height, const sf::Vector2f& position,
        const sf::Color &color, const sf::Font &font,
        const Button::Origin &origin )
{
    // Seting data
    setFont( font );
    setHeight( height );
    setTitle( title );
    setOrigin( origin );
    setPos( position );
    setColor( color );

    refreshTextActive();
    f_active = false;
}

Button::~Button()
{
    --quantity;
    std::cout << "Button["<< ID <<"] has been destroyed. \n";
}

void Button::draw()
{
    if( f_active )
        App::draw( text_active );
    else
        App::draw( text );
}

void Button::setTitle( const std::string& title, const float height )
{
    // Setting new title
    text.setString( title );
    if( height > 0.0f )
        setHeight( height );
    else if( this->height > 0.0f )
        setHeight( this->height );

    refreshTextActive();
}

const std::string Button::getTitle() const
{
    return text.getString();
}

void Button::setHeight( const float& height )
{
    // Setting size of the text

    text.setCharacterSize( App::getResFactor() * height );
    text.setScale( 1.0f/ App::getResFactor(), 1.0f / App::getResFactor());
    this->height = height;

    refreshTextActive();
}

float Button::getHeight() const
{
    return height;
}

void Button::setPos( const sf::Vector2f& position )
{
    text.setPosition( position );
    refreshTextActive();
}

sf::Vector2f Button::getPos() const
{
    return text.getPosition();
}

void Button::setOrigin( const Button::Origin& origin )
{
    this->origin = origin;
    if( origin == Button::Origin::TOPLEFT )
        text.setOrigin( 0.0f, 0.0f );
    else if( origin == Button::Origin::CENTER )
        text.setOrigin( text.getLocalBounds().width/2.0f, 0.0f );
    refreshTextActive();
}

Button::Origin Button::getOrigin() const
{
    return origin;
}

void Button::setFont( const sf::Font &font )
{
    text.setFont( font );
    refreshTextActive();
}

void Button::setColor( const sf::Color &color )
{
    text.setFillColor( color );
    refreshTextActive();
}

void Button::refreshTextActive()
{
    text_active = text;
    text_active.setString( "> "+ text.getString() );
    if( origin == Button::Origin::TOPLEFT )
        text_active.setOrigin( 0.0f, 0.0f );
    else if( origin == Button::Origin::CENTER )
        text_active.setOrigin( text_active.getLocalBounds().width/2.0f, 0.0f );
}

void Button::switchStatus()
{
    f_active = !f_active;
}

void Button::switchStatus( const bool& f_active )
{
    this->f_active = f_active;
}

bool Button::getStatus() const
{
    return f_active;
}
