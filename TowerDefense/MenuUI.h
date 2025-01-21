#pragma once
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>



class MenuUI {
private:
    enum class  uiEffect {uiDefault = 0, uiHover = 1, uiPressed = 2};
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text;
    sf::Color color;
    sf::Vector2f position;
    sf::Vector2f size;

    uiEffect uiEffect;

    sf::Vector2i mousePos;
    sf::RenderWindow* window;

protected:  
    bool buttonPressed = false;
    bool buttonHovered = false;

public:
    MenuUI(sf::Vector2f size, sf::Vector2f position,
         sf::Color textColor, sf::String buttonText);
    ~MenuUI();

    void updateMousePos();
   


    bool isPressed();
    bool isHovered();
     
    void update(sf::Vector2f mousePos) ;
    void render(sf::RenderTarget* target);
};