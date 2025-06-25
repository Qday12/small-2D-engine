#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>

#include "ball.h"
//test

float getRandomIncrementOf5() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(0, 4); // 0 to 4 inclusive

    // Possible values: 10, 15, 20, 25, 30
    return 8 + dis(gen) * 2;
}


sf::Vector2f gravity = {0, 1000};


//Ball ball(30);
Ball smallBall(8);
// Small ball launch parameters
sf::Vector2f launchPosition = {500.0f, 500.0f};
sf::Vector2f launchDirection = {1.0f, 0.0f}; // Start pointing right
float launchSpeed = 300.0f;
int numberOfSmallBalls = 700;
bool smallBallLunchFlag = false;
int k = 0;

bool mouseBallFlag = false;
Ball mouseBall(30);


std::vector<Ball> balls;



void drawAll(sf::RenderWindow& window) {
    for (Ball& ball:balls) {
        window.draw(ball.shape);
    }
}

void applyGravity() {
    for (Ball& ball : balls) {
        ball.accelerate(gravity);
    }
}
void updatePosition(float dt) {

    for (Ball& ball : balls) {

        ball.updatePosition(dt);

    }
}

void applyBorders(sf::RenderWindow& window) {
    for (Ball& ball : balls) {
        float radius = ball.shape.getRadius();
        sf::Vector2f& pos = ball.position_current;
        sf::Vector2f& old_pos = ball.position_old;
        float wallDamping = 0.7f; // Lose 30% energy on wall collision

        // Ensure the shape origin is correct (center of circle)
        ball.shape.setOrigin(sf::Vector2f(radius, radius));

        // X-axis
        if (pos.x - radius < 0) {
            pos.x = radius;
            old_pos.x = pos.x + (pos.x - old_pos.x) * wallDamping;
        } else if (pos.x + radius > window.getSize().x) {
            pos.x = window.getSize().x - radius;
            old_pos.x = pos.x + (pos.x - old_pos.x) * wallDamping;
        }

        // Y-axis
        if (pos.y - radius < 0) {
            pos.y = radius;
            old_pos.y = pos.y + (pos.y - old_pos.y) * wallDamping;
        } else if (pos.y + radius > window.getSize().y) {
            pos.y = window.getSize().y - radius;
            old_pos.y = pos.y + (pos.y - old_pos.y) * wallDamping;
        }

        ball.shape.setPosition(pos);
    }
}

void brutforceSolveColisions() {
    float collisionDamping = 0.95f; // Slight energy loss on collision
    
    for (int i = 0; i < balls.size(); i++) {
        for (int k = i + 1; k < balls.size(); k++) {
            sf::Vector2f collision_axis = balls[i].position_current - balls[k].position_current;
            float dist = sqrt(collision_axis.x * collision_axis.x + collision_axis.y * collision_axis.y);
            float added_dist = balls[i].shape.getRadius() + balls[k].shape.getRadius();
            
            if (dist < added_dist && dist > 0) {
                sf::Vector2f normal = collision_axis / dist;
                float delta = added_dist - dist;
                
                // Separate the balls
                balls[i].position_current += 0.5f * delta * normal;
                balls[k].position_current -= 0.5f * delta * normal;
                
                // Simple velocity damping - reduce velocities slightly
                sf::Vector2f vel_i = balls[i].position_current - balls[i].position_old;
                sf::Vector2f vel_k = balls[k].position_current - balls[k].position_old;
                
                // Apply damping by adjusting old positions
                balls[i].position_old = balls[i].position_current - vel_i * collisionDamping;
                balls[k].position_old = balls[k].position_current - vel_k * collisionDamping;
            }
        }
    }
}

void update(float dt, sf::RenderWindow& window) {
    int subSteps = 8;
    float subDt = dt / subSteps;

    for (int i = 0; i < subSteps; i++) {
        applyGravity();
        applyBorders(window);
        brutforceSolveColisions();
        updatePosition(subDt);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML works!");
    sf::Clock clock;

    // Q - mouseBall
    mouseBall.shape.setFillColor(sf::Color::Black);
    //balls.push_back(mouseBall);





    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        // handle events
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

        // SMALL BALL SPAWN (R)
        if (k < numberOfSmallBalls && smallBallLunchFlag) {
            // Set ball at launch position
            smallBall.position_current = launchPosition;
            
            // Give ball initial velocity in the rotating direction
            smallBall.position_old = launchPosition - launchDirection * launchSpeed * dt;
            
            float newRadius = getRandomIncrementOf5();
            smallBall.shape.setRadius(newRadius);
            smallBall.shape.setOrigin(sf::Vector2f(newRadius, newRadius)); // Fix origin
            
            // Rotate the launch direction for next ball
            float oldX = launchDirection.x;
            launchDirection.x = oldX * 0.999848f - launchDirection.y * 0.017452f;
            launchDirection.y = oldX * 0.017452f + launchDirection.y * 0.999848f;

            balls.push_back(smallBall);
            k++;
            std::cout << k << std::endl;
        }

        // MOUSE BALL (Q)

        if (mouseBallFlag) {
            balls[0].shape.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
            balls[0].position_current = sf::Vector2f(sf::Mouse::getPosition(window));
            balls[0].position_old = balls[0].position_current;
        }

        window.clear();
        update(dt, window);
        drawAll(window);
        window.display();
    }
}