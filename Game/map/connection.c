#include <SFML/Graphics.hpp>

using namespace sf;
int ground = 302;  

// карта 

const int H = 12;
const int W = 40;


String TileMap[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB                      B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};


//персонаж  
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
		coordinates_x = 32;
		coordinates_y = 302;

        dx = dy = 0;
		currentFrame = 0;	
	}

	void update(float time)
	{

		//rect.left += dx * time;
		coordinates_x += dx * time;
		Collision(0);



		if (!onGround) dy = dy + 0.0005 * time;// если не на земле то падаем с ускорением 
		//rect.top += dy * time; // прибавляем к координате y  
		coordinates_y += dy * time;

		onGround = false;
		Collision(1);



		//if (coordinates_y > ground) { coordinates_y = ground; dy = 0; onGround = true; }

		currentFrame += 0.005 * time;
		if (currentFrame > 6) currentFrame -= 6;

		if (dx > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
		if (dx < 0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40, 50));

		sprite.setPosition(coordinates_x, coordinates_y);

		dx = 0;

	}

	void Collision(int dir)
	{
		for (int i = coordinates_y / 32; i < (coordinates_y + 50) / 32; i++)
			for (int j = coordinates_x / 32; j < (coordinates_x + 40) / 32; j++)
			{
				if (TileMap[i][j] == 'B')
				{
					if ((dx > 0) && (dir == 0)) coordinates_x = j * 32 - 40;
					if ((dx < 0) && (dir == 0)) coordinates_x = j * 32 + 32;
					if ((dy > 0) && (dir == 1)) { coordinates_y = i * 32 - 50;  dy = 0;   onGround = true; }
					if ((dy < 0) && (dir == 1)) { coordinates_y = i * 32 + 32;   dy = 0; }
				}

				if (TileMap[i][j] == '0')
				{
					TileMap[i][j] = ' ';
				}

			}

	}
};




int main()
{
	
	RenderWindow window(VideoMode(800, 800), "SFML Works!");
	//600, 450 
	Texture t;
	t.loadFromFile("fang.png");

	float currentFrame = 0; // номер текужего кадра 

	PLAYER p(t);

	p.sprite.setTextureRect(IntRect(32, 302, 40, 50));
	p.sprite.setPosition(32, 302);


	RectangleShape rectangle(Vector2f(32, 32));

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

		window.clear(Color::White);
		

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Blue);

				if (TileMap[i][j] == '0')  rectangle.setFillColor(Color::Green);

				if (TileMap[i][j] == ' ') continue;

				rectangle.setPosition(j * 32, i * 32 );
				window.draw(rectangle);
			}
		
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}
