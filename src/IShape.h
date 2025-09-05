#pragma once
#include <SFML/Graphics.hpp>

class IShape {
public:
   IShape() {};
   virtual void shapeRender(sf::RenderWindow &window) = 0;
   virtual const char* getName() const = 0;
   virtual ~IShape() = default;
};

class Circle :public IShape {
private:
   sf::CircleShape circle;
   Circle();
public:
   Circle(float radius, float x, float y, float thikness = 5.0, 
      sf::Color outColor = sf::Color::Green, sf::Color fillColor = sf::Color::Black);
   void shapeRender(sf::RenderWindow& window) override { window.draw(circle); };
   const char* getName() const override{ return "Circle"; };
};

class Square :public IShape {
private:
   sf::RectangleShape square;
   Square();
public:
   Square(float size, float x, float y, float thikness = 5.0, 
      sf::Color outColor = sf::Color::Red, sf::Color fillColor = sf::Color::Black);
   void shapeRender(sf::RenderWindow& window) override { window.draw(square); };
   const char* getName() const override{ return "Square"; };
};

class Triangle :public IShape {
private:
   sf::ConvexShape triangle;
   Triangle();
public:
   Triangle(float size, float x, float y, float thikness = 5.0, 
      sf::Color outColor = sf::Color::Yellow, sf::Color fillColor = sf::Color::Black);
   void shapeRender(sf::RenderWindow& window) override { window.draw(triangle); };
   const char* getName() const override{ return "Triangle"; };
};

class RenderFactory {
public:
   static std::unique_ptr<IShape> createShape(int type, float size, float x, float y) {
      switch (type) {
      case 0: return std::make_unique<Circle>(size, x, y);
      case 1: return std::make_unique<Square>(size, x, y);
      case 2: return std::make_unique<Triangle>(size, x, y);
      default: return nullptr;
      }
   };
};
