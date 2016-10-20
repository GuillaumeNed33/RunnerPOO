#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "MovableElement.h"

//Indique le type de l'obstacle
enum TypeObstacle
{
    ObstacleType1,
    ObstacleType2,
    ObstacleType3
};

//=========================================================================
// Description:
//
// Cette classe permet de gérer les propriétés des obstacle.
//=========================================================================
class Obstacle : public MovableElement
{
private:
    TypeObstacle _type; //type de l'obstacle

public:
    Obstacle(float x, float y, unsigned int w, unsigned int h, float dx, float dy, TypeObstacle type, HeightElement height);
    TypeObstacle get_type() const;
    HeightElement get_height() const;
    virtual ~Obstacle() override;
};

#endif // OBSTACLE_H
