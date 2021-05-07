#include <SFML/Graphics.hpp>
#include <vector>
#include <list>



using namespace sf;
int ground = 302;

float offsetX = 0, offsetY = 0;

// карта 

const int H = 12;
const int W = 40;

String TileMap[H];

//std::vector <String> TileMap[H];

String TileMap1[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB         BB           B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};

String TileMap2[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB         BB           B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};

String TileMap3[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB         BB           B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};






//персонаж  
class PLAYER {

public:

	FloatRect rect; 
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



		rect = FloatRect(coordinates_x, coordinates_y, 40, 50);
		sprite.setPosition(coordinates_x - offsetX, coordinates_y - offsetY);

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


class ENEMY
{

public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	bool life;


	ENEMY (Texture& image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 32, 32);

		dx = 0.05;
		currentFrame = 0;
		life = true;
	}

	void update(float time)
	{
		rect.left += dx * time;

		Collision();


		//currentFrame += time * 0.005;
		//if (currentFrame > 2) currentFrame -= 2;

		sprite.setTextureRect(IntRect(0, 0, 32, 32));
		if (!life) sprite.setTextureRect(IntRect(58, 0, 32, 32));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}


	void Collision()
	{

		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
				if (TileMap[i][j] == 'B')
				{
					if (dx > 0)
					{
						rect.left = j * 32 - rect.width; dx *= -1;
					}
					else if (dx < 0)
					{
						rect.left = j * 32 + 32;  dx *= -1;
					}

				}
			}
		}

	}
};


bool startGame(RenderWindow& window, int& numberLevel) 
{
	
	if (numberLevel == 1) { TileMap[H] = TileMap1[H]; }
	if (numberLevel == 2) { TileMap[H] = TileMap2[H]; }
	if (numberLevel == 3) { TileMap[H] = TileMap3[H]; }

	
	
	//600, 450 
	Texture t, t_2;
	t.loadFromFile("fang.png");
	//t_2.loadFromFile("fang.png");
	float currentFrame = 0; // номер текужего кадра 

	PLAYER p(t);
	////////////// добавленеие врага в вектор//////////////

	//ENEMY  enemy;
	
	std::vector<ENEMY> entities;
	//int x = 2;
	//for (int i = 0; i < 2; i++)//проходимся по элементам этого вектора(а именно по врагам)
	//entities.push_back(sf::Vector2f(640,288));//и закидываем в список всех наших врагов с карты
	entities.push_back(ENEMY (t,640 , 288));
	entities.push_back(ENEMY (t, 640, 160));


	///////////////////////////

	//ENEMY  enemy;
	//enemy.set(t, entities[0].x , entities[0].y);
	//ENEMY enemy(t,640 , 288);
	//ENEMY enemy(t, 640, 288);



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

		if (Keyboard::isKeyPressed(Keyboard::T)) { numberLevel++; return true; }
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }//если таб, то перезагружаем игру
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//если эскейп, то выходим из игры



		p.update(time);

		for (int i = 0; i < 2 ; i++)
		 entities[i].update(time);



		if (p.coordinates_x > 400) offsetX = p.coordinates_x - 800 / 2;

		if (p.coordinates_y > 400) offsetY = p.coordinates_y - 800 / 2;

		//if  (p.coordinates_x > 600) offsetX = p.coordinates_x - 800 / 2;


		window.clear(Color::White);


		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Blue);

				if (TileMap[i][j] == '0')  rectangle.setFillColor(Color::Green);

				if (TileMap[i][j] == ' ') continue;

				rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(rectangle);
			}

		for (int i = 0; i < 2; i++) {
			if (p.rect.intersects(entities[i].rect))
			{
				if (entities[i].life) {
					if (p.dy > 0) { entities[i].dx = 0; p.dy = -0.2; entities[i].life = false; }
					else p.sprite.setColor(Color::Red);
				}
			}
		}

		window.draw(p.sprite);
		for (int i = 0; i < 2; i++)
		  window.draw(entities[i].sprite);

		window.display();
	}

	
}


void gameRunning(RenderWindow& window, int& numberLevel) {//ф-ция перезагружает игру , если это необходимо
	if (startGame(window, numberLevel)) { gameRunning(window, numberLevel); }//принимает с какого уровня начать игру
}



int main()
{
	RenderWindow window(VideoMode(800, 384), "SFML Works!");
	int numberLevel = 1;//сначала 1-ый уровень
	gameRunning(window, numberLevel);
	return 0;
}
