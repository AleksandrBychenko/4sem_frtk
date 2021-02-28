#include <SFML\Graphics.hpp>
/*
struct circl {
    sf::CircleShape circle;
    int i;





};
*/

int main() 
{

  //  vector < sf::CircleShape> cir; 


  
    
    
    
  sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
  /*
  while (window.isOpen())
  {
    window.clear(sf::Color::Red);
    window.display();
  }
  */



  sf::Clock clock;

 // sf::CircleShape circle(50);

  sf::Texture texture;
  texture.loadFromFile("hero.png");
  sf::Sprite circle(texture);

  circle.setScale(0.5f, 0.5f);

 


  while (window.isOpen()) {

      sf::Event event;
      
      while (window.pollEvent(event))
      {

          if (event.type == sf::Event::Closed)
              window.close();
      }



      //реализация направления на курсор 
      sf::Vector2u circleSize = circle.getTexture()->getSize();
      circle.setOrigin(circleSize.x / 2, circleSize.y / 2);

      sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
      sf::Vector2f center = circle.getPosition();
      sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;

      const float Pi = 3.14159f;
      circle.setRotation(90 + atan2f(d.y, d.x) * 180 / Pi);


     /*
      //circle 
      sf::CircleShape circle(50, 5);
      //circle.setPosition(100, 100);

      //circle.setFillColor(sf::Color(150, 50, 250));
     circle.setOutlineThickness(10);
      circle.setOutlineColor(sf::Color(250, 150, 100));
      //window.draw(circle);


      //line 
      sf::Vertex line[]  = 
      {
          sf::Vertex(sf::Vector2f(300, 300)),
          sf::Vertex(sf::Vector2f(150, 150))
      };
      
      // define a triangle
     // sf::CircleShape triangle(10, 3);

      // define a square
      //sf::CircleShape square(80, 4);

      // define an octagon
      //sf::CircleShape octagon(80, 8);

      //rectange 
      sf::RectangleShape rectangele(sf::Vector2f(120, 50));
      rectangele.setSize(sf::Vector2f(100, 300));
      rectangele.move(sf::Vector2f(400, 200));


      window.clear(sf::Color::Red);
      window.draw(circle);
      window.draw(line, 2, sf::Lines);
      window.draw(rectangele);
     // window.draw(triangle);
      */




      //движение 
      

      //sf::Time time = clock.getElapsedTime();

      //circle 
      //sf::CircleShape circle(50);
      //circle.setFillColor(sf::Color(150, 50, 250));
     // circle.setPosition(100 + 20 * time.asSeconds(), 100);

      
      window.clear(sf::Color::Color(50, 50, 50));
      window.draw(circle);
  


          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
              circle.move(-1, 0);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
              circle.move(1, 0);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
              circle.move(0, -1);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          {
              circle.move(0, 1);
          }
    



      /*
      // обработка ошибок 
      sf::Event event;
      //while there are pending events...
      while (window.pollEvent(event))
      {
          //check the type of the event 
          switch (event.type)
          {
              //window closed
          case sf::Event::Closed:
              window.close();
          break;
          case sf::Event::KeyPressed:
          {
              if (event.key.code == sf::Keyboard::Left)
              {
                  //do something 
              }
          } break;
          //we don't process other types of events
          default;
          break;
          


          }
      }

      */
      window.display();
  }








  return 0;
}
