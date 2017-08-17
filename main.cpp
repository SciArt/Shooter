////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "App.hpp"
#include <iostream>

////////////////////////////////////////////////////////////
// Main function
////////////////////////////////////////////////////////////
int main( int argc,  char** argv )
{
    // Initializing application
    // Creating window, loading textures etc.
    if( !App::init() )
    {
        // Unsuccessful initialization
        std::cout << "Initialization failed.\n";
        return 1;
    }

    // Running application, closing app is embedded
    // App::run();

    return 0;
}
