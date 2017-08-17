////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef ROCKET_HPP
#define ROCKET_HPP

#include "Bullet.hpp"

/// BOOST - Serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
////////////////////////////////////////////////////////////

class Rocket : public Bullet
{
    /// BOOST - Serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Bullet>(*this);

        ar & target_ID;

        ar & ID;
        ar & max_quantity;
        ar & quantity;
    }
    ////////////////////////////////////////////////////////////
public:
    Rocket();
    ~Rocket();

    virtual void logic();

    virtual void create( bool reset = true );
    virtual void create( float velocity, float pos_x=0.0f, float pos_y=0.0f );

    void setTarget( Moveable* moveable );

    unsigned int getID() const { return ID; };

private:

    unsigned int target_ID;

    unsigned int ID;
    static unsigned int max_quantity;
    static unsigned int quantity;
};

#endif //ROCKET_HPP
