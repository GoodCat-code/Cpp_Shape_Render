#include <SFML/Graphics.hpp>
//using namespace std;

class Shape {
public:
   virtual void draw(sf::RenderWindow &window) = 0;
};

class Circle :public Shape {
public:
   Circle(float radius, float x, float y) { 
      circle.setRadius(radius); 
      circle.setPosition(sf::Vector2f(x, y)); 
      circle.setOutlineThickness(5.0); 
      circle.setOutlineColor(sf::Color::Blue); 
      circle.setFillColor(sf::Color::Black); };

   void draw(sf::RenderWindow& window) override {
      window.draw(circle);
   };
private:
   sf::CircleShape circle;
};

class Square :public Shape {
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
private:
   sf::RectangleShape square;
};

class Triangle :public Shape {
public:
   Triangle(float size, float x, float y) { 
      triangle.setPointCount(3); triangle.setPoint(0, sf::Vector2f(x, y)); 
      triangle.setPoint(1, sf::Vector2f(x - size, y + size)); 
      triangle.setPoint(2, sf::Vector2f(x + size, y + size)); 
      /*triangle.setPosition(sf::Vector2f(x, y));*/   //optional: if must use relative coordinats
      triangle.setOutlineThickness(5.0); 
      triangle.setOutlineColor(sf::Color::Yellow); 
      triangle.setFillColor(sf::Color::Black); };

   void draw(sf::RenderWindow& window) override {
      window.draw(triangle);
   };
private:
   sf::ConvexShape triangle;
};

int main()
{   
   Circle circle(100, 100, 100);       //hardcode review
   Square square(100, 300, 300);       //hardcode review
   Triangle triangle(100, 500, 500);   //hardcode review

   auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "Shape render");
   window.setFramerateLimit(144);

   while (window.isOpen())
   {
      while (const std::optional event = window.pollEvent())
      {
         if (event->is<sf::Event::Closed>())
         {
            window.close();
         }
      }

      window.clear();

      circle.draw(window);
      square.draw(window);
      triangle.draw(window);

      window.display();
   }
}
