////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#include "EnemyAttacker.hpp"
#include "InGame.hpp"
#include "App.hpp"
#include "Bullet.hpp"
#include "Statistics.hpp"

unsigned int EnemyAttacker::max_quantity = 0;
unsigned int EnemyAttacker::quantity = 0;

EnemyAttacker::EnemyAttacker()
{
    ID = ++max_quantity;
    ++quantity;
    std::cout << "    EnemyAttacker["<< ID <<"] has been created. \n";

    time_counter = 0;
}

EnemyAttacker::~EnemyAttacker()
{
    --quantity;
    std::cout << "    EnemyAttacker["<< ID <<"] has been destroyed. \n";
}

void EnemyAttacker::create( bool reset )
{
    sprite.setTexture( InGame::getTexture( InGame::TexName::ENEMY_ATTACKER ) );
}

void EnemyAttacker::logic()
{
    time_counter += App::getElapsedTime();

    this->Enemy::logic();
    if( time_counter > 1000 )
    {
        time_counter = 0;
        if( static_cast<double>(std::rand())/RAND_MAX > 0.25 )
            shoot();
    }
}

void EnemyAttacker::shoot()
{
    Bullet* bullet;
    bullet = new Bullet;

    bullet->create( 2.0f );
    bullet->getSprite().setOrigin(bullet->getPositionCenterRelative());
    bullet->setPosition( sprite.getPosition().x + getWidth()/2.0f, sprite.getPosition().y + getHeight() );
    bullet->setRotation( 180 );

    bullet->setOwner( this );

    Board::addMoveable( bullet );

    Statistics::addBulletsShooted();
}
