
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <iostream>
#include <cstdlib>


float m = 10;

struct Balls { //структура шариков 
    sf::CircleShape circle;
    sf::Vector2f position;
    float ras;
    sf::Vector2f velocity;
    sf::Vector2f p;
    sf::Vector2f n;

    float Dobav(float r, float x, float y, float vx, float vy) { // функция добавление в шарики параметры  
        ras = r;

        position.x = x;
        position.y = y;

        velocity.x = vx;
        velocity.y = vy;
        return 0;
    }

};

float operator*(const sf::Vector2f& v1, const sf::Vector2f& v2)// переобазночение умножения векторов 
{
    return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f operator*(float k, const sf::Vector2f& v)
{
    return sf::Vector2f(v.x * k, v.y * k);
}


float len(sf::Vector2f a)//длина вектора 
{

    float rasm = sqrt(a.x * a.x + a.y * a.y);
    return rasm;
}

std::vector<Balls> particles;


void animate(sf::Clock& clock) {//движение 
    sf::Time dt = clock.getElapsedTime();
    clock.restart();
    int p;//impuls

    for (int i = 0; i < particles.size(); i++) {

        auto& item = particles[i];
        auto& p = item.position;
        auto& v = item.velocity;

        item.position = p + v * dt.asSeconds();
        particles[i].circle.setPosition(particles[i].position);


        //сталкновение со стенкой 
        if (v.x > 0 && p.x > (800 - 50)) {
            v.x *= -1; //right
        }
        else if (v.x < 0 && p.x < 0) {
            v.x *= -1; //left
        }
        else if (v.y < 0 && p.y < 0) {
            v.y *= -1;//tern down 
        }
        else if (v.y > 0 && p.y > (800 - 50)) {
            v.y *= -1;//tern down 
        }




        //сталкновение через  импулс 
        for (int j = i + 1; j < particles.size(); j++) {
            if (sqrt(((particles[j].position.x - 25) - (particles[i].position.x - 25)) * ((particles[j].position.x - 25) - (particles[i].position.x - 25)) + ((particles[j].position.y - 25) - (particles[i].position.y - 25)) * ((particles[j].position.y - 25) - (particles[i].position.y - 25))) < 50)
            {

                sf::Vector2f n = (particles[j].position - particles[i].position) / len(particles[j].position - particles[i].position);
                sf::Vector2f p = (((2 / ((1 / m) + (1 / m))) * (particles[j].velocity - particles[i].velocity) * n) * n);

                particles[j].velocity = particles[j].velocity - (p / m);
                particles[i].velocity = particles[i].velocity + (p / m);

                /*
               // движение без  импулса
                   particles[j].velocity.x *= -1;
                   particles[j].velocity.y *= -1;
                   particles[i].velocity.y *= -1;
                   particles[i].velocity.x *= -1;
               */

            }


        }

    }
}

sf::Vector2f position2b;
sf::Vector2f position2a;
sf::Vector2f new_velocity;


int main()
{


    sf::Clock clock;

    float quantaty = 3;
    particles.resize(quantaty);
    

    for (int i = 0; i < quantaty; i++) {
        float ras = 100 * i;
        particles[i].Dobav(25, 100, 50 + ras, 200, 50);
        particles[i].circle.setRadius(particles[i].ras);
        particles[i].circle.setPosition(particles[i].position);
    }




   

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    
    particles[0].circle.setFillColor(sf::Color::Green);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (event.type)
            {

            case sf::Event::MouseButtonPressed: //нажатие на мышку 
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    std::cout << "mouse Left button Press" << std::endl;

                    std::cout << "mouse Button Press coord x : " << event.mouseButton.x << " y : " << event.mouseButton.y << std::endl;
                    position2a.x = event.mouseButton.x;
                    position2a.y = event.mouseButton.y;
                }

                break;

            case sf::Event::MouseButtonReleased:// отжатие мышки 
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "mouse Left button Press" << std::endl;
                    std::cout << "mouse Button Press coord x : " << event.mouseButton.x << " y : " << event.mouseButton.y << std::endl;

                    position2b.x = event.mouseButton.x;
                    position2b.y = event.mouseButton.y;

                    new_velocity.x = position2b.x - position2a.x;
                    new_velocity.y = position2b.y - position2a.y;

                    // добавление нового шарика 
                    quantaty += 1;
                    particles.resize(quantaty);
                    particles[quantaty - 1].Dobav(25, position2a.x, position2a.y, new_velocity.x, new_velocity.y);
                    particles[quantaty - 1].circle.setFillColor(sf::Color::Blue);
                    particles[quantaty - 1].circle.setRadius(particles[quantaty - 1].ras);
                    particles[quantaty - 1].circle.setPosition(particles[quantaty - 1].position);


                }
                break;

            }

        }

        animate(clock);

        window.clear();
        for (auto& i : particles) {
            window.draw(i.circle);
        }
       
        window.display();
    }

    return 0;
}
