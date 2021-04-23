
/*
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(200, 200), "SFML Works!");

	sf::SoundBuffer buffer;
	buffer.loadFromFile("shoot.ogg");
	
	
	//std::vector<sf::Int16> samples = { 20, 19, 18, 17,  16, 15 ,14,  13,  12,11,10,11,12,  13, 14, 15, 16, 17, 18, 19, 20   };
	//buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);


	sf::Sound sound;
	sound.setBuffer(buffer);
	
	while (window.isOpen())
	{
		


		Event event;
		while (window.pollEvent(event))
		{
			
			
			if (event.type == Event::Closed)
				
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{

			sound.play();
		}
			
		
		window.display();
	}

	return 0;
}

*/


