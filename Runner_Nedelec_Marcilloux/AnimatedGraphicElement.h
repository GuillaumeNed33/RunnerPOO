#ifndef ANIMATEDGRAPHICELEMENT_H
#define ANIMATEDGRAPHICELEMENT_H

#include "GraphicElement.h"

//=========================================================================
// Description:
//
// Cette classe permet de creer et gerer des éléments graphiques animés
//=========================================================================

class AnimatedGraphicElement : public GraphicElement
{
protected:
    std::vector<sf::IntRect> _clip_rects; //Ensemble des rectangles de lectures à lire sur la feuille de sprites
    unsigned int _current_clip_rect = 0; //Indice du rectangle de lecture courant (qui est ou va être affiché)
    sf::Clock _clockFrame; //Horloge permettant de changer de rectangle de lecture au bout d'un certain temps

public:
    AnimatedGraphicElement(const std::vector<sf::IntRect> & clipRects, sf::Texture & image, int x, int y, int w, int h);
    virtual void draw(sf::RenderWindow *window) override;
    virtual ~AnimatedGraphicElement();
    void setVectRect(std::vector<sf::IntRect> c);
};

#endif // ANIMATEDGRAPHICELEMENT_H


