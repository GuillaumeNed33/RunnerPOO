#ifndef _MODEL_
#define _MODEL_

#include "Player.h"
#include "Obstacle.h"
#include "Coin.h"
#include "Bonus.h"
#include <set>

//TAILLES DES DIFFERENTS ELEMENTS MOBILES DU JEU
static const unsigned int SIZE_BONUS = 50;
static const unsigned int SIZE_COIN = 30;

static const unsigned int WIDTH_BIRD = 75;
static const unsigned int HEIGHT_BIRD = 40;

static const unsigned int WIDTH_HELICO = 100;
static const unsigned int HEIGHT_HELICO = 100;

static const unsigned int WIDTH_EAGLE = 100;
static const unsigned int HEIGHT_EAGLE = 50;

static const unsigned int WIDTH_ROCK = 50;
static const unsigned int HEIGHT_ROCK = 50;

static const unsigned int WIDTH_TREE = 60;
static const unsigned int HEIGHT_TREE = 110;

static const unsigned int WIDTH_WOLF = 100;
static const unsigned int HEIGHT_WOLF = 75;

//Designe le type d'éléments mobiles
enum Element
{
    Ennemies,
    Points,
    PowerUp
};

//Difficulté
enum Difficulty {
    Easy,
    Medium,
    Hard
};

class Player;


//=========================================================================
// Description:
//
// Cette classe est le coeur du jeu. Chaque étape du jeu se déroule dans cette classe (déplacement, apparition d'éléments ect...)
//=========================================================================
class Model {
private:

    //Temps minimum et maximum d'apparition
    static const unsigned int MIN_APPARITION_OBSTACLE = 50;
    static const unsigned int MAX_APPARITION_OBSTACLE = 100;
    static const unsigned int MIN_APPARITION_COIN = 300;
    static const unsigned int MAX_APPARITION_COIN = 500;
    static const unsigned int MIN_APPARITION_BONUS = 200;
    static const unsigned int MAX_APPARITION_BONUS = 300;
    static const unsigned int ACTIVE_TIME_BONUS = 450;

    //POSITION A LA CREATION DES OBJETS
    static const int INIT_POSX_PLAYER = 100;
    static const int INIT_POSY_PLAYER = 470;
    static const int INIT_POSX_MOVABLE_ELEMENT = 1300;
    static const int INIT_POSY_GROUND = 450;
    static const int INIT_POSY_MID_AIR = 340;
    static const int INIT_POSY_UP_AIR = 280;
    static const int INIT_POSY_TREE = INIT_POSY_GROUND - HEIGHT_TREE + 25;

    //VALEUR D'AJOUT DE SCORE
    static const unsigned int ADD_TO_SCORE = 100;
    static const unsigned int ADD_TO_SCORE_WITH_BONUS = 200;

    int _w, _h; // Taille du modele
    unsigned int _score = 0;
    unsigned int _takenCoins = 0; //Nombres de pièces récupérées
    float _speedStaticElement = -4; //Vitesse des éléments statiques (pierre, arbre ect..)
    float _speedMovingElement = -7; //Vitesse des éléments mobiles (hélico, aigle ect...)
    Difficulty _difficulty = Medium;
    bool _endGame =false;

    //Compeur de frame utilisé pour diverses fonctions
    unsigned int _cptFrameScore = 1;
    unsigned int _cptFrameObstacle = 0;
    unsigned int _cptFrameCoin = 0;
    unsigned int _cptFrameBonus = 0;
    unsigned int _cptFrameActiveBonusPoint = 1;
    unsigned int _cptFrameActiveInvincibleBonus = 1;
    unsigned int _cptFrameActiveDoubleJumpBonus = 1;

    //DELAIS D4APPARITION
    unsigned int apparitionTimeObstacle;
    unsigned int apparitionTimeCoin;
    unsigned int apparitionTimeBonus;

    //INDICATEUR D'APPARITION
    bool _obstacleAppears = false;
    bool _coinAppears = false;
    bool _bonusAppears = false;

    //INDICATEUR DE BONUS
    bool _doublePointBonusActive = false;
    bool _invincibleBonusActive= false;
    bool _doubleJumpBonusActive = false;

    //CONTENEURS D'ELEMENTS
    std::set<Obstacle *> _obstacles;
    std::set<Coin *> _coins;
    std::set<Bonus *> _bonus;
    std::set<MovableElement*>_trash;

public:
    Player * _player;
    Model(int w, int h);
    ~Model();
    Player* getPlayer() const;

    void nextStep();
    void getPlayerPosition(int &x, int &y) const;
    void getObstaclePosition(Obstacle *obst, int &x, int &y) const;
    void getCoinPosition(Coin *coin, int &x, int &y) const;
    void getBonusPosition(Bonus *bonus, int &x, int &y) const;
    void movePlayer();
    void scoreCalculation();
    unsigned int getScore() const;
    unsigned int getTakenCoins() const;

    std::set<Obstacle *> getObstacle() const;
    std::set<Coin *> getCoin() const;
    std::set<Bonus *> getBonus() const;
    std::set<MovableElement *> getRemovable() const;

    void addElement(Element elem);
    unsigned int getDuration(Element elem) const;

    void incrementation();
    void elementApparition();
    void elementManagement();

    void deleteElement();

    void addToScore();
    void bonusEffects(BonusType type);
    void EndInvincibleBonus();
    void EndDoublePointBonus();
    void EndDoubleJumpBonus();
    bool getDoublePointBonus() const;
    float getSpeedElement() const;
    float getSpeedMovingElement() const;
    void addDifficulty();
    void decreaseDifficulty();
    Difficulty getDifficulty();
    void setEndGame(bool b);
    bool getEndGame();
    void reset();
    void bestScoresManagement();
};

#endif

