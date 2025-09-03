#include "IShape.h"

Circle::Circle(float radius, float x, float y)
{
   circle.setRadius(radius);
   circle.setPosition(sf::Vector2f(x, y));
   circle.setOutlineThickness(5.0);
   circle.setOutlineColor(sf::Color::Green);
   circle.setFillColor(sf::Color::Black);
}

Square::Square(float size, float x, float y)
{ 
   square.setSize(sf::Vector2f(size, size)); 
   square.setPosition(sf::Vector2f(x, y)); 
   square.setOutlineThickness(5.0); 
   square.setOutlineColor(sf::Color::Red); 
   square.setFillColor(sf::Color::Black); 
}

Triangle::Triangle(float size, float x, float y)
{ 
   triangle.setPointCount(3); triangle.setPoint(0, sf::Vector2f(x, y)); 
   triangle.setPoint(1, sf::Vector2f(x - size, y + size)); 
   triangle.setPoint(2, sf::Vector2f(x + size, y + size)); 
   triangle.setOutlineThickness(5.0); 
   triangle.setOutlineColor(sf::Color::Yellow); 
   triangle.setFillColor(sf::Color::Black); 
}
