#include "Coin.h"





//==========================================================================================================
// Description : Constructeur de Coin
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet de creer des Coin à partir de 4 float, 2 unsigned int et un HeightElement
//==========================================================================================================
Coin::Coin(float x, float y, unsigned int w, unsigned int h, float dx, float dy, HeightElement height):
    MovableElement{x,y,w,h,dx,dy}
{
    _height = height;
}





//=====================================
// Description : Destructeur de Coin
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet de detruire l'objet
//=====================================
Coin::~Coin() {}

