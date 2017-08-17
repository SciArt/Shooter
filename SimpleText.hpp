////////////////////////////////////////////////////////////
//
// SHOOTER
//
// Autor:       Gerard Wypych
// Prowadzący:  mgr inż. Bartłomiej Gajewski
//
////////////////////////////////////////////////////////////

#ifndef SIMPLETEXT_HPP
#define SIMPLETEXT_HPP

#include "SFML/Graphics/Text.hpp"

class SimpleText : public sf::Text
{
public:

    enum Origin
    {
        TOPLEFT,
        CENTER
    };

    SimpleText();
    ~SimpleText();

    SimpleText( const std::string &title,
        const float &height, const sf::Vector2f& position,
        const sf::Color &color, const sf::Font &font,
        const SimpleText::Origin &origin = SimpleText::Origin::CENTER );

    void create( const std::string &title,
        const float &height, const sf::Vector2f& position,
        const sf::Color &color, const sf::Font &font,
        const SimpleText::Origin &origin = SimpleText::Origin::TOPLEFT );

    void setOrigin( const SimpleText::Origin& origin );

private:
    unsigned int ID;
    static unsigned int max_quantity;
    static unsigned int quantity;
};

#endif // SIMPLETEXT_HPP
