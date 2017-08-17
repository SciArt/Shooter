////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////


#ifndef TRACK_HPP
#define TRACK_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include "Moveable.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

#include <list>

/// BOOST - Serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/export.hpp>
////////////////////////////////////////////////////////////

class Track
{
    /// BOOST - Serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        //ar & moveables_list;
        //ar & sprite;
        ar & track_pos_id;
        ar & speed;

        ar & ID;
        ar & max_quantity;
        ar & quantity;
    }
    ////////////////////////////////////////////////////////////
public:
    ////////////////////////////////////////////////////////////
    /// \brief  Constructor, sets basic and unique params
    ///
    ////////////////////////////////////////////////////////////
    Track();

    ////////////////////////////////////////////////////////////
    /// \brief  Destructor, deletes all moveables from track
    ///
    ////////////////////////////////////////////////////////////
    ~Track();

    ////////////////////////////////////////////////////////////
    /// \brief  Create, set texture, scale, ID etc.
    ///
    ////////////////////////////////////////////////////////////
    void create( unsigned int id );

    ////////////////////////////////////////////////////////////
    /// \brief  Draw the track with all moveables
    ///
    ////////////////////////////////////////////////////////////
    void draw();

    ////////////////////////////////////////////////////////////
    /// \brief  Handle all the actions on the track, move moveables
    ///
    ////////////////////////////////////////////////////////////
    void logic( Player* player, std::list<Moveable*>& moveables_list );
    float speed; /// Speed of the track
private:

    sf::Sprite sprite; /// < Sprite of the track

    int track_pos_id; /// < Track position ID (1 of 5)



    unsigned int ID;
    static unsigned int max_quantity;
    static unsigned int quantity;
};

#endif // TRACK_HPP
