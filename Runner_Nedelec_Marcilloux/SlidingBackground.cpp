#include "SlidingBackground.h"

//================================================================================
// Description : Constructeur de SlidingBackground
// Auteur : Guillaume Nedelec
// Date : 20/05/16
// Interêt : Permet de construire des arrières plans défilants
//================================================================================
SlidingBackground::SlidingBackground(sf::Texture &image, int w, int h, unsigned int speed):
    _left{image,0,0,w,h},
    _right{image,w,0,w,h},
    _width{w},
    _height{h},
    _speed{speed}
{
    _left.setTexture(image);
    _right.setTexture(image);
    _left.setPosition(0,0);
    _right.setPosition(w,0);
}

//=========================================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/03/16
// Interêt : Permet de dessiner le fond dans la fenetre et de le faire defiler à chaque étape
//=========================================================================
void SlidingBackground::draw(sf::RenderWindow * &window)
{
    _left.setPosition(_left.getPosition().x - (_speed), _left.getPosition().y );
    _right.setPosition(_right.getPosition().x - (_speed), _right.getPosition().y );

    if(_right.getPosition().x < 0)
    {
        _left.setPosition(0,_left.getPosition().y);
        _right.setPosition(_width, _right.getPosition().y);
    }

    window->draw(_left);
    window->draw(_right);
}

//=========================================================================
// Description : Mutateur de speed
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/03/16
// Interêt : Permet de modifier la vitesse de défilement
//=========================================================================
void SlidingBackground::setSpeed(unsigned int speed)
{
    this->_speed = speed;
}


