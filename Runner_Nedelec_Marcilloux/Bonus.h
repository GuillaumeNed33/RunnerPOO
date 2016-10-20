#ifndef BONUS_H
#define BONUS_H

#include "MovableElement.h"

//Définit les differents types de bonus
enum BonusType
{
    Invincible,
    Health,
    Jump,
    Pointx2,
    Nuke
};

//=========================================================================
// Description:
//
// Cette classe permet de definir les propriétés des bonus ainsi que les effets qu'ils doivent produire.
//=========================================================================

class Bonus : public MovableElement
{
private:
    BonusType _type; //Type du bonus

public:
    Bonus(float x, float y, unsigned int w, unsigned int h, float dx, float dy, BonusType type, HeightElement height);
    virtual ~Bonus() override;
    BonusType get_type() const;
};

#endif // BONUS_H
