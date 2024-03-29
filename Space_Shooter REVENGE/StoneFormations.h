#pragma once 
#include "StoneNode.h"  
#include <stdlib.h> 
#include<vector> 
#include<random>
class StoneFormations
{
public:
	StoneFormations();
	~StoneFormations(); 
	enum levelDificulty {
		veryEasy = 1,
		Easy = 2,
		Normal = 3,
		Medium = 4,
		Hard = 6,
		Brutal = 16,
		Extrem = 30
	};
	void SetArrowFormation(float spaceBetween, int numberOfRows);
	void SetSingleStone(sf::Vector2f position); 
	void SetBigTriangle(); 
	
	void SetRandom(levelDificulty level, int amountOfRow, float spaceBetweenRow);
	
	void update(sf::Time deltaTime); 
	void render(sf::RenderWindow &window_);

	vector<StoneNode> m_stoneVector;
	
private: 
	
	StoneNode stoneExample;

};

