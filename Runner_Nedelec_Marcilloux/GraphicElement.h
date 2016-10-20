#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <SFML/Graphics.hpp>

//=========================================================================
// Description:
//
// Cette classe permet de gérer tous les sprites (non animés) du jeu et de pouvoir changer leur taille
//=========================================================================
class GraphicElement:public sf::Sprite
{
protected:
    int _w; //Largeur de l'image
    int _h; //Hauteur de l'image
public:
    GraphicElement(sf::Texture &image, int x, int y, int w, int h);
    virtual ~GraphicElement();
    virtual void draw(sf::RenderWindow * window);
    virtual void resize(int w, int h);
    int get_w() const;
    int get_h() const;
};

#endif // GRAPHICELEMENT_H
