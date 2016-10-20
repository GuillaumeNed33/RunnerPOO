#include "Menu.h"

using namespace std;





//=============================================================================
// Description : Constructeur de Menu
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de creer des Menu à partir d'une fenetre et de deux entiers
//=============================================================================
Menu::Menu(int w, int h, sf::RenderWindow* window) :
    View{w,h, window}
{
    _statut = MENU;
    if(!_musicBegin)
    {
        _music.play();
        _musicBegin = true;
    }

    _musicButton->setPosition(50,500);
    _soundButton->setPosition(160,500);

    _new_game = new Button(300,75,sf::Color(18,182,209,150), _stringNewGame);
    _quit = new Button(300,75,sf::Color::Blue, _stringQuit);
    _ranking = new Button(300,75,sf::Color::Blue, _stringRanking);
    _settings = new Button(300,75,sf::Color::Blue, _stringSettings);
    _rules = new Button(300,75,sf::Color::Blue, _stringRules);
    _license = new Button(200,50,sf::Color::Blue, _stringLicense);

    _new_game->setPosition(450,125);
    _settings->setPosition(450,220);
    _ranking->setPosition(450,315);
    _quit->setPosition(450,505);
    _rules->setPosition(450,410);
    _license->setPosition(975,530);

    _buttons.insert(_new_game);
    _buttons.insert(_quit);
    _buttons.insert(_ranking);
    _buttons.insert(_settings);
    _buttons.insert(_rules);
    _buttons.insert(_license);

    _title.setFont(_fontTitle);
    _title.setColor(sf::Color::Black);
    _title.setCharacterSize(48);

    _licenseContent.setFont(_font);
    _licenseContent.setColor(sf::Color::Black);

    _header = sf::RectangleShape{sf::Vector2f{600,60}};
    _header.setOutlineColor(sf::Color::Black);
    _header.setFillColor(sf::Color(18,140,225,150));
    _header.setOutlineThickness(7);
    _header.setPosition(300, 30);

    _struct = sf::RectangleShape{sf::Vector2f{600,450}};
    _struct.setOutlineColor(sf::Color::Black);
    _struct.setFillColor(sf::Color(18,140,225,150));
    _struct.setOutlineThickness(2);
    _struct.setPosition(300, 115);
}





//========================================================================================================================
// Description : Destructeur d'Intro
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de désallouer toutes les cases mémoires allouées dynamiquement dans le menu et de supprimer ce dernier
//========================================================================================================================
Menu::~Menu()
{
    for(auto e : _buttons)
    {
        delete e;
    }
    _buttons.clear();
}





//======================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de dessiner sur une fenêtre, un menu
//======================================================
void Menu::draw()
{
    View::draw();
    _musicButton->draw(_window);
    _soundButton->draw(_window);

    if(_mainMenu)
    {
        for(auto e : _buttons)
        {
            e->draw(_window);
        }
    }
    if(_licenseMenu)
    {
        _window->draw(_struct);
        _license->draw(_window);
        _window->draw(_licenseContent);
    }

    _window->draw(_header);
    _window->draw(_title);
    _cursor->draw(_window);
    _window->display();
}





//=======================================================================================================
// Description : Detecteur et traitement d'évenements
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de récupérer les évenements de l'utilisateur et de les traiter en fonction de ceux-ci
//=======================================================================================================
bool Menu::treatEvents()
{
    bool result = false;
    if(_window->isOpen())
    {
        result = true;
        sf::Event event;

        _window_position = (_window->getPosition());
        _mouse_position = (sf::Mouse::getPosition());
        _mouseX = ((_mouse_position.x) - (_window_position.x)) -20;
        _mouseY = ((_mouse_position.y) - (_window_position.y)) +35;

        while (_window->pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                _window->close();
                result = false;
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f blocPosition = _musicButton->getPosition();
                sf::Vector2f blocSoundPosition = _soundButton->getPosition();

                if (_license->getSelected())
                {
                    if(_mainMenu)
                    {
                        _mainMenu = false;
                        _licenseMenu = true;
                    }
                    else if (!_mainMenu)
                    {
                        _mainMenu = true;
                        _licenseMenu = false;
                    }
                }

                if(_mainMenu)
                {
                    if (_new_game->getSelected())
                    {
                        _statut= GAME;
                        result = false;
                    }

                    else if(_quit->getSelected())
                    {
                        _window->close();
                        result = false;
                    }
                    else if(_ranking->getSelected())
                    {
                        _statut= RANKING;
                        result = false;
                    }
                    else if(_settings->getSelected())
                    {
                        _statut= SETTINGS;
                        result = false;
                    }
                    else if(_rules->getSelected())
                    {
                        _statut = RULES;
                        result = false;
                    }
                }

                if(_mouseX >= blocPosition.x-20 &&  _mouseX <= blocPosition.x+_musicButton->get_w()-40
                        && _mouseY >= blocPosition.y && _mouseY <= blocPosition.y+_musicButton->get_h()-20)
                {
                    if(_music.getStatus() == _music.Playing)
                    {
                        _music.pause();
                    }

                    else
                    {
                        _music.play();
                    }
                }
                if(_mouseX >= blocSoundPosition.x-20 &&  _mouseX <= blocSoundPosition.x+_musicButton->get_w()-40
                        && _mouseY >= blocSoundPosition.y && _mouseY <= blocSoundPosition.y+_musicButton->get_h()-20)
                {
                    if(_sounds)
                    {
                        _sounds = false;
                    }

                    else
                    {
                        _sounds = true;
                    }
                }
                _cursor->setTexture(_TextureCursorClicPressed);
            }

            else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                _cursor->setTexture(_TextureCursorClicReleased);
            }

            for(Button*b : _buttons)
            {
                if(_mouseX >= b->get_x()-17 && _mouseX <= b->get_x()+b->get_w()-15
                        && _mouseY >= b->get_y()-7 && _mouseY <= b->get_y()+b->get_h())
                    b->setSelection(true);

                else
                    b->setSelection(false);
            }
        }
    }
    return result;
}





//=========================================
// Description : Synchronisation du menu
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : met à jour l'affichage du menu
//=========================================
void Menu::synchronize()
{
    View::synchronize();
    for(Button* b : _buttons)
    {
        if(b->getSelected())
        {
            b->rectColorChange(sf::Color(18,225,225,180));
        }
        else
        {
            b->rectColorChange(sf::Color(18,140,225,230));
        }
    }

    _cursor->setPosition(_mouseX, _mouseY);

    for(auto b : _buttons)
    {
        b->textSize(30);
    }

    _license->textSize(30);

    if(_lang == English)
    {
        _stringNewGame = "New Game";
        _stringQuit = "Quit";
        _stringRanking = "High Scores";
        _stringSettings = "Settings";

        if(_mainMenu)
        {
            _stringTitle = "The Yeti Runner";
            _stringLicense = "License";
            _title.setPosition(380, 30);
            _license->setTextPosition(1020,535);
        }
        else
        {
            _stringTitle = "License";
            _stringLicense = "Main Menu";
            _title.setPosition(500, 30);
            _license->setTextPosition(1000,535);
        }

        _stringRules = "Rules";

        _quit->setTextPosition(565,520);
        _ranking->setTextPosition(525,330);
        _new_game->setTextPosition(525,140);
        _settings->setTextPosition(540,235);
        _rules->setTextPosition(565,425);
    }

    else if(_lang == French)
    {
        _stringNewGame = "Nouvelle Partie";
        _stringQuit = "Quitter";
        _stringRanking = "Meilleurs Scores";
        _stringSettings = "Options";

        _license->textSize(24);
        if(_mainMenu)
        {
            _stringTitle = "Yeti Runner";
            _stringLicense = "Licence";
            _title.setPosition(425, 30);
            _license->setTextPosition(1030,540);
        }
        else
        {
            _stringTitle = "Licence";
            _stringLicense = "Menu principal";
            _title.setPosition(500, 30);
            _license->setTextPosition(995,540);
        }

        _stringRules = "Regles du Jeu";

        _quit->setTextPosition(550,520);
        _ranking->setTextPosition(485,330);
        _new_game->setTextPosition(490,140);
        _settings->setTextPosition(550,235);
        _rules->setTextPosition(505,425);

    }
    else if(_lang == Spanish)
    {
        _stringNewGame = "Nuevo Juego";
        _stringQuit = "Dejar";
        _stringRanking = "Mejores Puntuaciones";
        _stringSettings = "Opciones";
        _license->textSize(24);
        if(_mainMenu)
        {
            _stringTitle = "El Yeti Corredor";
            _stringLicense = "Licencia";
            _title.setPosition(370, 30);
            _license->setTextPosition(1030,540);
        }
        else
        {
            _stringTitle = "Licencia";
            _stringLicense = "menu principal";
            _title.setPosition(500, 30);
            _license->setTextPosition(995,540);
        }
        _stringRules = "Reglas del juego";

        _quit->setTextPosition(565,525);
        _ranking->setTextPosition(465,335);
        _new_game->setTextPosition(525,145);
        _settings->setTextPosition(545,240);
        _rules->setTextPosition(497,430);

        _quit->textSize(26);
        _ranking->textSize(26);
        _new_game->textSize(26);
        _settings->textSize(26);
        _rules->textSize(26);
    }

    else if(_lang == German)
    {
        _stringNewGame = "Neues Spiel";
        _stringQuit = "Verlassen";
        _stringRanking = "Highscores";
        _stringSettings = "Optionen";
        if(_mainMenu)
        {
            _stringTitle = "Der Yeti Runner";
            _stringLicense = "Lizenz";
            _title.setPosition(390, 30);
            _license->setTextPosition(1035,535);
        }
        else
        {
            _stringTitle = "Lizenz";
            _stringLicense = "Hauptmenu";
            _title.setPosition(500, 30);
            _license->setTextPosition(995,535);
        }
        _stringRules = "Regeln des Spiels";

        _quit->setTextPosition(525,520);
        _ranking->setTextPosition(520,330);
        _new_game->setTextPosition(515,140);
        _settings->setTextPosition(530,235);
        _rules->setTextPosition(480,425);
    }

    _content = "Emeline Vinzio \n\n"
            + string("Mageker\n\n")
            + "http://retrogamezone.co.uk/metalslug/info.htm \n\n"
            + "Game chefs \n\n"
            + "Gussprint \n\n"
            + "KitsuneRedWolf \n\n"
            + "Mndarrr \n\n"
            + "SEGA \n\n"
            + "TechoKami \n\n"
            + "vecteezy \n\n"
            + "SMT13/Yoshi101 \n\n"
            + "Spork Thug Typography";

    _licenseContent.setPosition(321, 135);
    _licenseContent.setCharacterSize(18);
    _licenseContent.setString(_content);

    _new_game->setText(_stringNewGame);
    _quit->setText(_stringQuit);
    _ranking->setText(_stringRanking);
    _settings->setText(_stringSettings);
    _rules->setText(_stringRules);
    _title.setString(_stringTitle);
    _license->setText(_stringLicense);
}

