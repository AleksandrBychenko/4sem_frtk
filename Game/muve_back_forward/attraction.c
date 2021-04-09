#include <SFML/Graphics.hpp>

using namespace sf;
int ground = 150;  


class PLAYER {

public:

	float dx, dy; // скорость  
	//FloatRect rect;// координата , ширина ,  высота 
	bool onGround;// на  земле мы или нет  
	Sprite sprite; // загружает картинку  
	float currentFrame; // ТИКУЩИЙ КАДР ДЛЯ АНИМАЦИИ 
	float coordinates_x, coordinates_y;
	 
	// ЗАГРУЖАЕМ КАРТИНКУ  
	PLAYER(Texture& image)
	{
		sprite.setTexture(image);
		//rect = FloatRect(0, 150, 40, 50);//загружаем его координаты и размер 
		coordinates_x = 0;
		coordinates_y = 150;

        dx = dy = 0;
		currentFrame = 0;	
	}

	void update(float time)
	{

		//rect.left += dx * time;
		coordinates_x += dx * time;

		if (!onGround) dy = dy + 0.0005 * time;// если не на земле то падаем с ускорением 
		//rect.top += dy * time; // прибавляем к координате y  
		coordinates_y += dy * time;

		onGround = false;
		
		if (coordinates_y > ground) { coordinates_y = ground; dy = 0; onGround = true; }

		currentFrame += 0.005 * time;
		if (currentFrame > 6) currentFrame -= 6;

		if (dx > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
		if (dx < 0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40, 50));

		sprite.setPosition(coordinates_x, coordinates_y);

		dx = 0;

	}


};




int main()
{
	
	RenderWindow window(VideoMode(800, 800), "SFML Works!");

	Texture t;
	t.loadFromFile("fang.png");

	float currentFrame = 0; // номер текужего кадра 

	PLAYER p(t);

	p.sprite.setTextureRect(IntRect(0, 244, 40, 50));
	p.sprite.setPosition(0, 150);

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
			p.dx = -0.1;

		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (p.onGround) { p.dy = -0.4; p.onGround = false; }
		}

		p.update(time);

		window.clear();
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}
