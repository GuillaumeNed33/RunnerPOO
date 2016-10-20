#ifndef COINS_H
#define COINS_H

#include "MovableElement.h"

// Indique si les pièces apparaissent par series de 3, 4 ou 5 pièces.
enum TypeCoinSeries
{
    SeriesOf3,
    SeriesOf4,
    SeriesOf5
};

//=========================================================================
// Description:
//
// Cette classe permet de définir les propriétés des pièces à recupérer dans le jeu
//=========================================================================

class Coin : public MovableElement
{
public:
    Coin(float x, float y, unsigned int w, unsigned int h, float dx, float dy, HeightElement height);
    virtual ~Coin() override;
};

#endif // COINS_H
