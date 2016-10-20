#include "Model.h"
#include "Menu.h"
#include "GameView.h"
#include "Settings.h"
#include "Ranking.h"
#include "Intro.h"
#include "Rules.h"

#include <iostream>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

using namespace std;





//================================================================================================================
// Description : FONCTION MERE
// Auteur : Guillaume Nedelec
// Date : 01/02/16
// Interêt : permet d'initialiser un modèle et des vues (GameView, Rules, Menu...)c'est la fonction 'déclencheuse'
//================================================================================================================
int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Runner", sf::Style::Close);
    window.setFramerateLimit(60);

    Model model(SCREEN_WIDTH, SCREEN_HEIGHT);
    Intro* intro = new Intro(SCREEN_WIDTH,SCREEN_HEIGHT, &window);
    Menu* menu;
    GameView* game;
    Settings* settings;
    Ranking* ranking;
    Rules* rules;

    while(intro->treatEvents())
    {
        intro->draw();
        intro->synchronize();
    }
    delete intro;

    menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, &window);

    while(window.isOpen())
    {
        while(menu->treatEvents())
        {
            menu->draw();
            menu->synchronize();
        }

        if(menu->getStatut() == GAME)
        {
            game = new GameView(SCREEN_WIDTH, SCREEN_HEIGHT, &window);
            delete menu;
            model.setEndGame(false);
            game->setModel(&model);

            while(game->treatEvents())
            {
                if(!game->getPause())
                    model.nextStep();
                game->synchronize();
                game->draw();
            }
            delete game;
            model.reset();
            menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, &window);
        }

        else if(menu->getStatut() == SETTINGS)
        {
            settings = new Settings(SCREEN_WIDTH, SCREEN_HEIGHT, &window);
            delete menu;
            settings->setModel(&model);
            while(settings->treatEvents())
            {
                settings->draw();
                settings->synchronize();
            }
            delete settings;
            menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, &window);
        }

        else if(menu->getStatut() == RANKING)
        {
            ranking = new Ranking(SCREEN_WIDTH, SCREEN_HEIGHT, &window);
            delete menu;

            while(ranking->treatEvents())
            {
                ranking->draw();
                ranking->synchronize();
            }
            delete ranking;
            menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, &window);
        }

        else if(menu->getStatut() == RULES)
        {
            rules = new Rules(SCREEN_WIDTH, SCREEN_HEIGHT, &window);
            delete menu;

            while(rules->treatEvents())
            {
                rules->draw();
                rules->synchronize();
            }
            delete rules;
            menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, &window);
        }
    }
    delete menu;
    return EXIT_SUCCESS;
}
