#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RunnerUnitsTests

#include <boost/test/unit_test.hpp>
#include "Model.h"


//======================================================
// Verification de l'ajout d'élément ainsi que leur suppression
//======================================================
BOOST_AUTO_TEST_CASE(addSupprElementTest)
{
    Model m(1200, 600);

    //Verification que tout est bien vide
    BOOST_CHECK(m.getBonus().size() == 0);
    BOOST_CHECK(m.getObstacle().size() == 0);
    BOOST_CHECK(m.getCoin().size() == 0);

    m.addElement(0); //Ajout d'un obstacle
    m.addElement(1); //Ajout d'une serie de pièce (aléatoire entre 3 et 5 pièce)
    m.addElement(2); //Ajout d'un bonus

    unsigned int nb_coin_added = m.getCoin().size(); //On se renseigne sur le nombre de pièce ajoutées

    //Verification de la taille des sets (1 pour les obstacles et les bonus)
    BOOST_CHECK(m.getBonus().size() == 1);
    BOOST_CHECK(m.getObstacle().size() == 1);
    BOOST_CHECK((m.getCoin().size() == nb_coin_added));

    //Suppression du premier element de chaque set
    m.deleteObstacle(*m.getObstacle().begin());
    m.deleteCoin(*m.getCoin().begin());
    m.deleteBonus(*m.getBonus().begin());

    //Verification de la suppression dans tous les sets
   BOOST_CHECK(m.getObstacle().size() == 0);
   BOOST_CHECK(m.getBonus().size() == 0);
   BOOST_CHECK(m.getCoin().size() == nb_coin_added - 1);
}




//======================================================
// Verifie que l'incrémentation du score avec le temps
//(compteur par frames) se réalise
//======================================================
BOOST_AUTO_TEST_CASE(scoreCalculationTest)
{
    Model m(1200, 600);

    BOOST_CHECK(m.getScore() == 0);

    m.setCptFrameScore(30); //On suppose que 30 frame se sont déroulée pour les tests Unitaires
    m.scoreCalculation(); //Calcul du score en prenant en compte les frames
    BOOST_CHECK(m.getScore() == 1);

    m.setCptFrameScore(1); //On initialise le compteur de frame a 1 pour veerifier que le score ne se modifie pas
    m.scoreCalculation();
    BOOST_CHECK(m.getScore() == 1);

    m.setCptFrameScore(30);
    m.scoreCalculation();
    BOOST_CHECK(m.getScore() == 2);
}




//===========================================
// Verifie que les MovableElement se créent
// avec les bonnes valeurs
//===========================================
BOOST_AUTO_TEST_CASE(getElementTest)
{
    Obstacle o{1,2,3,4,5,6,7};
    BOOST_CHECK(o.get_x() == 1);
    BOOST_CHECK(o.get_y() == 2);
    BOOST_CHECK(o.get_w() == 3);
    BOOST_CHECK(o.get_h() == 4);
    BOOST_CHECK(o.get_type() == 7);

    Bonus b{8,9,10,11,12,13,14};
    BOOST_CHECK(b.get_x() == 8);
    BOOST_CHECK(b.get_y() == 9);
    BOOST_CHECK(b.get_w() == 10);
    BOOST_CHECK(b.get_h() == 11);
    BOOST_CHECK(b.get_type() == 14);

    Coin c{15,16,17,18,19,20};
    BOOST_CHECK(c.get_x() == 15);
    BOOST_CHECK(c.get_y() == 16);
    BOOST_CHECK(c.get_w() == 17);
    BOOST_CHECK(c.get_h() == 18);
}

//===========================================
// Verification de l'existence de collision
//===========================================
BOOST_AUTO_TEST_CASE(Collision)
{
    Ball b{300,400,50,50,0,0};
    Obstacle* o = new Obstacle{400,400,100,25,0,0,1};
    Obstacle* o2 = new Obstacle{340,400,100,25,0,0,1};
    Obstacle* o3 = new Obstacle{305,500,100,25,0,0,1};
    Obstacle* o4 = new Obstacle{305,420,100,25,0,0,1};
    Obstacle* o5 = new Obstacle{190,400,100,25,0,0,1};
    Obstacle* o6 = new Obstacle{250,400,100,25,0,0,1};
    Obstacle* o7 = new Obstacle{305,250,100,25,0,0,1};
    Obstacle* o8 = new Obstacle{305,380,100,25,0,0,1};

    BOOST_CHECK(b.collision(o) == false);
    BOOST_CHECK(b.collision(o2) == true);
    BOOST_CHECK(b.collision(o3) == false);
    BOOST_CHECK(b.collision(o4) == true);
    BOOST_CHECK(b.collision(o5) == false);
    BOOST_CHECK(b.collision(o6) == true);
    BOOST_CHECK(b.collision(o7) == false);
    BOOST_CHECK(b.collision(o8) == true);

    delete o;
    delete o2;
    delete o3;
    delete o4;
    delete o5;
    delete o6;
    delete o7;
    delete o8;
}

//====================================================================
// Verifie que, lorsque la balle reçoit des dommages, sa vie diminue
//====================================================================
BOOST_AUTO_TEST_CASE(damagesTest)
{
    Ball b{0,0,0,0,0,0};
    BOOST_CHECK(b.getLife() == 100);

    b.damages(0); //Obstacle de type 0 ( -10 points de vie)
    BOOST_CHECK(b.getLife() == 90);

    b.damages(1); //Obstacle de type 1 ( -20 points de vie)
    BOOST_CHECK(b.getLife() == 70);

    b.damages(2); //Obstacle de type 2 ( -30 points de vie)
    BOOST_CHECK(b.getLife() == 40);
}


//===============================================
// Verification des coordonnées y lors d'un saut
//===============================================
BOOST_AUTO_TEST_CASE(jumpBallTest)
{
    Ball b{450,450,10,10,0,0};

    b.jumpBall();
    BOOST_CHECK(b.get_y() == 442);

    b.jumpBall();
    BOOST_CHECK(b.get_y() == 434);
}




//===========================================================
// Verification du mouvement des Elements Mobiles
//===========================================================
BOOST_AUTO_TEST_CASE(moveElementTest)
{
     Coin c{1000, 400, 10, 10, -10, 0};
     BOOST_CHECK(c.get_x() == 1000);

     c.move();
     BOOST_CHECK(c.get_x() == 990);

     c.move();
     BOOST_CHECK(c.get_x() == 980);


     Bonus b{1000, 400, 10, 10, 10, 0, 0};
     BOOST_CHECK(b.get_x() == 1000);

     b.move();
     BOOST_CHECK(b.get_x() == 1010);

     b.move();
     BOOST_CHECK(b.get_x() == 1020);
}

//===================================================
// Verification du mouvement de la balle
//===================================================
BOOST_AUTO_TEST_CASE(moveBallTest)
{
   Ball b{450,450,10,10,10,0};
   BOOST_CHECK(b.get_x() == 450);

   b.move();
   BOOST_CHECK(b.get_x() == 460);

   b.move();
   BOOST_CHECK(b.get_x() == 470);

   b.set_dx(-10);

   b.move();
   BOOST_CHECK(b.get_x() == 460);

   b.move();
   BOOST_CHECK(b.get_x() == 450);


   b.setJump(true);
   //Pendant un saut le deplacement horizontal est divisé par 2
   b.move();
   BOOST_CHECK(b.get_x() == 445);
   b.move();
   BOOST_CHECK(b.get_x() == 440);
}

//===========================================================================
// Verification du changement de vitesse en fonction du temps (toutes les 2000 frames)
//===========================================================================
BOOST_AUTO_TEST_CASE(VitesseChangement)
{
    Model model(1200, 600);

    model.addElement(0);
    BOOST_CHECK(model.getVitesseElement() == -4); //Vitesse initiale = -4

    model.setCptFrameScore(2000); //On suppose que 2000frames se sont déroulées
    model.nextStep(); //Changement de vitesse présent dans cette fonction
    BOOST_CHECK(model.getVitesseElement() == -5);
}

//=============================
// Teste les effets des Bonus
//=============================
BOOST_AUTO_TEST_CASE(bonusEffectTest)
{
    Model m(1200, 600);

    // TEST BONUS VIE //
    BOOST_CHECK(m.getBall()->getLife() == 100);

    m.bonusEffects(1);
    BOOST_CHECK(m.getBall()->getLife()== 100);

    m.getBall()->damages(1);
    m.getBall()->damages(2);
    BOOST_CHECK(m.getBall()->getLife()== 50);

    m.bonusEffects(1);
    BOOST_CHECK(m.getBall()->getLife()== 70);

    m.bonusEffects(1);
    BOOST_CHECK(m.getBall()->getLife()== 90);

    m.bonusEffects(1);
    BOOST_CHECK(m.getBall()->getLife()== 100);


    // TEST BONUS INVINCIBLE //
    m.getBall()->damages(0);
    BOOST_CHECK(m.getBall()->getLife() == 90);

    m.bonusEffects(0); //Activation Bonus
    m.getBall()->damages(0);
    BOOST_CHECK(m.getBall()->getLife() == 90);

    m.EndInvincibleBonus(); //Fin Bonus
    m.getBall()->damages(0);
    BOOST_CHECK(m.getBall()->getLife() == 80);


     // TEST BONUS DOUBLE POINTS //
    BOOST_CHECK(m.getScore() == 0);

    m.addToScore();
    BOOST_CHECK(m.getScore() == 100);

    m.bonusEffects(3); //Activation du bonus
    m.addToScore();
    BOOST_CHECK(m.getScore() == 300);

    m.EndBonusPoint(); //Fin du Bonus
    m.addToScore();
    BOOST_CHECK(m.getScore() == 400);
}

