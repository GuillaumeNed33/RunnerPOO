#ifndef SETTINGS_H
#define SETTINGS_H

#include "View.h"
#include "Button.h"
#include "Model.h"

class Model;

//=========================================================================
// Description:
//
// Cette classe est un menu permettant de gérer les options du jeu
//=========================================================================
class Settings : public View
{
private:
    Model* _model; //Modele du jeu pour appliquer les options séléctionnées
    Button* _backToMenu; //Bouton permettant le retour au menu principal
    sf::Text _title; //Titre du sous menu
    sf::RectangleShape _titleBorder; //Cadre du titre
    sf::RectangleShape _struct; //Structure ou sont affichées les données

    sf::Text _difficultyTitle; //Enoncé du paramètre (Difficulté)
    sf::Text _difficultyParam; //Valeur de la difficulté
    sf::CircleShape _decreasementDifficulty; //Petit triangle permettant de baisser la difficulté
    sf::CircleShape _addingDifficulty; //Idem pour l'augmenter

    sf::Text _musicInfo; //Enoncé du paramètre (Musique)
    sf::Text _musicParam; //Valeur du paramètre
    sf::Text _SoundEffectInfo; //Enoncé du paramètre (Effets Sonores)
    sf::Text _SoundEffectParam; //Valeur du paramètre

    sf::Text _languageInfo; //Enoncé du paramètre (Effets Sonores)
    sf::Text _languageParam; //Valeur du paramètre
    sf::CircleShape _changeUpLanguage; //Petit triangle permettant de baisser la difficulté
    sf::CircleShape _changeDownLanguage; //Idem pour l'augmenter

    std::string _stringTitle;
    std::string _stringDifficultyTitle;
    std::string _stringDifficultyParam;
    std::string _stringMusic;
    std::string _stringMusicParam;
    std::string _stringSoundsEffects;
    std::string _stringSoundsEffectsParam;
    std::string _stringLanguage;
    std::string _stringLanguageParam;
    std::string _stringBackMenu;

public:
    Settings(int w, int h, sf::RenderWindow *window);
    ~Settings();
    void draw() override;
    void synchronize() override;
    bool treatEvents() override;
    void setModel(Model* model);
};

#endif // SETTINGS_H
