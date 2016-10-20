#ifndef _VIEW_
#define _VIEW_

#include <SFML/Audio.hpp>
#include "AnimatedGraphicElement.h"
#include "SlidingBackground.h"

//Indique dans quel est le statut ou l'utilisateur se trouve
enum Statut{MENU,GAME,RANKING,SETTINGS, RULES};
//Indique la langue utilisé
enum Language{English, French, Spanish, German};

//=========================================================================
// Description:
//
// Cette classe est la base de la vue du jeu. Elle comprend les éléments communs à toutes les vues utilisées
// (Menu principal, jeu, meilleurs score etc...)
//=========================================================================
class View {
protected:
    const std::string MUSIC_BUTTON = "Images/Boutons/MusicButtons.png";      //Image pour le bouton de musique
    const std::string SOUND = "Sounds/Music/Action.wav";                        //Lien de la musique
    const std::string BACKGROUND_IMAGE = "Images/Background/sapins.png";        //Image du premier fond défilant
    const std::string BACKGROUND_IMAGE2 = "Images/Background/montain.png";      //Image du second fond défilant
    const std::string CURSOR = "Images/Curseur/cursor.png";                     //Image du curseur
    const std::string CURSOR_CLIC = "Images/Curseur/cursor2.png";               //Image du curseur lors d'un clic

    int _w, _h; //Largeur et hauteur de la fenetre
    sf::RenderWindow * _window; //fenetre d'affichage

    Statut _statut; //Statut du programme (Menu, jeu, ect...)

    static bool  _charge; //Indique si la musique a été chargé (pour ne le faire qu'une seule fois)
    static bool _musicBegin;
    static sf::Music _music; //Musique du jeu
    static bool _sounds; //Indique si es effets sonores sont activé ou non

    sf::Vector2i _window_position; //Position de la fenetre dans l'écran
    sf::Vector2i _mouse_position; //Position de la souris dans la fenetre
    float _mouseX ; //Position X de la souris
    float _mouseY; //Position Y de la souris

    //Texture relative aux fonds ainsi qu'au curseur et au bouton de la musique
    sf::Texture _TextureBackground1;
    sf::Texture _TextureBackground2;
    sf::Texture _TextureCursorClicPressed;
    sf::Texture _TextureCursorClicReleased;
    sf::Texture _TextureMusicButton;

    GraphicElement* _musicButton; //Image du bouton musique
    GraphicElement* _soundButton; //Image du bouton musique
    GraphicElement* _cursor; //Element graphique du curseur

    SlidingBackground* _background1; //Fond défilant 1
    SlidingBackground* _background2; //Fond défilant 2

    static Language _lang; //Langue du jeu

public:
    static sf::Font _fontTitle; //Font utilisé dans le jeu
    static sf::Font _font; //Font utilisé dans le jeu


    View(int w, int h, sf::RenderWindow *window);
    virtual ~View();
    virtual void draw();
    virtual bool treatEvents() =0;
    virtual void synchronize()=0;
    Statut getStatut();
};

#endif

