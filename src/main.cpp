#include <SFML/Graphics.hpp>
#include <iostream>
//using namespace std;
const sf::Font font("E:/C++ projects/Cpp_Shape_Render/build/Bubble Sans/BubbleSans-Regular.otf"); // ошибка неизбежна, но на "универсализацию" не хватило времени

class Shape {
public:
   virtual void draw(sf::RenderWindow &window) = 0;
   virtual std::string getName() = 0;
   ~Shape() {};
};

class Circle :public Shape {
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
   std::string getName() {
      return name;
   };

private:
   std::string name = "1.Circle";
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
   std::string getName() {
      return name;
   }
private:
   std::string name = "2.Square";
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
   std::string getName() {
      return name;
   }
private:
   std::string name = "3.Triangle";
   sf::ConvexShape triangle;
};

void Render(Shape& shape, sf::RenderWindow& window, const float offset = 0)
{
   shape.draw(window);
   sf::Text text(font, shape.getName());
   text.setPosition(sf::Vector2f(0, offset));
   window.draw(text);
};

int main()
{
   bool isCircle = false;
   bool isSquare = false;
   bool isTriangle = false;
   float offset = 0.0;
   sf::Text ScreenText(font, "Press 1, 2 or 3");
   ScreenText.setPosition(sf::Vector2f(1500, 900));

   sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;

   Circle circle(150, 100, 300);       //hardcode review
   Square square(300, 700, 300);       //hardcode review
   Triangle triangle(250, 1500, 300);   //hardcode review

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

         if (event->is<sf::Event::KeyPressed>())
         {
            auto keyEvent = event->getIf<sf::Event::KeyPressed>();
            key = keyEvent->code;

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

      if (isCircle)
         Render(circle, window);

      if (isSquare)
         Render(square, window, offset + 50.0);

      if (isTriangle)
         Render(triangle, window, offset + 100.0);

      window.display();
   }
}