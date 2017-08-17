////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr. inż Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "InGame.hpp"
#include "Button.hpp"
#include "Moveable.hpp"

#include <iostream>

InGame * InGame::p_this = nullptr;
const float InGame::track_width = (16.0f/1920.0f) * 200.0f;
const float InGame::track_height = 9.0f/8.0f;
const float InGame::board_begin = -8.0f + ((16.0f/1920.0f) * 460.0f);
const float InGame::board_end = InGame::board_begin + 5*(InGame::track_width);


InGame::InGame()
{
    f_pause = false;
}

InGame::~InGame()
{
}

const sf::Texture& InGame::getTexture( TexName tex_name )
{
    return (p_this->texture[tex_name]);
}

bool InGame::init()
{
    p_this = new InGame;
    if( !p_this )
        return false;

    // Loading textures

    if( !p_this->texture[TexName::TRACK1].loadFromFile( "track1.png" ) )
        return false;

    if( !p_this->texture[TexName::TRACK2].loadFromFile( "track2.png" ) )
        return false;

    if( !p_this->texture[TexName::ENEMY].loadFromFile( "enemy.png" ) )
        return false;
    if( !p_this->texture[TexName::ENEMY_ATTACKER].loadFromFile( "enemy_attacker.png" ) )
        return false;
    if( !p_this->texture[TexName::ENEMY_AVOIDER].loadFromFile( "enemy_avoider.png" ) )
        return false;

    if( !p_this->texture[TexName::OBSTACLE].loadFromFile( "obstacle.png" ) )
        return false;

    if( !p_this->texture[TexName::PLAYER_OUTLINE].loadFromFile( "player/outline.png" ) )
        return false;
    if( !p_this->texture[TexName::PLAYER_BODY].loadFromFile( "player/body.png" ) )
        return false;
    if( !p_this->texture[TexName::PLAYER_NOSE_CONE].loadFromFile( "player/nose_cone.png" ) )
        return false;
    if( !p_this->texture[TexName::PLAYER_SIDE_GUNS].loadFromFile( "player/side_guns.png" ) )
        return false;
    if( !p_this->texture[TexName::PLAYER_WINGS_GUNS].loadFromFile( "player/wings_guns.png" ) )
        return false;
    if( !p_this->texture[TexName::PLAYER_EYE].loadFromFile( "player/eye.png" ) )
        return false;

    if( !p_this->texture[TexName::BULLET].loadFromFile( "bullet.png" ) )
        return false;
    if( !p_this->texture[TexName::ROCKET].loadFromFile( "rocket.png" ) )
        return false;

    if( !p_this->tex_selection.loadFromFile( "selection.png" ) )
        return false;

    p_this->texture[TexName::ENEMY].setSmooth(true);
    p_this->texture[TexName::ENEMY_ATTACKER].setSmooth(true);
    p_this->texture[TexName::ENEMY_AVOIDER].setSmooth(true);
    p_this->texture[TexName::OBSTACLE].setSmooth(true);
    p_this->texture[TexName::PLAYER_OUTLINE].setSmooth(true);
    p_this->texture[TexName::PLAYER_BODY].setSmooth(true);
    p_this->texture[TexName::PLAYER_NOSE_CONE].setSmooth(true);
    p_this->texture[TexName::PLAYER_SIDE_GUNS].setSmooth(true);
    p_this->texture[TexName::PLAYER_WINGS_GUNS].setSmooth(true);
    p_this->texture[TexName::PLAYER_EYE].setSmooth(true);
    p_this->texture[TexName::BULLET].setSmooth(true);
    p_this->texture[TexName::ROCKET].setSmooth(true);
    // Selection and developer options stuff

    p_this->selection.setTexture( p_this->tex_selection );
    p_this->selection.setScale( 16.0/1920.0 , 16.0/1920.0 );
    p_this->selection.setPosition( InGame::board_begin, -4.5f );
    p_this->f_selection = false;
    p_this->f_create_enemy = false;
    p_this->type_of_enemy_to_create = 0;
    p_this->f_create_obstacle = false;
    p_this->f_delete_selected = false;
    p_this->track_id_selection = 0;
    p_this->moveable_id_selection = 0;

    if( !Board::init() )
        return false;

    // Creating board
    Board::create();
    Board::f_auto_generating = true;

    p_this->info.create( "Press Esc\nfor more options", 0.4f, sf::Vector2f( -7.7f, -4.4f ),
        sf::Color::White, App::getFont(), SimpleText::Origin::TOPLEFT );

    p_this->resume.create( "resume", 0.5f, sf::Vector2f( -7.7f, -4.4f ),
        sf::Color::White, App::getFont(), Button::Origin::TOPLEFT );
    p_this->load.create( "load game", 0.5f, sf::Vector2f( -7.7f, -3.6f ),
        sf::Color::White, App::getFont(), Button::Origin::TOPLEFT );
    p_this->save.create( "save game", 0.5f, sf::Vector2f( -7.7f, -2.8f ),
        sf::Color::White, App::getFont(), Button::Origin::TOPLEFT );
    p_this->exit.create( "exit", 0.5f, sf::Vector2f( -7.7f, -2.0f ),
        sf::Color::White, App::getFont(), Button::Origin::TOPLEFT );

    // Developer options, texts and buttons

    p_this->developer_options.create( "Developer options:", 0.4f, sf::Vector2f( -7.7f, -0.9f ),
        sf::Color::White, App::getFont(), SimpleText::Origin::TOPLEFT );

    p_this->auto_generating.create( "auto generating\n[ON/off]",
        0.4f, sf::Vector2f( -7.7f, -0.4f ),
        sf::Color::Green, App::getFont(), Button::Origin::TOPLEFT );

    p_this->create_enemy.create( "create enemy", 0.4f, sf::Vector2f( -7.7f, 0.6f ),
        sf::Color::White, App::getFont(), Button::Origin::TOPLEFT );
    p_this->create_obstacle.create( "create obstacle", 0.4f, sf::Vector2f( -7.7f, 1.2f ),
        sf::Color::White, App::getFont(), Button::Origin::TOPLEFT );

    p_this->delete_selected.create( "delete selected", 0.4f, sf::Vector2f( -7.7f, 1.8f ),
        sf::Color::White, App::getFont(), Button::Origin::TOPLEFT );
    p_this->delete_all.create( "delete all", 0.4f, sf::Vector2f( -7.7f, 2.4f ),
        sf::Color::White, App::getFont(), Button::Origin::TOPLEFT );

    p_this->info_selection.create( "\
Press Enter\nto do the operation\non selected area\n\n\
Use arrows on keyboard\nto change the position\nof the selection\n\n\
Press Esc\nto cancel this operation",
            0.3f, sf::Vector2f( InGame::board_end + 0.3f, -4.4f ), sf::Color::White,
            App::getFont(), Button::Origin::TOPLEFT );

    p_this->info_operation.create( "", 0.3f, sf::Vector2f( InGame::board_end + 0.3f, -4.4f + (10* 0.4f) ),
        sf::Color::White, App::getFont(), Button::Origin::TOPLEFT );

    return true;
}

void InGame::draw()
{
    // Drawing the board
    Board::draw();

    // When game is paused
    if( p_this->f_pause )
    {
        p_this->resume.draw();
        p_this->load.draw();
        p_this->save.draw();
        p_this->exit.draw();
        App::draw( p_this->developer_options );
        p_this->auto_generating.draw();
        p_this->create_enemy.draw();
        p_this->create_obstacle.draw();
        p_this->delete_selected.draw();
        p_this->delete_all.draw();
    }
    else // When game is not paused
        App::draw(p_this->info);

    // Drawing elements for selection
    if( p_this->f_selection )
    {
        p_this->info_selection.draw();
        p_this->info_operation.draw();
        App::draw( p_this->selection );
    }

}

void InGame::logic()
{
    if( p_this->f_selection ) // When user uses selection
    {
        InGame::useSelection();
        if( p_this->f_create_enemy )
        {
            if( App::isKeyReleased( sf::Keyboard::Num1 ) )
            {
                p_this->type_of_enemy_to_create = 0;
            }
            if( App::isKeyReleased( sf::Keyboard::Num2 ) )
            {
                p_this->type_of_enemy_to_create = 1;
            }
            if( App::isKeyReleased( sf::Keyboard::Num3 ) )
            {
                p_this->type_of_enemy_to_create = 2;
            }
        }
    }
    else if( !p_this->f_pause ) // When game is not paused
    {
        Board::logic();
        if( App::isKeyReleased( sf::Keyboard::Key::F5 ) )
        {
            SaveLoad::Save();
        }
        if( App::isKeyReleased( sf::Keyboard::Key::F8 ) )
        {
            SaveLoad::Load();
        }
        Statistics::addTimePlayed( App::getElapsedTime() );
    }
    else
    {
        InGame::ifKeyUp();
        InGame::ifKeyDown();
        InGame::ifKeyReturn();
    }

    InGame::ifKeyEscape();
}

void InGame::ifKeyUp()
{
    // Switching between buttons

        if( App::isKeyReleased( sf::Keyboard::Up ) )
        {
            if( p_this->resume.getStatus() )
            {
                p_this->resume.switchStatus();
                p_this->delete_all.switchStatus();
            }
            else if( p_this->load.getStatus() )
            {
                p_this->load.switchStatus();
                p_this->resume.switchStatus();
            }
            else if( p_this->save.getStatus() )
            {
                p_this->save.switchStatus();
                p_this->load.switchStatus();
            }
            else if( p_this->exit.getStatus() )
            {
                p_this->exit.switchStatus();
                p_this->resume.switchStatus();
            }
            else if( p_this->auto_generating.getStatus() )
            {
                p_this->auto_generating.switchStatus();
                p_this->exit.switchStatus();
            }
            else if( p_this->create_enemy.getStatus() )
            {
                p_this->create_enemy.switchStatus();
                p_this->auto_generating.switchStatus();
            }
            else if( p_this->create_obstacle.getStatus() )
            {
                p_this->create_obstacle.switchStatus();
                p_this->create_enemy.switchStatus();
            }
            else if( p_this->delete_selected.getStatus() )
            {
                p_this->delete_selected.switchStatus();
                p_this->create_obstacle.switchStatus();
            }
            else if( p_this->delete_all.getStatus() )
            {
                p_this->delete_all.switchStatus();
                p_this->delete_selected.switchStatus();
            }
        }
}

void InGame::ifKeyDown()
{
    // Switching between buttons

        if( App::isKeyReleased( sf::Keyboard::Down ) )
        {
            if( p_this->resume.getStatus() )
            {
                p_this->resume.switchStatus();
                p_this->load.switchStatus();
            }
            else if( p_this->load.getStatus() )
            {
                p_this->load.switchStatus();
                p_this->save.switchStatus();
            }
            else if( p_this->save.getStatus() )
            {
                p_this->save.switchStatus();
                p_this->exit.switchStatus();
            }
            else if( p_this->exit.getStatus() )
            {
                p_this->exit.switchStatus();
                p_this->auto_generating.switchStatus();
            }
            else if( p_this->auto_generating.getStatus() )
            {
                p_this->auto_generating.switchStatus();
                p_this->create_enemy.switchStatus();
            }
            else if( p_this->create_enemy.getStatus() )
            {
                p_this->create_enemy.switchStatus();
                p_this->create_obstacle.switchStatus();
            }
            else if( p_this->create_obstacle.getStatus() )
            {
                p_this->create_obstacle.switchStatus();
                p_this->delete_selected.switchStatus();
            }
            else if( p_this->delete_selected.getStatus() )
            {
                p_this->delete_selected.switchStatus();
                p_this->delete_all.switchStatus();
            }
            else if( p_this->delete_all.getStatus() )
            {
                p_this->delete_all.switchStatus();
                p_this->resume.switchStatus();
            }
        }
}

void InGame::ifKeyReturn()
{
    if( App::isKeyReleased( sf::Keyboard::Return ) )
    {
            /// When resume button is active
            if( p_this->resume.getStatus() )
            {
                p_this->f_pause = false;
            }
            else if( p_this->load.getStatus() )
            {
                SaveLoad::Load();
            }
            else if( p_this->save.getStatus() )
            {
                SaveLoad::Save();
            }
            /// When exit button is active
            else if( p_this->exit.getStatus() )
            {
                p_this->resume.switchStatus( true );
                p_this->exit.switchStatus( false );
                App::setStatus( App::Status::MENU );
            }
            /// When auto_generating button is active
            else if( p_this->auto_generating.getStatus() )
            {
                Board::f_auto_generating = !Board::f_auto_generating;
                if( Board::f_auto_generating )
                {
                    p_this->auto_generating.setTitle( "auto generating\n[ON/off]", 0.4f );
                    p_this->auto_generating.setColor( sf::Color::Green );
                }
                else
                {
                    p_this->auto_generating.setTitle( "auto generating\n[on/OFF]", 0.4f );
                    p_this->auto_generating.setColor( sf::Color::Red );
                }
            }
            /// When create_enemy button active
            else if( p_this->create_enemy.getStatus() )
            {
                p_this->f_selection = true;
                p_this->f_create_enemy = true;
            }
            /// When create_obstacle button active
            else if( p_this->create_obstacle.getStatus() )
            {
                p_this->f_selection = true;
                p_this->f_create_obstacle = true;
            }
            /// When delete_selected button active
            else if( p_this->delete_selected.getStatus() )
            {
                p_this->f_selection = true;
                p_this->f_delete_selected = true;
                p_this->moveable_id_selection = 0;
                InGame::updateDeleteSelectionNext();
            }
            /// When delete_all button active
            else if( p_this->delete_all.getStatus() )
            {
                Board::deleteAllMoveables();
            }
        }
}

void InGame::ifKeyEscape()
{
    if( App::isKeyReleased( sf::Keyboard::Escape ) )
    {
        /// When user uses selection
        if( p_this->f_selection )
        {
            p_this->f_selection = false;
            p_this->f_create_enemy = false;
            p_this->f_create_obstacle = false;
            p_this->f_delete_selected = false;

            p_this->info_operation.setTitle( "", 0.3f );

            p_this->moveable_id_selection = 0;
            p_this->track_id_selection = 0;
            p_this->selection.setPosition( InGame::board_begin, -4.5f );
        }
        /// When game is not paused
        else if( !p_this->f_pause )
        {
            // PAUSE THE GAME

            p_this->f_pause = true;

            p_this->resume.switchStatus( true );
            p_this->load.switchStatus( false );
            p_this->save.switchStatus( false );
            p_this->exit.switchStatus( false );
            p_this->create_enemy.switchStatus( false );
            p_this->create_obstacle.switchStatus( false );
            p_this->auto_generating.switchStatus( false );
            p_this->delete_selected.switchStatus( false );
            p_this->delete_all.switchStatus( false );
        }
        /// When game is paused and selection is off
        else
        {
            // RESUME THE GAME

            p_this->f_pause = false;

            p_this->resume.switchStatus( true );
            p_this->exit.switchStatus( false );
            p_this->create_enemy.switchStatus( false );
            p_this->create_obstacle.switchStatus( false );
            p_this->auto_generating.switchStatus( false );
            p_this->delete_selected.switchStatus( false );
            p_this->delete_all.switchStatus( false );
        }
    }
}


void InGame::useSelection()
{
    /// When user uses selection
    if( p_this->f_delete_selected )
    {
        // Up and Down keys force getting another moveable to snap

        if( App::isKeyReleased( sf::Keyboard::Up ) )
        {
            InGame::updateDeleteSelectionPrevious();
        }
        if( App::isKeyReleased( sf::Keyboard::Down ) )
        {
            InGame::updateDeleteSelectionNext();
        }
    }
    else
    {
        // Up and Down keys moves the viewfinder verticaly by half of moveable_height

        if( App::isKeyReleased( sf::Keyboard::Up ) )
        {
            if( (p_this->selection.getPosition().y - InGame::track_height/2) >= -4.6f -InGame::track_height )
                p_this->selection.move( 0.0f, -InGame::track_height/2 );
        }
        if( App::isKeyReleased( sf::Keyboard::Down ) )
        {
            if( (p_this->selection.getPosition().y + InGame::track_height/2) < 4.5f )
                p_this->selection.move( 0.0f, InGame::track_height/2 );
        }


        if( App::isKeyReleased( sf::Keyboard::Left ) )
        {
            // Moves the viewfinder to another track
            if( (p_this->selection.getPosition().x - InGame::track_width ) >= InGame::board_begin )// - 0.1f )
            {
                p_this->selection.move( -InGame::track_width, 0.0f );
                --(p_this->track_id_selection);

                // When user uses selection, update the moveable selection
                //if( p_this->f_delete_selected )
                //    InGame::updateDeleteSelectionNext();
            }
        }
        if( App::isKeyReleased( sf::Keyboard::Right ) )
        {
            // Moves the viewfinder to another track
            if( (p_this->selection.getPosition().x + InGame::track_width ) <= InGame::board_end - InGame::track_width )//+ 0.1f )
            {
                p_this->selection.move( InGame::track_width, 0.0f );
                ++(p_this->track_id_selection);

                // When user uses selection, update the moveable selection
                //if( p_this->f_delete_selected )
                //    InGame::updateDeleteSelectionNext();
            }
        }
    }

    if( App::isKeyReleased( sf::Keyboard::Return ) )
    {
        // Creating enemy
        if( p_this->f_create_enemy )
        {
            InGame::createEnemy();
        }
        // Creating obstacle
        else if( p_this->f_create_obstacle )
        {
            InGame::createObstacle();
        }
        // Deleting selection, display the info about operation
        else if( p_this->f_delete_selected )
        {
            if(Board::deleteMoveable( p_this->moveable_id_selection ))
            {
                p_this->info_operation.setTitle( "Deleting successfully\ncompleted." , 0.3f);
                p_this->info_operation.setColor( sf::Color::Green );
            }
            else
            {
                p_this->info_operation.setTitle( "Deleting failed.\nNothing to delete." , 0.3f );
                p_this->info_operation.setColor( sf::Color::Red );
            }
        }
    }
}

void InGame::updateDeleteSelectionNext()
{
    // Get the pointer to next moveable
    const Moveable* moveable = Board::getNextMoveable( p_this->moveable_id_selection );

    // If there is any moveable, set the viewfinder position to this moveable, and get id of this moveable
    if( moveable != nullptr )
    {
        p_this->selection.setPosition(moveable->getPosition()); // Position
        p_this->moveable_id_selection = moveable->getID(); // Unique ID
    }
}

void InGame::updateDeleteSelectionPrevious()
{
    // Get the pointer to previous moveable
    const Moveable* moveable = Board::getPreviousMoveable( p_this->moveable_id_selection );

    // If there is any moveable, set the viewfinder position to this moveable, and get id of this moveable
    if( moveable != nullptr )
    {
        p_this->selection.setPosition(moveable->getPosition()); // Position
        p_this->moveable_id_selection = moveable->getID(); // Unique ID
    }
}

void InGame::createEnemy()
{
    // Try to create enemy and display info about operation
    bool f_success = false;

    if( p_this->type_of_enemy_to_create == 0 )
        f_success = Board::addEnemy( p_this->selection.getPosition() );
    if( p_this->type_of_enemy_to_create == 1 )
        f_success = Board::addEnemyAttacker( p_this->selection.getPosition() );
    if( p_this->type_of_enemy_to_create == 2 )
        f_success = Board::addEnemyAvoider( p_this->selection.getPosition() );

    if( f_success )
    {
        p_this->info_operation.setTitle( "Creating enemy\nsuccessfully completed." , 0.3f );
        p_this->info_operation.setColor( sf::Color::Green );
    }
    else
    {
        p_this->info_operation.setTitle( "Creating enemy\nfailed.\nCollision detected." , 0.3f );
        p_this->info_operation.setColor( sf::Color::Red );
    }
}

void InGame::createObstacle()
{
    // Try to create obstacle and display info about operation
    if( Board::addObstacle( p_this->selection.getPosition() ) )
    {
        p_this->info_operation.setTitle( "Creating obstacle\nsuccessfully completed." , 0.3f );
        p_this->info_operation.setColor( sf::Color::Green );
    }
    else
    {
        p_this->info_operation.setTitle( "Creating obstacle\nfailed.\nCollision detected." , 0.3f );
        p_this->info_operation.setColor( sf::Color::Red );
    }
}

bool InGame::isPaused()
{
    return p_this->f_pause;
}

void InGame::close()
{
    Board::close();
    Statistics::close();

    if( p_this )
        delete p_this;
    p_this = nullptr;
}
