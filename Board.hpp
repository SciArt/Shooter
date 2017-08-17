////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef BOARD_HPP
#define BOARD_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include "Track.hpp"

#include "Player.hpp"

#include "SimpleText.hpp"

#include "SaveLoad.hpp"

/// BOOST - Serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
////////////////////////////////////////////////////////////

class Board
{
    /// BOOST - Serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        for( int i = 0; i < 5; ++i )
            ar & track[i];

        ar & moveables_list;

        ar & player;

        ar & f_auto_generating;
    }
    ////////////////////////////////////////////////////////////

    friend class SaveLoad;
    friend class EnemyAvoider;
public:
    ~Board();

    static bool init();
    static void close();

    static void draw();

    static void logic();

    static void create();
    static void reload();

    static bool addObstacle( sf::Vector2f position );
    static bool addEnemy( sf::Vector2f position );
    static bool addEnemyAttacker( sf::Vector2f position );
    static bool addEnemyAvoider( sf::Vector2f position );

    static void addMoveable( Moveable* moveable );

    static Moveable* getMoveable( unsigned int ID );

    static const Moveable* getNextMoveable( unsigned int moveable_ID = 0 );
    static const Moveable* getPreviousMoveable( unsigned int moveable_ID = 0 );

    static bool deleteMoveable( Moveable* moveable );
    static bool deleteMoveable( unsigned int moveable_ID );
    static bool deleteMoveable( std::list<Moveable*>::iterator it );
    static void deleteAllMoveables();

    static Moveable* checkCollision( Moveable* moveable );
    static Moveable* checkCollision( std::list<Moveable*>::iterator it );

    static bool f_auto_generating;

    static Moveable* searchForNearestMoveable( Moveable* moveable );

    static float distance(sf::Vector2f a, sf::Vector2f b);

    //template<class type_of_moveable>
    static Bullet* searchForNearestBullet( Moveable* moveable );

    Track track[5]; /// < Array with tracks

private:
    Board();

    static Board* p_this;

    std::list<Moveable*> moveables_list; /// < List with moveables in the track

    ////////////////////////////////////////////////////////////
    /// \brief Automaticly generates random moveables
    ///
    ////////////////////////////////////////////////////////////
    static void generateMoveablesAuto();

    sf::Clock trigger; /// < Clock for auto generating moveables


    Player player;

    SimpleText scores;
    SimpleText moveables_destroyed;
    SimpleText bullets_shooted;
    SimpleText time_played;
    SimpleText health_left;
};

#endif // BOARD_HPP
