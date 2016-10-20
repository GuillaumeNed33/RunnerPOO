#include "Bonus.h"





//==========================================================================================================
// Description : Constructeur de Bonus
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet de creer des Bonus à partir de 4 float, 2 unsigned int, un BonusType et un HeightElement
//==========================================================================================================
Bonus::Bonus(float x, float y, unsigned int w, unsigned int h, float dx, float dy, BonusType type, HeightElement height):
    MovableElement{x,y,w,h,dx,dy}, _type{type}
{
     _height = height;
}






//=====================================
// Description : Destructeur de Bonus
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet de detruire l'objet
//=====================================
Bonus::~Bonus() {}






//===============================================
// Description : Accesseur du type
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet de récupérer le type du Bonus
//===============================================
BonusType Bonus::get_type() const
{
    return _type;
}
