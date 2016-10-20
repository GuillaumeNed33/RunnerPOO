#ifndef SLIDINGBACKGROUND_H
#define SLIDINGBACKGROUND_H

#include "GraphicElement.h"

//=========================================================================
// Description:
//
// Cette classe permet de gérer les fonds défilants
//=========================================================================
class SlidingBackground {
private:
    GraphicElement _left; //Image en partant du coté gauche
    GraphicElement _right; //Image en partant de la droite (vers la droite)
    //Les images de _left et _right se succèdent pour un affichage constant.
    int _width; //Largeur de l'image
    int _height; //Hauteur de l'image
    unsigned int _speed = 0; //Vitesse de défilement
public:
    SlidingBackground(sf::Texture &image, int w, int h, unsigned int speed);
    void draw(sf::RenderWindow *&window);
    void setSpeed(unsigned int speed);
};

#endif // SLIDINGBACKGROUND_H

