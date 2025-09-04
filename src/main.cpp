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
      std::cerr << "Font not found!";

   std::vector<std::unique_ptr<IShape>> arr_shapes;
   sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;

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

            // TODO: ptr params
            switch (key) {
            case sf::Keyboard::Key::Num1:
               shapeMover(RenderFactory::createShape(1, 150, 100, 300), arr_shapes);
               break;
            case sf::Keyboard::Key::Num2:
               shapeMover(RenderFactory::createShape(2, 300, 700, 300), arr_shapes);
               break;
            case sf::Keyboard::Key::Num3:
               shapeMover(RenderFactory::createShape(3, 250, 1500, 300), arr_shapes);
               break;
            }
         }
      }

      window.clear();
      sf::Text ScreenText(font, "Press 1, 2 or 3");
      ScreenText.setPosition(sf::Vector2f(1500, 900));
      window.draw(ScreenText);

      for (auto& el : arr_shapes)
         el->draw(window);

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
         it = vector.erase(it);
         return;
      }
   }

   vector.push_back(std::move(shape));
}