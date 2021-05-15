#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <windows.h>

using namespace std;
using namespace sf;

//int ground = 302;

int Enemis = 4;

int Level_Next;

float offsetX = 0, offsetY = 256;

bool Deth = false;

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
"B                B               B              L",
"B                BBBBB       BB  B              L",
"B                                B      DDDDDDDDD",
"D                         BBBBGGBB             DD",
"DD                           G    B            DD",
"DDDD      G                  B                 DD",
"D        GGG                 B                 DD",
"B         B             BB   B                 DD",
"B     D   B             BB   BRRRRRRRRRRRRRRRRRRD",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};

String TileMap2[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                            D                 DB",
"B                            D                  B",
"B       DD0D0D0D0D          RD      DD          B",
"BDD                DDDDD           D0           B",
"B                       D          D            B",
"B     D00D              DDDDDDDD  DR        DD0DB",
"B                             D                 B",
"B         DD                  D        R  R R   B",
"B          D                  D     DDDDDDDDDDDDB",
"B           D                 DR      RD        B",
"B                              DRR     D        B",
"BDD           D                DDDD            DD",
"B         0000                                 LB",
"B                                B             LB",
"B    000DD        DD                       DDDDDD",
"B             DD       D                        B",
"B                                     D         B",
"BRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRB",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};

String TileMap3[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                D                              B",
"B                D                              B",
"B       DD0D000D0           D                   B",
"B      DD        D                              B",
"B       D        D                              B",
"B    D  D        D                              B",
"B       D        D                              B",
"BD      DR000RRR0D                             LB",
"B       D        D                 B           LB",
"B       D        D               BBBBBBBBBBBBBBBB",
"B     D D        D              B               B",
"ВDDDD   D        D             B   G        G   B",
"B       D        D            B      GGGGGGG    B",
"B       D        D           B      G  L L  G   B",
"BBB     D        D          B       GL     LG   B",
"B       DR00R0000B         B         GLLLLLG    B",
"B       D                BB           GGGGG     B",
"B    B  D                BB                     B",
"BBBBBBBBDBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

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

				if (TileMap[i][j] == 'R') Deth = true;


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


	ENEMY(Texture& image, int x, int y, float v_x, float v_y )
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 32, 32);

		dx = v_x; 
		dy = v_y;//0.005
		currentFrame = 0;
		life = true;
	}

	void update(float time)
	{
		
		rect.left += dx * time;
        Collision(0);



		rect.top += dy * time;
		Collision(1);


		sprite.setTextureRect(IntRect(0, 0, 32, 32));
		if (!life) sprite.setTextureRect(IntRect(58, 0, 32, 32));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}


	
	void Collision(int dir)
	{
		
		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
				if (TileMap[i][j] == 'B' || TileMap[i][j] == 'D' || TileMap[i][j] == 'G')
				{
					
					if (dx > 0 && dir == 0)
					{
						rect.left = j * 32 - 32;//rect.width; 
						dx *= -1;
					}
				    else if (dx < 0 && dir == 0)
					{
						rect.left = j * 32 + 32;  dx *= -1;
					}
					else if (dy > 0 && dir == 1)
					{
						rect.top = i * 32 - 32;// rect.height; 
						dy *= -1;
					}
					else if (dy < 0 && dir == 1)
					{
						rect.top = i * 32 + 32;  dy *= -1;
					}

				}
				
			}
		}
		
		
	}
};

void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("111.png");
	menuTexture2.loadFromFile("222.png");
	menuTexture3.loadFromFile("333.png");
	//aboutTexture.loadFromFile("about.png");
	menuBackground.loadFromFile("Sherek2.jpeg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 0);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear();

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Green); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Green); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Green); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			//if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}

////// Главная функция по уровням ///////
bool startGame(RenderWindow& window, int& numberLevel)
{
	int N;
	float coordinates_x, coordinates_y;

	if (numberLevel == 1) {
		for (int i = 0; i < H; i++) {
			TileMap[i] = TileMap1[i];
			coordinates_x = 32;
			coordinates_y = 558;
		}
	}
	if (numberLevel == 2) {
		for (int i = 0; i < H; i++) {
			TileMap[i] = TileMap2[i];
			
			coordinates_x = 32;
			coordinates_y = 334;

		}
	}
	if (numberLevel == 3) {
		for (int i = 0; i < H; i++) {
			TileMap[i] = TileMap3[i];
			coordinates_x = 32;
			coordinates_y = 334;
		}
	}


	//загрузка текстур 
	Texture t, t_2;
	t.loadFromFile("fang1.png");
	t_2.loadFromFile("Mush.png");
	
	float currentFrame = 0; // номер текужего кадра 

	PLAYER p(t, coordinates_x, coordinates_y );
	
	
	////////////// добавленеие врага в вектор//////////////


	std::vector<ENEMY> entities;



	std::vector<ENEMY> entities1;
	entities1.push_back(ENEMY(t_2, 640, 320 , 0.05 , 0));
	entities1.push_back(ENEMY(t_2, 640, 576, 0.05, 0));
	entities1.push_back(ENEMY(t_2, 1472, 224, 0, 0.055));
	entities1.push_back(ENEMY(t_2, 1408, 288, 0, 0.055));

	std::vector<ENEMY> entities2;
	entities2.push_back(ENEMY(t_2, 224, 224, 0.05, 0));
	entities2.push_back(ENEMY(t_2, 640, 544, 0.05, 0));
	entities2.push_back(ENEMY(t_2, 96, 96, 0, 0.05));
	entities2.push_back(ENEMY(t_2, 160, 160, 0, 0.05));
	entities2.push_back(ENEMY(t_2, 448, 480, 0.05, 0));
	entities2.push_back(ENEMY(t_2, 1536, 512, 0.05, 0));

	std::vector<ENEMY> entities3;
	entities3.push_back(ENEMY(t_2, 192, 192, 0, 0.05));
	entities3.push_back(ENEMY(t_2, 640, 544, 0, 0.05));
	entities3.push_back(ENEMY(t_2, 96, 96, 0, 0.05));
	entities3.push_back(ENEMY(t_2, 160, 160, 0, 0.05));



	if (numberLevel == 1) {
		entities = entities1;
		N = 4;
	}
	if (numberLevel == 2) {
		N = 6;
		entities = entities2;
	}
	if (numberLevel == 3) {
		N = 4;
		entities = entities3;
	}
    
	///////////////////////////
	p.sprite.setTextureRect(IntRect(0, 244, 40, 50));
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

		/// коненц левола ///
		if (Level_Next == 1) {
			numberLevel++;
			offsetX = 0;
			offsetY = 0;
			return true;
		}

		
		p.update(time);

		/// появление врагов 
			for (int i = 0; i < N; i++)
				entities[i].update(time);
		
		

		// следование карты  
		if (p.coordinates_x > 400 && p.coordinates_x < 1200) offsetX = p.coordinates_x - 800 / 2;

		if (p.coordinates_y > 160 && p.coordinates_y < 416) offsetY = p.coordinates_y - 320 / 2;

		
		window.clear(Color::White);

		// Рисуем карту 
		for (int i = 0; i < H; i++) {
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
		}
		//взаимодействие с врагом 
		for (int i = 0; i < N; i++) {
			if (p.rect.intersects(entities[i].rect))
			{
				if (entities[i].life) {
					if (p.dy > 0) { entities[i].dx = 0; p.dy = -0.2; entities[i].life = false; }
					else {		
						p.sprite.setColor(Color::Red);
						Deth = true;
						break;
	
					}
				}
			}
		}
		
		if (!Deth) {
			window.draw(p.sprite);
			for (int i = 0; i < N; i++)
				window.draw(entities[i].sprite);
			window.display();
		}
		else break;
	}


}


void gameRunning(RenderWindow& window, int& numberLevel) {//ф-ция перезагружает игру , если это необходимо
	if (startGame(window, numberLevel)) {
		
		if (Deth) {
			Deth = false;
			menu(window);//вызов меню
			Level_Next = 0;
			int numberLevel = 1;//сначала 1-ый уровень
			offsetX = 0;
			offsetY = 256;
			gameRunning(window, numberLevel);
		}
		else if (numberLevel < 4) {
			Level_Next = 0; gameRunning(window, numberLevel);
		}//принимает с какого уровня начать игру

		else {
			cout << "The END of Game !!!!!";
			exit;
		}
	}
}

int main()
{
	RenderWindow window(VideoMode(800, 384), "SFML Works!");
	float offsetX = 0, offsetY = 256;
	menu(window);//вызов меню
	Level_Next = 0;
	int numberLevel = 1;//сначала 1-ый уровень
	gameRunning(window, numberLevel);
	return 0;
}
