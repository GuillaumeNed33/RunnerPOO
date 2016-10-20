#include "GraphicElement.h"





//==========================================================================================
// Description : Constructeur de GraphicElement
// Auteur : Guillaume Nedelec,  Nicolas Marcilloux
// Date : 25/02/16
// Interêt : permet de creer des GraphicELement à partir d'une texture et de quatre entiers
//==========================================================================================
GraphicElement::GraphicElement(sf::Texture &image, int x, int y, int w, int h)
{
    this->setTexture(image);
    this->setPosition(sf::Vector2f(x,y));
    this->_w = w;
    this->_h = h;
}





//====================================================
// Description : Destructeur de GraphicElement
// Auteur : Guillaume Nedelec
// Date : 25/02/16
// Interêt : permet de detruire l'objet
//====================================================
GraphicElement::~GraphicElement() {}





//===================================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec
// Date : 25/02/16
// Interêt : permet de dessiner sur une fenêtre, un élément graphique
//===================================================================
void GraphicElement::draw(sf::RenderWindow * window)
{
   window->draw(*this);
}




//===============================================================================
// Description : Modification de la taille
// Auteur : Guillaume Nedelec,  Nicolas Marcilloux
// Date : 25/02/16
// Interêt : permet de modifier la largeur et la longueur des éléments graphiques
//===============================================================================
void GraphicElement::resize(int w, int h)
{
    float widht = w;
    float height = h;
    sf::FloatRect bb = this->getLocalBounds();
    float width_factor = widht / bb.width;
    float height_factor = height / bb.height;
    this->setScale(width_factor, height_factor);
}






//================================================================
// Description : Accesseur de largeur
// Auteur :  Nicolas Marcilloux
// Date : 22/05/16
// Interêt : permet de d'obtenir la largeur de l'élément graphique
//================================================================
int GraphicElement::get_w() const
{
    return _w;
}





//=================================================================
// Description : Accesseur de longueur
// Auteur : Nicolas Marcilloux
// Date : 22/05/16
// Interêt : permet de d'obtenir la longueur de l'élément graphique
//=================================================================
int GraphicElement::get_h() const
{
    return _h;
}
