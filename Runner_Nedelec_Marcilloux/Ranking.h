#ifndef RANKING_H
#define RANKING_H

#include "View.h"
#include "Button.h"

//=========================================================================
// Description:
//
// Cette classe permet de gérer les éléments visuel du menu des meilleurs scores
//=========================================================================
class Ranking : public View
{
private:
    Button* _backToMenu; //Bouton permettant de retourner au menu principal
    sf::Text _title; //Titre du menu des meilleurs scores
    sf::RectangleShape _titleBorder; //Cadre autour du titre
    sf::RectangleShape _struct; //Cadre ou les données seront affichées
    sf::Text _score1; //Meilleur score
    sf::Text _score2; //2e Meilleur score
    sf::Text _score3; //3e Meilleur score
    sf::Text _score4; //...
    sf::Text _score5;

    std::string _stringBackMenu;
    std::string _stringTitle;

public:
    Ranking(int w, int h, sf::RenderWindow *window);
    ~Ranking();
    void draw() override;
    void synchronize() override;
    bool treatEvents() override;
    void ReadingScores();
};

#endif // RANKING_H
