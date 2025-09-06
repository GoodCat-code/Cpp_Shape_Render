#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iterator>

bool shapeToVector(std::unique_ptr<IShape>& shape, std::vector<std::unique_ptr<IShape>>& vector)
{
   if (vector.size() != 0)
   {
      for (std::vector<std::unique_ptr<IShape>>::iterator it = vector.begin(); it != vector.end(); it++)
      {
         if (std::string(shape->getName()) == std::string((*it)->getName()))
         {
            vector.erase(it);
            return false;
         }
      }
   }
   vector.push_back(std::move(shape));
   return true;
}

void textRender(sf::RenderWindow& window, sf::Font& font, const char* text = "Press LMB", float x = 1500, float y = 100)
{
   sf::Text screenText(font, text);
   screenText.setPosition(sf::Vector2f(x, y));
   window.draw(screenText);
}

sf::Vector2i positionAfterClick(sf::RenderWindow& window, sf::Font& font, const char* text = "Press LMB", float x = 1500, float y = 100)
{
   sf::Vector2i position;
   while (window.waitEvent())
   {
      window.clear();
      textRender(window, font, text, x, y);     // displays clue
      window.display();
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
      {
         position = sf::Mouse::getPosition();
         break;
      }
   }
   return position;
}