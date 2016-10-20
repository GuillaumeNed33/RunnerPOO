#include "Obstacle.h"





//==================================================================================================================
// Description : Constructeur d'Obstacle
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet de creer des Obstacles à partir de 4 float, 2 unsigned int, un TypeObstacles et un HeightElement
//==================================================================================================================
Obstacle::Obstacle(float x, float y, unsigned int w, unsigned int h, float dx, float dy, TypeObstacle type, HeightElement height):
    MovableElement{x,y,w,h,dx,dy}, _type{type}
{
    _height = height;
}






//=====================================
// Description : Destructeur d'Obstacle
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet de detruire l'objet
//=====================================
Obstacle::~Obstacle() {}






//====================================================
// Description : Accesseur du type
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet de récupérer le type de l'Obstacle
//====================================================
TypeObstacle Obstacle::get_type() const
{
    return _type;
}






//=======================================================
// Description : Accesseur de la hauteur
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet de récupérer la hauteur de l'Obstacle
//=======================================================
HeightElement Obstacle::get_height() const
{
    return _height;
}

