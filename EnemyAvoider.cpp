////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#include "EnemyAvoider.hpp"
#include "Board.hpp"
#include "App.hpp"
#include "Bullet.hpp"
#include "Moveable.hpp"

unsigned int EnemyAvoider::max_quantity = 0;
unsigned int EnemyAvoider::quantity = 0;

EnemyAvoider::EnemyAvoider()
{
    ID = ++max_quantity;
    ++quantity;
    std::cout << "    EnemyAvoider["<< ID <<"] has been created. \n";

    velocity = 1.5f;
}

EnemyAvoider::~EnemyAvoider()
{
    --quantity;
    std::cout << "    EnemyAvoider["<< ID <<"] has been destroyed. \n";
}


void EnemyAvoider::create( bool reset )
{
    sprite.setTexture( InGame::getTexture( InGame::TexName::ENEMY_AVOIDER ) );
}

void EnemyAvoider::logic()
{
    Bullet* target = Board::searchForNearestBullet( this );

    if( target )
    {
        sf::Vector2f target_position = target->getPosition();

        // Bullet is flying up
        if( (0.0f <= target->getSprite().getRotation() && target->getSprite().getRotation() <= 90.0f) ||
            (270.0f <= target->getSprite().getRotation() && target->getSprite().getRotation() <= 360.0f ) )
        {
            if( target->velocity > Board::p_this->track[target->getTrackID()].speed && target->getPosition().y >= getPosition().y )
            {
                target->setPosition( target_position.x, getPosition().y );
                if( checkCollision( target ) )
                {
                    if( target->getPositionCenter().x < getPositionCenter().x )
                    {
                        sprite.move( velocity*App::getElapsedTime()/1000.0f, 0.0f );
                    }
                    else
                    {
                        sprite.move( -velocity*App::getElapsedTime()/1000.0f, 0.0f );
                    }

                    if( getPosition().x < InGame::board_begin )
                    {
                        setPosition( InGame::board_begin , getPosition().y );
                    }
                    if( getPosition().x > InGame::board_end - getWidth() )
                    {
                        setPosition( InGame::board_end - getWidth(), getPosition().y );
                    }
                }
            }
        }
        else // Bullet is flying down
        {
            if( target->velocity + Board::p_this->track[target->getTrackID()].speed > 0 && target->getPosition().y < getPosition().y )
            {
                target->setPosition( target_position.x, getPosition().y );
                if( checkCollision( target ) )
                {
                    if( target->getPositionCenter().x < getPositionCenter().x )
                    {
                        sprite.move( velocity*App::getElapsedTime()/1000.0f, 0.0f );
                    }
                    else
                    {
                        sprite.move( -velocity*App::getElapsedTime()/1000.0f, 0.0f );
                    }

                    if( getPosition().x < InGame::board_begin )
                    {
                        setPosition( InGame::board_begin , getPosition().y );
                    }
                    if( getPosition().x > InGame::board_end - getWidth() )
                    {
                        setPosition( InGame::board_end - getWidth(), getPosition().y );
                    }
                }
            }
        }
        target->setPosition( target_position );
    }
    updateTrackID();
}
