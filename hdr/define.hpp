///
/// \file Define.hpp
///

#ifndef DEFINE_H
#define DEFINE_H

#define NAME "PONYVADERS"
#define FONT "fonts/8-bit.ttf"
#define FONT_SIZE (16)

#define DEBUG_ON false

#define VIT (1)
#define IPS (50 * VIT)
#define AA (8)

#define WIN_W (600)
#define WIN_H (800)
#define WIN_BORD (WIN_H / 100)

#define COLOR1 sf::Color(42, 42, 42)
#define COLOR2 sf::Color(169, 169, 169)
#define COLOR3 sf::Color(255, 255, 255)
#define COLOR4 sf::Color(70, 130, 180)

#define SQUAD_H (2)
#define SQUAD_W (4)
#define SQUAD_SPEEDX (50)
#define SQUAD_SPEEDY (20)
#define SQUAD_ACCX (5)

#define LASER_SPEED (500)
#define AGENT_SPEED (300)
#define AGENT_SIZE (24)

#define HUMAN false
#define LEARNING true
#define SPEED_SIMU (20)

#define DISCRET_DIM (8)  // = 1 2 4 5 8 10 20 25 40 50 100 200
#define dW (WIN_W / DISCRET_DIM)
#define dH (WIN_H / DISCRET_DIM)
#define N_STATES (dW * 2 * dH * 2)

#if (DEBUG_ON == true)
#define DEBUG(str) std::cout << str << std::endl
#else
#define DEBUG(str) ;
#endif

#endif