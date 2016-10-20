#include "Player.h"

using namespace std;

//==================================================================================================================
// Description : Constructeur du joueur
// Auteur : Nicolas Marcilloux et Guillaume Nédélec
// Date : 10/02/16
// Interêt : permet de creer des un joueur comme un MovableElement
//==================================================================================================================
Player::Player(float x, float y, unsigned int w, unsigned int h, float dx, float dy)
    :MovableElement{x,y,w,h,dx,dy}
{}


//==================================================================================================================
// Description : Destructeur de Player
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 10/02/16
// Interêt : permet de détruire les objets de type Player
//==================================================================================================================
Player::~Player()
{}


//==================================================================================================================
// Description : Accesseur de left
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 10/02/16
// Interêt : permet d'acceder au parametre _left
//==================================================================================================================
bool Player::getLeft() const
{
    return _left; //Indique si la balle se dirige à gauche
}


//==================================================================================================================
// Description : Accesseur de right
// Auteur : Nicolas Marcilloux
// Date : 10/02/16
// Interêt : permet d'acceder au parametre _right
//==================================================================================================================
bool Player::getRight() const
{
    return _right; //Indique si la balle se dirige à droite
}


//==================================================================================================================
// Description : Mutateur de left
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 10/02/16
// Interêt : permet de modifier le parametre _left
//==================================================================================================================
void Player::setLeft(bool b)
{
    _left = b;
}


//==================================================================================================================
// Description : Mutateur de right
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 10/02/16
// Interêt : permet de modifier le parametre _right
//==================================================================================================================
void Player::setRight(bool b)
{
    _right = b;
}


//==================================================================================================================
// Description : Accesseur de jump
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 10/02/16
// Interêt : permet d'acceder au parametre _jump (savoir si le joueur est en saut)
//==================================================================================================================
bool Player::getJump() const
{
    return _jump; //Indique si une phase de saut est activée
}

//==================================================================================================================
// Description : Mutateur de jump
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 10/02/16
// Interêt : permet de modifier le parametre _jump
//==================================================================================================================
void Player::setJump(bool b)
{
    _jump=b;
}


//==================================================================================================================
// Description : Accesseur de doubleJump
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 10/03/16
// Interêt : permet d'acceder au parametre _doubleJump (savoir si le joueur est en double saut)
//==================================================================================================================
void Player::setDoubleJump(bool b)
{
    _doubleJump = b;
}



//==================================================================================================================
// Description : Deplacement de l'objet
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 18/02/16
// Interêt : Permet de faire deplacer le joueur
//==================================================================================================================
void Player::move()
{

    if(_jump && !_doubleJump) //Si le saut est activé
    {
        jump();
        _x+=_dx/1.5; //Deplacement horizontal limité
    }

    else if(_doubleJump) //Si le double saut est activé
    {
        doubleJump();
        _x+=_dx/1.5; //Deplacement horizontal limité
    }

    else
    {
        this->_x=_x+_dx; //Déplacement Normal de la balle
        this->_y=_y-_dy;
    }
}


//==================================================================================================================
// Description : Saut de l'objet
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 18/02/16
// Interêt : Permet de faire sauter le joueur
//==================================================================================================================
void Player::jump()
{
    _endJump = false;

    if(_begining)
    {
        _dy = 27.8;
        _begining = false;
    }

    if(_y > MAX_HEIGHT_JUMP && !_falling)
    {
        _dy *= GRAVITE;
        _y -= _dy;
    }

   if(_y <= MAX_HEIGHT_JUMP)
    {
        _falling = true;
    }

    if(_falling && !_endJump)
    {
        _dy /= GRAVITE;
        _y += _dy;

        if(_y >= (GROUND_HEIGHT))
        {
            _dy = 0;
            _y = (GROUND_HEIGHT);
            _falling = false;
            _endJump = true;
            _begining = true;
        }
    }

    if (_endJump)
    {
         _jump = false;
    }
}


//==================================================================================================================
// Description : DoubleSaut de l'objet
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 18/02/16
// Interêt : Permet de faire sauter le joueur alors qu'il est déja en saut
//==================================================================================================================
void Player::doubleJump()
{
    _endDoubleJump = false;

    if(_doubleJumpBegining)
    {
        _dy = 27.8;
        _doubleJumpBegining = false;
    }

    if(_y > _save_PosY - HEIGHT_JUMP && !_doubleJumpFalling)
    {
        _dy *= GRAVITE; //Ralentissement du joueur
        _y -= _dy;
    }

   if(_y <= _save_PosY - HEIGHT_JUMP)
    {
        _doubleJumpFalling = true;
    }

    if(_doubleJumpFalling && !_endDoubleJump)
    {
        _dy = (_dy/GRAVITE); //Acceleration du joueur
        _y += _dy;

        if(_y >= (GROUND_HEIGHT))
        {
            _dy = 0;
            _y = (GROUND_HEIGHT);
            _falling = false;
            _endJump = true;
            _begining = true;
            _doubleJumpFalling = false;
            _endDoubleJump = true;
            _doubleJumpBegining = true;
        }
    }

    if (_endDoubleJump)
    {
         _jump = false;
         _doubleJump = false;
    }
}


//==================================================================================================================
// Description : Collision avec le joueur
// Auteur :  Guillaume Nédélec
// Date : 18/02/16
// Interêt : Permet de detecter les collisions avec le joueur
//==================================================================================================================
bool Player::collision(MovableElement *m)
{
    const float leftA = _x-25; //Cote gauche de la balle
    const float rightA = _x + _w-25; //Le droit
    const float topA = _y-25; //Le Haut
    const float bottomA = _y + _h-25; //Le bas

    //Idem pour l'element mobile
    const float leftB = m->get_x();
    const float rightB = m->get_x() + m->get_w();
    const float topB = m->get_y();
    const float bottomB = m->get_y() + m->get_h();

    if(bottomA <= topB)
        return false;
    if(topA >= bottomB)
        return false;
    if(rightA <= leftB)
        return false;
    if(leftA >= rightB)
        return false;

    return true;
}



//==================================================================================================================
// Description : Degats
// Auteur :  Guillaume Nédélec
// Date : 18/02/16
// Interêt : Permet de de baisser la vie du joueur
//==================================================================================================================
void Player::damages(int obstacleType)
{
    if(!_invincibleBonus) //Si le bonus d'invicibilité n'est pas actif
    {
        if(obstacleType == 0)
            _life -= HEALTH_1;
        else if(obstacleType == 1)
            _life -= HEALTH_2;
        else if(obstacleType == 2)
            _life -= HEALTH_3;
    }
}


//==================================================================================================================
// Description : Accesseur de life
// Auteur : Nicolas Marcilloux, Guillaume Nédélec
// Date : 18/02/16
// Interêt : Permet de recupérer le niveau de vie du joueur
//==================================================================================================================
int Player::getLife() const
{
    return _life;
}


//==================================================================================================================
// Description : Mutateur de _invincibleBonus
// Auteur :  Guillaume Nédélec
// Date : 18/03/16
// Interêt : Permet d'attribuer le bonus invincibilité (ou de le retirer)
//==================================================================================================================
void Player::setInvincibleBonus(bool b)
{
    _invincibleBonus = b;
}

//==================================================================================================================
// Description : Mutateur de _doubleJumpBonus
// Auteur :  Guillaume Nédélec
// Date : 18/03/16
// Interêt : Permet d'attribuer le bonus double saut (ou de le retirer)
//==================================================================================================================
void Player::setDoubleJumpBonus(bool b)
{
    _doubleJumpBonus = b;
}

//==================================================================================================================
// Description : Ajout de vie
// Auteur :  Guillaume Nédélec
// Date : 18/03/16
// Interêt : Permet de redonner de la vie au joueur (effet d'un bonus)
//==================================================================================================================
void Player::addLife()
{
    if(_life >= 80 ) //Pour que la vie ne depasse jamais 100
        _life = FULL_LIFE;
    else
        _life +=HEALTH_2;
}

//==================================================================================================================
// Description : Reinitialisation
// Auteur :  Guillaume Nédélec
// Date : 18/03/16
// Interêt : Reinitialise la balle comme si le jeu recommençais
//==================================================================================================================
void Player::reset()
{
    _x = 100;
    _y = GROUND_HEIGHT;
    _w = SIZE_PLAYER;
    _h = SIZE_PLAYER;
    _dx= 0;
    _dy = 0;
    _left = false;
    _right = false;
    _jump = false;
    _life =FULL_LIFE;
    _invincibleBonus = false;
    _doubleJumpBonus = false;
}

//==================================================================================================================
// Description : Mutateur de _invincibleBonus
// Auteur :  Guillaume Nédélec
// Date : 18/03/16
// Interêt : Permet de savoir si le bonus double d'invincibilité est activé ou non
//==================================================================================================================
bool Player::getInvincibleBonus()
{
    return _invincibleBonus;
}

//==================================================================================================================
// Description : Accesseur de _doubleJumpBonus
// Auteur :  Guillaume Nédélec
// Date : 18/03/16
// Interêt : Permet de savoir si le bonus double saut est activé ou non
//==================================================================================================================
bool Player::getDoubleJumpBonus()
{
    return _doubleJumpBonus;
}

//==================================================================================================================
// Description : SavePosition
// Auteur :  Guillaume Nédélec
// Date : 18/03/16
// Interêt : Permet de sauvegarder la position y de la balle
//==================================================================================================================
void Player::set_y(float y)
{
    _save_PosY = y;
}
