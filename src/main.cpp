#include <iostream>
#include "IShape.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iterator>

void shapeMover(std::unique_ptr<IShape>& shape, std::vector<std::unique_ptr<IShape>>& vector);

int main()
{
   sf::Font font;
   if (!font.openFromFile("assets/fonts/BubbleSans-Regular.otf"))
      std::cerr << "Font not found! Default used";

   std::vector<std::unique_ptr<IShape>> arrShapes;
   sf::Keyboard::Key pressedKey = sf::Keyboard::Key::Unknown;
   enum shapeEquivalent { Circle, Square, Triangle };    // masking magic numbers

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
            pressedKey = keyEvent->code;

            // TODO: ptr params
            switch (pressedKey) {
            case sf::Keyboard::Key::Num1:
               shapeMover(RenderFactory::createShape(Circle, 150, 100, 300), arrShapes);
               break;
            case sf::Keyboard::Key::Num2:
               shapeMover(RenderFactory::createShape(Square, 300, 700, 300), arrShapes);
               break;
            case sf::Keyboard::Key::Num3:
               shapeMover(RenderFactory::createShape(Triangle, 250, 1500, 300), arrShapes);
               break;
            }
         }
      }

      // main window
      window.clear();
      sf::Text clueScreenText(font, "Press 1, 2 or 3");
      clueScreenText.setPosition(sf::Vector2f(1500, 900));
      window.draw(clueScreenText);

      // Scene
      for (auto& shape : arrShapes)
         shape->shapeRender(window);

      window.display();
   }
}

void shapeMover(std::unique_ptr<IShape>& shape, std::vector<std::unique_ptr<IShape>>& vector)
{
   if (vector.size() == 0)
   {
      vector.push_back(std::move(shape));
      return;
   }

   for (std::vector<std::unique_ptr<IShape>>::iterator it = vector.begin(); it != vector.end(); it++)
   {
      if (std::string(shape->getName()) == std::string((*it)->getName()))
      {
         vector.erase(it);
         return;
      }
   }

   vector.push_back(std::move(shape));
}