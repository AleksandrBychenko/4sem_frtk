#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf; // подключаем пространство имен sf



std::vector<sf::Vector3f> charge;

float r = 25 ;

Vector2f begin;
Vector2f begin2;
Vector2f result;
Vector2f result2;



float quantaty = 2;

sf::Vector2f operator*(float k, const sf::Vector2f& v)
{
	return sf::Vector2f(v.x * k, v.y * k);
}


float len(sf::Vector2f a)//длина вектора 
{

	float rasm = sqrt(a.x * a.x + a.y * a.y) ;
	return rasm;
}

void singl_vector(std::vector<sf::Vector3f> ch, Vector2f beg) {
	Vector2f fist;
	Vector2f second; 
	Vector2f fist1;
	Vector2f second1;

	if (ch[0].z = 1) {
		fist.x = beg.x - ch[0].x;
		fist.y = beg.y - ch[0].y;
	}
	else {
		fist.x = ch[0].x - beg.x;
		fist.y = ch[0].y - beg.y;
	}
	
	/*
	fist.x = beg.x - ch[0].x;
	fist.y = beg.y - ch[0].y;

	
	second.x = ch[1].x - beg.x;
	second.y = ch[1].y - beg.y;
	*/

	for (int i = 1; i < quantaty; i++) {

		if (ch[i].z = 0) {
			second.x = beg.x - ch[i].x;
			second.y = beg.y - ch[i].y;
		}
		else {
			second.x = ch[i].x - beg.x;
			second.y = ch[i].y - beg.y;
		}

		float f = len(fist);
		float s = len(second);

		fist1 = (fist / len(fist)) * s * s;
		second1 = (second / len(second)) * f * f;

		result.x = fist1.x + second1.x;
		result.y = fist1.y + second1.y;
		
		fist = second;

		
		

	}
	result = result / len(result);
}



void singl_vector2(std::vector<sf::Vector3f> ch, Vector2f beg) {
	Vector2f fist;
	Vector2f second;
	Vector2f fist1;
	Vector2f second1;

	if (ch[0].z = 1) {
		fist.x = ch[0].x - beg.x;
		fist.y = ch[0].y - beg.y;

	}
	else {
		fist.x = beg.x - ch[0].x;
		fist.y = beg.y - ch[0].y;
	}

	/*
	fist.x = beg.x - ch[0].x;
	fist.y = beg.y - ch[0].y;


	second.x = ch[1].x - beg.x;
	second.y = ch[1].y - beg.y;
	*/

	for (int i = 1; i < quantaty; i++) {

		if (ch[i].z = 1) {
			second.x = beg.x - ch[i].x;
			second.y = beg.y - ch[i].y;
		}
		else {
			second.x = ch[i].x - beg.x;
			second.y = ch[i].y - beg.y;
		}

		float f = len(fist);
		float s = len(second);

		fist1 = (fist / len(fist)) * s * s;
		second1 = (second / len(second)) * f * f;

		result2.x = fist1.x + second1.x;
		result2.y = fist1.y + second1.y;

		fist = second;




	}
	result2 = result2 / len(result2);
}



int main()
{
	RenderWindow window(VideoMode(800, 800), "SFML Works!");
	CircleShape circle(r);
	
	
	charge.resize(quantaty);

	/*
	charge[0].x = 200;
	charge[0].y = 400;
	charge[0].z = 0;

	charge[1].x = 600;
	charge[1].y = 400;
	charge[1].z = 1;
	*/

	charge[0].x = 300;
	charge[0].y = 300;
	charge[0].z = 0;

	charge[1].x = 500;
	charge[1].y = 500;
	charge[1].z = 1;


	/*
	charge[2].x = 700;
	charge[2].y = 500;
	charge[2].z = 1;
	*/

	/*
	begin.x = 700;
	begin.y = 200;

	begin2 = begin;
	*/

	while (window.isOpen())
	{

		for (int i = 0; i < quantaty; i++) {

			circle.setPosition(charge[i].x - r, charge[i].y- r);
			if (charge[i].z == 0) {
			circle.setFillColor(sf::Color::Blue);
		   }
			else
			{
				circle.setFillColor(sf::Color::Green);
			}
			//window.clear();
			window.draw(circle);
		}
		



		Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == Event::Closed)
				window.close(); 
			switch (event.type)
			{

			case sf::Event::MouseButtonPressed: //нажатие на мышку 
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					std::cout << "mouse Left button Press" << std::endl;

					std::cout << "mouse Button Press coord x : " << event.mouseButton.x << " y : " << event.mouseButton.y << std::endl;
					begin.x = event.mouseButton.x;
					begin.y = event.mouseButton.y;
					begin2 = begin;
				}

				break;

			}




		}
		

	

			singl_vector(charge, begin);

			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(begin.x + result.x, begin.y + result.y)),
				sf::Vertex(sf::Vector2f(begin.x, begin.y))
			};


			if (begin.x < 800 && begin.y < 800 && begin.x > 0 && begin.y > 0) {
				begin = begin + result;
			}
			//window.draw(line, 2, sf::Lines);

			singl_vector2(charge, begin2);

			sf::Vertex line2[] =
			{
				sf::Vertex(sf::Vector2f(begin2.x + result2.x, begin2.y + result2.y)),
				sf::Vertex(sf::Vector2f(begin2.x, begin2.y))
			};
			
			if (begin2.x < 800 && begin2.y < 800 && begin2.x > 0 && begin2.y > 0) {
				begin2 = begin2 + result2;
			}
			//begin2 = begin2 + result2;

			//window.draw(line2, 2, sf::Lines);

		

	

			
				window.draw(line, 2, sf::Lines);
				window.draw(line2, 2, sf::Lines);
			
		
		window.display();
	}

	return 0;
}

