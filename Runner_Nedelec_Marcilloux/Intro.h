#ifndef INTRO_H
#define INTRO_H

#include "View.h"

//=========================================================================
// Description:
//
// Cette classe permet l'affichage d'un ecran d'introduction au lancement de l'application
// Cet écran montre quelques informations du cadre du projet
//=========================================================================
class Intro : public View
{
private:
    const std::string LOGO_BDX_IUT = "Images/Logo/logo.png";
    const std::string LOGO_IUT = "Images/Logo/logo_iut.png";
    const std::string LOGO_BDX = "Images/Logo/logo_Bdx.png";

    sf::Text _title; //titre du projet
    sf::Text _date; //Annee de réalisation

    //Images des différents logos
    GraphicElement* _logo;
    GraphicElement* _logo_iut;
    GraphicElement* _logo_ent;

    //Texture des images précédentes
    sf::Texture _logoTexture;
    sf::Texture _logoIUTTexture;
    sf::Texture _logoBdxTexture;

    //Informations sur les developpeurs
    sf::Text _developersInfosPart1;
    sf::Text _developersInfosPart2;

    //Permet de réalisé un fondu
    sf::RectangleShape _opacity;

    //Serie de variable nécésaire au bon déroulement du fondu
    int _cpt;
    bool _nextOpacityStep = false;
    bool _endAnimation = false;
    bool _result = true;
    sf::Clock _clock;

public:
    Intro(int w, int h, sf::RenderWindow * window);
    ~Intro();
    void draw() override;
    void synchronize() override;
    bool treatEvents() override;
};

#endif // INTRO_H
