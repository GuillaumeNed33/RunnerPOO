#include "Settings.h"


//=====================================================================================
// Description : Constructeur de Settings
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de construire un ecran d'options
//=====================================================================================
Settings::Settings(int w, int h, sf::RenderWindow *window) :
    View{w,h,window}
{
    _statut = SETTINGS;

    _backToMenu = new Button(200,75,sf::Color(18,140,225,230), _stringBackMenu);
    _backToMenu->setPosition(10,10);
    _backToMenu->setTextPosition(32,30);
    _backToMenu->textSize(22);

    _titleBorder = sf::RectangleShape{sf::Vector2f{600,60}};
    _titleBorder.setOutlineColor(sf::Color::Black);
    _titleBorder.setFillColor(sf::Color(18,140,225,150));
    _titleBorder.setOutlineThickness(7);
    _titleBorder.setPosition(300, 30);

    _struct = sf::RectangleShape{sf::Vector2f{800,450}};
    _struct.setOutlineColor(sf::Color::Black);
    _struct.setFillColor(sf::Color(18,140,225,150));
    _struct.setOutlineThickness(2);
    _struct.setPosition(200, 130);

    _title.setFont(_fontTitle);
    _title.setColor(sf::Color::Black);
    _title.setPosition(500,28);
    _title.setCharacterSize(48);

    _difficultyTitle.setFont(_font);
    _difficultyTitle.setColor(sf::Color::White);
    _difficultyTitle.setPosition(300,180);
    _difficultyTitle.setCharacterSize(36);

    _difficultyParam.setFont(_font);
    _difficultyParam.setColor(sf::Color::White);
    _difficultyParam.setPosition(715,180);
    _difficultyParam.setCharacterSize(36);

    _decreasementDifficulty= sf::CircleShape(15, 3);
    _addingDifficulty= sf::CircleShape(15, 3);
    _decreasementDifficulty.setRotation(270);
    _addingDifficulty.setRotation(90);
    _decreasementDifficulty.setPosition(650,220);
    _addingDifficulty.setPosition(910,190);

    _musicInfo.setFont(_font);
    _musicInfo.setColor(sf::Color::White);
    _musicInfo.setPosition(300,280);
    _musicInfo.setCharacterSize(36);

    _musicParam.setFont(_font);
    _musicParam.setColor(sf::Color::White);
    _musicParam.setPosition(715,280);
    _musicParam.setCharacterSize(36);

    _SoundEffectInfo.setFont(_font);
    _SoundEffectInfo.setColor(sf::Color::White);
    _SoundEffectInfo.setPosition(300,380);
    _SoundEffectInfo.setCharacterSize(36);

    _SoundEffectParam.setFont(_font);
    _SoundEffectParam.setColor(sf::Color::White);
    _SoundEffectParam.setPosition(715,380);
    _SoundEffectParam.setCharacterSize(36);

    _languageInfo.setFont(_font);
    _languageInfo.setColor(sf::Color::White);
    _languageInfo.setPosition(300,480);
    _languageInfo.setCharacterSize(36);

    _languageParam.setFont(_font);
    _languageParam.setColor(sf::Color::White);
    _languageParam.setPosition(715,480);
    _languageParam.setCharacterSize(36);

    _changeDownLanguage= sf::CircleShape(15, 3);
    _changeUpLanguage= sf::CircleShape(15, 3);
    _changeDownLanguage.setRotation(270);
    _changeUpLanguage.setRotation(90);
    _changeDownLanguage.setPosition(650,520);
    _changeUpLanguage.setPosition(910,490);
}

//============================================================================================================================
// Description : Destructeur de Settings
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de désallouer toutes les cases mémoires allouées dynamiquement dans le GameView et de supprimer ce dernier
//============================================================================================================================
Settings::~Settings()
{
    delete _backToMenu;
}

//=========================================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : Permet de dessiner tous les elements graphiques sur la fenêtre
//=========================================================================
void Settings::draw()
{
    View::draw();
    _backToMenu->draw(_window);
    _window->draw(_titleBorder);
    _window->draw(_title);
    _window->draw(_struct);
    _window->draw(_difficultyTitle);
    _window->draw(_difficultyParam);

    if(_model->getDifficulty() != Easy)
        _window->draw(_decreasementDifficulty);
    if(_model->getDifficulty() != Hard)
        _window->draw(_addingDifficulty);

    _window->draw(_musicInfo);
    _window->draw(_musicParam);
    _window->draw(_SoundEffectInfo);
    _window->draw(_SoundEffectParam);
    _window->draw(_languageInfo);
    _window->draw(_languageParam);

    if(_lang != English)
        _window->draw(_changeDownLanguage);
    if(_lang != German)
        _window->draw(_changeUpLanguage);

    _cursor->draw(_window);
    _window->display();
}



//=======================================================================================================
// Description : Detecteur et traitement d'évenements
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de récupérer les évenements de l'utilisateur et de les traiter en fonction de ceux-ci
//=======================================================================================================
bool Settings::treatEvents()
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
                if(_backToMenu->getSelected())
                {
                    result = false;
                    _statut = MENU;
                }

                else if(_mouseX >=_decreasementDifficulty.getPosition().x-25 && _mouseX <= _decreasementDifficulty.getPosition().x+25
                        && _mouseY >=_decreasementDifficulty.getPosition().y-25 && _mouseY <= _decreasementDifficulty.getPosition().y)
                {

                    _model->decreaseDifficulty();
                }

                else if(_mouseX >=_addingDifficulty.getPosition().x-75 && _mouseX <= _addingDifficulty.getPosition().x
                        && _mouseY >=_addingDifficulty.getPosition().y && _mouseY <= _addingDifficulty.getPosition().y+25)
                    _model->addDifficulty();


                else if(_mouseX >= 690 &&  _mouseX <= 760 && _mouseY >= 275 && _mouseY <= 320)
                {
                    if(_music.getStatus() == _music.Playing)
                        _music.pause();
                    else
                        _music.play();
                }
                else if(_mouseX >= 690 &&  _mouseX <= 760 && _mouseY >= 375 && _mouseY <= 420)
                {
                    if(_sounds)
                        _sounds = false;
                    else
                        _sounds = true;
                }
                else if(_mouseX >=_changeUpLanguage.getPosition().x-75 && _mouseX <= _changeUpLanguage.getPosition().x
                        && _mouseY >=_changeUpLanguage.getPosition().y && _mouseY <= _changeUpLanguage.getPosition().y+25)
                {
                    if(_lang == English)
                        _lang = French;
                    else if(_lang == French)
                        _lang = Spanish;
                    else if(_lang == Spanish)
                        _lang = German;
                }

                else if(_mouseX >=_changeDownLanguage.getPosition().x-25 && _mouseX <= _changeDownLanguage.getPosition().x+25
                        && _mouseY >=_changeDownLanguage.getPosition().y-25 && _mouseY <= _changeDownLanguage.getPosition().y)
                {
                    if(_lang == German)
                        _lang = Spanish;
                    else if(_lang == French)
                        _lang = English;
                    else if(_lang == Spanish)
                        _lang = French;
                }
                _cursor->setTexture(_TextureCursorClicPressed);
            }
            else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                _cursor->setTexture(_TextureCursorClicReleased);
            }

        }

        if(_mouseX >= -12 && _mouseX <= 10 +_backToMenu->get_w()-15
                && _mouseY >= 10 && _mouseY <= 10 + _backToMenu->get_h())
            _backToMenu->setSelection(true);

        else if(_mouseX >=_decreasementDifficulty.getPosition().x-25 && _mouseX <= _decreasementDifficulty.getPosition().x+25
                && _mouseY >=_decreasementDifficulty.getPosition().y-25 && _mouseY <= _decreasementDifficulty.getPosition().y)
            _decreasementDifficulty.setFillColor(sf::Color(200,190,210,180));

        else if(_mouseX >=_addingDifficulty.getPosition().x-75 && _mouseX <= _addingDifficulty.getPosition().x
                && _mouseY >=_addingDifficulty.getPosition().y && _mouseY <= _addingDifficulty.getPosition().y+25)
            _addingDifficulty.setFillColor(sf::Color(200,190,210,180));

        else if(_mouseX >=_changeUpLanguage.getPosition().x-75 && _mouseX <= _changeUpLanguage.getPosition().x
                && _mouseY >=_changeUpLanguage.getPosition().y && _mouseY <= _changeUpLanguage.getPosition().y+25)
            _changeUpLanguage.setFillColor(sf::Color(200,190,210,180));

        else if(_mouseX >=_changeDownLanguage.getPosition().x-25 && _mouseX <= _changeDownLanguage.getPosition().x+25
                && _mouseY >=_changeDownLanguage.getPosition().y-25 && _mouseY <= _changeDownLanguage.getPosition().y)
            _changeDownLanguage.setFillColor(sf::Color(200,190,210,180));


        else if(_mouseX >= 690 &&  _mouseX <= 760 && _mouseY >= 275 && _mouseY <= 320)
        {
            _musicParam.setColor(sf::Color(200,190,210,180));
        }
        else if(_mouseX >= 690 &&  _mouseX <= 760 && _mouseY >= 375 && _mouseY <= 420)
        {
            _SoundEffectParam.setColor(sf::Color(200,190,210,180));
        }
        else
        {
            _decreasementDifficulty.setFillColor(sf::Color::White);
            _addingDifficulty.setFillColor(sf::Color::White);
            _changeDownLanguage.setFillColor(sf::Color::White);
            _changeUpLanguage.setFillColor(sf::Color::White);
            _musicParam.setColor(sf::Color::White);
            _SoundEffectParam.setColor(sf::Color::White);
            _backToMenu->setSelection(false);
        }
    }
    return result;
}


//===========================================================================================================================================================
// Description : Synchronisation avec le modèle et le traitement d'évenements
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : Permet de mettre à jour l'affiche à l'ecran
//============================================================================================================================================================
void Settings::synchronize()
{
    View::synchronize();

    if(_backToMenu->getSelected())
        _backToMenu->rectColorChange(sf::Color(18,225,225,180));
    else
        _backToMenu->rectColorChange(sf::Color(18,140,225,230));
    _cursor->setPosition(_mouseX, _mouseY);

    if(_lang == English)
    {
        if(_sounds)
            _stringSoundsEffectsParam = "Yes";
        else
            _stringSoundsEffectsParam = "No";

        if(_music.getStatus() == _music.Playing)
            _stringMusicParam = "Yes";
        else
            _stringMusicParam = "No";

        if(_model->getDifficulty()== Easy)
            _stringDifficultyParam = "Easy";

        else if(_model->getDifficulty()== Medium)
            _stringDifficultyParam = "Medium";

        else if(_model->getDifficulty()== Hard)
            _stringDifficultyParam = "Hard";

        _stringTitle = "Settings";
        _stringDifficultyTitle = "Difficulty";
        _stringMusic = "Music";
        _stringSoundsEffects = "Sounds Effects";
        _stringLanguage = "Language";
        _stringLanguageParam = "English";
        _stringBackMenu = "Back to menu";
        _backToMenu->setTextPosition(40 ,30);
    }

    else if(_lang == French)
    {
        if(_sounds)
            _stringSoundsEffectsParam = "Oui";
        else
            _stringSoundsEffectsParam = "Non";

        if(_music.getStatus() == _music.Playing)
            _stringMusicParam = "Oui";
        else
            _stringMusicParam = "Non";

        if(_model->getDifficulty()== Easy)
            _stringDifficultyParam = "Facile";

        else if(_model->getDifficulty()== Medium)
            _stringDifficultyParam = "Normal";

        else if(_model->getDifficulty()== Hard)
            _stringDifficultyParam = "Difficile";

        _stringTitle = "Options";
        _stringDifficultyTitle = "Difficulte";
        _stringMusic = "Musique";
        _stringSoundsEffects = "Effets Sonores";
        _stringLanguage = "Langage";
        _stringLanguageParam = "Francais";
        _stringBackMenu = "Retour Menu";
        _backToMenu->setTextPosition(45 ,30);
    }

    else if(_lang == Spanish)
    {
        if(_sounds)
            _stringSoundsEffectsParam = "Si";
        else
            _stringSoundsEffectsParam = "No";

        if(_music.getStatus() == _music.Playing)
            _stringMusicParam = "Si";
        else
            _stringMusicParam = "No";

        if(_model->getDifficulty()== Easy)
            _stringDifficultyParam = "Facil";

        else if(_model->getDifficulty()== Medium)
            _stringDifficultyParam = "Normal";

        else if(_model->getDifficulty()== Hard)
            _stringDifficultyParam = "Dificil";

        _stringTitle = "Opciones";
        _stringDifficultyTitle = "Dificultad";
        _stringMusic = "Musica";
        _stringSoundsEffects = "Efectos Sonoros";
        _stringLanguage = "Idioma";
        _stringLanguageParam = "Espanol";
        _stringBackMenu = "Volver al Menu";
        _backToMenu->setTextPosition(35 ,30);
    }

    else if(_lang == German)
    {
        if(_sounds)
            _stringSoundsEffectsParam = "Ja";
        else
            _stringSoundsEffectsParam = "Nein";

        if(_music.getStatus() == _music.Playing)
            _stringMusicParam = "Ja";
        else
            _stringMusicParam = "Nein";

        if(_model->getDifficulty()== Easy)
            _stringDifficultyParam = "Leicht";

        else if(_model->getDifficulty()== Medium)
            _stringDifficultyParam = "Mittel";

        else if(_model->getDifficulty()== Hard)
            _stringDifficultyParam = "Schwer";

        _stringTitle = "Optionen";
        _stringDifficultyTitle = "Schwierigkeit";
        _stringMusic = "Musik";
        _stringSoundsEffects = "Soundeffekte";
        _stringLanguage = "Sprache";
        _stringLanguageParam = "Deutsch";
        _stringBackMenu = "Zuruck zum Menu";
        _backToMenu->setTextPosition(20 ,30);
    }

    _title.setString(_stringTitle);
    _difficultyTitle.setString(_stringDifficultyTitle);
    _difficultyParam.setString(_stringDifficultyParam);
    _musicInfo.setString(_stringMusic);
    _musicParam.setString(_stringMusicParam);
    _SoundEffectInfo.setString(_stringSoundsEffects);
    _SoundEffectParam.setString(_stringSoundsEffectsParam);
    _languageInfo.setString(_stringLanguage);
    _languageParam.setString(_stringLanguageParam);

    _backToMenu->setText(_stringBackMenu);
}


//================================================================================
// Description : Mutateur de modèle
// Auteur : Guillaume Nedelec
// Date : 20/05/16
// Interêt : permet de charger de le modèle courant (celui construit dans le main)
//================================================================================
void Settings::setModel(Model *model)
{
    _model = model;
}
