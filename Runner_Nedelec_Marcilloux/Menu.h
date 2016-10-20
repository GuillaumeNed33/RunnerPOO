#ifndef MENU_H
#define MENU_H

#include "View.h"
#include "Button.h"

//=========================================================================
// Description:
//
// Cette classe permet de créer un menu avec les fonctionnalités nécéssaires à son fonctionnement
// (Gestion des boutons ect...)
//=========================================================================
class Menu : public View
{
private:
    std::set<Button*> _buttons; //Conteneur de tous les boutons présents dans le menu.
    Button* _new_game; //Bouton permettant l'accès à la phase de jeu
    Button* _quit; //Bouton pour quitter
    Button* _settings; //Bouton pour accéder aux obstacles
    Button* _ranking; //Bouton pour accéder aux classements
    Button* _rules; //Bouton pour accéder aux règles du jeu
    sf::Text _title; //Titre du jeu
    sf::RectangleShape _header; //Rectangle de présentation au niveau du titre


    //Textes présents sur cet écran
    std::string _stringNewGame;
    std::string _stringQuit;
    std::string _stringRanking;
    std::string _stringSettings;
    std::string _stringTitle;
    std::string _stringRules;

    Button* _license;
    std::string _stringLicense;
    sf::RectangleShape _struct;
    bool _mainMenu = true;
    bool _licenseMenu = false;
    sf::Text _licenseContent;
    std::string _content;


public:
    Menu(int w, int h, sf::RenderWindow *window);
    ~Menu();
    void draw() override;
    void synchronize() override;
    bool treatEvents() override;
};

#endif // MENU_H
