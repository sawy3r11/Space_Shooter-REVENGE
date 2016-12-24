#include "StoneFormations.h"



StoneFormations::StoneFormations()
{
	//stworzenie objektu kt�ry bd wstawiany do stoneVector	
	if (!stoneExample.texture.loadFromFile("..\\\\sprite\\stone.png"))
		cout << "B�a�d przy wczytywnaiu tekstury";
	else {
		//cout << "Wczytano stone";
		stoneExample.sprite.setTexture(stoneExample.texture);
		stoneExample.sprite.setTextureRect(sf::IntRect(27, 20, 39, 25));
	}
}


StoneFormations::~StoneFormations()
{
}

/*------Formations--------------------------*/
void StoneFormations::SetArrowFormation() {
	float x = 0; 
	float y = -240;
	for (int i = 0; i < 11; i++) {
		x += 39.f;
		if (i < 6)
			y += 30;
		else
			y -= 30;
		
		//m_stoneVector.emplace_back(sf::Vector2f(x, y));  
		stoneExample.rect.setRotation(rand() % 180 + 1);
		stoneExample.rect.setPosition(sf::Vector2f(x, y));
		m_stoneVector.push_back(stoneExample);
	}
} 

void StoneFormations::SetSingleStone(sf::Vector2f position){
	stoneExample.rect.setPosition(position); 
	m_stoneVector.push_back(stoneExample);
}

void StoneFormations::SetBigTriangle() {
	float x = 0; 
	float y = -240;
	float rowAmount = 11;

	for (int i = 0; i < 7; i++){
		for (int i2 = rowAmount; i2 > -2; i2--) {
			stoneExample.rect.setRotation(rand() % 180 + 1); 
			stoneExample.rect.setPosition(sf::Vector2f(x, y)); 
			m_stoneVector.push_back(stoneExample);

			x += 39.f;
		} 
		rowAmount -= 2;
		y += 50.f;
		x = (i+1)*39.f;
	}
} 

void StoneFormations::SetRandom(levelDificulty level) {
	float x=0; 
	float y=-700;

	for (int i = 0; i < 10; i++) {
		int randomRow = rand() % level + 1;
		for (randomRow; randomRow > 0; randomRow--) {
			x = rand() % 460 + 0; 
			stoneExample.rect.setRotation(rand() % 180 + 1);
			stoneExample.rect.setPosition(sf::Vector2f(x, y));
			m_stoneVector.push_back(stoneExample);
		} 

		y += 70;
	}
}
/*---------Update-----Render----------------*/
void StoneFormations::update(sf::Time deltaTime) {
	for (std::vector<StoneNode>::iterator it = m_stoneVector.begin(); it != m_stoneVector.end(); it++) {
		(*it).rotateStone();
		(*it).update(deltaTime); 
	}
} 

void StoneFormations::render(sf::RenderWindow& window_) {
	for (std::vector<StoneNode>::iterator it = m_stoneVector.begin(); it != m_stoneVector.end(); it++) {
		(*it).render(window_);
	}
}