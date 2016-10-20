#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"
#include "Model.h"
#include "Button.h"

// Liens vers les fichiers images utilisés dans GameView et dans Rules

const std::string SILVER_COIN = "Images/MovableElement/Coins/SilverCoins.png";
const std::string GOLD_COIN = "Images/MovableElement/Coins/GoldCoins.png";
const std::string BONUS_LIFE = "Images/MovableElement/Bonus/BonusHealth.png";
const std::string BONUS_POINT = "Images/MovableElement/Bonus/BonusDoublePoint.png";
const std::string BONUS_INVINCIBLE = "Images/MovableElement/Bonus/BonusInvincible.png";
const std::string BONUS_JUMP = "Images/MovableElement/Bonus/BonusDoubleJump.png";
const std::string BONUS_NUKE = "Images/MovableElement/Bonus/BonusNuke.png";

const std::string TREE = "Images/MovableElement/Obstacles/tree.png";
const std::string ROCK = "Images/MovableElement/Obstacles/rock.png";
const std::string WOLF = "Images/MovableElement/Obstacles/wolves.png";
const std::string EAGLE = "Images/MovableElement/Obstacles/eagle.png";
const std::string HELICO = "Images/MovableElement/Obstacles/helico.png";
const std::string BIRD = "Images/MovableElement/Obstacles/bird.png";

const std::string YETI_WALK = "Images/MovableElement/Yeti/YetiWalk.png";


//=========================================================================
// Description:
//
// Cette classe représente la partie graphique du jeu
// Elle recupère les informations du modèle pour les retranscrire à l'écran
//=========================================================================
class GameView : public View
{
private :

    // Liens vers les fichiers images (.png) utilisés dans GameView
    const std::string EXPLOSION = "Images/MovableElement/Obstacles/Explosion.png";
    const std::string SHIELD = "Images/MovableElement/Yeti/Shield.png";
    const std::string LIFEBAR = "Images/LifeBar/LifeBar.png";
    const std::string IMPACT = "Images/MovableElement/Obstacles/explosion.png";
    const std::string YETI_JUMP = "Images/MovableElement/Yeti/YetiJump.png";
    const std::string YETI_JUMP2 = "Images/MovableElement/Yeti/YetiJump2.png";
    const std::string AVATAR = "Images/MovableElement/Yeti/yetiFaces.png";
    const std::string NUKE = "Images/MovableElement/Bonus/Nuke.png";

    // Liens vers les fichiers sons (.wav) utilisés dans GameView
    const std::string SOUND_COIN = "Sounds/coin.wav";
    const std::string SOUND_BONUS = "Sounds/Bonus.wav";
    const std::string SOUND_HEALTHBONUS = "Sounds/HealthBonus.wav";
    const std::string SOUND_WOLF = "Sounds/wolf.wav";
    const std::string SOUND_EAGLE = "Sounds/eagle.wav";
    const std::string SOUND_NUKE = "Sounds/nuke.wav";
    const std::string SOUND_HELICO = "Sounds/helico.wav";
    const std::string SOUND_IMPACT = "Sounds/impact.wav";


    Model * _model; // variable permettant d'accéder aux données du modèle

    int _scoreView;

    //HORLOGES
    sf::Clock _clock;
    sf::Clock _clockNuke;
    sf::Clock _clockCopter;
    sf::Clock _clockMovingElem;
    sf::Clock _clockStaticElem;
    bool _doubleJumpBonusActivated = false;
    bool _gameOver = false;
    bool _colStaticElement = false;
    bool _colMovingElement = false;
    bool _colTree = false;
    bool _colHelico = false;
    int _col_x, _col_y, _posXCopter, _posYCopter, _posXElem, _posYElem;
    int _nuke_x, _nuke_y;
    bool _left = false;
    bool _nukeActivation = false;
    bool _jump = false;
    bool _invincible = false;
    sf::RectangleShape _flashBomb;
    int _opacity = 0;
    bool _endNukeFlash = false;

    sf::RectangleShape _lifeLevel;
    sf::RectangleShape _delimitation{sf::Vector2f{1200,5}};

    // ELEMENTS GRAPHIQUES OBSTACLES
    GraphicElement* _tree;
    GraphicElement* _rock;
    // ELEMENTS GRAPHIQUES ANIMES OBSTACLES
    AnimatedGraphicElement* _helico;
    AnimatedGraphicElement* _bird;
    AnimatedGraphicElement* _wolf;
    AnimatedGraphicElement* _eagle;

    // ELEMENTS GRAPHIQUES BONUS
    GraphicElement* _bonusInvincible;
    GraphicElement* _bonusLife;
    GraphicElement* _bonusDoubleJump;
    GraphicElement* _bonusDoublePoint;
    GraphicElement* _bonusNuke;

    // ELEMENTS GRAPHIQUES ANIMES PIECES
    AnimatedGraphicElement* _coin;

    // ELEMENT GRAPHIQUE LIFEBAR
    GraphicElement* _lifebar;

    // ELEMENT GRAPHIQUE YETI JUMP
    GraphicElement* _yetiJump;
    GraphicElement* _yetiJump2;
    // ELEMENT GRAPHIQUE ANIME YETI & AVATAR
    AnimatedGraphicElement* _yeti;
    AnimatedGraphicElement* _yetiFace;

    // ELEMENT GRAPHIQUE ANIME SHIELD
    AnimatedGraphicElement* _shield;

    // ELEMENT GRAPHIQUE ANIME COLLISION
    AnimatedGraphicElement* _nuke;
    AnimatedGraphicElement* _impact;
    AnimatedGraphicElement* _explosion;

    // VECTEURS DE LECTURE DES FEUILLES DE SPRITES
    // PIECES
    std::vector<sf::IntRect> AnimCoin;
    // SHIELD
    std::vector<sf::IntRect> AnimShield;
    std::vector<sf::IntRect> AnimShield2;
    // OBSTACLES
    std::vector<sf::IntRect> AnimWolf;
    std::vector<sf::IntRect> AnimEagle;
    std::vector<sf::IntRect> AnimHelico;
    std::vector<sf::IntRect> AnimBird;
    // COLLISION
    std::vector<sf::IntRect> AnimNuke;
    std::vector<sf::IntRect> AnimImpact;
    std::vector<sf::IntRect> AnimExplosion;
    // YETI
    std::vector<sf::IntRect> AnimYetiForward;
    std::vector<sf::IntRect> AnimYetiBackward;
    std::vector<sf::IntRect> AnimYetiStand;
    std::vector<sf::IntRect> AnimYetiHit;

    // TEXTE DES INFOS DU JEU
    sf::Text _score_distance;
    sf::Text _lifeInfo;
    sf::Text _textPause;
    sf::Text _takenCoins;
    sf::Text _overText;
    sf::Text _highScores;

    // SONS DU JEU
    sf::Sound _soundCoins;
    sf::Sound _soundBonus;
    sf::Sound _soundHealthBonus;
    sf::Sound _soundWolf;
    sf::Sound _soundEagle;
    sf::Sound _soundNuke;
    sf::Sound _soundHelico;
    sf::Sound _soundImpact;

    // BUFFER DE CHARGEMENT DES SONS
    sf::SoundBuffer _bufferCoin;
    sf::SoundBuffer _bufferBonus;
    sf::SoundBuffer _bufferHealthBonus;
    sf::SoundBuffer _bufferWolf;
    sf::SoundBuffer _bufferEagle;
    sf::SoundBuffer _bufferImpact;
    sf::SoundBuffer _bufferHelico;
    sf::SoundBuffer _bufferNuke;

    // TEXTURE DES ELEMENTS GRAPHIQUES
    sf::Texture _TextureNuke;
    sf::Texture _TextureTree;
    sf::Texture _TextureRock;
    sf::Texture _TextureLifebar;
    sf::Texture _TextureBonusNuke;
    sf::Texture _TextureBonusInvincible;
    sf::Texture _TextureBonusLife;
    sf::Texture _TextureBonusPoint;
    sf::Texture _TextureBonusJump;
    sf::Texture _TextureSilverCoin;
    sf::Texture _TextureGoldCoin;
    sf::Texture _TextureShield;
    sf::Texture _TextureShield2;
    sf::Texture _TextureWolf;
    sf::Texture _TextureEagle;
    sf::Texture _TextureCollision;
    sf::Texture _TextureYeti;
    sf::Texture _TextureHelico;
    sf::Texture _TextureBird;
    sf::Texture _TextureExplosion;
    sf::Texture _TextureYetiJump;
    sf::Texture _TextureYetiJump2;
    sf::Texture _TextureYetiFaces;

    // STRING VARIABLES CONTENANT DIVERSES INFORMATIONS
    std::string _stringTextPause;
    std::string _stringResume;
    std::string _stringRules;
    std::string _stringBacktoMenu;
    std::string _stringHighScores;

    /*** PARTIE PAUSE ***/

    // BOOLEENS DE JEU
    bool _pause = false;
    bool _game = true;

    // BOUTONS DU MENU PAUSE
    Button* _resume_game;
    Button* _rules;
    Button* _backToMenu;

    // TITRE DE LA PAUSE
    sf::Text _pauseTitle;

    // RECTANGLE DU HEADER DE LA PAUSE
    sf::RectangleShape _header;

public:
    GameView(int w, int h, sf::RenderWindow *window);
    GameView() = delete;
    ~GameView() override;
    void draw() override;
    void synchronize() override;
    bool treatEvents() override;
    void setModel(Model * model);
    void cuttingSprite();
    bool loadImages();
    void cleanSprite();
    void loadSound();
    bool getPause();
    bool checkScore();
};

#endif // GAMEVIEW_H
