#include "View.h"
#include <iostream>

using namespace std;

sf::Music       View::_music;
bool            View::_charge = false;
bool            View::_musicBegin = false;
bool            View::_sounds = true;
sf::Font        View::_fontTitle;
sf::Font        View::_font;
Language        View::_lang = English;

//=====================================================================================
// Description : Constructeur de View
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/03/16
// Interêt : permet de construire une fenetre avec des éléments
//=====================================================================================
View::View(int w, int h, sf::RenderWindow *window): _w{w}, _h{h}, _window{window}
{
    _fontTitle.loadFromFile("Font/frow.ttf");
    _font.loadFromFile("Font/Antique Olive.ttf");

    if (!_TextureBackground1.loadFromFile(BACKGROUND_IMAGE))
        std::cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE << std::endl;

    if (!_TextureBackground2.loadFromFile(BACKGROUND_IMAGE2))
       std::cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE2 << std::endl;

    if (!_TextureCursorClicPressed.loadFromFile(CURSOR_CLIC))
        std::cerr << "ERROR when loading image file: " << CURSOR_CLIC << std::endl;

    if (!_TextureCursorClicReleased.loadFromFile(CURSOR))
       std::cerr << "ERROR when loading image file: " << CURSOR << std::endl;

    if (!_TextureMusicButton.loadFromFile(MUSIC_BUTTON))
        std::cerr << "ERROR when loading image file: " << MUSIC_BUTTON << std::endl;

    if(!_charge)
    {
        if(!_music.openFromFile(SOUND))
            std::cerr << "ERROR when loading audio file: " << SOUND << std::endl;
        _charge = true;
        _music.setLoop(true);
        _music.setVolume(20);
     }

    _cursor = new GraphicElement(_TextureCursorClicReleased,0.f, 0.f,50,50);
    _musicButton = new GraphicElement(_TextureMusicButton,0.f,0.f, 100,100);
    _soundButton = new GraphicElement(_TextureMusicButton,0.f,0.f, 100,100);
    _background1 = new SlidingBackground(_TextureBackground1,_w, _h,3);
    _background2 = new SlidingBackground(_TextureBackground2,_w, _h,1);
}

//============================================================================================================================
// Description : Destructeur de View
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/03/16
// Interêt : permet de désallouer toutes les cases mémoires allouées dynamiquement dans le GameView et de supprimer ce dernier
//============================================================================================================================
View::~View()
{
    delete _background1;
    delete _background2;
    delete _musicButton;
    delete _cursor;
    delete _soundButton;
}

//============================================================================================================================
// Description : Action de dessin
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de dessiner les arrières plan défilants
//============================================================================================================================
void View::draw()
{
    _window->clear();
    _background2->draw(_window);
    _background1->draw(_window);
}

//============================================================================================================================
// Description : Mutateurs de Statut
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : Permet de trouver dans quel état est l'utilisateur
//============================================================================================================================
Statut View::getStatut()
{
    return _statut;
}

//============================================================================================================================
// Description : Synchronisation
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : Permet de mettre à jour l'affichage
//============================================================================================================================
void View::synchronize()
{
    if(_music.getStatus() == _music.Playing)
    {
        _musicButton->setTextureRect(sf::IntRect(0,0,115,115));
    }
    else
    {
        _musicButton->setTextureRect(sf::IntRect(134,0,115,115));
    }
    if(_sounds)
    {
        _soundButton->setTextureRect(sf::IntRect(0,136,115,115));
    }
    else
    {
        _soundButton->setTextureRect(sf::IntRect(125,136,115,115));
    }
    _musicButton->resize(75,75);
    _soundButton->resize(75,75);
}

