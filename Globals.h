#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "ball.h"

// Global variables
extern Ball smallBall;
extern std::vector<Ball> balls;

extern sf::Vector2f gravity;
extern int k;
extern bool smallBallLunchFlag;
extern bool mouseBallFlag;
extern Ball mouseBall;

#endif // GLOBALS_H