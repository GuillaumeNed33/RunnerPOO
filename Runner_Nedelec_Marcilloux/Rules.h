#ifndef RULES_H
#define RULES_H

#include "View.h"
#include "Button.h"

class Rules : public View
{
private:
    const std::string ARROW = "Images/Boutons/arrow.png";

    sf::RectangleShape _header;
    sf::Text _title;
    std::string _stringTitle;
    sf::RectangleShape _struct;

    //Elements textes utilisés pour les règles
    sf::Text _subTitle;
    std::string _stringSubTitle;

    sf::Text _subSubTitle;
    std::string _stringSubSubTitle;

    sf::Text _subSubTitle2;
    std::string _stringSubSubTitle2;

    sf::Text _desc1;
    std::string _stringDesc1;

    sf::Text _desc2;
    std::string _stringDesc2;

    sf::Text _desc3;
    std::string _stringDesc3;

    sf::Text _desc4;
    std::string _stringDesc4;

    sf::Text _desc5;
    std::string _stringDesc5;

    sf::Text _desc6;
    std::string _stringDesc6;

    sf::Text _closeInfo;
    std::string _stringCloseInfo;

    //Indique sur quelle page se situe l'utilisateur
    bool _page1 = true;
    bool _page2 = false;
    bool _page3 = false;

    //Boutons pour changer de pages
    Button* _nextPage;
    Button* _previousPage;
    std::string _stringNextButton;
    std::string _stringPreviousButton;

   /// ELEMENTS DES DIFFERENTES PAGES

    // PAGE 1 : JOUEUR ET OBJECTIFS
    AnimatedGraphicElement* _yeti;
    sf::Texture _TextureYeti;
    GraphicElement* _arrow;
    sf::Texture _TextureArrow;

    // PAGE 2 : LES OBSTACLES
    GraphicElement* _tree;
    GraphicElement* _rock;
    AnimatedGraphicElement* _wolf;
    AnimatedGraphicElement* _bird;
    AnimatedGraphicElement* _eagle;
    AnimatedGraphicElement* _copter;

    std::vector<sf::IntRect> AnimYeti;
    std::vector<sf::IntRect> AnimBird;
    std::vector<sf::IntRect> AnimWolf;
    std::vector<sf::IntRect> AnimEagle;
    std::vector<sf::IntRect> AnimCopter;

    sf::Texture _TextureTree;
    sf::Texture _TextureRock;
    sf::Texture _TextureWolf;
    sf::Texture _TextureEagle;
    sf::Texture _TextureBird;
    sf::Texture _TextureCopter;


    // PAGE 3 : LES BONUS
    GraphicElement* _bonusHealth;
    GraphicElement* _bonusJump;
    GraphicElement* _bonusShield;
    GraphicElement* _bonusNuke;
    GraphicElement* _bonusPoint;
    AnimatedGraphicElement *_silverCoin;
    AnimatedGraphicElement *_goldCoin;

    std::vector<sf::IntRect> AnimCoin;

    sf::Texture _TextureBonusNuke;
    sf::Texture _TextureBonusInvincible;
    sf::Texture _TextureBonusLife;
    sf::Texture _TextureBonusPoint;
    sf::Texture _TextureBonusJump;
    sf::Texture _TextureSilverCoin;
    sf::Texture _TextureGoldCoin;



public:
    Rules(int w, int h, sf::RenderWindow* window);
    ~Rules();
    void draw();
    bool treatEvents();
    void synchronize();
    bool loadImages();
};

#endif // RULES_H
