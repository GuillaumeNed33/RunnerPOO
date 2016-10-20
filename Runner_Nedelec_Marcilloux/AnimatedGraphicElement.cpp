#include "AnimatedGraphicElement.h"




//===========================================================================================================================
// Description : Constructeur de AnimatedGraphicElement
// Auteur : Guillaume Nedelec
// Date : 8/04/16
// Interêt : permet de creer des AnimatedGraphicELement à partir d'un vecteur de lecture, d'une texture et de quatre entiers
//===========================================================================================================================
AnimatedGraphicElement::AnimatedGraphicElement(const std::vector<sf::IntRect> &clipRects, sf::Texture &image, int x, int y, int w, int h) :
        GraphicElement{image,x,y,w,h}, _clip_rects{clipRects}
{}





//====================================================
// Description : Destructeur de AnimatedGraphicElement
// Auteur : Guillaume Nedelec
// Date : 8/04/16
// Interêt : permet de detruire l'objet
//====================================================
AnimatedGraphicElement::~AnimatedGraphicElement() {}





//==============================================================================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec
// Date : 8/04/16
// Interêt : permet de dessiner sur une fenêtre, un élément graphique qui changera en fonction du temps (horloge)
//===============================================================================================================
void AnimatedGraphicElement::draw(sf::RenderWindow *window)
{
    setTextureRect(_clip_rects[_current_clip_rect%_clip_rects.size()]);
    window->draw(*this);

    sf::Time time = _clockFrame.getElapsedTime();
    if(time.asSeconds() > 0.1)
    {
        _current_clip_rect++;
        _clockFrame.restart();
    }
}





//==================================================================================
// Description : Mutateur de vecteur de lecture
// Auteur : Nicolas Marcilloux
// Date : 24/05/16
// Interêt : permet d'appliquer un vecteur de lecture sur un élément graphique animé
//==================================================================================
void AnimatedGraphicElement::setVectRect(std::vector<sf::IntRect> c)
{
   _clip_rects = c;
}
