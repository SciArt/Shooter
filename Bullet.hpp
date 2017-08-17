////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef BULLET_HPP
#define BULLET_HPP

#include "Moveable.hpp"

/// BOOST - Serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
////////////////////////////////////////////////////////////

class Bullet : public Moveable
{
    /// BOOST - Serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Moveable>(*this);
        ar & ID;
        ar & max_quantity;
        ar & quantity;

        ar & velocity;

        ar & owner_ID;

        ar & angle;
    }
    ////////////////////////////////////////////////////////////
public:
    Bullet();
    ~Bullet();

    virtual void create( bool reset = true );
    virtual void create( float velocity, float pos_x=0.0f, float pos_y=0.0f );
    virtual void logic();

    void setOwner( Moveable* moveable );
    virtual bool checkCollision( Moveable* moveable );

    void setRotation( float angle );

    ////////////////////////////////////////////////////////////
    /// \brief Return unique ID
    ///
    ////////////////////////////////////////////////////////////
    unsigned int getID() const { return ID; };

    float velocity;

protected:
    float angle;

private:

    int owner_ID;

    unsigned int ID;
    static unsigned int max_quantity;
    static unsigned int quantity;
};


#endif // BULLET_HPP
