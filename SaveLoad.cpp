////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#include "SaveLoad.hpp"

BOOST_CLASS_EXPORT_GUID(Obstacle, "Obstacle")
BOOST_CLASS_EXPORT_GUID(Enemy, "Enemy")
BOOST_CLASS_EXPORT_GUID(EnemyAttacker, "EnemyAttacker")
BOOST_CLASS_EXPORT_GUID(EnemyAvoider, "EnemyAvoider")
BOOST_CLASS_EXPORT_GUID(Rocket, "Rocket")
BOOST_CLASS_EXPORT_GUID(Bullet, "Bullet")
BOOST_CLASS_EXPORT_GUID(Player, "Player")

void SaveLoad::Save()
{
    try
    {
        std::ofstream ofs("save.txt");
        boost::archive::text_oarchive oa(ofs);
        oa << Board::p_this;
        oa << Statistics::p_this;
    }
    catch(...)
    {
        std::cerr << "Saving game error.\n";
    }
}

void SaveLoad::Load()
{
    std::stringstream current_game_save;
    boost::archive::text_oarchive tmp_iarchive(current_game_save);
    tmp_iarchive << Board::p_this;
    tmp_iarchive << Statistics::p_this;
    try
    {
        Board::close();
        Statistics::close();
        {
        std::ifstream ifs("save.txt");
        boost::archive::text_iarchive ia(ifs);
        ia >> Board::p_this;
        ia >> Statistics::p_this;
        }
        Board::reload();
    }
    catch(...)
    {
        std::cerr << "Loading game error.\n";

        try
        {
            boost::archive::text_iarchive tmp_oarchive(current_game_save);
            tmp_oarchive >> Board::p_this;
            tmp_oarchive >> Statistics::p_this;
            Board::reload();
            std::cerr << "Game restored successfully.\n";
        }
        catch(...)
        {
            std::cerr << "FATAL ERROR: Failed to restore game.\n";
        }
    }
}
