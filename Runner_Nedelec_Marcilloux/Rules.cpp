#include "Rules.h"
#include "GameView.h"
#include <iostream>
#include <string>

using namespace std;

//==============================================================================
// Description : Constructeur de Rules
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de creer un ecran de Règles du jeu
//==============================================================================
Rules::Rules(int w, int h, sf::RenderWindow *window) :
    View{w,h,window}
{
    if(loadImages())
    {
        _statut = RULES;

        _musicButton->setPosition(12,400);
        _soundButton->setPosition(12,490);

        _header = sf::RectangleShape{sf::Vector2f{600,60}};
        _header.setOutlineColor(sf::Color::Black);
        _header.setFillColor(sf::Color(18,140,225,150));
        _header.setOutlineThickness(7);
        _header.setPosition(300, 30);

        _title.setFont(_fontTitle);
        _title.setColor(sf::Color::Black);
        _title.setCharacterSize(48);

        _subTitle.setFont(_font);
        _subTitle.setColor(sf::Color::Black);
        _subTitle.setCharacterSize(32);
        _subTitle.setStyle(sf::Text::Bold | sf::Text::Italic);

        _subSubTitle.setFont(_font);
        _subSubTitle.setColor(sf::Color::Black);
        _subSubTitle.setCharacterSize(22);
        _subSubTitle.setStyle(sf::Text::Underlined);

        _subSubTitle2.setFont(_font);
        _subSubTitle2.setColor(sf::Color::Black);
        _subSubTitle2.setCharacterSize(22);
        _subSubTitle2.setStyle(sf::Text::Underlined);

        _desc1.setFont(_font);
        _desc1.setColor(sf::Color::Black);
        _desc1.setCharacterSize(16);

        _desc2.setFont(_font);
        _desc2.setColor(sf::Color::Black);
        _desc2.setCharacterSize(16);

        _desc3.setFont(_font);
        _desc3.setColor(sf::Color::Black);
        _desc3.setCharacterSize(16);

        _desc4.setFont(_font);
        _desc4.setColor(sf::Color::Black);
        _desc4.setCharacterSize(16);

        _desc5.setFont(_font);
        _desc5.setColor(sf::Color::Black);
        _desc5.setCharacterSize(16);

        _desc6.setFont(_font);
        _desc6.setColor(sf::Color::Black);
        _desc6.setCharacterSize(16);

        _struct = sf::RectangleShape{sf::Vector2f{1000,450}};
        _struct.setOutlineColor(sf::Color::Black);
        _struct.setFillColor(sf::Color(18,140,225,150));
        _struct.setOutlineThickness(2);
        _struct.setPosition(100, 115);

        _closeInfo.setFont(_font);
        _closeInfo.setColor(sf::Color::Black);
        _closeInfo.setCharacterSize(48);

        _nextPage = new Button(200,75,sf::Color(18,140,225,230), _stringNextButton);
        _nextPage->setPosition(990,10);
        _previousPage = new Button(200,75,sf::Color(18,140,225,230), _stringPreviousButton);
        _previousPage->setPosition(10,10);

        //PAGE 1
        _yeti = new AnimatedGraphicElement(AnimYeti, _TextureYeti, 200, 240, 0, 0);
        _arrow = new GraphicElement(_TextureArrow,170,360,0,0);

        //PAGE 2
        _rock = new GraphicElement(_TextureRock,160,220,50,50);
        _tree = new GraphicElement(_TextureTree,140,310,50,50);
        _wolf = new AnimatedGraphicElement(AnimWolf,_TextureWolf,100,470,50,50);
        _bird = new AnimatedGraphicElement(AnimBird, _TextureBird,620,230,50,50);
        _eagle = new AnimatedGraphicElement(AnimEagle,_TextureEagle,620,350,50,50);
        _copter = new AnimatedGraphicElement(AnimCopter,_TextureCopter,620,450,50,50);

        // PAGE 3
        _bonusNuke = new GraphicElement(_TextureBonusNuke, 620,220,50,50);
        _bonusHealth  = new GraphicElement(_TextureBonusLife,160,350,50,50);
        _bonusJump = new GraphicElement(_TextureBonusJump,160,480,50,50);
        _bonusShield = new GraphicElement(_TextureBonusInvincible,160,220,50,50);
        _bonusPoint = new GraphicElement(_TextureBonusPoint,620,350,50,50);
        _silverCoin = new AnimatedGraphicElement(AnimCoin,_TextureSilverCoin,620,450,50,50);
        _goldCoin = new AnimatedGraphicElement(AnimCoin,_TextureGoldCoin,620,500,50,50);
    }
}


//============================================================================================================================
// Description : Destructeur de Rules
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de désallouer toutes les cases mémoires allouées dynamiquement dans les Regles et de supprimer cette dernière
//============================================================================================================================
Rules::~Rules()
{
    delete _nextPage;
    delete _previousPage;

    delete _yeti;
    delete _arrow;

    delete _tree;
    delete _rock;
    delete _bird;
    delete _wolf;
    delete _eagle;
    delete _copter;

    delete _bonusHealth;
    delete _bonusJump;
    delete _bonusShield;
    delete _bonusNuke;
    delete _bonusPoint;
    delete _silverCoin;
    delete _goldCoin;
}

//========================================================
// Description : Action de Dessin
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de dessiner sur une fenêtre, l'ecran de regles
//========================================================
void Rules::draw()
{
    View::draw();
    _musicButton->draw(_window);
    _soundButton->draw(_window);
    _window->draw(_struct);
    _window->draw(_header);
    _window->draw(_title);
    _window->draw(_closeInfo);


    if(_page1)
    {
        _nextPage->draw(_window);
        _yeti->draw(_window);
        _arrow->draw(_window);
        _window->draw(_subTitle);
        _window->draw(_desc1);
        _window->draw(_desc2);

    }
    else if(_page2)
    {
        _nextPage->draw(_window);
        _previousPage->draw(_window);
        _tree->draw(_window);
        _rock->draw(_window);
        _wolf->draw(_window);
        _eagle->draw(_window);
        _bird->draw(_window);
        _copter->draw(_window);
        _window->draw(_subTitle);
        _window->draw(_subSubTitle);
        _window->draw(_subSubTitle2);
        _window->draw(_desc1);
        _window->draw(_desc2);
        _window->draw(_desc3);
        _window->draw(_desc4);
        _window->draw(_desc5);
        _window->draw(_desc6);
    }
    else if(_page3)
    {
        _previousPage->draw(_window);
        _bonusHealth->draw(_window);
        _bonusNuke->draw(_window);
        _bonusPoint->draw(_window);
        _bonusJump->draw(_window);
        _bonusShield->draw(_window);
        _silverCoin->draw(_window);
        _goldCoin->draw(_window);

        _window->draw(_subTitle);
        _window->draw(_desc1);
        _window->draw(_desc2);
        _window->draw(_desc3);
        _window->draw(_desc4);
        _window->draw(_desc5);
        _window->draw(_desc6);
    }
    _cursor->draw(_window);
    _window->display();
}

//================================================
// Description : Synchronisation de l'écran
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de mettre à jour l'affichage
//===============================================
void Rules::synchronize()
{
    View::synchronize();

    _cursor->setPosition(_mouseX, _mouseY);

    _nextPage->textSize(24);
    _previousPage->textSize(24);

    if(_lang == English)
    {
        _stringTitle = "Rules";
        _stringNextButton = "Next Page";
        _stringPreviousButton = "Previous Page";
        _stringCloseInfo = "Press 'Escape' to return to the previous menu";

        if(_page1)
        {
            _stringSubTitle = "Player";
            _stringDesc1 = "Your are Yetiti, the nice Yeti of Mt Everest who forgot,\n"
                    +string("despite all his reminders, the first day of the sales.\n")
                    +string("So he quickly get out of his cave to find the most\n")
                    +string("interessant prices. In his trek, he will face a lot of obstacles,\n")
                    +string("such as imposing firs, famished wolves or Army's helicopter\n")
                    +string("whom confound him with his criminal cousin : Bigfoot\n")
                    +string("During this, he'll have to catch a lot of coins\n")
                    +string("in order to buy his clothes.");
            _stringDesc2 = "The game is only played on keyboard :\n"
                    +string("'RIGHT ARROW' to go Forward\n")
                    +string("'LEFT ARROW' to go Backward\n")
                    +string("'UP ARROW' to Jump\n")
                    +string("'ESCAPE' to Pause");

            _subTitle.setPosition(550, 120);
            _desc1.setPosition(350, 220);
            _desc2.setPosition(350, 400);
        }

        if(_page2)
        {
            _stringSubTitle = "Ennemies";
            _stringSubSubTitle = "Ground Ennemies";
            _stringSubSubTitle2 = "Flying Ennemies";
            _stringDesc1 = "ROCK : A simple block of granite\nDAMAGE : 10%\nMOVEMENT : NO";
            _stringDesc2 = "TREE : A beautiful fir (but not least dangerous)\nDAMAGE : 15%\nMOVEMENT : NO";
            _stringDesc3 = "WOLF : A wild famished wolf\nDAMAGE : 20%\nMOVEMENT : YES";
            _stringDesc4 = "LITTLE BIRD : A clumsy grey bird\nDAMAGE : 10%\nMOVEMENT : YES";
            _stringDesc5 = "BIG BIRD : A proud and fierce bald eagle\nDAMAGE : 15%\nMOVEMENT : YES";
            _stringDesc6 = "HELICOPTER : Death from the Skies !\nDAMAGE : 20%\nMOVEMENT : YES";

            _subTitle.setPosition(550, 120);
            _subSubTitle.setPosition(330, 170);
            _subSubTitle2.setPosition(800, 170);
            _desc1.setPosition(250, 220);
            _desc2.setPosition(250, 350);
            _desc3.setPosition(250, 480);
            _desc4.setPosition(750, 220);
            _desc5.setPosition(750, 350);
            _desc6.setPosition(750, 480);
        }

        else if(_page3)
        {
            _stringSubTitle = "Power-ups and Coins";
            _stringDesc1 = "SHIELD : Makes you invincible during few second.";
            _stringDesc2 = "HEALTH : Restore 15% of your HP.";
            _stringDesc3 = "WINGS : Allows you to execute a double-jump.";
            _stringDesc4 = "NUKE : KABOOM !";
            _stringDesc5 = "MULTIPLIER : Doubles the value of coins. Jackpot !";
            _stringDesc6 = "COIN AND GOLDEN COIN (x2 Bonus) : Gotta catch'em all !";

            _subTitle.setPosition(460, 120);
            _desc1.setPosition(230, 230);
            _desc2.setPosition(230, 360);
            _desc3.setPosition(230, 490);
            _desc4.setPosition(690, 230);
            _desc5.setPosition(690, 360);
            _desc6.setPosition(690, 490);
        }

        _title.setPosition(545,28);
        _closeInfo.setPosition(380,570);
        _nextPage->setTextPosition(1035,30);
        _previousPage->setTextPosition(30,30);
    }
    else if(_lang == French)
    {
        _stringTitle = "Regles du Jeu";
        _stringNextButton = "Page Suivante";
        _stringPreviousButton = "Page Precedente";
        _stringCloseInfo = "Appuyer sur 'Echap' pour revenir au menu precedent";

        if(_page1)
        {
            _stringSubTitle = "Joueur";
            _stringDesc1 = "Vous incarnez Yetiti, le gentil Yeti du Mont Everest qui oublia,\n"
                    +string("malgre tous ses pense-betes, le fameux jour d'ouverture des soldes.\n")
                    +string("Celui-ci du donc sortir en trombe de sa caverne afin de denicher\n")
                    +string("les prix les plus interessants. Dans son periple il devra faire face\n")
                    +string("a de nombreux obstacles, tels que les imposants sapins, les loups affames\n")
                    +string("ou encore les helicopteres de l'armee qui le confondent avec son\n")
                    +string("cousin criminel : 'Bigfoot'. Au passage il devra ramasser un maximum\n")
                    +string("de pieces pour realiser ses depenses vestimentaires.");
            _stringDesc2 = "Le jeu ne se joue qu'au clavier' :\n"
                    +string("'FLECHE DROITE' pour avancer\n")
                    +string("'FLECHE GAUCHE' pour reculer\n")
                    +string("'FLECHE HAUT' pour sauter\n")
                    +string("'ECHAP' pour faire Pause");

            _subTitle.setPosition(550, 120);
            _desc1.setPosition(350, 220);
            _desc2.setPosition(350, 400);
        }

        if(_page2)
        {
            _stringSubTitle = "Ennemis";
            _stringSubSubTitle = "Ennemis Terrestres";
            _stringSubSubTitle2 = "Ennemis Aeriens";
            _stringDesc1 = "ROCHER : Un simple bloc de granit\nDEGAT : 10%\nMOUVEMENT : NON";
            _stringDesc2 = "ARBRE : Un magnifique sapin\n       (mais pas moins dangereux)\nDEGAT : 15%\nMOUVEMENT : NON";
            _stringDesc3 = "LOUP : Un loup sauvage affame\nDEGAT : 20%\nMOUVEMENT : OUI";
            _stringDesc4 = "PETIT OISEAU : Un oiseau gris et maladroit\nDEGAT : 10%\nMOUVEMENT : OUI";
            _stringDesc5 = "GRAND OISEAU : Un aigle fier et feroce\nDEGAT : 15%\nMOUVEMENT : OUI";
            _stringDesc6 = "HELICOPTERE : La Mort vient du ciel !\nDEGAT : 20%\nMOUVEMENT : OUI";

            _subTitle.setPosition(550, 120);
            _subSubTitle.setPosition(330, 170);
            _subSubTitle2.setPosition(800, 170);
            _desc1.setPosition(250, 220);
            _desc2.setPosition(250, 340);
            _desc3.setPosition(250, 480);
            _desc4.setPosition(750, 220);
            _desc5.setPosition(750, 350);
            _desc6.setPosition(750, 480);
        }

        else if(_page3)
        {
            _stringSubTitle = "Bonus et Pieces";
            _stringDesc1 = "BOUCLIER : Vous rend invincible pendant\n        quelques secondes.";
            _stringDesc2 = "VIE : Restaure 15% de vos HP.";
            _stringDesc3 = "AILES : Vous permez d'effectuer des double-saut.";
            _stringDesc4 = "OGIVE NUCLEAIRE : KABOOM !";
            _stringDesc5 = "MULTIPLICATEUR : Double la valeur des pieces. Jackpot !";
            _stringDesc6 = "PIECE ET PIECE DOREE (Bonus x2) : Attrapez-les toutes !";

            _subTitle.setPosition(480, 120);
            _desc1.setPosition(230, 230);
            _desc2.setPosition(230, 360);
            _desc3.setPosition(230, 490);
            _desc4.setPosition(690, 230);
            _desc5.setPosition(690, 360);
            _desc6.setPosition(690, 490);
        }

        _title.setPosition(460,28);
        _closeInfo.setPosition(350,570);
        _nextPage->setTextPosition(1010,30);
        _previousPage->setTextPosition(17,30);
    }
    else if(_lang == Spanish)
    {
        _stringTitle = "Reglas del Juego";
        _stringNextButton = "Pagina Siguiente";
        _stringPreviousButton = "Pagina Anterior";
        _stringCloseInfo = "Pulse 'Escape' para volver al menu anterior";

        if(_page1)
        {
            _stringSubTitle = "Jugador";
            _stringDesc1 = "Usted juega Yetiti, agradable Yeti Everest se olvido de que,\n"
                    +string("a pesar de todas sus think-betes, los famosos saldos día de apertura.\n")
                    +string("Esto por lo tanto fuera del torbellino de su cueva para desenterrar\n")
                    +string("el precio mas interesante. En su viaje se enfrentara a muchos obstaculos,\n")
                    +string("como los abetos imponentes, lobos hambrientos, los helicópteros del ejercito\n")
                    +string("que lo confunda con su primo criminal: 'Bigfoot'. De paso debe recoger los\n")
                    +string("pedazos para lograr sus gastos de ropa.");
            _stringDesc2 = "El juego se juegan solo con el teclado' :\n"
                    +string("'FLECHA DERECHA' para avanzar")
                    +string("'FLECHA IZQUIERDA' para respaldar\n")
                    +string("'FLECHE UP' para saltar")
                    +string("'ESCAPE' para hacer una Pausa");

            _subTitle.setPosition(550, 120);
            _desc1.setPosition(350, 220);
            _desc2.setPosition(350, 400);
        }

        if(_page2)
        {
            _stringSubTitle = "Enemigos";
            _stringSubSubTitle = "Enemigos Terrenales";
            _stringSubSubTitle2 = "Enemigos de Aire";
            _stringDesc1 = "ROCA : Un solo bloque de granito\nDANO : 10%\nMOVIMIENTO : NO";
            _stringDesc2 = "ARBOL : Un abeto magnifica\n        (pero no meno peligroso)\nDAMAGE : 15%\nMOVIMIENTO : NO";
            _stringDesc3 = "LOBO : Un lobo salvaje famelico\nDANO : 20%\nMOVIMIENTO : SI";
            _stringDesc4 = "PEQUENO PAJARO : Un ave gris y torpe\nDANO : 10%\nMOVIMIENTO : SI";
            _stringDesc5 = "GRAN PAJARO : Un aguila orgulloso y feroz\nDANO : 15%\nMOVIMIENTO : SI";
            _stringDesc6 = "HELICOPTERO : La Muerte viene del cielo !\nDANO : 20%\nMOVIMIENTO : SI";

            _subTitle.setPosition(550, 120);
            _subSubTitle.setPosition(330, 170);
            _subSubTitle2.setPosition(800, 170);
            _desc1.setPosition(250, 220);
            _desc2.setPosition(250, 340);
            _desc3.setPosition(250, 480);
            _desc4.setPosition(750, 220);
            _desc5.setPosition(750, 350);
            _desc6.setPosition(750, 480);
        }

        if(_page3)
        {
            _stringSubTitle = "Bonificaciones";
            _stringDesc1 = "BLINDAR : Esto te hace invencible durante\n      algunos segundo.";
            _stringDesc2 = "SALUD : Restaura 15% de su HP.";
            _stringDesc3 = "ALAS : Permite realizar doble saltos";
            _stringDesc4 = "ARMA NUCLEAR : KABOOM !";
            _stringDesc5 = "MULTIPLICADOR : Duplica el valor de las monedas.\n       Jackpot !";
            _stringDesc6 = "MONEDAS Y MONEDAS DE ORO (x2 Bonificaciones) :\n       Atraparlos a todos !";

            _subTitle.setPosition(480, 120);
            _desc1.setPosition(230, 230);
            _desc2.setPosition(230, 360);
            _desc3.setPosition(230, 490);
            _desc4.setPosition(690, 230);
            _desc5.setPosition(690, 360);
            _desc6.setPosition(690, 490);
        }

        _title.setPosition(375,28);
        _closeInfo.setPosition(380,570);
        _nextPage->setTextPosition(1000,30);
        _previousPage->setTextPosition(20,30);

    }
    else if(_lang == German)
    {
        _stringTitle = "Spielregeln";
        _stringNextButton = "Nachste Seite";
        _stringPreviousButton = "Vorherige Seite";
        _stringCloseInfo ="Drücken Sie 'Flucht' zurück zum vorherigen Menu";

        if(_page1)
        {
            _stringSubTitle = "Spieler";
            _stringDesc1 =  "Sie spielen Yetiti, nette Yeti Everest vergessen, \n"
                    +string(" dass trotz all seiner Think-betes, die berühmten Salden Eröffnungstag.\n")
                    +string("Dies deshalb aus dem Wirbelwind aus seiner Höhle den interessantesten\n")
                    +string("Preis ans Licht zu bringen. In seiner Reise wird er viele Hindernisse,\n")
                    +string(" wie zum Beispiel den hohen Tannen, hungrige Wölfe Gesicht, die Hubschrauber\n")
                    +string("der Armee, die ihn mit seiner kriminellen Cousin verwechseln: 'Bigfoot'. Im Vorbeigehen\n")
                    +string("sollte Stücke abholen zu seiner Kleidung Kosten erreichen.");
            _stringDesc2 = "Das Spiel wird gespielt nur mit der Tastatur' :\n"
                    +string("'PFEIL RECHT' um vorzurucken\n")
                    +string("'PFEIL LINKS' um Back\n")
                    +string("'PFEIL UP' zu springen\n")
                    +string("'FLUCHT' pausieren");

            _subTitle.setPosition(550, 120);
            _desc1.setPosition(350, 220);
            _desc2.setPosition(350, 400);
        }

        if(_page2)
        {
            _stringSubTitle = "Feinde";
            _stringSubSubTitle = "Irdischen Feinde";
            _stringSubSubTitle2 = "Air Feinde";
            _stringDesc1 = "ROCK : Ein einzelner Block aus Granit\nSCHADEN : 10%\nBEWEGUNG : NEIN";
            _stringDesc2 = "BAUM : Ein schoner Tanne (but not least dangerous)\nSCHADEN : 15%\nBEWEGUNG : NEIN";
            _stringDesc3 = "WOLF : Ein wilde ausgehungert Wolf\nSCHADEN : 20%\nBEWEGUNG : JA";
            _stringDesc4 = "LITTLE BIRD : Ein umstandlich grauer Vogel\nSCHADEN : 10%\nBEWEGUNG : JA";
            _stringDesc5 = "BIG BIRD : Ein stolzer und heftige Adler\nSCHADEN : 15%\nBEWEGUNG : JA";
            _stringDesc6 = "HELICOPTER : Der Tod kommt vom Himmel !\nSCHADEN : 20%\nBEWEGUNG : JA";

            _subTitle.setPosition(550, 120);
            _subSubTitle.setPosition(330, 170);
            _subSubTitle2.setPosition(800, 170);
            _desc1.setPosition(250, 220);
            _desc2.setPosition(250, 340);
            _desc3.setPosition(250, 480);
            _desc4.setPosition(750, 220);
            _desc5.setPosition(750, 350);
            _desc6.setPosition(750, 480);
        }

        if(_page3)
        {
            _stringSubTitle = "Bonus";
            _stringDesc1 = "ABSCHIRMEN : Dieser Bonus macht Sie unbesiegbar\n       für einige Sekunden.";
            _stringDesc2 = "GESUNDHEIT : Erholen 15% Ihrer HP.";
            _stringDesc3 = "FLUGEL : Ermoglicht make Doppelsprunge.";
            _stringDesc4 = "KERNWAFFEN : KABOOM !";
            _stringDesc5 = "MULTIPLIKATOR : Verdopplen Sie den Wert der Munzen.\n       Jackpot !";
            _stringDesc6 = "MUNZEN UND GOLDMUNZEN (x2 Feinde) :\n       Fangen sie alle !";

            _subTitle.setPosition(550, 120);
            _desc1.setPosition(230, 230);
            _desc2.setPosition(230, 360);
            _desc3.setPosition(230, 490);
            _desc4.setPosition(690, 230);
            _desc5.setPosition(690, 360);
            _desc6.setPosition(690, 490);
        }

        _title.setPosition(480,28);
        _closeInfo.setPosition(375,570);
        _nextPage->setTextPosition(1015,30);
        _previousPage->setTextPosition(20,30);
    }

    _title.setString(_stringTitle);
    _subTitle.setString(_stringSubTitle);
    _subSubTitle.setString(_stringSubSubTitle);
    _subSubTitle2.setString(_stringSubSubTitle2);
    _desc1.setString(_stringDesc1);
    _desc2.setString(_stringDesc2);
    _desc3.setString(_stringDesc3);
    _desc4.setString(_stringDesc4);
    _desc5.setString(_stringDesc5);
    _desc6.setString(_stringDesc6);
    _closeInfo.setString(_stringCloseInfo);
    _closeInfo.setCharacterSize(20);
    _nextPage->setText(_stringNextButton);
    _previousPage->setText(_stringPreviousButton);
}

//=======================================================================================================
// Description : Detecteur et traitement d'évenements
// Auteur : Guillaume Nedelec
// Date : 23/05/16
// Interêt : permet de récupérer les évenements de l'utilisateur et de les traiter en fonction de ceux-ci
//=======================================================================================================
bool Rules::treatEvents()
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

                if(_page1)
                {
                    if(_nextPage->getSelected())
                    {
                        _page1 = false;
                        _page2 = true;
                    }
                }
                else if(_page2)
                {
                    if(_nextPage->getSelected())
                    {
                        _page2 = false;
                        _page3 = true;
                    }
                    else if(_previousPage->getSelected())
                    {
                        _page1 = true;
                        _page2 = false;
                    }
                }
                else if(_page3)
                {
                    if(_previousPage->getSelected())
                    {
                        _page3 = false;
                        _page2 = true;
                    }
                }
                if(_mouseX >= _closeInfo.getPosition().x-20 && _mouseX <= _closeInfo.getPosition().x +400
                        && _mouseY >= _closeInfo.getPosition().y -10 && _mouseY <= _closeInfo.getPosition().y + 30)
                {
                    result = false;
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

            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                result = false;
            }
        }
        if(_mouseX >= -12 && _mouseX <= 10 +_previousPage->get_w()-15
                && _mouseY >= 10 && _mouseY <= 10 + _previousPage->get_h())
        {
            _previousPage->setSelection(true);
            _previousPage->rectColorChange(sf::Color(18,225,225,180));
        }
        else if(_mouseX >= 965 && _mouseX <= 990 +_nextPage->get_w()
                && _mouseY >= 10 && _mouseY <= 10 + _nextPage->get_h())
        {
            _nextPage->setSelection(true);
            _nextPage->rectColorChange(sf::Color(18,225,225,180));
        }
        else if(_mouseX >= _closeInfo.getPosition().x-20 && _mouseX <= _closeInfo.getPosition().x +400
                && _mouseY >= _closeInfo.getPosition().y -10 && _mouseY <= _closeInfo.getPosition().y + 30)
        {
            _closeInfo.setColor(sf::Color(125,130,122,200));
        }
        else
        {
            _nextPage->setSelection(false);
            _previousPage->setSelection(false);
            _nextPage->rectColorChange(sf::Color(18,140,225,230));
            _previousPage->rectColorChange(sf::Color(18,140,225,230));
            _closeInfo.setColor(sf::Color::Black);
        }
    }
    return result;
}


//====================================================================================================================================================
// Description : Chargement d'images
// Auteur : Guillaume Nedelec, Nicolas Marcilloux
// Date : 20/05/16
// Interêt : permet de charger les images dans les textures et fait planter le jeu si une image ne s'est pas chargé (accompagné d'un message d'erreur)
//====================================================================================================================================================
bool Rules::loadImages()
{
    bool success = true;

    for(int i=0; i<12;i++)
    {
        sf::IntRect r(52*i,0,50,50);
        AnimCoin.push_back(r);
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

    for(int i=0; i<6; i++)
    {
        sf::IntRect r16(110*i,0,110,100);
        AnimCopter.push_back(r16);
    }

    for(int i=0; i<4; i++)
    {
        sf::IntRect r1(75*i,0,73,75);
        AnimYeti.push_back(r1);
    }
    if (!_TextureYeti.loadFromFile(YETI_WALK))
    {
        std::cerr << "ERROR when loading image file: " << YETI_WALK << std::endl;
        success = false;
    }
    if (!_TextureBird.loadFromFile(BIRD))
    {
        std::cerr << "ERROR when loading image file: " << BIRD << std::endl;
        success = false;
    }
    if (!_TextureCopter.loadFromFile(HELICO))
    {
        std::cerr << "ERROR when loading image file: " << HELICO << std::endl;
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
    if (!_TextureRock.loadFromFile(ROCK))
    {
        std::cerr << "ERROR when loading image file: " << ROCK << std::endl;
        success = false;
    }
    if (!_TextureTree.loadFromFile(TREE))
    {
        std::cerr << "ERROR when loading image file: " << TREE << std::endl;
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
    if (!_TextureArrow.loadFromFile(ARROW))
    {
        std::cerr << "ERROR when loading image file: " << ARROW << std::endl;
        success = false;
    }
    return success;
}
