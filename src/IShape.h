#pragma once
#include <SFML/Graphics.hpp>

class IShape {
public:
   IShape() {};
   virtual void draw(sf::RenderWindow &window) = 0;
   virtual const char *getName() = 0;                  // now has const & childs dont waste mem by 'name'
   virtual ~IShape() = default;                        // now exists
};

class Circle :public IShape {
public:
   Circle(float radius, float x, float y) { 
      circle.setRadius(radius); 
      circle.setPosition(sf::Vector2f(x, y)); 
      circle.setOutlineThickness(5.0); 
      circle.setOutlineColor(sf::Color::Green); 
      circle.setFillColor(sf::Color::Black); };

   void draw(sf::RenderWindow& window) override {
      window.draw(circle);
   };
   const char *getName() override{
      return "1.Circle";
   };
private:
   sf::CircleShape circle;
};

class Square :public IShape {
public:
   Square(float size, float x, float y) { 
      square.setSize(sf::Vector2f(size, size)); 
      square.setPosition(sf::Vector2f(x, y)); 
      square.setOutlineThickness(5.0); 
      square.setOutlineColor(sf::Color::Red); 
      square.setFillColor(sf::Color::Black); };

   void draw(sf::RenderWindow& window) override {
      window.draw(square);
   };
   const char *getName() override{
      return "2.Square";
   };
private:
   sf::RectangleShape square;
};

class Triangle :public IShape {
public:
   Triangle(float size, float x, float y) { 
      triangle.setPointCount(3); triangle.setPoint(0, sf::Vector2f(x, y)); 
      triangle.setPoint(1, sf::Vector2f(x - size, y + size)); 
      triangle.setPoint(2, sf::Vector2f(x + size, y + size)); 
      /*triangle.setPosition(sf::Vector2f(x, y));*/                              //optional: if must use relative coordinats
      triangle.setOutlineThickness(5.0); 
      triangle.setOutlineColor(sf::Color::Yellow); 
      triangle.setFillColor(sf::Color::Black); };

   void draw(sf::RenderWindow& window) override {
      window.draw(triangle);
   };
   const char *getName() override{
      return "3.Triangle";
   };
private:
   sf::ConvexShape triangle;
};

class RenderFactory {
public:
   static std::unique_ptr<IShape> createShape(int type, float size, float x, float y) {
      switch (type) {
      case 1: return std::make_unique<Circle>(size, x, y);
      case 2: return std::make_unique<Square>(size, x, y);
      case 3: return std::make_unique<Triangle>(size, x, y);
      default: return nullptr;
      }
   };
};

//void Render(IShape& shape, sf::RenderWindow& window, const float offset = 0)
//{
//   shape.draw(window);
//   sf::Text text(font, shape.getName());
//   text.setPosition(sf::Vector2f(0, offset));
//   window.draw(text);
//};
