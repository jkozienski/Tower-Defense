#include "MenuUI.h"


MenuUI::MenuUI(sf::Vector2f size, sf::Vector2f position,
     sf::Color textColor, sf::String buttonText) {

    this->font.loadFromFile("Resources\\Fonts\\04B_30__.ttf");
    this->text.setFont(this->font);

    this->uiEffect = uiEffect::uiDefault;

    // Ustawienia kszta³tu przycisku
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Transparent);

    // Ustawienia tekstu na przycisku
    text.setPosition(position);
    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(48);
    text.setFillColor(textColor);

    // Ustawienia kszta³tu przycisku na podstawie rozmiaru tekstu
    sf::FloatRect textBounds = text.getGlobalBounds();
   shape.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20)); // Dodaj margines
   // shape.setPosition(position);

    //  pozycjê tekstu na œrodek kszta³tu
   /* text.setPosition(position.x + (shape.getSize().x - textBounds.width) / 2,
        position.y + (shape.getSize().y - textBounds.height) / 2);*/
}




MenuUI::~MenuUI() = default;


void MenuUI::updateMousePos()
{
    if (window != nullptr) {
        this->mousePos = sf::Mouse::getPosition(*window);
    }

}


bool MenuUI::isPressed()
{
    if(this->uiEffect == uiEffect::uiPressed)
        return true;
    else
        return false;
}

bool MenuUI::isHovered()
{
    if (this->uiEffect == uiEffect::uiHover)
        return true;
    else
        return false;
}

void MenuUI::update(sf::Vector2f mousePos)
{

    this->updateMousePos();

    if (!this->shape.getGlobalBounds().contains(mousePos)) {
        this->uiEffect = uiEffect::uiDefault;

    }
    if (this->shape.getGlobalBounds().contains(mousePos)) {
        this->uiEffect = uiEffect::uiHover;

    } 
    if (this->shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->uiEffect = uiEffect::uiPressed;
    }


    if (uiEffect == uiEffect::uiDefault) {
        this->text.setFillColor(sf::Color::Black);
        this->text.setCharacterSize(48);


    }
    else if (uiEffect == uiEffect::uiHover){
        sf::Color color = sf::Color::Green;
        color.a = 96;
        this->text.setFillColor(color);
        this->text.setCharacterSize(51);

    }
    else if (uiEffect == uiEffect::uiPressed) {
        this->text.setFillColor(sf::Color::Green);
    }
}

void MenuUI::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);

}
