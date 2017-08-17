////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#include "Statistics.hpp"
#include <iostream>


Statistics* Statistics::p_this = nullptr;

Statistics::Statistics()
{

}

Statistics::~Statistics()
{

}

bool Statistics::init()
{
    p_this = new Statistics;
    if( p_this == nullptr )
        return false;

    reset();

    return true;
}

void Statistics::close()
{
    if( p_this != nullptr )
    {
        delete p_this;
        p_this = nullptr;
    }
}

void Statistics::reset()
{
    p_this->scores = 0;
    p_this->moveables_destroyed = 0;
    p_this->bullets_shooted = 0;
    p_this->time_played = 0;
}
