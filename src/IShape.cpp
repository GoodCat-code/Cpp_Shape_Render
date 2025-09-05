#include "IShape.h"

Circle::Circle(float radius, float x, float y, float thikness, sf::Color outColor, sf::Color fillColor)
{
   circle.setRadius(radius);
   circle.setPosition(sf::Vector2f(x, y));
   circle.setOutlineThickness(thikness);
   circle.setOutlineColor(outColor);
   circle.setFillColor(fillColor);
}

Square::Square(float size, float x, float y, float thikness, sf::Color outColor, sf::Color fillColor)
{ 
   square.setSize(sf::Vector2f(size, size));
   square.setPosition(sf::Vector2f(x, y));
   square.setOutlineThickness(thikness);
   square.setOutlineColor(outColor);
   square.setFillColor(fillColor);
}

Triangle::Triangle(float size, float x, float y, float thikness, sf::Color outColor, sf::Color fillColor)
{ 
   triangle.setPointCount(3); triangle.setPoint(0, sf::Vector2f(x, y)); 
   triangle.setPoint(1, sf::Vector2f(x - size, y + size)); 
   triangle.setPoint(2, sf::Vector2f(x + size, y + size)); 
   triangle.setOutlineThickness(thikness); 
   triangle.setOutlineColor(outColor); 
   triangle.setFillColor(fillColor); 
}
