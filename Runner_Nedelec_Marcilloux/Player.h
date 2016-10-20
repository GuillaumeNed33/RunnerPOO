#ifndef BALL_H
#define BALL_H

#include "MovableElement.h"
#include "View.h"


static const unsigned int SIZE_PLAYER = 75;

//=========================================================================
// Description:
//
// Cette classe permet de créer le joueur et de gérer les actions dont il est acteur (saut, collision ect...)
//=========================================================================
class Player:public MovableElement
{
private: 
    static const unsigned int HEALTH_1 = 10; //Degats d'un obstacle de type 1
    static const unsigned int HEALTH_2 = 15; //Degats d'un obstacle de type 2
    static const unsigned int HEALTH_3 = 20; //Degats d'un obstacle de type 3
    static const unsigned int FULL_LIFE = 100; //Niveau de vie Maximum
    static const unsigned int MAX_HEIGHT_JUMP = 250; //Coordonnées de la hauteur maximum du saut
    const float GRAVITE = 0.9; //Constante gravitationnelle (pour le saut)
    static const unsigned int HEIGHT_JUMP = 220; //Hauteur d'un saut
    static const unsigned int GROUND_HEIGHT = 470; //Coordonnées de la hauteur du sol dans le jeu

    bool _left = false; //Indique que le joueur va vers la gauche
    bool _right = false; //Indique que le joueur va vers la droite
    bool _jump = false; //Indique si le joueur est en saut
    bool _falling = false; //Indique si lae joueur est en train de tomber (dans le saut)
    bool _begining = true; //Debut du saut
    bool _endJump = false; //Fin du saut
    bool _doubleJump = false; //Indique si le joueur est en double saut
    bool _doubleJumpFalling = false; //Indique si le joueur est en train de tomber (dans le  deuxième saut)
    bool _doubleJumpBegining = true; //Debut du deuxième saut
    bool _endDoubleJump = false; //Fin du duexième saut
    bool _invincibleBonus = false; //Bonus d'invincibilité actif ou non
    bool _doubleJumpBonus = false; //Bonus de double saut actif ou non
    int _life = FULL_LIFE; //Vie du joueur
    float _save_PosY; //Sauvegarde de la position du joueur pour l'execution du double saut

public:
    Player() {}
    Player(float x, float y, unsigned int w, unsigned int h, float dx, float dy);
    ~Player();
    bool getLeft() const;
    bool getRight() const;
    bool getJump() const;
    int getLife() const;
    void setLeft(bool b);
    void setRight(bool b);
    void setJump(bool b);
    void setDoubleJump(bool b);
    void jump();
    void doubleJump();
    void move() override;

    bool collision(MovableElement *m) override;
    void damages(int obstacleType);
    void setInvincibleBonus(bool b);
    bool getInvincibleBonus();
    void setDoubleJumpBonus(bool b);
    bool getDoubleJumpBonus();
    void addLife();
    void reset();
    void set_y(float y);
};

#endif // BALL_H
