#include <iostream>
#include <SFML/Graphics.hpp>
#include "IShape.h"
#include "Custom.h"

// Preset
int circleRadius = 150;
int squareSide = 300;
int triangleSide = 300;

int main()
{
   bool isCircleOnSceneFlag = false;
   bool isSquareOnSceneFlag = false;
   bool isTriangleOnSceneFlag = false;
   std::vector<std::unique_ptr<IShape>> arrShapes;
   sf::Keyboard::Key pressedKey = sf::Keyboard::Key::Unknown;
   enum shapeEquivalent { Circle, Square, Triangle };                                     // masking magic numbers at RenderFactory
   // set up window for render
   auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "IShape render");
   window.setFramerateLimit(144);
   // set up custom font
   sf::Font font;
   if (!font.openFromFile("assets/fonts/BubbleSans-Regular.otf"))
      std::cerr << "Font not found! Default used";

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

            // main input logic
            // select shape and press key -> choose place and click LMB -> for deleting press key 
            sf::Vector2i currentCursorPosition;
            switch (pressedKey) {
            case sf::Keyboard::Key::Num1:
               if (!isCircleOnSceneFlag)
                  currentCursorPosition = positionAfterClick(window, font);
               isCircleOnSceneFlag = shapeToVector(RenderFactory::createShape(Circle, circleRadius, 
                  currentCursorPosition.x - circleRadius, currentCursorPosition.y - circleRadius), arrShapes);
               break;
            case sf::Keyboard::Key::Num2:
               if (!isSquareOnSceneFlag)
                  currentCursorPosition = positionAfterClick(window, font);
               isSquareOnSceneFlag = shapeToVector(RenderFactory::createShape(Square, squareSide,
                  currentCursorPosition.x - squareSide / 2, currentCursorPosition.y - squareSide / 2), arrShapes);
               break;
            case sf::Keyboard::Key::Num3:
               if (!isTriangleOnSceneFlag)
                  currentCursorPosition = positionAfterClick(window, font);
               isTriangleOnSceneFlag = shapeToVector(RenderFactory::createShape(Triangle, triangleSide,
                  currentCursorPosition.x, currentCursorPosition.y - triangleSide / 1.5), arrShapes);
               break;
            }
         }
      }

      // Scene
      window.clear();
      textRender(window, font, "Press:\n1 for circle\n2 for square\n3 for triangle");

      for (auto& shape : arrShapes)
         shape->shapeRender(window);

      window.display();
   }
}
