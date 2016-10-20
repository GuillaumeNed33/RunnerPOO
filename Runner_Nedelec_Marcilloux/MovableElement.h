#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H

//Indique la hauteur d'apparition des éléments
enum HeightElement
{
    Ground,
    Mid_Air,
    Up_Air
};

//=========================================================================
// Description:
//
// Cette classe permet la gestion des éléments mobiles du jeu (personnage, obstacle, bonus et pièces)
//=========================================================================
class MovableElement
{
protected:
    float _x; //Position x
    float _y; // Position y
    unsigned int _w; //Largeur de l'objet
    unsigned int _h; //Hauteur de l'objet
    float _dy; //Vitesse verticale
    float _dx; //Vitesse horizontale
    HeightElement _height; //Indicateur de la hauteur d'apparition de l'objet

public:
    MovableElement() {}
    MovableElement(float x, float y, unsigned int w, unsigned int h, float dx, float dy);
    virtual void move();
    void set_dx(float dx);
    void set_dy(float dy);
    float get_x() const;
    float get_y() const;
    unsigned int get_w() const;
    unsigned int get_h() const;
    float get_dx() const;
    float get_dy() const;
    virtual ~MovableElement();
    virtual bool collision(MovableElement *m);
};

#endif // MOVABLEELEMENT_H
