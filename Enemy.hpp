////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef ENEMY_HPP
#define ENEMY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Moveable.hpp"

/// BOOST - Serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
////////////////////////////////////////////////////////////

class Enemy : public Moveable
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
    }
    ////////////////////////////////////////////////////////////

public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor with counter
    ///
    ////////////////////////////////////////////////////////////
    Enemy();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor with counter
    ///
    ////////////////////////////////////////////////////////////
    ~Enemy();

    ////////////////////////////////////////////////////////////
    /// \brief Creating enemy, simply setting texture
    ///
    ////////////////////////////////////////////////////////////
    virtual void create( bool reset = true );

    virtual void logic();

    ////////////////////////////////////////////////////////////
    /// \brief Return unique ID of Enemy
    ///
    ////////////////////////////////////////////////////////////
    virtual unsigned int getID() const;
protected:
    float velocity;

private:

    unsigned int ID;
    static unsigned int max_quantity;
    static unsigned int quantity;
};

#endif // ENEMY_HPP