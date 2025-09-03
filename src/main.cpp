#include <iostream>
#include "IShape.h"
#include <SFML/Graphics.hpp>

int main()
{
   sf::Font font;
   if (!font.openFromFile("assets/fonts/BubbleSans-Regular.otf"))
      std::cerr << "Font not found!";

   bool isCircle = false;     // hardcode
   bool isSquare = false;     // hardcode
   bool isTriangle = false;   // hardcode
   float offset = 0.0;
   sf::Text ScreenText(font, "Press 1, 2 or 3");
   ScreenText.setPosition(sf::Vector2f(1500, 900));

   sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;

   auto circle = RenderFactory::createShape(1, 150, 100, 300);       // hardcode
   auto square = RenderFactory::createShape(2, 300, 700, 300);       // hardcode
   auto triangle = RenderFactory::createShape(3, 250, 1500, 300);    // hardcode

   auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "IShape render");
   window.setFramerateLimit(144);

   while (window.isOpen())
   {
      while (const std::optional event = window.pollEvent())
      {
         if (event->is<sf::Event::Closed>())
         {
            window.close();
         }

         if (event->is<sf::Event::KeyPressed>())
         {
            // input
            auto keyEvent = event->getIf<sf::Event::KeyPressed>();
            key = keyEvent->code;

            // facepalm
            switch (key) {
            case sf::Keyboard::Key::Num1:
               isCircle = !isCircle;
               break;
            case sf::Keyboard::Key::Num2:
               isSquare = !isSquare;
               break;
            case sf::Keyboard::Key::Num3:
               isTriangle = !isTriangle;
               break;
            }
         }
      }

      window.clear();

      window.draw(ScreenText);

      // hardcode
      if (isCircle)
         circle->draw(window);

      if (isSquare)
         square->draw(window);

      if (isTriangle)
         triangle->draw(window);

      window.display();
   }
}