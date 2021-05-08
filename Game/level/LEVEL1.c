#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include  <stdlib.h>




using namespace sf;
int ground = 302;

int Level_Next;

float offsetX = 0, offsetY = 0;

// карта 

const int H = 20;
const int W = 50;

String TileMap[H];


String TileMap1[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                              BB               B",
"B                            BB            DD DDD",
"B                                B        D  D  D",
"B                      BBB       B        D  D  D",
"B                              BBB        D  D  D",
"B                                B              L",
"B                   BB       BB  B              L",
"B                                B     DDDDDDDDDD",
"D                         BBBB  BB             DD",
"DD                                B            DD",
"DDDD      G                  B                 DD",
"D        GGG                 B                 DD",
"B         B             BB   B                 DD",
"B     D   B             BB   BRRRRRRRRRRRRRRRRRRD",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};

String TileMap2[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                B              B",
"B                                B              B",
"B                                B              B",
"B                                B              B",
"B         0000                BBBB              B",
"B                                B              B",
"BBB        000                   BL             B",
"B              BB                BB             B",
"B              BB         BB                    B",
"B    B         BB         BB                    B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};

String TileMap3[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                               B",
"B                                B              B",
"B                                B              B",
"B                                B              B",
"B                                B              B",
"B         0000                BBBB              B",
"B                                B              B",
"BBB       BBB                    BL             B",
"B              BB                BB             B",
"B              BB         BB                    B",
"B    B         BB         BB                    B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};






//////////////////////Персонаж////////////////////////  
class PLAYER {

public:

	FloatRect rect;
	float dx, dy; // скорость  
	//FloatRect rect;// координата , ширина ,  высота 
	bool onGround;// на  земле мы или нет  
	Sprite sprite; // загружает картинку  
	float currentFrame; // ТИКУЩИЙ КАДР ДЛЯ АНИМАЦИИ 
	float coordinates_x, coordinates_y;

	///// ЗАГРУЖАЕМ КАРТИНКУ //////// 
	PLAYER(Texture& image, float x, float y)
	{
		sprite.setTexture(image);
		coordinates_x = x;
		coordinates_y = y;
        dx = dy = 0; // скорость 
		currentFrame = 0;
	}

	////// Перемещение ///////////
	void update(float time)
	{

		//for x
		coordinates_x += dx * time;
		Collision(0);

        //for y
		if (!onGround) dy = dy + 0.0005 * time;// если не на земле то падаем с ускорением 
		coordinates_y += dy * time;
        onGround = false;
		Collision(1);

        //chang currentFrame
		currentFrame += 0.005 * time;
		if (currentFrame > 6) currentFrame -= 6;
        if (dx > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
		if (dx < 0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40, 50));

		// для сталкновений 
		rect = FloatRect(coordinates_x, coordinates_y, 40, 50);
		
		//change positions
		sprite.setPosition(coordinates_x - offsetX, coordinates_y - offsetY);
        dx = 0;

	}

	/////////// Сталкновение  //////////////
	void Collision(int dir)
	{
		for (int i = coordinates_y / 32; i < (coordinates_y + 50) / 32; i++)
			for (int j = coordinates_x / 32; j < (coordinates_x + 40) / 32; j++)
			{
				if (TileMap[i][j] == 'B' || TileMap[i][j] == 'D' || TileMap[i][j] == 'G')
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

				if (TileMap[i][j] == 'R') exit(0);


				if (TileMap[i][j] == 'L')
				{
					Level_Next = 1;
				}

			}

	}
	///////////
};
    /////////////////


/////////Враг//////
class ENEMY
{

public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	bool life;


	ENEMY(Texture& image, int x, int y)
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

		sprite.setTextureRect(IntRect(0, 0, 32, 32));
		if (!life) sprite.setTextureRect(IntRect(58, 0, 32, 32));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}


	void Collision()
	{

		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
				if (TileMap[i][j] == 'B' || TileMap[i][j] == 'D' || TileMap[i][j] == 'G')
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
				//if (TileMap[i][j] == 'R') exit(0);
			}
		}

	}
};

////// Главная функция по уровням ///////
bool startGame(RenderWindow& window, int& numberLevel)
{
	float coordinates_x, coordinates_y;

	if (numberLevel == 1) {
		for (int i = 0; i < H; i++) {
			TileMap[i] = TileMap1[i];
			coordinates_x = 32;
			coordinates_y = 302;
		}
	}
	if (numberLevel == 2) {
		for (int i = 0; i < H; i++) {
			TileMap[i] = TileMap2[i];
			
			coordinates_x = 32;
			coordinates_y = 32;

		}
	}
	if (numberLevel == 3) {
		for (int i = 0; i < H; i++) {
			TileMap[i] = TileMap3[i];
			coordinates_x = 32;
			coordinates_y = 32;
		}
	}


	//загрузка текстур 
	Texture t, t_2;
	t.loadFromFile("fang1.png");
	t_2.loadFromFile("Mush.png");
	
	float currentFrame = 0; // номер текужего кадра 

	PLAYER p(t, coordinates_x,coordinates_y );
	
	
	////////////// добавленеие врага в вектор//////////////


	std::vector<ENEMY> entities;
	entities.push_back(ENEMY(t_2, 640, 288));
	entities.push_back(ENEMY(t_2, 640, 160));


	///////////////////////////




	p.sprite.setTextureRect(IntRect(32, 302, 40, 50));
	


	RectangleShape rectangle(Vector2f(32, 32));

	Clock clock;





	
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();// дать прошедшее время в микросекиндах 
		clock.restart();

		time = time / 800;

		
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
			if (p.onGround) { p.dy = -0.38; p.onGround = false; }
		}

		//////доп кнопки ///// 
		if (Keyboard::isKeyPressed(Keyboard::T)) {
			numberLevel++; 
			offsetX = 0; 
			offsetY = 0;
			return true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { 
			offsetX = 0;
			offsetY = 0;
			
			return true; 
		
		}//если таб, то перезагружаем игру
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			offsetX = 0; offsetY = 0; return false;
		}//если эскейп, то выходим из игры
		/////


		if (Level_Next == 1) {
			numberLevel++;
			offsetX = 0;
			offsetY = 0;
			return true;
		}

		
		p.update(time);

	
		for (int i = 0; i < 2; i++)
			entities[i].update(time);


		// следование карты  
		if (p.coordinates_x > 400 && p.coordinates_x < 1200) offsetX = p.coordinates_x - 800 / 2;

		if (p.coordinates_y > 160 && p.coordinates_y < 416) offsetY = p.coordinates_y - 320 / 2;

		


		window.clear(Color::White);

		// Рисуем карту 
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'D') rectangle.setFillColor(Color::Black);

				if (TileMap[i][j] == '0')  rectangle.setFillColor(Color::Green);

				if (TileMap[i][j] == 'L')  rectangle.setFillColor(Color::Blue);

				if (TileMap[i][j] == 'B') rectangle.setFillColor(Color(128, 64, 0));

				if (TileMap[i][j] == 'G')  rectangle.setFillColor(Color::Green);

				if (TileMap[i][j] == 'R')  rectangle.setFillColor(Color::Red);



				if (TileMap[i][j] == ' ') continue;

				rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(rectangle);
			}
		
		//взаимодействие с врагом 
		for (int i = 0; i < 2; i++) {
			if (p.rect.intersects(entities[i].rect))
			{
				if (entities[i].life) {
					if (p.dy > 0) { entities[i].dx = 0; p.dy = -0.2; entities[i].life = false; }
					else {
						
						p.sprite.setColor(Color::Red);
						exit(0);	
						
						
					}
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
	if (startGame(window, numberLevel)) {
		if (numberLevel < 4) {
			Level_Next = 0; gameRunning(window, numberLevel);
		}//принимает с какого уровня начать игру
		else 
			exit;

	}
}



int main()
{
	RenderWindow window(VideoMode(800, 384), "SFML Works!");
	Level_Next = 0;
	int numberLevel = 1;//сначала 1-ый уровень
	gameRunning(window, numberLevel);
	return 0;
}
