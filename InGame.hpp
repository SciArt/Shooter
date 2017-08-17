////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef INGAME_HPP
#define INGAME_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include "App.hpp"
#include "Board.hpp"
#include "Button.hpp"
#include "SimpleText.hpp"
#include "SaveLoad.hpp"

class InGame
{
friend class SaveLoad;
//friend class Rocket;
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ///
    ////////////////////////////////////////////////////////////
    ~InGame();

    ////////////////////////////////////////////////////////////
    /// \brief Initializing InGame part of application
    ///
    ////////////////////////////////////////////////////////////
    static bool init();

    ////////////////////////////////////////////////////////////
    /// \brief Drawing all in InGame part
    ///
    ////////////////////////////////////////////////////////////
    static void draw();

    ////////////////////////////////////////////////////////////
    /// \brief Handles of actions in InGame part
    ///
    ////////////////////////////////////////////////////////////
    static void logic();

    ////////////////////////////////////////////////////////////
    /// \brief Run InGame part of application
    ///
    ////////////////////////////////////////////////////////////
    //static void run();

    ////////////////////////////////////////////////////////////
    /// \brief Close InGame part of application
    ///
    ////////////////////////////////////////////////////////////
    static void close();

    ////////////////////////////////////////////////////////////
    /// \brief Enumeration of textures
    ///
    ////////////////////////////////////////////////////////////
    enum TexName
    {
        TRACK1,
        TRACK2,
        ENEMY,
        ENEMY_ATTACKER,
        ENEMY_AVOIDER,
        OBSTACLE,
        PLAYER_OUTLINE,
        PLAYER_BODY,
        PLAYER_NOSE_CONE,
        PLAYER_SIDE_GUNS,
        PLAYER_WINGS_GUNS,
        PLAYER_EYE,
        BULLET,
        ROCKET,

        END_OF_ENUM
    };

    ////////////////////////////////////////////////////////////
    /// \brief Return reference on desired texture
    ///
    ////////////////////////////////////////////////////////////
    static const sf::Texture& getTexture( TexName tex_name );

    ////////////////////////////////////////////////////////////
    /// \brief Check if game is Paused
    ///
    ////////////////////////////////////////////////////////////
    static bool isPaused();

    ////////////////////////////////////////////////////////////
    /// \brief Set of const, sizes and coordinates
    ///
    ////////////////////////////////////////////////////////////
    static const float track_width; /// < Width of moveable
    static const float track_height; /// < Height of moveable
    static const float board_begin; /// < Begin of the board
    static const float board_end; /// < End of the board

private:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    ////////////////////////////////////////////////////////////
    InGame();

    static InGame * p_this; /// < The pointer to the only object from this class

    bool f_pause; /// < True if game is paused

    sf::Texture texture[TexName::END_OF_ENUM]; /// < Array of textures

    SimpleText info; /// < Text saying "Press escape for more options?"

    Button resume; /// < Resume the game
    Button save;
    Button load;
    Button exit; /// < Exit to main menu

    ////////////////////////////////////////////////////////////
    /// \brief  All actions when Key Up is released
    ///
    ////////////////////////////////////////////////////////////
    static void ifKeyUp();

    ////////////////////////////////////////////////////////////
    /// \brief  All actions when Key Down is released
    ///
    ////////////////////////////////////////////////////////////
    static void ifKeyDown();

    ////////////////////////////////////////////////////////////
    /// \brief  All actions when Key Return is released
    ///
    ////////////////////////////////////////////////////////////
    static void ifKeyReturn();

    ////////////////////////////////////////////////////////////
    /// \brief  All actions when Key Escape is released
    ///
    ////////////////////////////////////////////////////////////
    static void ifKeyEscape();


    ////////////////////////////////////////////////////////////
    /// DEVELOPER OPTIONS
    ////////////////////////////////////////////////////////////

    SimpleText developer_options; /// < Text saying "Developer options:"

    ////////////////////////////////////////////////////////////
    /// Buttons in developer options section
    ////////////////////////////////////////////////////////////
    Button auto_generating;
    Button create_enemy;
    Button create_obstacle;
    Button delete_selected;
    Button delete_all;

    ////////////////////////////////////////////////////////////
    /// \brief  Creating Enemy
    ///
    ////////////////////////////////////////////////////////////
    static void createEnemy();

    ////////////////////////////////////////////////////////////
    /// \brief  Creating Obstacle
    ///
    ////////////////////////////////////////////////////////////
    static void createObstacle();

    ////////////////////////////////////////////////////////////
    /// \brief  Actions when selection is required
    ///
    ////////////////////////////////////////////////////////////
    static void useSelection();

    ////////////////////////////////////////////////////////////
    /// All stuff for selecting
    ////////////////////////////////////////////////////////////
    sf::Sprite selection; /// < Viewfinder for selection
    sf::Texture tex_selection; /// < Texture od viewfinder
    unsigned int track_id_selection; /// < ID of selected track
    unsigned int moveable_id_selection; /// < ID f selected moveable

    ////////////////////////////////////////////////////////////
    /// \brief  Upadting selection, getting new object to snap
    /// Getting the next one (lower positioned)
    ////////////////////////////////////////////////////////////
    static void updateDeleteSelectionNext();

    ////////////////////////////////////////////////////////////
    /// \brief  Upadting selection, getting new object to snap
    /// Getting the previous one (higher positioned)
    ////////////////////////////////////////////////////////////
    static void updateDeleteSelectionPrevious();

    Button info_selection; /// < Text with instructions for selection
    Button info_operation; /// < Text with info about status of current operation

    bool f_selection; /// < True if selection is active
    bool f_create_enemy; /// < True if user wants to create enemy
    int type_of_enemy_to_create;
    bool f_create_obstacle; /// < True if user wants to create obstacle
    bool f_delete_selected; /// < True if user wants to delete selection

    //SideBar side_bar_left;
    //SideBar side_bar_right;
};

#endif // INGAME_HPP