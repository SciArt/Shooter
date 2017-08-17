////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef MOVEABLE_HPP
#define MOVEABLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <iostream>

/// BOOST - Serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
////////////////////////////////////////////////////////////

class Moveable
{
    /// BOOST - Serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & sprite; /// < Sprite of the moveable
        ar & collision_damage;
        ar & health;
        ar & track_ID;
        ar & ID;
        ar & max_quantity;
        ar & quantity;
    }
    ////////////////////////////////////////////////////////////

public:
    ////////////////////////////////////////////////////////////
    /// \brief  Constructor, sets scale and unique parameters
    ///
    ////////////////////////////////////////////////////////////
    Moveable();

    ////////////////////////////////////////////////////////////
    /// \brief  Virtual destructor, sets unique parameters
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Moveable();

    ////////////////////////////////////////////////////////////
    /// \brief  Return reference to sprite
    ///
    ////////////////////////////////////////////////////////////
    sf::Sprite& getSprite();

    ////////////////////////////////////////////////////////////
    /// \brief  Get position of the moveable
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f getPosition() const;

    sf::Vector2f getPositionCenter() const;

    sf::Vector2f getPositionTopCenter() const;

    sf::Vector2f getPositionCenterRelative() const;

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

    ////////////////////////////////////////////////////////////
    /// \brief  Check if moveable is in collision with another moveable
    /// Doesn't work without texture.
    ///
    /// \param  position_y  The coord of top edge of moveable
    ///
    ////////////////////////////////////////////////////////////
    bool checkCollision( const float position_y ) const;

    virtual bool checkCollision( Moveable* moveable );

    ////////////////////////////////////////////////////////////
    /// \brief  Virtual function create. Depends on moveable.
    ///
    ////////////////////////////////////////////////////////////
    virtual void create( bool reset = true ) = 0;

    virtual void logic(){}
    virtual void causeDamage( unsigned int damage ){health-=damage;}

    float getWidth() const;

    float getHeight() const;

    int getCollisionDamage(){ return collision_damage; }
    int getHealth(){ return health; }

    int getTrackID() const { return track_ID; }
    void setTrackID( int track_ID ){ this->track_ID = track_ID; }
    void updateTrackID();

    ////////////////////////////////////////////////////////////
    /// \brief  Return unique ID of the moveable.
    ///
    ////////////////////////////////////////////////////////////
    unsigned int getID() const;

protected:
    sf::Sprite sprite; /// < Sprite of the moveable
    int collision_damage;
    int health;
    int track_ID;

    //float pos_x; float pos_y;
private:
    unsigned int ID;
    static unsigned int max_quantity;
    static unsigned int quantity;
};

//BOOST_CLASS_EXPORT_GUID(Moveable, "Moveable")

#endif // MOVEABLE_HPP
