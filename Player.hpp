////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Moveable.hpp"
#include <list>

class Bullet;

/// BOOST - Serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
////////////////////////////////////////////////////////////

class Player : public Moveable
{
    /// BOOST - Serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Moveable>(*this);
        ar & speed;
        ar & eye_color;

        ar & body;
        ar & nose_cone;
        ar & side_guns;
        ar & wings_guns;
        ar & eye;

        ar & weapon_selected;
    }
    ////////////////////////////////////////////////////////////
public:
    Player();
    ~Player();

    void create( bool reset = true );

    void logic();

    void reset();

    ////////////////////////////////////////////////////////////
    /// \brief  Set position of the moveable
    ///
    /// \param  position    As sf::Vector2f
    ///
    ////////////////////////////////////////////////////////////
    virtual void setPosition( const sf::Vector2f& position );

    ////////////////////////////////////////////////////////////
    /// \brief  Set position of the moveable
    ///
    /// \param  x   Position on X axis
    ///
    /// \param  y   Position on Y axis
    ///
    ////////////////////////////////////////////////////////////
    virtual void setPosition( const float x, const float y );

    void draw();

private:

    void shoot();

    enum PlayerWeapon
    {
    SINGLE,
    DUAL,
    ROCKET,
    END_OF_ENUM
    };

    PlayerWeapon weapon_selected;;

    float speed;

    sf::Sprite body;
    sf::Sprite nose_cone;
    sf::Sprite side_guns;
    sf::Sprite wings_guns;
    sf::Sprite eye;
    double eye_color;
};


#endif // PLAYER_HPP
