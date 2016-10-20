#include "Ranking.h"
#include <iostream>
#include <fstream>

using namespace std;

//==============================================================================
// Description : Constructeur de Ranking
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de creer un écran de score à partir d'une fenetre et de deux entiers
//==============================================================================
Ranking::Ranking(int w, int h, sf::RenderWindow *window) :
    View{w,h,window}
{
    _statut = RANKING;

    _musicButton->setPosition(50,410);
    _soundButton->setPosition(50,500);

    _backToMenu = new Button(200,75,sf::Color(18,140,225,230), _stringBackMenu);
    _backToMenu->setPosition(10,10);
    _backToMenu->setTextPosition(32,30);

    _titleBorder = sf::RectangleShape{sf::Vector2f{600,60}};
    _titleBorder.setOutlineColor(sf::Color::Black);
    _titleBorder.setFillColor(sf::Color(18,140,225,150));
    _titleBorder.setOutlineThickness(7);
    _titleBorder.setPosition(300, 30);

    _struct = sf::RectangleShape{sf::Vector2f{800,400}};
    _struct.setOutlineColor(sf::Color::Black);
    _struct.setFillColor(sf::Color(18,140,225,150));
    _struct.setOutlineThickness(2);
    _struct.setPosition(200, 130);

    _title.setFont(_fontTitle);
    _title.setColor(sf::Color::Black);
    _title.setCharacterSize(48);

    _score1.setFont(_font);
    _score1.setColor(sf::Color::White);
    _score1.setPosition(500,180);
    _score1.setCharacterSize(48);

    _score2.setFont(_font);
    _score2.setColor(sf::Color::White);
    _score2.setPosition(500,240);
    _score2.setCharacterSize(48);

    _score3.setFont(_font);
    _score3.setColor(sf::Color::White);
    _score3.setPosition(500,300);
    _score3.setCharacterSize(48);

    _score4.setFont(_font);
    _score4.setColor(sf::Color::White);
    _score4.setPosition(500,360);
    _score4.setCharacterSize(48);

    _score5.setFont(_font);
    _score5.setColor(sf::Color::White);
    _score5.setPosition(500,420);
    _score5.setCharacterSize(48);

    ReadingScores();
}

//============================================================================================================================
// Description : Destructeur de Ranking
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de désallouer toutes les cases mémoires allouées dynamiquement dans Ranking et de supprimer cette dernière
//============================================================================================================================
Ranking::~Ranking()
{
    delete _backToMenu;
}

//========================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de dessiner sur une fenêtre, les éléments pour faire l'ecran de score
//========================================================
void Ranking::draw()
{
    View::draw();
    _musicButton->draw(_window);
    _soundButton->draw(_window);
    _backToMenu->draw(_window);
    _window->draw(_titleBorder);
    _window->draw(_title);
    _window->draw(_struct);
    _window->draw(_score1);
    _window->draw(_score2);
    _window->draw(_score3);
    _window->draw(_score4);
    _window->draw(_score5);
    _cursor->draw(_window);
    _window->display();
}

//=======================================================================================================
// Description : Detecteur et traitement d'évenements
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de récupérer les évenements de l'utilisateur et de les traiter en fonction de ceux-ci
//=======================================================================================================
bool Ranking::treatEvents()
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
            if(event.type == sf::Event::Closed)
            {
                _window->close();
                result = false;
            }


            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f blocPosition = _musicButton->getPosition();
                sf::Vector2f blocSoundPosition = _soundButton->getPosition();

                if(_backToMenu->getSelected())
                {
                    result = false;
                    _statut = MENU;
                }
                else if(_mouseX >= blocPosition.x-20 &&  _mouseX <= blocPosition.x+_musicButton->get_w()-40
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
                else if(_mouseX >= blocSoundPosition.x-20 &&  _mouseX <= blocSoundPosition.x+_soundButton->get_w()-40
                        && _mouseY >= blocSoundPosition.y && _mouseY <= blocSoundPosition.y+_soundButton->get_h()-20)
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


            if(_mouseX >= -12 && _mouseX <= 10 +_backToMenu->get_w()-15
                    && _mouseY >= 10 && _mouseY <= 10 + _backToMenu->get_h())
                _backToMenu->setSelection(true);

            else
                _backToMenu->setSelection(false);
        }
    }
    return result;
}

//================================================
// Description : Synchronisation de l'écran
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de creer mettre à jour l'affichage
//===============================================
void Ranking::synchronize()
{
    View::synchronize();

    if(_backToMenu->getSelected())
        _backToMenu->rectColorChange(sf::Color(18,225,225,180));
    else
        _backToMenu->rectColorChange(sf::Color(18,140,225,230));

    _backToMenu->textSize(24);
    _backToMenu->setTextPosition(32,30);
    if(_lang == English)
    {
        _stringBackMenu = "Back to Menu";
        _stringTitle = "Highscores";
        _title.setPosition(480,28);
    }
    else if(_lang == French)
    {
        _stringBackMenu = "Retour Menu";
        _stringTitle = "Meilleurs Scores";
        _title.setPosition(425,28);
    }

    else if(_lang == Spanish)
    {
        _stringBackMenu = "Volver al Menu";
        _stringTitle = "Mejores Puntuaciones";
        _title.setPosition(325,28);
    }

    else if(_lang == German)
    {
        _stringBackMenu = "Zuruck zum Menu";
        _stringTitle = "Highscores";
        _title.setPosition(475,28);
        _backToMenu->setTextPosition(25,30);
        _backToMenu->textSize(20);
    }

    _title.setString(_stringTitle);
    _backToMenu->setText(_stringBackMenu);

    _cursor->setPosition(_mouseX, _mouseY);
}

//================================================
// Description : Lecture de fichier
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : Permet de lire le fichier scores pour garder les variables
//===============================================
void Ranking::ReadingScores()
{
    fstream f;
    int element;
    string fichier = "scores.txt";
    int saveScore[5];
    int i = 0;

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
    }
    else
    {
        for(i=0;i<5 ; i++)// i<5 parce qu'il n'y a que 5 meilleurs scores
        {
            saveScore[i] = 0; //on copie le fichier tampon dans le fichier meilleur score en effaçant ce qu'il y avait au préalable.
        }
    }

    _score1.setString("1. " + to_string(saveScore[0]));
    _score2.setString("2. " + to_string(saveScore[1]));
    _score3.setString("3. " + to_string(saveScore[2]));
    _score4.setString("4. " + to_string(saveScore[3]));
    _score5.setString("5. " + to_string(saveScore[4]));
}
