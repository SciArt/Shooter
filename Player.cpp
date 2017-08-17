////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#include "Player.hpp"

#include "App.hpp"
#include "InGame.hpp"
#include "Board.hpp"
#include "Bullet.hpp"
#include "Bullet.hpp"
#include "Rocket.hpp"
#include "SFML/Graphics.hpp"

#include <iostream>
#include "Statistics.hpp"

#include <typeinfo>

Player::Player()
{
    body.setScale( 16.0f/1920.0f , 16.0f/1920.0f );
    nose_cone.setScale( 16.0f/1920.0f , 16.0f/1920.0f );
    side_guns.setScale( 16.0f/1920.0f , 16.0f/1920.0f );
    wings_guns.setScale( 16.0f/1920.0f , 16.0f/1920.0f );
    eye.setScale( 16.0f/1920.0f , 16.0f/1920.0f );

    weapon_selected = PlayerWeapon::SINGLE;

    std::cout << "Player has been created.\n";
}

Player::~Player()
{
    std::cout << "Player has been destroyed.\n";
}

void Player::setPosition( const sf::Vector2f& position )
{
    sprite.setPosition( position );
    body.setPosition( sprite.getPosition() );
    nose_cone.setPosition( sprite.getPosition() );
    side_guns.setPosition( sprite.getPosition() );
    wings_guns.setPosition( sprite.getPosition() );
    eye.setPosition( sprite.getPosition() );
}

void Player::setPosition( const float x, const float y )
{
    sprite.setPosition( x, y );
    body.setPosition( sprite.getPosition() );
    nose_cone.setPosition( sprite.getPosition() );
    side_guns.setPosition( sprite.getPosition() );
    wings_guns.setPosition( sprite.getPosition() );
    eye.setPosition( sprite.getPosition() );
}

void Player::reset()
{
    track_ID = 2;
    sprite.setPosition(
        InGame::board_begin + ( InGame::track_width * track_ID ) + (InGame::track_width-getWidth())/2.0,
        4.5f - getHeight() );
    body.setPosition( sprite.getPosition() );
    nose_cone.setPosition( sprite.getPosition() );
    side_guns.setPosition( sprite.getPosition() );
    wings_guns.setPosition( sprite.getPosition() );
    eye.setPosition( sprite.getPosition() );
    speed = 2.5;
    health = 5;

    eye_color = 0.0;
    weapon_selected = Player::PlayerWeapon::SINGLE;

}

void Player::create( bool reset )
{
    std::cout << "Player::create( " << reset << " )\n";
    sprite.setTexture( InGame::getTexture( InGame::TexName::PLAYER_OUTLINE ) );

    body.setTexture( InGame::getTexture( InGame::TexName::PLAYER_BODY ) );
    body.setColor( sf::Color( 255, 255, 255) );

    nose_cone.setTexture( InGame::getTexture( InGame::TexName::PLAYER_NOSE_CONE ) );
    nose_cone.setColor( sf::Color( 0,0,0 ) );

    side_guns.setTexture( InGame::getTexture( InGame::TexName::PLAYER_SIDE_GUNS ) );
    side_guns.setColor( sf::Color( 0,0,0 ) );

    wings_guns.setTexture( InGame::getTexture( InGame::TexName::PLAYER_WINGS_GUNS ) );
    wings_guns.setColor( sf::Color( 0,0,0 ) );

    eye.setTexture( InGame::getTexture( InGame::TexName::PLAYER_EYE ) );
    eye.setColor( sf::Color( 0,0,0 ) );

    if( reset )
        this->reset();
}

void Player::draw()
{
    App::draw( body );
    App::draw( nose_cone );
    App::draw( side_guns );
    App::draw( wings_guns );
    App::draw( eye );
    App::draw( sprite );
}

void Player::logic()
{
    if( App::isKeyReleased( sf::Keyboard::Key::LShift ) )
    {
        if( weapon_selected == PlayerWeapon::SINGLE )
            weapon_selected = PlayerWeapon::DUAL;
        else if( weapon_selected == PlayerWeapon::DUAL )
            weapon_selected = PlayerWeapon::ROCKET;
        else if( weapon_selected == PlayerWeapon::ROCKET )
            weapon_selected = PlayerWeapon::SINGLE;
    }

    if( App::isKeyReleased( sf::Keyboard::Num1 ) )
        weapon_selected = PlayerWeapon::SINGLE;
    if( App::isKeyReleased( sf::Keyboard::Num2 ) )
        weapon_selected = PlayerWeapon::DUAL;
    if( App::isKeyReleased( sf::Keyboard::Num3 ) )
        weapon_selected = PlayerWeapon::ROCKET;


    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Left ) )
    {
        setPosition( getPosition().x - App::getElapsedTime()/1000.0 * speed, getPosition().y );
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Right ) )
    {
        setPosition( getPosition().x + App::getElapsedTime()/1000.0 * speed, getPosition().y );
    }

    // SETTING TRACK_ID

    track_ID = static_cast<int>( (getPosition().x + (getWidth()/2.0f) - InGame::board_begin) / InGame::track_width  );

    // CHECKING FOR BOARD EDGES
    if( getPosition().x < InGame::board_begin )
    {
        setPosition( InGame::board_begin , getPosition().y );
    }
    if( getPosition().x > InGame::board_end - getWidth() )
    {
        setPosition( InGame::board_end - getWidth(), getPosition().y );
    }

    if( App::isKeyReleased( sf::Keyboard::Space ) )
    {
        shoot();
    }

    eye_color -= App::getElapsedTime()/1000.0 * 255.0/2.0;
    if( eye_color < 0.0 ) eye_color = 0.0;
    eye.setColor( sf::Color(static_cast<int>(eye_color), 0 , 0) );

    side_guns.setColor( sf::Color(static_cast<int>(eye_color), 0 , 0) );
    wings_guns.setColor( sf::Color(static_cast<int>(eye_color), 0 , 0) );
    nose_cone.setColor( sf::Color(static_cast<int>(eye_color), 0 , 0) );
}

void Player::shoot()
{
    if( weapon_selected == PlayerWeapon::SINGLE )
    {
        Bullet* bullet;

        bullet = new Bullet;

        bullet->create( 6.0f );
        bullet->getSprite().setOrigin(bullet->getPositionCenterRelative());
        bullet->setPosition( sprite.getPosition().x + getWidth()/2.0f, sprite.getPosition().y );
        bullet->setRotation( 0 );

        bullet->setOwner( this );

        Board::addMoveable( bullet );

        eye_color = 255;

        Statistics::addBulletsShooted();
    }
    else if( weapon_selected == PlayerWeapon::DUAL )
    {
        Bullet* bullet;


        bullet = new Bullet;

        bullet->create( 6.0f );
        bullet->getSprite().setOrigin(bullet->getPositionCenterRelative());
        bullet->setPosition( sprite.getPosition().x + 3.0*getWidth()/4.0, sprite.getPosition().y );
        bullet->setRotation( 15 );

        bullet->setOwner( this );

        Board::addMoveable( bullet );


        bullet = new Bullet;

        bullet->create( 6.0f );
        bullet->getSprite().setOrigin( bullet->getPositionCenterRelative() );
        bullet->setPosition( sprite.getPosition().x + getWidth()/4.0, sprite.getPosition().y );
        bullet->setRotation( -15 );

        bullet->setOwner( this );

        Board::addMoveable( bullet );


        eye_color = 255;

        Statistics::addBulletsShooted(2);
    }
    else if( weapon_selected == PlayerWeapon::ROCKET )
    {
        Rocket* bullet = new Rocket;

        bullet->create( 6.0f );
        bullet->getSprite().setOrigin(bullet->getPositionCenterRelative());
        bullet->setPosition( getPosition().x + getWidth()/2.0f, getPosition().y );

        bullet->setOwner( this );

        Board::addMoveable( bullet );

        eye_color = 255;

        Statistics::addBulletsShooted();
    }
}

