//
// Created by qday on 6/25/25.
//
#pragma once
#include "Globals.h"

class EventHandler {
public:
    //EventHandler();
    void handleEvents(sf::RenderWindow& window) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>()) {
                smallBall.shape.setRadius(30);
                smallBall.position_current = (sf::Vector2f(sf::Mouse::getPosition(window)));
                smallBall.position_old = smallBall.position_current;
                //ball.position_old = ball.position_current - sf::Vector2f(2.f, -2.f);
                balls.push_back(smallBall);
            }
            if (event->is<sf::Event::KeyPressed>()) {
                const sf::Event::KeyPressed* keyEvent = event->getIf<sf::Event::KeyPressed>();

                if (keyEvent) {
                    switch (keyEvent->code) {
                        case sf::Keyboard::Key::Space:
                            // Clear all balls
                            balls.clear();
                            k = 0;
                            break;

                        case sf::Keyboard::Key::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::Key::R:
                            smallBallLunchFlag = !smallBallLunchFlag;
                            break;
                        case sf::Keyboard::Key::Q:
                            if (mouseBallFlag) {
                                if (!balls.empty()) {
                                    balls.erase(balls.begin());
                                }
                            } else {

                                balls.insert(balls.begin(), mouseBall);
                            }

                            mouseBallFlag = !mouseBallFlag;

                        default:
                            break;
                    }
                }
            }
        }
    }

};