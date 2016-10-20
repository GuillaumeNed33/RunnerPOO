#include "MovableElement.h"





//===========================================================================================
// Description : Constructeur de MovableElement
// Auteur : Guillaume Nedelec,  Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de creer des MovableELement à partir de quatre float et de 2 unsigned int
//===========================================================================================
MovableElement::MovableElement(float x, float y, unsigned int w, unsigned int h, float dx, float dy)
{
    this->_x = x;
    this->_y = y;
    this->_w = w;
    this->_h = h;
    this->_dx= dx;
    this->_dy= dy;
}





//====================================================
// Description : Destructeur de MovableElement
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de detruire l'objet
//====================================================
MovableElement::~MovableElement(){}





//==========================================================================
// Description : Accesseur de position horizontale
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de d'obtenir la position horizontale de l'élément mobile
//==========================================================================
float MovableElement::get_x() const
{
    return _x; //Coordonnées des abscisses
}





//========================================================================
// Description : Accesseur de position verticale
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de d'obtenir la position verticale de l'élément mobile
//========================================================================
float MovableElement::get_y() const
{
    return _y; //Coordonnées des ordonnées
}





//=============================================================
// Description : Accesseur de largeur
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de d'obtenir la largeur de l'élément mobile
//=============================================================
unsigned int MovableElement::get_w() const
{
    return _w; //Largeur de l'élément
}






//==============================================================
// Description : Accesseur de longueur
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de d'obtenir la longueur de l'élément mobile
//==============================================================
unsigned int MovableElement::get_h() const
{
    return _h; //Hauteur de l'élément
}





//==========================================================================
// Description : Accesseur de vitesse horizontale
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de d'obtenir la vitesse horizontale de l'élément mobile
//==========================================================================
float MovableElement::get_dx() const
{
    return _dx; //Vitesse de déplacement horizontal
}





//========================================================================
// Description : Accesseur de vitesse verticale
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de d'obtenir la vitesse verticale de l'élément mobile
//========================================================================
float MovableElement::get_dy() const
{
    return _dy; //Vitesse de déplacement vertical
}





//========================================================================
// Description : Mutateur de vitesse horizontale
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de modifier la vitesse horizontale de l'élément mobile
//========================================================================
void MovableElement::set_dx(float dx)
{
    this->_dx = dx;
}





//========================================================================
// Description : Mutateur de vitesse verticale
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de modifier la vitesse verticale de l'élément mobile
//========================================================================
void MovableElement::set_dy(float dy)
{
    this->_dy = dy;
}





//================================================================
// Description : Mouvement des éléments mobiles
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de gerer les déplacements des éléments mobiles
//================================================================
void MovableElement::move()
{
    this->_x=_x+_dx;
    this->_y=_y+_dy;
}





//============================================================================
// Description : Mouvement des éléments mobiles
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 11/02/16
// Interêt : permet de détécter si il y a collision entre deux élément mobiles
//============================================================================
bool MovableElement::collision(MovableElement *m)
{
    const float leftA = _x; //Cote gauche de la balle
    const float rightA = _x + _w; //Le droit
    const float topA = _y; //Le Haut
    const float bottomA = _y + _h; //Le bas

    //Idem pour l'element mobile
    const float leftB = m->get_x();
    const float rightB = m->get_x() + m->get_w();
    const float topB = m->get_y();
    const float bottomB = m->get_y() + m->get_h();

    if(bottomA <= topB)
        return false;
    if(topA >= bottomB)
        return false;
    if(rightA <= leftB)
        return false;
    if(leftA >= rightB)
        return false;

    return true;
}
