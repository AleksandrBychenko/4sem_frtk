#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	
	RenderWindow window(VideoMode(200, 200), "SFML Works!");

	Texture t;
	t.loadFromFile("fang.png");

	float currentFrame = 0; // номер текужего кадра 

	Sprite s;
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 244, 40, 50));
	s.setPosition(50,100);




	//main cycle
	while (window.isOpen())
	{
		
		//event handling
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			s.move(-0.1, 0);
			
			currentFrame += 0.005;
			if (currentFrame > 6) currentFrame -= 6;

			s.setTextureRect(IntRect(40 * int(currentFrame) + 40 , 244, -40, 50));
			

		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			s.move(0.1, 0);
			currentFrame += 0.005;
			if (currentFrame > 6) currentFrame -= 6;

			s.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
		}


		window.clear();
		window.draw(s);
		window.display();
	}

	return 0;
}
