#include "Intro.h"
#include <iostream>



//==============================================================================
// Description : Constructeur d'Intro
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de creer des Intro à partir d'une fenetre et de deux entiers
//==============================================================================
Intro::Intro(int w, int h, sf::RenderWindow *window) :
    View{w,h,window}
{
    if (!_logoTexture.loadFromFile(LOGO_BDX_IUT))
        std::cerr << "ERROR when loading image file: " << LOGO_BDX_IUT << std::endl;
    if (!_logoIUTTexture.loadFromFile(LOGO_IUT))
        std::cerr << "ERROR when loading image file: " << LOGO_IUT << std::endl;
    if (!_logoBdxTexture.loadFromFile(LOGO_BDX))
        std::cerr << "ERROR when loading image file: " << LOGO_BDX << std::endl;

    _cpt = 0;

    _opacity = sf::RectangleShape{sf::Vector2f{(float)(_w),(float)(_h)}};
    _opacity.setFillColor(sf::Color(0,0,0,255));

    _title.setFont(_font);
    _title.setString("Runner Project");
    _title.setColor(sf::Color::Black);
    _title.setPosition(405,25);
    _title.setCharacterSize(58);

    _date.setFont(_font);
    _date.setString("2015 - 2016");
    _date.setColor(sf::Color::Black);
    _date.setPosition(540,100);
    _date.setCharacterSize(24);

    _logo = new GraphicElement(_logoTexture, 0.f, 0.f, 100,100);
    _logo->setPosition(125,200);

    _logo_ent = new GraphicElement(_logoBdxTexture, 0.f, 0.f, 100,100);
    _logo_ent->setPosition(480,250);

    _logo_iut = new GraphicElement(_logoIUTTexture, 0.f, 0.f, 100,100);
    _logo_iut->setPosition(875,210);

    _developersInfosPart1.setFont(_font);
    _developersInfosPart1.setString("developed by");
    _developersInfosPart1.setColor(sf::Color::Black);
    _developersInfosPart1.setPosition(515,500);
    _developersInfosPart1.setCharacterSize(24);

    _developersInfosPart2.setFont(_font);
    _developersInfosPart2.setString("Guillaume Nedelec & Nicolas Marcilloux");
    _developersInfosPart2.setColor(sf::Color::Black);
    _developersInfosPart2.setPosition(275,530);
    _developersInfosPart2.setCharacterSize(36);
}





//============================================================================================================================
// Description : Destructeur d'Intro
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de désallouer toutes les cases mémoires allouées dynamiquement dans l'Intro et de supprimer cette dernière
//============================================================================================================================
Intro::~Intro()
{
    delete _logo;
    delete _logo_iut;
    delete _logo_ent;
}





//========================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de dessiner sur une fenêtre, une Intro
//========================================================
void Intro::draw()
{
    _window->clear(sf::Color::White);
    _window->draw(_title);
    _window->draw(_date);
    _logo->draw(_window);
    _logo_iut->draw(_window);
    _logo_ent->draw(_window);
    _window->draw(_developersInfosPart1);
    _window->draw(_developersInfosPart2);
    _window->draw(_opacity);
    _window->display();
}






//================================================
// Description : Synchronisation de l'écran
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de creer un de fondu en Intro
//===============================================
void Intro::synchronize()
{
    if(!_endAnimation)
    {
        if (_cpt < 255 && !_nextOpacityStep)
        {
            _opacity.setFillColor(sf::Color(0,0,0,255-_cpt));
            _cpt+=2;
            _clock.restart();
        }
        else if(_cpt>= 255 && !_nextOpacityStep)
        {
            _cpt=255;
            sf::Time time = _clock.getElapsedTime();
            if(time.asSeconds() > 2.50)
            {
                _nextOpacityStep = true;
            }
        }
        else if(_nextOpacityStep)
        {
            _opacity.setFillColor(sf::Color(0,0,0,255-_cpt));
            _cpt-=2;
            if(_cpt <= 0)
            {
                _endAnimation = true;
                _result = false;
            }
        }
    }
}





//=======================================================================================================
// Description : Detecteur et traitement d'évenements
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de récupérer les évenements de l'utilisateur et de les traiter en fonction de ceux-ci
//=======================================================================================================
bool Intro::treatEvents()
{
    bool result = false;
    if(_window->isOpen())
    {
        result = _result;
        sf::Event event;

        while (_window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                _window->close();
                result = false;
            }

            else if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)
            {
                _nextOpacityStep = true;
                _window->setMouseCursorVisible(false);
            }
        }
    }
    return result;
}
