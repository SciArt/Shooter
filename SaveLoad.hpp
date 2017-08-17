////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef SAVELOAD_HPP
#define SAVELOAD_HPP

#include "InGame.hpp"
#include "Statistics.hpp"
#include "Rocket.hpp"
#include "Bullet.hpp"
#include "EnemyAttacker.hpp"
#include "EnemyAvoider.hpp"

#include <sstream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/export.hpp>
#include <exception>

// PROBLEM - rozróżnianie typów moveable

class SaveLoad
{
public:
    static void Save();

    static void Load();

private:

};

#endif // SAVELOAD_HPP
