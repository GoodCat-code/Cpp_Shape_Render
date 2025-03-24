#include <SFML/Graphics.hpp>
#include <iostream>
//using namespace std;
const sf::Font font("E:/C++ projects/Cpp_Shape_Render/build/Bubble Sans/BubbleSans-Regular.otf"); // ошибка неизбежна, но на "универсализацию" не хватило времени

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

   ~Circle() override {};

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

   ~Square() override {};

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

   ~Triangle() override {};

private:
   sf::ConvexShape triangle;
};

void Render(IShape& shape, sf::RenderWindow& window, const float offset = 0)
{
   shape.draw(window);
   sf::Text text(font, shape.getName());
   text.setPosition(sf::Vector2f(0, offset));
   window.draw(text);
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

int main()
{
   bool isCircle = false;
   bool isSquare = false;
   bool isTriangle = false;
   float offset = 0.0;
   sf::Text ScreenText(font, "Press 1, 2 or 3");
   ScreenText.setPosition(sf::Vector2f(1500, 900));

   sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;

   auto circle = RenderFactory::createShape(1, 150, 100, 300);
   auto square = RenderFactory::createShape(2, 300, 700, 300);
   auto triangle = RenderFactory::createShape(3, 250, 1500, 300);

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
         circle->draw(window);

      if (isSquare)
         square->draw(window);

      if (isTriangle)
         triangle->draw(window);

      window.display();
   }
}