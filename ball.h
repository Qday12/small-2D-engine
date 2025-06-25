//
// Created by qday on 6/23/25.
//

#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics/CircleShape.hpp>


struct Ball {

    sf::CircleShape shape;
    //float radius = 30;
    sf::Vector2f acceleration;
    sf::Vector2f position_current;// = {0,0};
    sf::Vector2f position_old;// = {-1,-1};

    Ball(float radius);
    void updatePosition(float dt);
    void accelerate(sf::Vector2f acc);


};



#endif //BALL_H
