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
#include "Board.hpp"

#include "App.hpp"
#include "InGame.hpp"
#include "Statistics.hpp"
#include "Gameover.hpp"
#include "EnemyAttacker.hpp"
#include "EnemyAvoider.hpp"
#include <iostream>

Board* Board::p_this = nullptr;
bool Board::f_auto_generating = true;

Board::Board()
{
    moveables_list.clear();
    std::cout << "Board has been created.\n";
}

Board::~Board()
{
    deleteAllMoveables();
    std::cout << "Board has been destroyed.\n";
}

bool Board::init()
{
    static bool f_initialized = false;
    if( f_initialized )
        return false;

    p_this = new Board;
    if( p_this != nullptr )
        return true;
    else
        return false;
}

void Board::close()
{
    deleteAllMoveables();
    delete p_this;
}

void Board::create()
{
    for( int i = 0; i < 5; ++i )
    {
        if( i%2 == 0 )
            p_this->track[i].create( i );
        else
            p_this->track[i].create( i );
    }
    p_this->player.create();

    // STATISTICS
    p_this->scores.create(              "scores:\n" + std::to_string( Statistics::getScores() ),
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -4.5 ), sf::Color::White, App::getFont() );
    p_this->moveables_destroyed.create(   "moveables destroyed:\n" + std::to_string( Statistics::getMoveablesDestroyed() ),
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -3.8 ), sf::Color::White, App::getFont() );
    p_this->bullets_shooted.create(   "bullets shooted:\n" + std::to_string( Statistics::getBulletsShooted() ),
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -3.1 ), sf::Color::White, App::getFont() );
    p_this->time_played.create(         "time played:\n" + std::to_string( Statistics::getTimePlayed()) + "sec",
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -2.4 ), sf::Color::White, App::getFont() );
    p_this->health_left.create(         "player health:\n" + std::to_string( p_this->player.getHealth() ),
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -1.7 ), sf::Color::White, App::getFont() );

    p_this->trigger.restart();
}

void Board::reload()
{
    for( int i = 0; i < 5; ++i )
    {
        if( i%2 == 0 )
            p_this->track[i].create( i );
        else
            p_this->track[i].create( i );
    }
    p_this->player.create( false );

    // STATISTICS
    p_this->scores.create(              "scores:\n" + std::to_string( Statistics::getScores() ),
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -4.5 ), sf::Color::White, App::getFont() );
    p_this->moveables_destroyed.create(   "moveables destroyed:\n" + std::to_string( Statistics::getMoveablesDestroyed() ),
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -3.8 ), sf::Color::White, App::getFont() );
    p_this->bullets_shooted.create(   "bullets shooted:\n" + std::to_string( Statistics::getBulletsShooted() ),
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -3.1 ), sf::Color::White, App::getFont() );
    p_this->time_played.create(         "time played:\n" + std::to_string( Statistics::getTimePlayed()) + "sec",
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -2.4 ), sf::Color::White, App::getFont() );
    p_this->health_left.create(         "player health:\n" + std::to_string( p_this->player.getHealth() ),
        0.3f, sf::Vector2f( InGame::board_end + 0.2 , -1.7 ), sf::Color::White, App::getFont() );

    // Reload moveables
    for( std::list<Moveable*>::iterator it = p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
            (*it)->create();

    p_this->trigger.restart();
}

void Board::draw()
{
    for( int i = 0; i < 5; ++i )
        p_this->track[i].draw();

    p_this->player.draw();

    for( std::list<Moveable*>::iterator it = p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
        App::draw( (*it)->getSprite() );

    if( !InGame::isPaused() )
    {
        // Drawing all statistics
        App::draw( p_this->scores );
        App::draw( p_this->moveables_destroyed );
        App::draw( p_this->bullets_shooted );
        App::draw( p_this->time_played );
        App::draw( p_this->health_left );
    }
}

void Board::logic()
{
    /// If player died, situation after GAMEOVER
    if( p_this->player.getHealth() <= 0 )
    {
        deleteAllMoveables();
        p_this->player.reset();
    }

    /// Tracks update, moving moveables by track etc.
    for( int i = 0; i < 5; ++i )
    {
        p_this->track[i].logic( &p_this->player, p_this->moveables_list );
    }

    /// Moveables logic, collisions etc.
    for( std::list<Moveable*>::iterator it=p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
    {
        // Moveable logic
        (*it)->logic();

        (*it)->updateTrackID();

        // Checking down and up edge of board
        if( (*it)->getPosition().y >= 4.5 || (*it)->getPosition().y < (-4.5 - (*it)->getHeight()) )
        {
            (*it)->causeDamage( (*it)->getHealth() );
        }

        // Checking left and right edge of board
        if( (*it)->getPosition().x > InGame::board_end  || (*it)->getPosition().x < InGame::board_begin - (*it)->getWidth() )
        {
            (*it)->causeDamage( (*it)->getHealth() );
        }

        // Checking collisions
        Moveable* colliding_moveable = checkCollision( it );
        if( colliding_moveable != nullptr )
        {
            //if( dynamic_cast<Bullet*>(colliding_moveable) != nullptr || dynamic_cast<Bullet*>(*it) == nullptr )
            {
                (*it)->causeDamage( colliding_moveable->getCollisionDamage() );

                colliding_moveable->causeDamage( (*it)->getCollisionDamage() );

                Statistics::addScores();
            }
        }
    }

    /// Collisions with player
    Moveable* colliding_moveable = checkCollision( &p_this->player );
    if( colliding_moveable != nullptr )
    {
        p_this->player.causeDamage( colliding_moveable->getCollisionDamage() );
        colliding_moveable->causeDamage( colliding_moveable->getHealth() );

        Statistics::addScores();
    }

    /// Checking moveables health
    for( std::list<Moveable*>::iterator it=p_this->moveables_list.begin(); it != p_this->moveables_list.end(); )
    {
        if( (*it)->getHealth() <= 0 )
        {
            deleteMoveable( it++ );
            Statistics::addMoveablesDestroyed();
        }
        else
            ++it;
    }

    /// Checking player's health
    if( p_this->player.getHealth() <= 0 && App::getStatus() == App::Status::INGAME )
    {
        App::setStatus( App::Status::GAMEOVER );
        Gameover::init();
    }

    /// Generating new moveables
    if( f_auto_generating )
        generateMoveablesAuto();

    /// Player controll
    p_this->player.logic();

    // STATISTICS
    p_this->time_played.setString( "time played:\n" + std::to_string( Statistics::getTimePlayed()) + "sec" );
    p_this->bullets_shooted.setString( "bullets shooted:\n" + std::to_string( Statistics::getBulletsShooted() ) );
    p_this->scores.setString( "scores:\n" + std::to_string( Statistics::getScores() ) );
    p_this->moveables_destroyed.setString( "moveables destroyed:\n" + std::to_string( Statistics::getMoveablesDestroyed() ) );
    p_this->health_left.setString( "player health:\n" + std::to_string( p_this->player.getHealth() ));
}

void Board::generateMoveablesAuto()
{
    // If 1 sec elapsed
    if( p_this->trigger.getElapsedTime().asSeconds() > 1.0 )
    {
        // For each of the track
        for( int i = 0; i < 5; ++i )
        {
            // Randomly generating
            if( static_cast<double>(std::rand())/RAND_MAX < 0.25 )
            {
                if( static_cast<double>(std::rand())/RAND_MAX > 0.75 )
                    addObstacle
                    (
                        sf::Vector2f
                            (
                            InGame::board_begin + ( (InGame::track_width * i ) + (InGame::track_width - InGame::getTexture(InGame::OBSTACLE).getSize().x * 16.0/1920.0)/2.0 ) ,
                            -4.5 - InGame::getTexture(InGame::OBSTACLE).getSize().x * 16.0/1920.0
                            )
                    );
                else
                    if( static_cast<double>(std::rand())/RAND_MAX < 0.33 )
                    {
                        addEnemy
                        (
                                sf::Vector2f
                                (
                                InGame::board_begin + ( (InGame::track_width * i ) + (InGame::track_width - InGame::getTexture(InGame::ENEMY).getSize().x * 16.0/1920.0)/2.0 ) ,
                                -4.5 - InGame::getTexture(InGame::ENEMY).getSize().x * 16.0/1920.0
                                )
                        );
                    }
                    else if( rand()%2 == 0 )
                    {
                        addEnemyAttacker
                        (
                                sf::Vector2f
                                (
                                InGame::board_begin + ( (InGame::track_width * i ) + (InGame::track_width - InGame::getTexture(InGame::ENEMY).getSize().x * 16.0/1920.0)/2.0 ) ,
                                -4.5 - InGame::getTexture(InGame::ENEMY).getSize().x * 16.0/1920.0
                                )
                        );
                    }
                    else
                    {
                        addEnemyAvoider
                        (
                                sf::Vector2f
                                (
                                InGame::board_begin + ( (InGame::track_width * i ) + (InGame::track_width - InGame::getTexture(InGame::ENEMY).getSize().x * 16.0/1920.0)/2.0 ) ,
                                -4.5 - InGame::getTexture(InGame::ENEMY).getSize().x * 16.0/1920.0
                                )
                        );
                    }
            }
        }

        // Clock restart
        p_this->trigger.restart();
    }
}

void Board::addMoveable( Moveable* moveable )
{
    p_this->moveables_list.push_back( moveable );
}

bool Board::addEnemy( sf::Vector2f position )
{
    p_this->moveables_list.push_back( new Enemy );

    // Set the position of the moveable and create it
    p_this->moveables_list.back()->create();
    p_this->moveables_list.back()->setPosition( position );
    p_this->moveables_list.back()->updateTrackID();

    if( checkCollision( p_this->moveables_list.back() ) )
    {
        deleteMoveable( --p_this->moveables_list.end() );
        return false;
    }

    return true;
}

bool Board::addEnemyAttacker( sf::Vector2f position )
{
    p_this->moveables_list.push_back( new EnemyAttacker );

    // Set the position of the moveable and create it
    p_this->moveables_list.back()->create();
    p_this->moveables_list.back()->setPosition( position );
    p_this->moveables_list.back()->updateTrackID();

    if( checkCollision( p_this->moveables_list.back() ) )
    {
        deleteMoveable( --p_this->moveables_list.end() );
        return false;
    }

    return true;
}

bool Board::addEnemyAvoider( sf::Vector2f position )
{
    p_this->moveables_list.push_back( new EnemyAvoider );

    // Set the position of the moveable and create it
    p_this->moveables_list.back()->create();
    p_this->moveables_list.back()->setPosition( position );
    p_this->moveables_list.back()->updateTrackID();

    if( checkCollision( p_this->moveables_list.back() ) )
    {
        deleteMoveable( --p_this->moveables_list.end() );
        return false;
    }

    return true;
}

bool Board::addObstacle( sf::Vector2f position )
{
    p_this->moveables_list.push_back( new Obstacle );

    // Set the position of the moveable and create it
    p_this->moveables_list.back()->create();
    p_this->moveables_list.back()->setPosition( position );
    p_this->moveables_list.back()->updateTrackID();

    if( checkCollision( p_this->moveables_list.back() ) )
    {
        deleteMoveable( --p_this->moveables_list.end() );
        return false;
    }

    return true;
}

const Moveable* Board::getNextMoveable( unsigned int moveable_ID )
{
    if( p_this->moveables_list.size() == 0 )
        return nullptr;

    std::list<Moveable*>::iterator it = p_this->moveables_list.begin();
    while( it != p_this->moveables_list.end() )
    {
        if( (*it)->getID() == moveable_ID )
            break;
        ++it;
    }

    if( (*it) == p_this->moveables_list.back() )
        return p_this->moveables_list.front();
    else
        return *(++it);
}

const Moveable* Board::getPreviousMoveable( unsigned int moveable_ID )
{
    if( p_this->moveables_list.size() == 0 )
        return nullptr;

    std::list<Moveable*>::iterator it = p_this->moveables_list.begin();
    while( it != p_this->moveables_list.end() )
    {
        if( (*it)->getID() == moveable_ID )
            break;
        ++it;
    }

    if( (*it) == p_this->moveables_list.front() )
        return p_this->moveables_list.back();
    else
        return *(--it);
}

bool Board::deleteMoveable( Moveable* moveable )
{
    for( std::list<Moveable*>::iterator it = p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
    {
        if( (*it) == moveable )
        {
            delete (*it);
            p_this->moveables_list.erase( it );
            return true;
        }
    }
    return false;
}

bool Board::deleteMoveable( unsigned int moveable_ID )
{
    for( std::list<Moveable*>::iterator it = p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
    {
        if( (*it)->getID() == moveable_ID )
        {
            delete (*it);
            (*it) = nullptr;
            p_this->moveables_list.erase( it );
            return true;
        }
    }
    return false;
}

bool Board::deleteMoveable( std::list<Moveable*>::iterator it )
{
    delete (*it);
    (*it) = nullptr;
    p_this->moveables_list.erase( it );
    return true;
}

void Board::deleteAllMoveables()
{
    for( std::list<Moveable*>::iterator it=p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
    {
        delete (*it);
        (*it) = nullptr;
    }
    p_this->moveables_list.clear();
}

Moveable* Board::checkCollision( Moveable* moveable )
{
    // Check if there is collision with some moveable in track
    for( std::list<Moveable*>::iterator it=p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
    {
        if( (*it) != moveable )
            if( (*it)->checkCollision( moveable ) )
                return (*it);
    }
    return nullptr;
}

Moveable* Board::checkCollision( std::list<Moveable*>::iterator it_begin )
{
    // Check if there is collision with some moveable in track
    for( std::list<Moveable*>::iterator it=it_begin; it != p_this->moveables_list.end(); ++it )
    {
        if( (*it) != (*it_begin) )
            if( (*it)->checkCollision( (*it_begin) ) )
                return (*it);
    }
    return nullptr;
}

Moveable* Board::getMoveable( unsigned int ID )
{
    for( std::list<Moveable*>::iterator it = p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
    {
        if( (*it)->getID() == ID )
        {
            return (*it);
        }
    }
    return nullptr;
}

Moveable* Board::searchForNearestMoveable( Moveable* moveable )
{
    Moveable* target = nullptr;
    for( std::list<Moveable*>::iterator it = p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
    {
        if( dynamic_cast<Bullet*>(*it) == nullptr )
        if( moveable != (*it) )
        {
            if( target == nullptr )
                target = (*it);
            else
            {
                if( distance( moveable->getPositionTopCenter(), (*it)->getPositionCenter() )
                    < distance( moveable->getPositionTopCenter(), target->getPositionCenter() ) )
                {
                    target = (*it);
                }
            }
        }
    }
    return target;
}

Bullet* Board::searchForNearestBullet( Moveable* moveable )
{
    Bullet* target = nullptr;
    for( std::list<Moveable*>::iterator it = p_this->moveables_list.begin(); it != p_this->moveables_list.end(); ++it )
    {
        //if( dynamic_cast<Bullet*>(*it) != nullptr )
        if( moveable != (*it) )
        {
            if( target == nullptr )
                target = dynamic_cast<Bullet*>(*it);
            else
            {
                if( distance( moveable->getPositionTopCenter(), (*it)->getPositionCenter() )
                    < distance( moveable->getPositionTopCenter(), target->getPositionCenter() ) )
                {
                    target = dynamic_cast<Bullet*>(*it);
                }
            }
        }
    }
    return target;
}

float Board::distance(sf::Vector2f a, sf::Vector2f b)
{
    return std::sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) );
}
