#include "GameView.h"
#include "Rules.h"
#include <iostream>
#include <fstream>

using namespace std;




//=====================================================================================
// Description : Constructeur de GameView
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de construire une GameView à partir d'une fenetre et de deux entier
//=====================================================================================
GameView::GameView(int w, int h, sf::RenderWindow *window) :
    View{w,h,window}
{
    _statut = GAME;
    if(loadImages())
    {
        cuttingSprite();
        cleanSprite();
        loadSound();

        /***JEU ***/
        _bonusInvincible = new GraphicElement(_TextureBonusInvincible, 0.f, 0.f, SIZE_BONUS,SIZE_BONUS );
        _bonusLife = new GraphicElement(_TextureBonusLife, 0.f, 0.f, SIZE_BONUS,SIZE_BONUS );
        _bonusDoubleJump = new GraphicElement(_TextureBonusJump, 0.f, 0.f, SIZE_BONUS,SIZE_BONUS );
        _bonusDoublePoint = new GraphicElement(_TextureBonusPoint, 0.f, 0.f, SIZE_BONUS,SIZE_BONUS );
        _bonusNuke = new GraphicElement(_TextureBonusNuke, 0.f, 0.f, SIZE_BONUS,SIZE_BONUS );

        _tree = new GraphicElement(_TextureTree, 0.f, 0.f, WIDTH_TREE,HEIGHT_TREE );
        _rock = new GraphicElement(_TextureRock, 0.f, 0.f, WIDTH_ROCK,HEIGHT_ROCK );
        _eagle = new AnimatedGraphicElement(AnimEagle,_TextureEagle, 0.f, 0.f, WIDTH_EAGLE,HEIGHT_EAGLE );
        _helico = new AnimatedGraphicElement(AnimHelico, _TextureHelico, 0, 0, 0, 0);
        _bird = new AnimatedGraphicElement(AnimBird, _TextureBird, 0, 0, 0, 0);
        _wolf = new AnimatedGraphicElement(AnimWolf,_TextureWolf, 0.f, 0.f, WIDTH_WOLF,HEIGHT_WOLF );

        _yeti = new AnimatedGraphicElement(AnimYetiForward, _TextureYeti, 0, 0, 0, 0);
        _yetiJump = new GraphicElement(_TextureYetiJump, 0, 0, 0, 0);
        _yetiJump2 = new GraphicElement(_TextureYetiJump2, 0, 0, 0, 0);
        _yetiFace = new AnimatedGraphicElement(AnimYetiStand, _TextureYetiFaces, 5, 540, 0, 0);

        _lifebar = new GraphicElement(_TextureLifebar, 0, 530, 50, 100);
        _coin = new AnimatedGraphicElement(AnimCoin,_TextureSilverCoin, 0.f, 0.f, SIZE_COIN,SIZE_COIN);

        _shield = new AnimatedGraphicElement(AnimShield, _TextureShield, 0, 0, 100, 100);
        _nuke = new AnimatedGraphicElement(AnimNuke, _TextureNuke, 500, 200, 0, 0);
        _impact = new AnimatedGraphicElement(AnimImpact, _TextureCollision, 0, 0, 0, 0);
        _explosion = new AnimatedGraphicElement(AnimExplosion, _TextureExplosion, 0, 0, 0, 0);

        _yeti->setOrigin(SIZE_PLAYER/2, SIZE_PLAYER/2);
        _shield->setColor(sf::Color(255,255,255,128));

        _soundCoins.setBuffer(_bufferCoin);
        _soundBonus.setBuffer(_bufferBonus);
        _soundHealthBonus.setBuffer(_bufferHealthBonus);
        _soundWolf.setBuffer(_bufferWolf);
        _soundEagle.setBuffer(_bufferEagle);
        _soundImpact.setBuffer(_bufferImpact);
        _soundNuke.setBuffer(_bufferNuke);
        _soundHelico.setBuffer(_bufferHelico);
        _soundHelico.setVolume(15);
        _soundCoins.setVolume(10);
        _soundEagle.setVolume(15);
        _soundImpact.setVolume(40);
        _soundHealthBonus.setVolume(20);
        _soundNuke.setVolume(40);


        _flashBomb = sf::RectangleShape(sf::Vector2f{(float)(w),(float)(h)});
        _flashBomb.setFillColor(sf::Color(255,255,255,_opacity));

        _delimitation.setFillColor(sf::Color::Black);
        _delimitation.setPosition(0,525);

        _score_distance.setFont(_font);
        _score_distance.setScale(1.5, 1.5);
        _score_distance.setPosition(900, 530);
        _score_distance.setColor(sf::Color::Black);

        _textPause.setFont(_font);
        _textPause.setColor(sf::Color::Black);
        _textPause.setStyle(sf::Text::Italic);

        _takenCoins.setFont(_font);
        _takenCoins.setPosition(810, 545);
        _takenCoins.setColor(sf::Color::Black);

        _lifeInfo.setFont(_font);
        _lifeInfo.setPosition(265, 562);
        _lifeInfo.setColor(sf::Color::Black);
        _lifeInfo.setScale(0.5, 0.5);

        _overText.setFont(_font);
        _overText.setColor(sf::Color::White);
        _overText.setString("GAME OVER");
        _overText.setCharacterSize(72);
        _overText.setPosition(400, 250);

        _highScores.setFont(_font);
        _highScores.setColor(sf::Color::White);
        _highScores.setCharacterSize(36);

        /*** PAUSE ***/

        _musicButton->setPosition(50,410);
        _soundButton->setPosition(50,500);

        _resume_game = new Button(300,75,sf::Color(18,140,225,230), _stringResume);
        _resume_game->setPosition(450,160);

        _rules = new Button(300,75,sf::Color(18,140,225,230), _stringRules);
        _rules->setPosition(450,260);

        _backToMenu = new Button(300,75,sf::Color(18,140,225,230), _stringBacktoMenu);
        _backToMenu->setPosition(450,360);
        _backToMenu->setTextPosition(500,375);

        _header = sf::RectangleShape{sf::Vector2f{600,60}};
        _header.setOutlineColor(sf::Color::Black);
        _header.setFillColor(sf::Color(18,140,225,150));
        _header.setOutlineThickness(7);
        _header.setPosition(300, 30);

        _pauseTitle.setFont(_fontTitle);
        _pauseTitle.setColor(sf::Color::Black);
        _pauseTitle.setString("PAUSE");
        _pauseTitle.setCharacterSize(48);
        _pauseTitle.setPosition(530, 28);
    }
}


//============================================================================================================================
// Description : Destructeur de GameView
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de désallouer toutes les cases mémoires allouées dynamiquement dans le GameView et de supprimer ce dernier
//============================================================================================================================
GameView::~GameView()
{
    delete _lifebar;
    delete _coin;
    delete _tree;
    delete _rock;
    delete _wolf;
    delete _eagle;
    delete _bonusInvincible;
    delete _bonusLife;
    delete _bonusDoubleJump;
    delete _bonusDoublePoint;
    delete _bonusNuke;
    delete _shield;
    delete _resume_game;
    delete _rules;
    delete _backToMenu;
    delete _nuke;
    delete _impact;
    delete _yeti;
    delete _helico;
    delete _bird;
    delete _explosion;
    delete _yetiJump;
    delete _yetiJump2;
    delete _yetiFace;
}


//=========================================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : Permet de dessiner tous les elements graphiques sur la fenêtre
//=========================================================================
void GameView::draw()
{
    View::draw();
    if(_game && !_pause)
    {
        if(_model->getPlayer()->getLife()>0)
        {
            for(auto e : _model->getCoin())
            {
                int x,y;
                _model->getCoinPosition(e,x,y);
                _coin->setPosition(x,y);
                _coin->draw(_window);
            }
            for(auto e : _model->getBonus())
            {
                int x,y;
                _model->getBonusPosition(e,x,y);

                if(e->get_type() == Invincible)
                {
                    _bonusInvincible->setPosition(x,y);
                    _bonusInvincible->draw(_window);
                }
                else if(e->get_type() == Health)
                {
                    _bonusLife->setPosition(x,y);
                    _bonusLife->draw(_window);
                }
                else if(e->get_type() == Jump)
                {
                    _bonusDoubleJump->setPosition(x,y);
                    _bonusDoubleJump->draw(_window);
                }
                else if(e->get_type() == Pointx2)
                {
                    _bonusDoublePoint->setPosition(x,y);
                    _bonusDoublePoint->draw(_window);
                }
                else if(e->get_type() == Nuke)
                {
                    _bonusNuke->setPosition(x,y);
                    _bonusNuke->draw(_window);
                }
            }
            for(Obstacle* e : _model->getObstacle())
            {
                int x,y;

                _model->getObstaclePosition(e,x,y);

                if(e->get_type() == ObstacleType1)
                {

                    if(e->get_height() == Ground)
                    {
                        _rock->setPosition(x-30,y);
                        _rock->draw(_window);
                    }
                    else
                    {
                        _bird->setPosition(x-30,y);
                        _bird->draw(_window);
                    }


                }
                else if(e->get_type() == ObstacleType2)
                {
                    if(e->get_height() == Ground)
                    {
                        _tree->setPosition(x-50,y);
                        _tree->draw(_window);
                    }
                    else
                    {

                        _eagle->setPosition(x-30,y);
                        _eagle->draw(_window);
                    }
                }

                else if(e->get_type() == ObstacleType3)
                {
                    if(e->get_height() == Ground)
                    {
                        _wolf->setPosition(x-30,y);
                        _wolf->draw(_window);
                    }
                    else
                    {
                        _helico->setPosition(x-30,y);
                        _helico->draw(_window);
                    }
                }

            }

            if(_colStaticElement)
            {
                if(_colTree)
                    _impact->setPosition(_col_x - 30, _col_y + 40);
                else
                    _impact->setPosition(_col_x, _col_y);
                _impact->draw(_window);
                sf::Time t = _clockStaticElem.getElapsedTime();

                _col_x += _model->getSpeedElement();

                if(t.asSeconds() > 1)
                    _colStaticElement = false;
            }

            if(_colMovingElement)
            {
                _impact->setPosition(_posXElem, _posYElem);
                _impact->draw(_window);
                sf::Time t3 = _clockMovingElem.getElapsedTime();

                _posXElem += _model->getSpeedElement();

                if(t3.asSeconds() > 1)
                    _colMovingElement = false;
            }

            if(_colHelico)
            {
                _explosion->setPosition(_posXCopter, _posYCopter);
                _explosion->draw(_window);
                sf::Time t2 = _clockCopter.getElapsedTime();
                _posXCopter += _model->getSpeedElement();
                if(t2.asSeconds() > 2.5)
                    _colHelico = false;
            }

            if(_nukeActivation)
            {
                _nuke->draw(_window);
                _nuke->setPosition((_nuke->getPosition().x + _model->getSpeedElement()), _nuke->getPosition().y);
                _window->draw(_flashBomb);

                if(!_endNukeFlash)
                {
                    if(_opacity < 245)
                        _opacity += 10;
                    else if(_opacity < 255 && _opacity >= 245)
                    {
                        _opacity = 255;
                        _endNukeFlash = true;
                    }
                }
                else
                {
                    if(_opacity >= 10)
                        _opacity-= 10;
                    else
                        _opacity = 0;
                }


                _flashBomb.setFillColor(sf::Color(255,255,255,_opacity));

                sf::Time time = _clockNuke.getElapsedTime();

                if(time.asSeconds() > 2.192)
                {
                    _nukeActivation = false;
                    _endNukeFlash = false;
                    _opacity = 0;
                }
            }

            _window->draw(_delimitation);
            if((_colStaticElement || _colHelico || _colMovingElement) && !_invincible)
                _yetiFace->setVectRect(AnimYetiHit);
            else
                _yetiFace->setVectRect(AnimYetiStand);

            _yetiFace->draw(_window);
            _window->draw(_lifeLevel);
            _window->draw(_lifeInfo);
            _lifebar->draw(_window);
            _window->draw(_score_distance);
            _window->draw(_takenCoins);
            _coin->setPosition(750, 540);
            _coin->draw(_window);

            if(_model->getDoublePointBonus())
            {
                _bonusDoublePoint->setPosition(600,540);
                _bonusDoublePoint->draw(_window);
                _coin->setTexture(_TextureGoldCoin);
            }
            else
            {
                _coin->setTexture(_TextureSilverCoin);
            }

            if(_jump)
            {
                if(_left)
                    _yetiJump2->draw(_window);
                else
                    _yetiJump->draw(_window);
            }
            else
                _yeti->draw(_window);

            if(_model->getPlayer()->getInvincibleBonus())
            {
                _bonusInvincible->setPosition(655,540);
                _bonusInvincible->draw(_window);
                _shield->draw(_window);
            }

            if(_model->getPlayer()->getDoubleJumpBonus())
            {
                _bonusDoubleJump->setPosition(545,540);
                _bonusDoubleJump->draw(_window);
            }


            _window->draw(_textPause);
        }
    }
    else if(_pause)
    {
        _musicButton->draw(_window);
        _soundButton->draw(_window);
        _window->draw(_header);
        _window->draw(_pauseTitle);
        _resume_game->draw(_window);
        _rules->draw(_window);
        _backToMenu->draw(_window);
        _cursor->draw(_window);
    }
    else if(!_game)
    {
        _soundCoins.stop();
        _soundBonus.stop();
        _soundHealthBonus.stop();
        _soundWolf.stop();
        _soundEagle.stop();
        _soundImpact.stop();
        _soundNuke.stop();
        _soundHelico.stop();
        sf::Time time = _clock.getElapsedTime();
        if(time.asSeconds() < 2)
        {
            _window->clear(sf::Color::Black);
            _window->draw(_overText);
            if(checkScore())
                _window->draw(_highScores);
        }
        else
        {
            _gameOver = true;
            _model->setEndGame(true);
        }
    }
    _window->display();
}


//===========================================================================================================================================================
// Description : Synchronisation avec le modèle et le traitement d'évenements
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de récupérer en temps réel toutes les infos du modèle les evenements provoqués par l'utilisateur et de mettre à jour l'interface graphique
//============================================================================================================================================================
void GameView::synchronize()
{
    View::synchronize();

    _pauseTitle.setString("PAUSE");
    if(_lang == English)
    {
        _stringTextPause = "Press 'Espace' to Pause";
        _stringResume = "Resume Game";
        _stringRules = "Rules";
        _stringBacktoMenu = "Back To Menu";
        _stringHighScores = "You enter the Highscore !";

        _textPause.setPosition(950, 5);
        _textPause.setCharacterSize(20);
        _resume_game->setTextPosition(500,175);
        _rules->setTextPosition(560,275);
        _backToMenu->setTextPosition(500,375);
        _highScores.setPosition(375, 375);
    }
    else if(_lang == French)
    {
        _stringTextPause = "Appuyer sur 'Echap' pour faire pause";
        _stringResume = "Reprendre la partie";
        _stringRules = "Regles du jeu";
        _stringBacktoMenu = "Retour au Menu";
        _stringHighScores = "Vous entrez dans les meilleurs scores !";

        _textPause.setPosition(815, 5);
        _textPause.setCharacterSize(20);
        _resume_game->setTextPosition(460,175);
        _rules->setTextPosition(505,275);
        _backToMenu->setTextPosition(490,375);
        _highScores.setPosition(300, 375);
    }
    else if(_lang == Spanish)
    {
        _stringTextPause = "Pulse 'Escape' para pausar";
        _stringResume = "Continuar partida";
        _stringRules = "Reglas del juego";
        _stringBacktoMenu = "Volver al Menu";
        _pauseTitle.setString("PAUSA");
        _stringHighScores = "Se introduce la puntuacion mas alta! !";

        _textPause.setPosition(915, 5);
        _textPause.setCharacterSize(20);
        _resume_game->setTextPosition(475,175);
        _rules->setTextPosition(485,275);
        _backToMenu->setTextPosition(500,375);
        _highScores.setPosition(300, 375);
    }
    else if(_lang == German)
    {
        _stringTextPause = "Drucken Sie die 'Flucht' zu Pause";
        _stringResume = "Fortsetzen der Wiedergabe";
        _stringRules = "Regeln des Spiels";
        _stringBacktoMenu = "Zuruck zum Menu";
        _stringHighScores = "Sie geben den HighScore !";

        _textPause.setPosition(865, 5);
        _textPause.setCharacterSize(20);
        _resume_game->setTextPosition(460,180);
        _rules->setTextPosition(515,280);
        _backToMenu->setTextPosition(505,380);
        _highScores.setPosition(400, 375);

        _resume_game->textSize(22);
        _rules->textSize(22);
        _backToMenu->textSize(22);
    }

    _textPause.setString(_stringTextPause);
    _resume_game->setText(_stringResume);
    _rules->setText(_stringRules);
    _backToMenu->setText(_stringBacktoMenu);
    _highScores.setString(_stringHighScores);

    if(!_pause)
    {
        if(!_model->getPlayer()->getJump())
        {
            _doubleJumpBonusActivated = false;
            _jump = false;
        }
        else
            _jump = true;

        _model->scoreCalculation();
        _scoreView = _model->getScore();

        for(auto e : _model->getObstacle())
        {

            if (_model->getPlayer()->collision(e))
            {
                if(e->get_type() == ObstacleType3 && e->get_height() == Up_Air)
                {
                    _colHelico = true;
                    _model->getObstaclePosition(e,_posXCopter,_posYCopter);
                    _clockCopter.restart();
                }
                else if(e->get_type() != ObstacleType3 && e->get_height() == Ground)
                {
                    if(e->get_type() == ObstacleType2)
                        _colTree = true;
                    else
                        _colTree = false;

                    _colStaticElement = true;
                    _model->getObstaclePosition(e, _col_x, _col_y);
                    _clockStaticElem.restart();
                }

                else
                {
                    _colMovingElement = true;
                    _model->getObstaclePosition(e,_posXElem,_posYElem);
                    _clockMovingElem.restart();
                }
            }
        }

        for(auto e : _model->getBonus())
        {
            if(e->get_type() == Nuke && _model->getPlayer()->collision(e))
            {
                _nuke->setPosition(500, 200);
                _clockNuke.restart();
                _nukeActivation = true;
            }
        }


        if(_sounds)
        {
            for(auto e : _model->getCoin())
            {
                if(_model->getPlayer()->collision(e))
                {
                    _soundCoins.play();
                }
            }

            for(auto e : _model->getBonus())
            {
                if(_model->getPlayer()->collision(e))
                {
                    if(e->get_type() == Health)
                        _soundHealthBonus.play();
                    else if (e->get_type() == Nuke)
                        _soundNuke.play();
                    else
                        _soundBonus.play();
                }
            }

            for(auto e : _model->getObstacle())
            {
                if(_model->getPlayer()->collision(e))
                {
                    _yetiFace->setVectRect(AnimYetiHit);
                    if(e->get_height() == Ground)
                    {
                        if(e->get_type() == ObstacleType3)
                            _soundWolf.play();
                        else
                            _soundImpact.play();
                    }

                    else if(e->get_height() == Up_Air)
                    {
                        if(e->get_type() == ObstacleType3)
                            _soundHelico.play();
                        else
                            _soundEagle.play();
                    }
                }
                else
                    _yetiFace->setVectRect(AnimYetiStand);
            }
        }

        _score_distance.setString("Score : " +std::to_string(_scoreView));
        _takenCoins.setString("x " + std::to_string(_model->getTakenCoins()));

        int x,y;
        _model->getPlayerPosition(x,y);
        _yeti->setPosition(x, y);
        _yetiJump->setPosition(x-20,y-50);
        _yetiJump2->setPosition(x-20,y-50);

        if(_model->getPlayer()->getInvincibleBonus())
        {
            _invincible = true;
            if(_jump)
            {
                _shield->setVectRect(AnimShield2);
                _shield->setPosition(x-60, y-50);
            }
            else
            {
                _shield->setVectRect(AnimShield);
                _shield->setPosition(x-70, y-60);
            }
        }
        else
            _invincible = false;

        if(_left)
            _yeti->setVectRect(AnimYetiBackward);
        else
            _yeti->setVectRect(AnimYetiForward);


        if(_model->getPlayer()->getLife() >0)
        {
            _lifeLevel= sf::RectangleShape{sf::Vector2f{(float)(_model->getPlayer()->getLife()*4),25}};
            _lifeInfo.setString(std::to_string(_model->getPlayer()->getLife()) + "%");

            if(_model->getPlayer()->getLife() >=60)
            {
                _lifeLevel.setFillColor(sf::Color::Green);
            }
            else if(_model->getPlayer()->getLife() >=20)
            {
                _lifeLevel.setFillColor(sf::Color::Yellow);
            }
            else
                _lifeLevel.setFillColor(sf::Color::Red);
        }

        else if(_model->getPlayer()->getLife() <= 0 && _game)
        {
            _game = false;
            _lifeLevel= sf::RectangleShape{sf::Vector2f{0,30}};
            _lifeInfo.setString("0%");
            _clock.restart();
        }
        _lifeLevel.setPosition(75,555);
    }

    else
    {
        if(_resume_game->getSelected())
            _resume_game->rectColorChange(sf::Color(18,225,225,180));
        else
            _resume_game->rectColorChange(sf::Color(18,140,225,230));
        if(_rules->getSelected())
            _rules->rectColorChange(sf::Color(18,225,225,180));
        else
            _rules->rectColorChange(sf::Color(18,140,225,230));
        if(_backToMenu->getSelected())
            _backToMenu->rectColorChange(sf::Color(18,225,225,180));
        else
            _backToMenu->rectColorChange(sf::Color(18,140,225,230));

        _cursor->setPosition(_mouseX,_mouseY);
    }

}



//=======================================================================================================
// Description : Detecteur et traitement d'évenements
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de récupérer les évenements de l'utilisateur et de les traiter en fonction de ceux-ci
//=======================================================================================================
bool GameView::treatEvents()
{
    bool result = false;
    if(_window->isOpen())
    {
        result = true;
        if(_gameOver)
        {
            result = false;
            _statut = MENU;
        }

        _window_position = (_window->getPosition());
        _mouse_position = (sf::Mouse::getPosition());
        _mouseX = ((_mouse_position.x) - (_window_position.x)) -20;
        _mouseY = ((_mouse_position.y) - (_window_position.y)) +35;

        sf::Event event;
        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window->close();
                result = false;
            }
            if(_pause)
            {
                if(_mouseX >= _resume_game->get_x()-17 && _mouseX <= _resume_game->get_x()+_resume_game->get_w()-15
                        && _mouseY >= _resume_game->get_y()-7 && _mouseY <= _resume_game->get_y()+_resume_game->get_h())
                    _resume_game->setSelection(true);

                else
                    _resume_game->setSelection(false);

                if(_mouseX >= _rules->get_x()-17 && _mouseX <= _rules->get_x()+_rules->get_w()-15
                        && _mouseY >= _rules->get_y()-7 && _mouseY <= _rules->get_y()+_rules->get_h())
                    _rules->setSelection(true);

                else
                    _rules->setSelection(false);

                if(_mouseX >= _backToMenu->get_x()-17 && _mouseX <= _backToMenu->get_x()+_backToMenu->get_w()-15
                        && _mouseY >= _backToMenu->get_y()-7 && _mouseY <= _backToMenu->get_y()+_backToMenu->get_h())
                    _backToMenu->setSelection(true);

                else
                    _backToMenu->setSelection(false);


                if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f blocPosition = _musicButton->getPosition();
                    sf::Vector2f blocSoundPosition = _soundButton->getPosition();

                    if(_backToMenu->getSelected())
                    {
                        result = false;
                        _statut = MENU;
                    }
                    else if(_resume_game->getSelected())
                    {
                        _pause=false;
                    }
                    else if(_rules->getSelected())
                    {
                        Rules* rules = new Rules(_w,_h,_window);
                        while(rules->treatEvents())
                        {
                            rules->draw();
                            rules->synchronize();
                        }
                        delete rules;
                    }
                    else if(_mouseX >= blocPosition.x-20 &&  _mouseX <= blocPosition.x+_musicButton->get_w()-40
                            && _mouseY >= blocPosition.y && _mouseY <= blocPosition.y+_musicButton->get_h()-20)
                    {
                        if(_music.getStatus() == _music.Playing)
                            _music.pause();
                        else
                            _music.play();
                    }
                    else if(_mouseX >= blocSoundPosition.x-20 &&  _mouseX <= blocSoundPosition.x+_soundButton->get_w()-40
                            && _mouseY >= blocSoundPosition.y && _mouseY <= blocSoundPosition.y+_soundButton->get_h()-20)
                    {
                        if(_sounds)
                            _sounds = false;
                        else
                            _sounds = true;
                    }
                    _cursor->setTexture(_TextureCursorClicPressed);
                }

                else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    _cursor->setTexture(_TextureCursorClicReleased);
                }

                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    if(_pause)
                        _pause = false;
                    else
                        _pause = true;
                }
            }
            else if(!_pause && _game)
            {

                if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Left)
                    {
                        if(_game && !_pause)
                        {
                            _model->getPlayer()->setLeft(true);
                            _model->getPlayer()->setRight(false);
                            _left = true;
                        }
                    }

                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        if(_pause)
                            _pause = false;
                        else
                            _pause = true;
                    }

                    else if(event.key.code == sf::Keyboard::Right)
                    {
                        if(_game && !_pause)
                        {
                            _model->getPlayer()->setRight(true);
                            _model->getPlayer()->setLeft(false);
                            _left = false;
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Up)
                    {
                        if(_game && !_pause)
                        {
                            if(_model->getPlayer()->getJump() && _model->getPlayer()->getDoubleJumpBonus())
                            {
                                _model->getPlayer()->setDoubleJump(true);
                                if(!_doubleJumpBonusActivated)
                                {
                                    _model->getPlayer()->set_y(_model->getPlayer()->get_y());
                                    _doubleJumpBonusActivated = true;
                                }
                            }

                            if(!_model->getPlayer()->getJump())
                                _model->getPlayer()->setJump(true);
                        }
                    }
                }
                if(event.type == sf::Event::KeyReleased)
                {
                    if(event.key.code == sf::Keyboard::Left)
                        _model->getPlayer()->setLeft(false);

                    else if(event.key.code == sf::Keyboard::Right)
                        _model->getPlayer()->setRight(false);
                }
            }
        }
    }
    return result;
}


//==========================================================================================================================
// Description : Decoupage de sprite
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de découper les feuilles de sprites en plusieurs images afin de les insérer dans des vecteurs de lecture
//==========================================================================================================================
void GameView::cuttingSprite()
{
    for(int i=0; i<12;i++)
    {
        sf::IntRect r(52*i,0,50,50);
        AnimCoin.push_back(r);
    }

    for(int i=0; i<6;i++)
    {
        sf::IntRect r8(150*i,0,150,125);
        AnimShield.push_back(r8);
    }

    for(int i=0; i<4;i++)
    {
        sf::IntRect r9(80*i,0,78,50);
        AnimBird.push_back(r9);
    }

    for(int i=0; i<7;i++)
    {
        sf::IntRect r10(150*i,0,148,75);
        AnimWolf.push_back(r10);
    }

    for(int i=0; i<4;i++)
    {
        sf::IntRect r11(100*i,0,99,50);
        AnimEagle.push_back(r11);
    }

    for(int i=0; i<23; i++)
    {
        sf::IntRect r12(300*i,0,300,300);
        AnimNuke.push_back(r12);
    }

    for(int i=0; i<3; i++)
    {
        sf::IntRect r13(67*i,0,67,67);
        AnimImpact.push_back(r13);
    }

    for(int i=0; i<4; i++)
    {
        sf::IntRect r14(75*i,0,73,75);
        AnimYetiForward.push_back(r14);
    }

    for(int i=0; i<4; i++)
    {
        sf::IntRect r15(75*i,75,73,75);
        AnimYetiBackward.push_back(r15);
    }

    for(int i=0; i<6; i++)
    {
        sf::IntRect r16(110*i,0,110,100);
        AnimHelico.push_back(r16);
    }

    for(int i=0; i<27; i++)
    {
        sf::IntRect r17(100*i,0,100,100);
        AnimExplosion.push_back(r17);
    }

    for(int i=0; i<6;i++)
    {
        sf::IntRect r18(150*i,125,150,150);
        AnimShield2.push_back(r18);
    }

    for(int i=0; i<3; i++)
    {
        sf::IntRect r19(60*i,0,60,50);
        AnimYetiStand.push_back(r19);
    }

    sf::IntRect r20(0, 55, 60, 50);
    AnimYetiHit.push_back(r20);
}

//================================================================================
// Description : Mutateur de modèle
// Auteur : Guillaume Nedelec
// Date : 20/05/16
// Interêt : permet de charger de le modèle courant (celui construit dans le main)
//================================================================================
void GameView::setModel(Model * model)
{
    _model = model;
}



//====================================================================================================================================================
// Description : Chargement d'images
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de charger les images dans les textures et fait planter le jeu si une image ne s'est pas chargé (accompagné d'un message d'erreur)
//====================================================================================================================================================
bool GameView::loadImages()
{
    bool success = true;

    if (!_TextureYetiFaces.loadFromFile(AVATAR))
    {
        std::cerr << "ERROR when loading image file: " << AVATAR << std::endl;
        success = false;
    }
    if (!_TextureExplosion.loadFromFile(EXPLOSION))
    {
        std::cerr << "ERROR when loading image file: " << EXPLOSION << std::endl;
        success = false;
    }
    if (!_TextureYeti.loadFromFile(YETI_WALK))
    {
        std::cerr << "ERROR when loading image file: " << YETI_WALK << std::endl;
        success = false;
    }
    if (!_TextureYetiJump.loadFromFile(YETI_JUMP))
    {
        std::cerr << "ERROR when loading image file: " << YETI_JUMP << std::endl;
        success = false;
    }
    if (!_TextureYetiJump2.loadFromFile(YETI_JUMP2))
    {
        std::cerr << "ERROR when loading image file: " << YETI_JUMP2 << std::endl;
        success = false;
    }
    if (!_TextureBird.loadFromFile(BIRD))
    {
        std::cerr << "ERROR when loading image file: " << BIRD << std::endl;
        success = false;
    }
    if (!_TextureHelico.loadFromFile(HELICO))
    {
        std::cerr << "ERROR when loading image file: " << HELICO << std::endl;
        success = false;
    }
    if (!_TextureCollision.loadFromFile(IMPACT))
    {
        std::cerr << "ERROR when loading image file: " << IMPACT << std::endl;
        success = false;
    }
    if (!_TextureBonusNuke.loadFromFile(BONUS_NUKE))
    {
        std::cerr << "ERROR when loading image file: " << BONUS_NUKE << std::endl;
        success = false;
    }
    if (!_TextureEagle.loadFromFile(EAGLE))
    {
        std::cerr << "ERROR when loading image file: " << EAGLE << std::endl;
        success = false;
    }
    if (!_TextureWolf.loadFromFile(WOLF))
    {
        std::cerr << "ERROR when loading image file: " << WOLF << std::endl;
        success = false;
    }
    if (!_TextureLifebar.loadFromFile(LIFEBAR))
    {
        std::cerr << "ERROR when loading image file: " << LIFEBAR << std::endl;
        success = false;
    }
    if (!_TextureRock.loadFromFile(ROCK))
    {
        std::cerr << "ERROR when loading image file: " << ROCK << std::endl;
        success = false;
    }
    if (!_TextureShield.loadFromFile(SHIELD))
    {
        std::cerr << "ERROR when loading image file: " << SHIELD << std::endl;
        success = false;
    }
    if (!_TextureTree.loadFromFile(TREE))
    {
        std::cerr << "ERROR when loading image file: " << TREE << std::endl;
        success = false;
    }
    if (!_TextureNuke.loadFromFile(NUKE))
    {
        std::cerr << "ERROR when loading image file: " << NUKE << std::endl;
        success = false;
    }
    if (!_TextureSilverCoin.loadFromFile(SILVER_COIN))
    {
        std::cerr << "ERROR when loading image file: " << SILVER_COIN << std::endl;
        success = false;
    }
    if (!_TextureGoldCoin.loadFromFile(GOLD_COIN))
    {
        std::cerr << "ERROR when loading image file: " << GOLD_COIN << std::endl;
        success = false;
    }
    if (!_TextureBonusLife.loadFromFile(BONUS_LIFE))
    {
        std::cerr << "ERROR when loading image file: " << BONUS_LIFE << std::endl;
        success = false;
    }
    if (!_TextureBonusInvincible.loadFromFile(BONUS_INVINCIBLE))
    {
        std::cerr << "ERROR when loading image file: " << BONUS_INVINCIBLE << std::endl;
        success = false;
    }
    if (!_TextureBonusPoint.loadFromFile(BONUS_POINT))
    {
        std::cerr << "ERROR when loading image file: " << BONUS_POINT << std::endl;
        success = false;
    }
    if (!_TextureBonusJump.loadFromFile(BONUS_JUMP))
    {
        std::cerr << "ERROR when loading image file: " << BONUS_JUMP << std::endl;
        success = false;
    }
    return success;
}



//====================================================================================================================================================
// Description : Chargement de sons
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de charger les sons dans les buffers et fait planter le jeu si une image ne s'est pas chargé (accompagné d'un message d'erreur)
//====================================================================================================================================================
void GameView::loadSound()
{
    if (!_bufferCoin.loadFromFile(SOUND_COIN))
        std::cerr << "ERROR when loading sound file: " << SOUND_COIN << std::endl;

    if (!_bufferBonus.loadFromFile(SOUND_BONUS))
        std::cerr << "ERROR when loading sound file: " << SOUND_BONUS << std::endl;

    if (!_bufferHealthBonus.loadFromFile(SOUND_HEALTHBONUS))
        std::cerr << "ERROR when loading sound file: " << SOUND_HEALTHBONUS << std::endl;

    if (!_bufferWolf.loadFromFile(SOUND_WOLF))
        std::cerr << "ERROR when loading sound file: " << SOUND_WOLF << std::endl;

    if (!_bufferEagle.loadFromFile(SOUND_EAGLE))
        std::cerr << "ERROR when loading sound file: " << SOUND_EAGLE << std::endl;

    if (!_bufferNuke.loadFromFile(SOUND_NUKE))
        std::cerr << "ERROR when loading sound file: " << SOUND_NUKE << std::endl;

    if (!_bufferHelico.loadFromFile(SOUND_HELICO))
        std::cerr << "ERROR when loading sound file: " << SOUND_HELICO << std::endl;

    if (!_bufferImpact.loadFromFile(SOUND_IMPACT))
        std::cerr << "ERROR when loading sound file: " << SOUND_IMPACT << std::endl;
}

bool GameView::getPause()
{
    return _pause;
}



//====================================================================================================================================================
// Description : Nettoyage des sprite
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de lisser les sprites chargés dans les textures
//====================================================================================================================================================
void GameView::cleanSprite()
{
    _TextureTree.setSmooth(true);
    _TextureRock.setSmooth(true);
    _TextureWolf.setSmooth(true);
    _TextureEagle.setSmooth(true);
    _TextureNuke.setSmooth(true);
    _TextureSilverCoin.setSmooth(true);
    _TextureGoldCoin.setSmooth(true);
    _TextureBonusLife.setSmooth(true);
    _TextureBonusJump.setSmooth(true);
    _TextureBonusInvincible.setSmooth(true);
    _TextureBonusPoint.setSmooth(true);
    _TextureBonusNuke.setSmooth(true);
    _TextureShield.setSmooth(true);
    _TextureLifebar.setSmooth(true);
    _TextureCollision.setSmooth(true);
    _TextureYeti.setSmooth(true);
    _TextureHelico.setSmooth(true);
    _TextureBird.setSmooth(true);
    _TextureExplosion.setSmooth(true);
    _TextureYetiJump.setSmooth(true);
    _TextureYetiJump2.setSmooth(true);
}



//===============================================================================================================
// Description : Vérification du score
// Auteur : Guillaume Nedelec
// Date : 20/05/16
// Interêt : permet de vérifier si le score atteind par le joueur est supérieur à l'un présent dans le classement
//===============================================================================================================
bool GameView::checkScore()
{
    fstream f;
    int element;
    string fichier = "scores.txt";
    bool enterToHighScore = false;

    std::ifstream infile(fichier);

    if(infile.good())
    {
        f.open(fichier.c_str(), ios:: in); //Ouverture en lecture

        if(f.fail())
        {
            std::cerr << "ouverture en lecture impossible" << endl;
            exit(EXIT_FAILURE);
        }
        while(!f.eof() && !enterToHighScore)
        {
            f >> element;
            if(_model->getScore() > (unsigned int)(element))
            {
                enterToHighScore = true;
            }
        }
        f.close();
    }

    return enterToHighScore;
}

