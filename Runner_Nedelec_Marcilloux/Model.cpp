#include "Model.h"
#include <fstream>
#include <iostream>

using namespace std;

//===============================================================================
// Description : Constructeur de modèle
// Auteur : Guillaume Nedelec
// Date : 01/02/16
// Interêt : permet de creer un modèle (squelette du jeu) à partir de deux entier
//===============================================================================
Model::Model(int w, int h)
    :  _w(w), _h(h), _player{nullptr} {

    _player = new Player(INIT_POSX_PLAYER, INIT_POSY_PLAYER, SIZE_PLAYER, SIZE_PLAYER , 0, 0); //Construction de la balle (le joueur)
}




//=========================================================================================================================
// Description : Destructeur de modèle
// Auteur : Guillaume Nedelec
// Date : 01/02/16
// Interêt : permet de désallouer toutes les case mémoires allouées dynamiquement dans le modèle et de supprimer ce dernier
//=========================================================================================================================
Model::~Model(){

    //Desallocation de tous les pointeurs du modele : Obstacle, Pièce et Bonus ainsi que la balle.
    delete _player;
    for(Obstacle * e : _obstacles)
        delete e;
    for(Coin * e : _coins)
        delete e;
    for(Bonus * e : _bonus)
        delete e;
    for(MovableElement * e : _trash)
        delete e;

    _obstacles.clear();
    _coins.clear();
    _bonus.clear();
    _trash.clear();
}




//===========================================================================================================================
// Description : Gestion de l'apparition des elements mobiles
// Auteur : Guillaume Nedelec
// Date : 22/02/16
// Interêt : permet de générer les les objets mobiles (sauf le joueur) sans qu'ils puissent apparaitre les uns sur les autres
//===========================================================================================================================
void Model::elementApparition()
{
    //Définie un délai aléatoire d'apparition d'un obstacle qui ne change pas tant qu'aucun obstacle est apparu
    if(!_obstacleAppears)
    {
        apparitionTimeObstacle = getDuration(Ennemies);
        _obstacleAppears = true; //Permet de ne plus modifier le délai d'apparition des obstacles
    }

    //Idem pour les pieces
    if(!_coinAppears)
    {
        apparitionTimeCoin = getDuration(Points);
        _coinAppears = true; //Permet de ne plus modifier le délai d'apparition des pieces
    }

    //Idem pour les bonus
    if(!_bonusAppears)
    {
        apparitionTimeBonus = getDuration(PowerUp);
        _bonusAppears = true; //Permet de ne plus modifier le délai d'apparition des bonus
    }

    //Apparition d'un obstacle
    if(_cptFrameObstacle%apparitionTimeObstacle == 0)
    {
        addElement(Ennemies);
        _cptFrameObstacle=0;
        _obstacleAppears = false;
    }

    //Apparition de pièces
    if(_cptFrameCoin%apparitionTimeCoin == 0)
    {
        addElement(Points);
        _cptFrameCoin=0;
        _coinAppears = false;
    }

    //Apparition de bonus
    if(_cptFrameBonus%apparitionTimeBonus == 0)
    {
        addElement(PowerUp);
        _cptFrameBonus=0;
        _bonusAppears = false;
    }
}


//================================================================
// Description : Deroulement des étapes temporelles (par frames)
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 10/03/16
// Interêt : permet de faire avancer le jeu en fonction des frames
//================================================================
void Model::nextStep()
{
    elementApparition(); //Fais apparaitre les divers éléments mobiles
    elementManagement(); //Gère les differents événements liés aux objets mobiles
    movePlayer(); //Permet le déplacement de la balle

    //Desactive les effets du bonus de doublage des points attrapés une fois le temps dépassé
    if(_cptFrameActiveBonusPoint%ACTIVE_TIME_BONUS == 0)
    {
        _cptFrameActiveBonusPoint = 1; //Remise du compteur à la valeur initiale (!= 0 pour ne pas remplir la condition du if)
        EndDoublePointBonus(); //Annule les effets du bonus
    }

    //Desactive les effets du bonus d'invincibilite attrapé une fois le temps dépassé
    if(_cptFrameActiveInvincibleBonus%ACTIVE_TIME_BONUS == 0)
    {
        _invincibleBonusActive = false; //Indique le fait que le bonus n'est plus actif
        _cptFrameActiveInvincibleBonus = 1; //Remise du compteur à la valeur initiale (!= 0 pour ne pas remplir la condition du if)
        EndInvincibleBonus(); //Annule les effets du bonus
    }

    //Desactive les effets du bonus de double saut attrapé une fois le temps dépassé
    if(_cptFrameActiveDoubleJumpBonus%ACTIVE_TIME_BONUS == 0)
    {
        _doubleJumpBonusActive = false; //Indique le fait que le bonus n'est plus actif
        _cptFrameActiveDoubleJumpBonus = 1; //Remise du compteur à la valeur initiale (!= 0 pour ne pas remplir la condition du if)
        EndDoubleJumpBonus(); //Annule les effets du bonus
    }

    //Accelere le jeu toutes les 2000 frames
    if(_cptFrameScore%1500 == 0)
    {
        _speedStaticElement-= 1;         //Vitesse négative car déplacement vers la gauche
        _speedMovingElement -=1;

        /**************************************************************************************************************************************/

        for(Obstacle* e : _obstacles)
        {
            e->set_dx(_speedStaticElement);
            if(e->get_height() == Ground)
            {
                if(e->get_type() == ObstacleType3)
                    e->set_dx(_speedMovingElement);
            }
            else if(e->get_height() == Up_Air)
            {
                e->set_dx(_speedMovingElement);
            }
        }
        for(Coin* e : _coins)
            e->set_dx(_speedStaticElement);
        for(Bonus* e : _bonus)
            e->set_dx(_speedStaticElement);
    }
    incrementation(); //Incremente tous les compteurs utilisés
}





//===================================================================================================================================================
// Description : Gestion des elements mobiles
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 15/03/16
// Interêt : permet de gérer les éléments mobiles (hors joueur) : les déplacement, les collisions, les pseudo-suppression (insertion dans la 'trash')
//===================================================================================================================================================
void Model::elementManagement()
{
    deleteElement();

    for(auto e : _obstacles) // On gère chaque obstacle contenu dans le set d'obstacle
    {
        if(_player->collision(e)) //Si la balle rentre en collision avec l'obstacle
        {
            _player->damages(e->get_type()); // On enleve de la vie à la balle selon le type de l'obstacle
            _trash.insert(e);
        }

        else if((e->get_x() + e->get_w()) < 0) //Si l'obstacle sort de l'ecran
        {
            _trash.insert(e);
        }

        else
        {
            e->move(); //On déplace l'obstacle
        }
    }

    for(auto e : _coins) // On gère toutes les pièces contenues dans le set de pièce
    {
        for(auto f : _obstacles)
        {
            if(f->collision(e) && f->get_type() != ObstacleType3)
            {
                _trash.insert(e);
            }
        }

        for(auto f : _bonus)
        {
            if(f->collision(e))
            {
                _trash.insert(e);
            }
        }

        if(_player->collision(e)) //Si il y a une collision entre la balle et la pièce
        {
            addToScore(); // On ajoute des points au score
            _trash.insert(e);
            _takenCoins++;
        }

        else if((e->get_x() + e->get_w()) < 0 ) //Si la pièce sort de l'ecran
        {
            _trash.insert(e);
        }

        else
        {
            e->move(); //On déplace la pièce
        }
    }

    for(auto e : _bonus) //On gere tous les bonus du set de bonus
    {
        for(auto f : _obstacles)
        {
            if(f->collision(e) && f->get_type() != ObstacleType3)
            {
                _trash.insert(e);
            }
        }

        if(_player->collision(e)) //Si la balle rentre en collision avec un bonus
        {
            bonusEffects(e->get_type()); //On active les effets bonus selon le type du bonus
            _trash.insert(e);
        }

        else if((e->get_x() + e->get_w()) < 0) //Si le bonus sort de l'ecran
        {
            _trash.insert(e);
        }

        else
        {
            e->move(); // On deplace le bonus
        }
    }
}





//============================================================================================================
// Description : Suppression des objets mobiles
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 23/03/16
// Interêt : permet de supprimer définitivement les objets mobiles et de désallouer leur case mémoire associée
//============================================================================================================
void Model::deleteElement()
{
    for(auto e : _trash)
    {
        if(dynamic_cast<Obstacle*>(e) != nullptr)
            _obstacles.erase(_obstacles.find(dynamic_cast<Obstacle*>(e)));

        else if(dynamic_cast<Coin*>(e) != nullptr)
            _coins.erase(_coins.find(dynamic_cast<Coin*>(e)));

        else if(dynamic_cast<Bonus*>(e) != nullptr)
            _bonus.erase(_bonus.find(dynamic_cast<Bonus*>(e)));

        delete e;
    }
    _trash.clear();
}





//=========================================================================================
// Description : incrementation des compteurs de frames
// Auteur : Guillaume Nedelec
// Date : 10/03/16
// Interêt : permet d'incrementer les compteurs gérant les les étapes temporelles du modèle
//=========================================================================================
void Model::incrementation()
{
    _cptFrameScore++; //Compteur permettant de calculer le score
    _cptFrameBonus++; //Compteur permettant de gerer l'apparition des bonus
    _cptFrameCoin++; //Compteur permettant de gerer l'apparition des pièces
    _cptFrameObstacle++; //Compteur permettant de gerer l'apparition des obstacles

    if(_doublePointBonusActive) //Si le bonus de point est activé
        _cptFrameActiveBonusPoint++; //Compteur permettant de calculer le temps d'activation du bonus

    if(_invincibleBonusActive) //Si le bonus d'invincibilite est activé
        _cptFrameActiveInvincibleBonus++; //Compteur permettant de calculer le temps d'activation du bonus

    if(_doubleJumpBonusActive) //Si le bonus de double saut est activé
        _cptFrameActiveDoubleJumpBonus++; //Compteur permettant de calculer le temps d'activation du bonus

}





//=======================================================================
// Description : Accesseur de Position du joueur
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de récupérer les positions actuelles x et y du joueur
//=======================================================================
void Model::getPlayerPosition(int &x, int &y) const
{
    x = _player->get_x(); //Affecte les coordonnées x de la balle
    y = _player->get_y(); //Affecte les coordonnées y de la balle
}






//=====================================================
// Description : Mouvement du joueur
// Auteur : Guillaume Nedelec
// Date : 11/02/16
// Interêt : permet de gerer les déplacements du joueur
//=====================================================
void Model::movePlayer()
{
    int x, y;
    this->getPlayerPosition(x,y); //Recuperation des coordonnées de la balle dans x et y

    if(_player->getLeft()&& x>0+25) //Si la balle n'est pas en dehors de l'ecran (à gauche)
        _player->set_dx(_speedStaticElement-2); //On affecte un déplacement horizontal de -6 (vers la gauche)

    else if(_player->getRight() && x<(_w-25)) //Si la balle n'est pas en dehors de l'ecran (à droite)
        _player->set_dx(-(_speedStaticElement)+2); //On affecte un déplacement horizontal de 6 (vers la droite)

    else
        _player->set_dx(0); //La position de la balle ne change pas sur l'axe des abscisses

    _player->move(); //Appel du déplacement de la balle
}






//==================================================
// Description : Accesseur du joueur
// Auteur : Nicolas Marcilloux
// Date : 20/2/16
// Interêt : permet d'acceder aux méthodes du joueur
//==================================================
Player* Model::getPlayer() const
{
    return _player;
}






//===============================================================================================
// Description : Accesseur de la position d'un obstacle
// Auteur : Nicolas Marcilloux
// Date : 12/02/16
// Interêt : permet de récupérer la position d'un obstacle et de la sauvegarder dans deux entiers
//===============================================================================================

void Model::getObstaclePosition(Obstacle *obst, int &x, int &y) const
{
    x = obst->get_x();
    y = obst->get_y();
}






//===============================================================================================
// Description : Accesseur de la position d'une pièce
// Auteur : Nicolas Marcilloux
// Date : 12/02/16
// Interêt : permet de récupérer la position d'une pièce et de la sauvegarder dans deux entiers
//===============================================================================================
void Model::getCoinPosition(Coin *coin, int &x, int &y) const
{
    x = coin->get_x();
    y = coin->get_y();
}






//===============================================================================================
// Description : Accesseur de la position d'un bonus
// Auteur : Nicolas Marcilloux
// Date : 12/02/16
// Interêt : permet de récupérer la position d'un bonus et de la sauvegarder dans deux entiers
//===============================================================================================
void Model::getBonusPosition(Bonus *bonus, int &x, int &y) const
{
    x = bonus->get_x();
    y = bonus->get_y();
}






//===============================================================
// Description : Incrementation du score
// Auteur : Guillaume Nedelec
// Date : 16/02/16
// Interêt : permet d'incrémenter le score en fonction des frames
//===============================================================
void Model::scoreCalculation()
{
    //Toute les 35 frames (environ 1 seconde) le score s'incremente de 1
    if(_cptFrameScore%35==0)
    {
        _score++;
    }
}






//=================================================
// Description : Accesseur du score
// Auteur : Nicolas Marcilloux
// Date : 12/02/16
// Interêt : permet de récupérer la valeur du score
//=================================================
unsigned int Model::getScore() const
{
    return _score;
}




//========================================================================
// Description : Accesseur des pièces récupérées
// Auteur : Nicolas Marcilloux
// Date : 15/05/16
// Interêt : permet de récupérer le nombre pièces récupérées par le joueur
//========================================================================
unsigned int Model::getTakenCoins() const
{
    return _takenCoins;
}




//=======================================================================
// Description : Ajout d'élements mobiles
// Auteur : Nicolas Marcilloux
// Date : 14/03/16
// Interêt : permet de construire les éléments mobiles de façon aléatoire
//=======================================================================
void Model::addElement(Element elem)
{
    int elementType;
    int elementHeight;
    //---------------------------------OBSTACLES----------------------------------//
    if (elem==Ennemies)
    {
        elementType = rand()%3; //Permet une génération aléatoire du type de l'élément
        elementHeight = rand()%6; //Permet une génération aléatoire de la Hauteur (au sol ou en l'air)

        if((elementHeight <=4 )) // Obstacles "au sol" (5 chances sur 9)
        {
            if(elementType == ObstacleType1) //ajout d'un obstacle de type 0 dans le set
            {
                Obstacle* obst = new Obstacle(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_GROUND, WIDTH_ROCK, HEIGHT_ROCK, _speedStaticElement, 0, ObstacleType1, Ground); // LITTLE ROCK
                _obstacles.insert(obst);
            }

            else if(elementType == ObstacleType2)
            {
                Obstacle* obst = new Obstacle(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_TREE+10, WIDTH_TREE, HEIGHT_TREE, _speedStaticElement, 0, ObstacleType2, Ground); // TREE
                _obstacles.insert(obst);
            }

            else if(elementType == ObstacleType3)
            {
                Obstacle* obst = new Obstacle(INIT_POSX_MOVABLE_ELEMENT, 425, WIDTH_WOLF, HEIGHT_WOLF, _speedMovingElement, 0, ObstacleType3, Ground); // WOLF
                _obstacles.insert(obst);
            }
        }

        else if(elementHeight > 4) // Obstacles "en l'air" (4 chances sur 9)
        {
            if(elementType == ObstacleType1)
            {
                Obstacle* obst = new Obstacle(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_UP_AIR, WIDTH_BIRD, HEIGHT_BIRD, _speedMovingElement, 0, ObstacleType1, Up_Air); // MISSILE
                _obstacles.insert(obst);
            }

            if(elementType == ObstacleType2)
            {
                Obstacle* obst = new Obstacle(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_UP_AIR, WIDTH_EAGLE, HEIGHT_EAGLE, _speedMovingElement, 0, ObstacleType2, Up_Air); // EAGLE
                _obstacles.insert(obst);
            }

            else if(elementType == ObstacleType3)
            {
                Obstacle* obst = new Obstacle(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_UP_AIR-50, WIDTH_HELICO, HEIGHT_HELICO, _speedMovingElement, 0, ObstacleType3, Up_Air); // HELICO
                _obstacles.insert(obst);
            }
        }
    }

    //---------------------------------COINS----------------------------------//

    else if (elem==Points)
    {
        elementType = rand()%3;
        elementHeight = rand()%8;

        if(elementHeight <= 4) // Pièces "au sol" ( 5 chances sur 8)
        {
            if(elementType == SeriesOf3) // serie de 3 pièces d'affilée
            {
                Coin* coin = new Coin(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                Coin* coin2 = new Coin(INIT_POSX_MOVABLE_ELEMENT+50, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                Coin* coin3 = new Coin(INIT_POSX_MOVABLE_ELEMENT+100, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                _coins.insert(coin);
                _coins.insert(coin2);
                _coins.insert(coin3);
            }

            else if(elementType == SeriesOf4) // serie de 4 pièces d'affilée
            {
                Coin* coin = new Coin(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                Coin* coin2 = new Coin(INIT_POSX_MOVABLE_ELEMENT+50, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                Coin* coin3 = new Coin(INIT_POSX_MOVABLE_ELEMENT+100, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                Coin* coin4 = new Coin(INIT_POSX_MOVABLE_ELEMENT+150, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                _coins.insert(coin);
                _coins.insert(coin2);
                _coins.insert(coin3);
                _coins.insert(coin4);
            }

            else if(elementType == SeriesOf5) // serie de 5 pièces d'affilée
            {
                Coin* coin = new Coin(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                Coin* coin2 = new Coin(INIT_POSX_MOVABLE_ELEMENT+50, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                Coin* coin3 = new Coin(INIT_POSX_MOVABLE_ELEMENT+100, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                Coin* coin4 = new Coin(INIT_POSX_MOVABLE_ELEMENT+150, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                Coin* coin5 = new Coin(INIT_POSX_MOVABLE_ELEMENT+200, INIT_POSY_GROUND, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Ground);
                _coins.insert(coin);
                _coins.insert(coin2);
                _coins.insert(coin3);
                _coins.insert(coin4);
                _coins.insert(coin5);
            }
        }

        else if(elementHeight > 4) // Pièces "en l'air" (3 chances sur 8)
        {
            if(elementType == SeriesOf3)
            {
                Coin* coin = new Coin(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                Coin* coin2 = new Coin(INIT_POSX_MOVABLE_ELEMENT+50, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                Coin* coin3 = new Coin(INIT_POSX_MOVABLE_ELEMENT+100, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                _coins.insert(coin);
                _coins.insert(coin2);
                _coins.insert(coin3);

            }

            else if(elementType == SeriesOf4)
            {
                Coin* coin = new Coin(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                Coin* coin2 = new Coin(INIT_POSX_MOVABLE_ELEMENT+50, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                Coin* coin3 = new Coin(INIT_POSX_MOVABLE_ELEMENT+100, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                Coin* coin4 = new Coin(INIT_POSX_MOVABLE_ELEMENT+150, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                _coins.insert(coin);
                _coins.insert(coin2);
                _coins.insert(coin3);
                _coins.insert(coin4);
            }

            else if(elementType == SeriesOf5)
            {
                Coin* coin = new Coin(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                Coin* coin2 = new Coin(INIT_POSX_MOVABLE_ELEMENT+50, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                Coin* coin3 = new Coin(INIT_POSX_MOVABLE_ELEMENT+100, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                Coin* coin4 = new Coin(INIT_POSX_MOVABLE_ELEMENT+150, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                Coin* coin5 = new Coin(INIT_POSX_MOVABLE_ELEMENT+200, INIT_POSY_MID_AIR, SIZE_COIN,SIZE_COIN, _speedStaticElement, 0, Mid_Air);
                _coins.insert(coin);
                _coins.insert(coin2);
                _coins.insert(coin3);
                _coins.insert(coin4);
                _coins.insert(coin5);
            }
        }
    }

    //---------------------------------BONUS----------------------------------//

    else if (elem==PowerUp)
    {
        elementType = rand()%30;
        elementHeight = rand()%2;

        if((elementHeight == 0)) // Bonus "au sol" (1 chance sur 2)
        {

            if(elementType <= 6) //Bonus d'invincibilité
            {
                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_GROUND, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Invincible, Ground);
                _bonus.insert(bonus);
            }

            else if(elementType > 6 && elementType <= 14) //Bonus de santé
            {
                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_GROUND, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Health, Ground);
                _bonus.insert(bonus);
            }

            else if(elementType > 14 && elementType <= 20) //Bonus double saut
            {
                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_GROUND, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Jump, Ground);
                _bonus.insert(bonus);
            }

            else if(elementType > 20 && elementType <= 26) //Bonus Point x2
            {
                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_GROUND, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Pointx2, Ground);
                _bonus.insert(bonus);
            }

            else  //Bonus Nucleaire
            {

                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_GROUND, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Nuke, Ground);
                _bonus.insert(bonus);
            }

        }

        else if((elementHeight == 1)) // Bonus "en l'air" (1 chance sur 2)
        {
            if(elementType <= 6)
            {
                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_MID_AIR, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Invincible, Mid_Air);
                _bonus.insert(bonus);
            }

            else if(elementType > 6 && elementType <= 14)
            {
                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_MID_AIR, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Health, Mid_Air);
                _bonus.insert(bonus);
            }

            else if(elementType > 14 && elementType <= 20)
            {
                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_MID_AIR, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Jump, Mid_Air);
                _bonus.insert(bonus);
            }

            else if(elementType > 20 && elementType <= 26)
            {
                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_MID_AIR, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Pointx2, Mid_Air);
                _bonus.insert(bonus);
            }

            else
            {
                Bonus* bonus = new Bonus(INIT_POSX_MOVABLE_ELEMENT, INIT_POSY_MID_AIR, SIZE_BONUS, SIZE_BONUS, _speedStaticElement, 0, Nuke, Mid_Air);
                _bonus.insert(bonus);
            }
        }
    }
}





//=================================================
// Description : Accesseur du set d'obstacles
// Auteur : Guillaume Nedelec
// Date : 10/03/16
// Interêt : permet de récupérer le set d'obstacles
//=================================================
std::set<Obstacle *> Model::getObstacle() const
{
    return _obstacles;
}





//===============================================
// Description : Accesseur du set de pièces
// Auteur : Guillaume Nedelec
// Date : 10/03/16
// Interêt : permet de récupérer le set de pièces
//===============================================
std::set<Coin *> Model::getCoin() const
{
    return _coins;
}





//==============================================
// Description : Accesseur du set de Bonus
// Auteur : Guillaume Nedelec
// Date : 10/03/16
// Interêt : permet de récupérer le set de Bonus
//==============================================
std::set<Bonus *> Model::getBonus() const
{
    return _bonus;
}





//============================================================================
// Description : Accesseur des délais d'apparitions d'éléments mobiles
// Auteur : Guillaume Nedelec
// Date : 13/03/16
// Interêt : permet de récupérer les délais d'apparitions des éléments mobiles
//============================================================================
unsigned int Model::getDuration(Element elem) const
{
    if (elem==Ennemies) //Pour les obstacles
    {
        return (MIN_APPARITION_OBSTACLE + 2*(int)(_speedStaticElement)) + (rand() % ((MAX_APPARITION_OBSTACLE + (int)(_speedStaticElement)) - MIN_APPARITION_OBSTACLE));
    }

    else if (elem==Points) // Pour les pièces
    {
        return MIN_APPARITION_COIN + (rand() % (MAX_APPARITION_COIN - MIN_APPARITION_COIN));
    }

    else if(elem==PowerUp)// Pour les Bonus
    {
        return MIN_APPARITION_BONUS+ (rand() % (MAX_APPARITION_BONUS- MIN_APPARITION_BONUS));
    }
    else
        return 0;
}





//======================================
// Description : Augmente le score
// Auteur : Guillaume Nedelec
// Date : 09/03/16
// Interêt : permet d'augmenter le score
//======================================
void Model::addToScore()
{
    if(!_doublePointBonusActive) //Lorsque le bonus Points x2 n'est pas actif
        _score +=ADD_TO_SCORE;
    else
        _score+=ADD_TO_SCORE_WITH_BONUS;
}






//================================================
// Description : Effets des bonus
// Auteur : Guillaume Nedelec
// Date : 15/03/16
// Interêt : permet d'activer les effets des bonus
//================================================
void Model::bonusEffects(BonusType type)
{
    if(type == Invincible) //Bonus d'invincibilité
    {
        if(!_invincibleBonusActive)
        {
            _player->setInvincibleBonus(true); //Active le bonus
            _invincibleBonusActive = true; //Indique que ce bonus est activé
        }
        else
            _cptFrameActiveInvincibleBonus=1;
    }
    else if(type == Health) //Bonus santé
    {
        _player->addLife(); //ajoute 20 points de vie à la balle
    }
    else if(type == Jump) //Bonus double saut
    {
        if(!_doubleJumpBonusActive)
        {
            _player->setDoubleJumpBonus(true);
            _doubleJumpBonusActive = true; //Indique que ce bonus est activé
        }
        else
            _cptFrameActiveDoubleJumpBonus=1;
    }
    else if(type == Pointx2) // Bonus Point x2
    {
        if(!_doublePointBonusActive)
            _doublePointBonusActive = true; //Active le bonus
        else
            _cptFrameActiveBonusPoint=1;
    }
    else if(type == Nuke)
    {
        for(auto e : _obstacles)
        {
            _trash.insert(e);
        }

        for(auto e : _coins)
        {
            _trash.insert(e);
        }

        for(auto e : _bonus)
        {
            _trash.insert(e);
        }
    }
}






//========================================================
// Description : Fin Bonus Invincible
// Auteur : Guillaume Nedelec
// Date : 10/03/16
// Interêt : permet de mettre fin au bonus d'invincibilité
//========================================================
void Model::EndInvincibleBonus()
{
    _player->setInvincibleBonus(false);
}





//=================================================================
// Description : Fin Bonus x2
// Auteur : Guillaume Nedelec
// Date : 10/03/16
// Interêt : permet de mettre fin au bonus multiplicateur de points
//=================================================================
void Model::EndDoublePointBonus()
{
    _doublePointBonusActive = false;
}





//=======================================================
// Description : Fin Bonus Double Saut
// Auteur : Guillaume Nedelec
// Date : 10/03/16
// Interêt : permet de mettre fin au bonus de double saut
//=======================================================
void Model::EndDoubleJumpBonus()
{
    _player->setDoubleJumpBonus(false);
}





//===========================================================================
// Description : Accesseur de vitesse d'éléments statiques
// Auteur : Guillaume Nedelec
// Date : 12/04/16
// Interêt : permet de recupérer la valeur de la vitesse d'élements statiques
//===========================================================================
float Model::getSpeedElement() const
{
    return _speedStaticElement;
}





//==========================================================================
// Description : Accesseur de vitesse d'éléments Mouvants
// Auteur : Guillaume Nedelec
// Date : 12/04/16
// Interêt : permet de recupérer la valeur de la vitesse d'élements Mouvants
//==========================================================================
float Model::getSpeedMovingElement() const
{
    return _speedMovingElement;
}





//===============================================================
// Description : Réinitialisation du jeu
// Auteur : Guillaume Nedelec
// Date : 16/05/16
// Interêt : permet de relancer le jeu avec ses valeurs de départ
//===============================================================
void Model::reset()
{
    _player->reset();

    if(_endGame)
        bestScoresManagement();

    _score = 0;
    _takenCoins = 0;
    _cptFrameScore=1;
    _cptFrameObstacle=0;
    _cptFrameCoin=0;
    _cptFrameBonus=0;
    _cptFrameActiveBonusPoint =1;
    _cptFrameActiveInvincibleBonus =1;

    _obstacleAppears = false;
    _coinAppears = false;
    _bonusAppears = false;

    _doublePointBonusActive = false;
    _invincibleBonusActive = false;
    _doubleJumpBonusActive = false;

    if(_difficulty == Easy)
    {
        _speedStaticElement = -3;
        _speedMovingElement = -6;
    }

    else if(_difficulty == Medium)
    {
        _speedStaticElement = -4;
        _speedMovingElement = -7;
    }

    else if(_difficulty == Hard)
    {
        _speedStaticElement = -5;
        _speedMovingElement = -8;
    }

    for(Obstacle * e : _obstacles)
        delete (e);
    for(Coin * e : _coins)
        delete (e);
    for(Bonus * e : _bonus)
        delete (e);


    _obstacles.clear();
    _coins.clear();
    _bonus.clear();
    _trash.clear();
}





//================================================================
// Description : Accesseur de l'activation du bonus x2
// Auteur : Guillaume Nedelec
// Date : 08/03/16
// Interêt : permet de savoir si le bonus multiplicateur est actif
//================================================================
bool Model::getDoublePointBonus() const
{
    return _doublePointBonusActive;
}





//==================================================================
// Description : Accesseur de la 'poubelle' à éléments mobiles (set)
// Auteur : Guillaume Nedelec
// Date : 15/03/16
// Interêt : permet d'avoir accès à la 'poubelle' à éléments mobiles
//==================================================================
set<MovableElement*> Model::getRemovable() const
{
    return _trash;
}




//=====================================================================================
// Description : Augmentation de la difficulté
// Auteur : Guillaume Nedelec
// Date : 10/05/16
// Interêt : permet d'augmenter la difficulté ainsi que la vitesse des éléments mobiles
//=====================================================================================
void Model::addDifficulty()
{
    if(_difficulty == Medium)
    {
        _difficulty = Hard;
        _speedStaticElement = -5;
        _speedMovingElement = -8;
    }
    else if(_difficulty == Easy)
    {
        _difficulty = Medium;
        _speedStaticElement = -4;
        _speedMovingElement = -7;
    }
}





//=====================================================================================
// Description : Diminuation de la difficulté
// Auteur : Guillaume Nedelec
// Date : 10/05/16
// Interêt : permet de diminuer la difficulté ainsi que la vitesse des éléments mobiles
//=====================================================================================
void Model::decreaseDifficulty()
{
    if(_difficulty == Medium)
    {
        _difficulty = Easy;
        _speedStaticElement = -3;
        _speedMovingElement = -6;
    }
    else if(_difficulty == Hard)
    {
        _difficulty = Medium;
        _speedStaticElement = -4;
        _speedMovingElement = -7;
    }
}





//=========================================================
// Description : Accesseur de la difficulté du jeu
// Auteur : Guillaume Nedelec
// Date : 15/03/16
// Interêt : permet de savoir la difficulté actuelle du jeu
//=========================================================
Difficulty Model::getDifficulty()
{
    return _difficulty;
}





//========================================================
// Description : Accesseur de la fin de jeu
// Auteur : Guillaume Nedelec
// Date : 15/03/16
// Interêt : permet de savoir si le jeu est terminé ou non
//========================================================
bool Model::getEndGame()
{
    return _endGame;
}





//==================================================
// Description : Mutateur de la fin de jeu
// Auteur : Guillaume Nedelec
// Date : 15/03/16
// Interêt : permet d'appliquer la fin du jeu ou non
//==================================================
void Model::setEndGame(bool b)
{
    _endGame = b;
}





//=======================================================================================================
// Description : Gestion des meilleurs scores
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de lire le fichier score.txt et de le modifier si le joueur rentre dans le classement
//=======================================================================================================
void Model::bestScoresManagement()
{
    fstream f;
    int element;
    int location = -1;
    int i=0;
    string fichier = "scores.txt";
    bool foundLocation = false;
    unsigned int saveScore[5];

    std::ifstream infile(fichier);
    if(infile.good())
    {
        f.open(fichier.c_str(), ios:: in); //Ouverture en lecture

        if(f.fail())
        {
            std::cerr << "ouverture en lecture impossible" << endl;
            exit(EXIT_FAILURE);
        }
        while(!f.eof())
        {
            f >> element;
            saveScore[i] = element;
            i++;
        }
        f.close();

        i=0;

        while(!foundLocation && i<5)
        {
            if(_score > saveScore[i] )
            {
                foundLocation = true;
                location = i;
            }
            else
                i++;
        }

        if(foundLocation)
        {
            for(int i = 5; i > location; i--)
                saveScore[i] = saveScore[i-1];

            saveScore[location] = _score;
        }
    }
    else
    {
        saveScore[0] = _score;
        for(int i = 1; i < 5; i++)
            saveScore[i] = 0;
    }

    f.open(fichier.c_str(), ios::out);
    if(f.fail())
    {
        std::cerr << "ouverture en ecriture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    for(i=0;i<5 ; i++)// i<5 parce qu'il n'y a que 5 meilleurs scores
    {
        f << saveScore[i] << endl; //on copie le fichier tampon dans le fichier meilleur score en effaçant ce qu'il y avait au préalable.
    }
    f.close();
}
