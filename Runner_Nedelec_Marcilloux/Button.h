#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

//=========================================================================
// Description:
//
// Cette classe permet de générer et modifier des boutons créés à partir d'un rectangle et d'un texte.
//=========================================================================
class Button
{
private :
    sf::RectangleShape _struct; //Structure du bouton
    float _w, _h; //Largeur et hauteur du bouton
    sf::Color _color = sf::Color::White; //Couleur du bouton
    sf::Color _textColor = sf::Color::White; //Couleur du texte dans le bouton
    sf::Text _text; //Texte du bouton
    bool _selected = false; //Indique si le curseur de la souris est sur le bouton ou non
    int _x, _y =0; //position x et y du bouton


public:
    Button(float w, float h, sf::Color col, std::string text);
    ~Button();
    void rectColorChange(sf::Color col);
    void textColorChange(sf::Color col);
    void textSize(unsigned int size);
    void rectSize(float w, float h);
    void draw(sf::RenderWindow* window);
    bool getSelected();
    void setSelection(bool b);
    void setPosition(int x, int y);
    void setTextPosition(int x, int y);
    void setText(std::string text);
    float get_w();
    float get_h();
    unsigned int get_x();
    unsigned int get_y();
};

#endif // BUTTON_H
