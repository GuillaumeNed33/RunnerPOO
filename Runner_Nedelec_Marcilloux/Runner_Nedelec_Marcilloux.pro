TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Model.cpp \
    View.cpp \
    AnimatedGraphicElement.cpp \
    SlidingBackground.cpp \
    MovableElement.cpp \
    GraphicElement.cpp \
    Obstacle.cpp \
    Coin.cpp \
    Bonus.cpp \
    Menu.cpp \
    GameView.cpp \
    Ranking.cpp \
    Button.cpp \
    Settings.cpp \
    Player.cpp \
    Intro.cpp \
    Rules.cpp

LIBS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

HEADERS += \
    GraphicElement.h \
    MovableElement.h \
    Model.h \
    SlidingBackground.h \
    View.h \
    AnimatedGraphicElement.h \
    Obstacle.h \
    Coin.h \
    Bonus.h \
    Menu.h \
    GameView.h \
    Ranking.h \
    Button.h \
    Settings.h \
    Player.h \
    Intro.h \
    Rules.h
