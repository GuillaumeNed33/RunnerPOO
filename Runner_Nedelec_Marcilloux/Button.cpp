#include "Button.h"
#include "View.h"





//===================================================================================
// Description : Constructeur de Button
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de creer des Button à partir de 2 float, une couleur et un string
//===================================================================================
Button::Button(float w, float h, sf::Color col, std::string text) :
     _w{w}, _h{h}, _color{col}
{
    _struct = sf::RectangleShape{sf::Vector2f{_w,_h}};
    _struct.setFillColor(_color);

    _text.setFont(View::_font);
    _text.setColor(sf::Color::White);
    _text.setString(text);
    _text.setPosition(_struct.getPosition().x, _struct.getPosition().y);
}





//=====================================
// Description : Destructeur de Button
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de detruire l'objet
//=====================================
Button::~Button(){}





//=============================================================================
// Description : Changement de couleur 1
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de changer la couleur (en paramètre) du rectangle du bouton
//=============================================================================
void Button::rectColorChange(sf::Color col)
{
    _color = col;
    _struct.setFillColor(col);
}





//=========================================================================
// Description : Changement de couleur 2
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de changer la couleur (en paramètre) du texte du bouton
//=========================================================================
void Button::textColorChange(sf::Color col)
{
    _textColor = col;
    _text.setColor(_textColor);
}





//==========================================================
// Description : Changement de taille de texte
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de modifier la police du texte du bouton
//==========================================================
void Button::textSize(unsigned int size)
{
    _text.setCharacterSize(size);
}





//==============================================================
// Description : Changement de taille de Rectangle
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de modifier la taille du rectangle du bouton
//==============================================================
void Button::rectSize(float w, float h)
{
    _struct = sf::RectangleShape{sf::Vector2f{w,h}};
}





//============================================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de dessiner le bouton (rectangle et texte) sur une fenêtre
//============================================================================
void Button::draw(sf::RenderWindow *window)
{
    window->draw(_struct);
    window->draw(_text);
}





//================================================================
// Description : Mutateur de position rectangle
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de modifier la position du rectangle du bouton
//================================================================
void Button::setPosition(int x, int y)
{
    _x = x;
    _y = y;
    _struct.setPosition(_x,_y);
}





//============================================================
// Description : Mutateur de position texte
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de modifier la position du texte du bouton
//============================================================
void Button::setTextPosition(int x, int y)
{
    _text.setPosition(x, y);
}





//========================================================
// Description : Accesseur de séléction
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de savoir si le bouton est séléctionné
//========================================================
bool Button::getSelected()
{
    return _selected;
}





//==========================================
// Description : Mutateur de séléction
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de séléctionné un bouton
//==========================================
void Button::setSelection(bool b)
{
    _selected = b;
}





//================================================================
// Description : Accesseur de position horizontale
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de d'obtenir la position horizontale du bouton
//================================================================
unsigned int Button::get_x()
{
    return _x;
}





//==============================================================
// Description : Accesseur de position verticale
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de d'obtenir la position verticale du bouton
//==============================================================
unsigned int Button::get_y()
{
    return _y;
}





//===================================================
// Description : Accesseur de largeur
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de d'obtenir la largeur du bouton
//===================================================
float Button::get_w()
{
    return _w;
}





//====================================================
// Description : Accesseur de longueur
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de d'obtenir la longueur du bouton
//====================================================
float Button::get_h()
{
    return _h;
}





//==================================================
// Description : Mutateur de texte
// Auteur : Guillaume Nedelec
// Date : 22/05/16
// Interêt : permet de modifier le texte d'un bouton
//==================================================
void Button::setText(std::string text)
{
    _text.setString(text);
}
