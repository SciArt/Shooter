////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "SFML/Graphics.hpp"
#include "SaveLoad.hpp"

/// BOOST - Serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
////////////////////////////////////////////////////////////

// Singleton
class Statistics
{
    friend class SaveLoad;
    /// BOOST - Serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & scores;
        ar & moveables_destroyed;
        ar & bullets_shooted;
        ar & time_played; // ?
    }
    ////////////////////////////////////////////////////////////
public:
    ~Statistics();

    static bool init();

    static void reset();

    static void close();

    static void addScores( unsigned int add = 1 )
            { p_this->scores += add; }

    static void addMoveablesDestroyed( unsigned int add = 1 )
            { p_this->moveables_destroyed += add; }

    static void addBulletsShooted( unsigned int add = 1 )
            { p_this->bullets_shooted += add; }

    static void addTimePlayed( sf::Int32 add )
            { p_this->time_played += add; }

    static unsigned int getScores()
            { return p_this->scores; }

    static unsigned int getMoveablesDestroyed()
            { return p_this->moveables_destroyed; }

    static unsigned int getBulletsShooted()
            { return p_this->bullets_shooted; }

    static float getTimePlayed()
            { return p_this->time_played/1000.0f; }


private:
    Statistics();

    static Statistics* p_this;

    unsigned int scores;
    unsigned int moveables_destroyed;
    unsigned int bullets_shooted;
    sf::Int32 time_played;
    //sf::Clock clock;
};

#endif // STATISTICS_HPP
