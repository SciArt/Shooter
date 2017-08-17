////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef ENEMYATTACKER_HPP
#define ENEMYATTACKER_HPP

#include "Enemy.hpp"

/// BOOST - Serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
////////////////////////////////////////////////////////////


class EnemyAttacker : public Enemy
{
    /// BOOST - Serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Enemy>(*this);
        ar & ID;
        ar & max_quantity;
        ar & quantity;

        ar & time_counter;
    }
    ////////////////////////////////////////////////////////////
public:
    EnemyAttacker();
    ~EnemyAttacker();

    virtual void create( bool reset = true );

    virtual void logic();

    void shoot();

    virtual unsigned int getID() const { return ID; }
private:
    sf::Int32 time_counter;

    unsigned int ID;
    static unsigned int max_quantity;
    static unsigned int quantity;
};

#endif // ENEMYATTACKER_HPP
