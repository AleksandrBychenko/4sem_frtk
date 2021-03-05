#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <iostream>
#include <cstdlib>

struct Balls {
    sf::CircleShape circle;
    sf::Vector2f position;
    int ras;
    sf::Vector2f velocity;
    
    float Dobav (int r, float x, float y, float vx, float vy) { // можно ли накзвание данной функции другое 
        ras = r;
        
        position.x = x;
        position.y = y;

        velocity.x = vx;
        velocity.y = vy;
        return 0;
    }
   
};

std::vector<Balls> particles;

void animate(sf::Clock& clock) {
    sf::Time dt = clock.getElapsedTime();
    clock.restart();
    std::cout << dt.asSeconds() << std::endl;


    for (int i = 0; i < particles.size(); i++) {

        auto& item = particles[i];
        auto& p = item.position;
        auto& v = item.velocity;

        //std::cout << item.velocity.x;


      
        item.position = p + v * dt.asSeconds();
        particles[i].circle.setPosition(particles[i].position);
        //std::cout << "1-2"<< item.position.x<< item.position.x << "&&&";
       // std::cout << dt.asSeconds();


         if (v.x > 0 && p.x > (800 -50)) {
             v.x *= -1; //right
         }
         else if (v.x < 0 && p.x < 0) {
             v.x *= -1; //left
         }
         else if (v.y < 0 && p.y < 0) {
             v.y *= -1;//tern down 
         }
         else if (v.y > 0 && p.y > (800- 50)) {
             v.y *= -1;//tern down 
         }
         
         for (int j = 1; j <= (particles.size() - 1) ; j++) {
             if (sqrt(((particles[j].position.x-25) - (particles[i].position.x - 25) ) * ((particles[j].position.x -25) - (particles[i].position.x - 25)) + ((particles[j].position.y -25) - (particles[i].position.y -25))* ((particles[j].position.y - 25) - (particles[i].position.y -25 )))< 50 ) {
                 particles[j].velocity.y *= -1;
                 particles[j].velocity.x *= -1;
                 particles[i].velocity.x *= -1;
                 particles[i].velocity.y *= -1;
             }
             /*
         
             else if (particles[j].position.x > (particles[j + 1].position.x )) {
                 particles[j].velocity.x *= -1 ;
                 particles[j + 1].velocity.x *= -1;
             }
             */
         }
         

         

        //clock.restart();
    }
}


int main()
{

    
    sf::Clock clock;
    
    int quantaty = 5;
    particles.resize(quantaty);
    //particles[0].ras = 60;
    for (int i = 0; i < quantaty; i++) {
        int ras = 100 * i ;
        particles[i].Dobav(25, 100 , 50 + ras , 200 , 50  );
        particles[i].circle.setRadius(particles[i].ras);
        particles[i].circle.setPosition(particles[i].position);
    }
    

    /*
    particles.resize(2);
    particles[0].Dobav(25, 100, 200, -100, 50);
    particles[0].circle.setRadius(particles[0].ras);

    particles[1].Dobav(25, 200, 200, 100, 50);
    particles[1].circle.setRadius(particles[1].ras);

    //particles[0].circle.setPosition(particles[0].position.x - (particles[0].ras / 2), particles[0].position.y - (particles[0].ras / 2));
    //particles[1].circle.setPosition(particles[1].position.x - (particles[1].ras / 2), particles[1].position.y - (particles[1].ras / 2));
    particles[0].circle.setPosition(particles[0].position);
    particles[1].circle.setPosition(particles[1].position);
    */


    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
   // sf::CircleShape shape(100.f);
    particles[0].circle.setFillColor(sf::Color::Green);
   

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }




        animate(clock);




        window.clear();
        for (auto& i : particles) {
            window.draw(i.circle);
        }
        //window.draw(particles[0].circle);
        window.display();
    }

    return 0;
}
