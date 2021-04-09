#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	
	RenderWindow window(VideoMode(800, 800), "SFML Works!");

	Texture t;
	t.loadFromFile("fang.png");

	float currentFrame = 0; // номер текужего кадра 

	Sprite s;
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 244, 40, 50));
	s.setPosition(50,100);


	Clock clock;

	//main cycle
	while (window.isOpen())
	{
		
		float time = clock.getElapsedTime().asMicroseconds();// дать прошедшее время в микросекиндах 
		clock.restart();

		time = time / 800;

		//event handling
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			s.move(-0.1*time, 0);
			
			currentFrame += 0.005 * time ;
			if (currentFrame > 6) currentFrame -= 6;

			s.setTextureRect(IntRect(40 * int(currentFrame) + 40 , 244, -40, 50));
			

		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			s.move(0.1 * time, 0);
			currentFrame += 0.005 *time ;
			if (currentFrame > 6) currentFrame -= 6;

			s.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
		}


		window.clear();
		window.draw(s);
		window.display();
	}

	return 0;
}
