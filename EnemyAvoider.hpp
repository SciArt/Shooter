////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef ENEMYAVOIDER_HPP
#define ENEMYAVOIDER_HPP

#include "Enemy.hpp"

class EnemyAvoider : public Enemy
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
    }
    ////////////////////////////////////////////////////////////
public:
    EnemyAvoider();
    ~EnemyAvoider();

    virtual void create( bool reset = true );
    virtual void logic();

    virtual unsigned int getID() const { return ID; }

private:
    unsigned int ID;
    static unsigned int max_quantity;
    static unsigned int quantity;
};

#endif // ENEMYAVOIDER_HPP
