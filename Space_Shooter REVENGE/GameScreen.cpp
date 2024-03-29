#include "GameScreen.h"



GameScreen::GameScreen()
{
	if (!font.loadFromFile("..\\\\font\\ARCADECLASSIC.ttf"))
		cout << "Nie wczytano czcionki!!!" << endl;
	else {
		
		TextWin = sf::Text(" ", font, 40);
	}
	TextWin.setPosition(220, 400);

		//Text = sf::Text("YOU HAVE WIN!!!!!", font, 40);
	//backGround 
	if (!backgorund[0].texture.loadFromFile("..\\\\sprite\\background1.png"))
		cout << "B�a�d przy wczytywnaiu tekstury t�a";
	else {
		//cout << "Wczytano stone";
		backgorund[0].sprite.setTexture(backgorund[0].texture);
		backgorund[0].sprite.setTextureRect(sf::IntRect(0, 0, 480, 800));

		backgorund[0].movementSpeed = 80.f;
		backgorund[1] = backgorund[0];
		backgorund[1].rect.setPosition(sf::Vector2f(0, -800));
	}
	
	//ustawienie health bar: 
	sizeOfHealtBar = sf::Vector2f(150, 18);
	if (!healthBarTexture.loadFromFile("..\\\\sprite\\healtBar.png"))
		cout << "B�a�d przy wczytywnaiu tekstury healtBar";
	else {
		healthBarSprite.setTextureRect(sf::IntRect(0, 0, sizeOfHealtBar.x, sizeOfHealtBar.y)); 
		healthBarSprite.setTexture(healthBarTexture);
		healthBarSprite.setPosition(sf::Vector2f(310, 15));
	}
	healthRectangeShape.setSize(sizeOfHealtBar);
	healthRectangeShape.setFillColor(sf::Color::Red); 
	healthRectangeShape.setPosition(sf::Vector2f(310, 15));
	
	//ustawianie napisu do score: 
	if (!m_font.loadFromFile("..\\\\font\\ARCADECLASSIC.ttf"))
		cout << "Nie wczytano czcionki!!!" << endl;
	else
		m_score = sf::Text("Score  0", m_font, 28);
	
	m_score.setPosition(20, 5);
	musicController.play_gameLoopMusicStage1();

	//Formations
	//m_stoneFormation.SetSingleStone(sf::Vector2f(50, 10));
	positionInQue = 0;
	lifeTimeOfGameScreen = sf::Time::Zero;  
	timeFromKillingBoss = sf::seconds(5.f);
}


GameScreen::~GameScreen()
{
} 

void GameScreen::handleInput(sf::RenderWindow& window) {
	//tuaj ma by� wywo��nie metody z klasy player, firetile, stone
	//kt�re trmu odpowiada 
	player_.handleInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		Game::Screen = std::make_shared<GameOVerScreen>(player_.score);
	}
}

void GameScreen::update(sf::Time delta)
{
	m_boxCollider.DetectCollision(&player_, &m_stoneFormation.m_stoneVector, &m_pickups.pickUpVector, 
									&m_pickups, &m_fireTilleController, m_enemyShipController.enemyShipVector, 
									m_enemyShipController.enemyBoss);
	player_.update(delta);
	m_stoneFormation.update(delta);
	//backgorund
	updateBackgorund();
	backgorund[0].update(delta); 
	backgorund[1].update(delta); 
	updateHealthBar(); 
	updateScore();
	
	//enemy
	enemyController(delta);
	// pick ups
	m_pickups.Update(delta); 
	//fireTile  
	if (player_.isEnableShoot())
		m_fireTilleController.AddFireTile(player_.rect.getPosition(), fire_TileNODE::playerFireTile);
	m_fireTilleController.update(delta, m_enemyShipController.getBossPos());
	//enemyController-------------------------------------- 
	m_enemyShipController.update(delta, m_fireTilleController, player_.rect.getPosition());
	//sprawdzanie czy hp  nie jest poni�ej 0
	if (player_.hp <= 0 || bossDead)
		Game::Screen = std::make_shared<GameOVerScreen>(player_.score);
}


	

void GameScreen::render(sf::RenderWindow& window) {
	window.draw(backgorund[0].sprite);
	window.draw(backgorund[1].sprite);
	
	m_stoneFormation.render(window);
	m_pickups.Render(window); 
	m_fireTilleController.render(window);
	m_enemyShipController.render(window);

	window.draw(healthRectangeShape);
	window.draw(healthBarSprite);

	window.draw(m_score);
	player_.render(window);   

	window.draw(TextWin);
}

void GameScreen::updateBackgorund() {
	if (backgorund[0].rect.getPosition().y > 800)
		backgorund[0].rect.setPosition(sf::Vector2f(0, -800)); 
	if (backgorund[1].rect.getPosition().y > 800)
		backgorund[1].rect.setPosition(sf::Vector2f(0, -800));
}

void GameScreen::updateHealthBar() {
	healthRectangeShape.setSize(sf::Vector2f(sizeOfHealtBar.x * (player_.hp / 100.f), sizeOfHealtBar.y));
}

void GameScreen::updateScore() {
	
	m_score.setString("Score  " + std::to_string(player_.score));
} 

void GameScreen::enemyController(sf::Time deltaTime) {
	lifeTimeOfGameScreen += deltaTime; 
	
	
	if (positionInQue == 0) {
		positionInQue++; 
		m_stoneFormation.SetRandom(StoneFormations::veryEasy, 10, 250.f);  
	} 
	
	
	if (positionInQue == 1 && lifeTimeOfGameScreen.asSeconds() > 10.f) {
		positionInQue++; 
		m_stoneFormation.SetRandom(StoneFormations::veryEasy, 10, 180);
	} 
	if (positionInQue == 2 && lifeTimeOfGameScreen.asSeconds() > 15.f) {
		positionInQue++; 
	}
	if (positionInQue == 3 && lifeTimeOfGameScreen.asSeconds() > 22.f) {
		positionInQue++; 
		m_stoneFormation.SetRandom(StoneFormations::veryEasy, 10, 150);
	} 

	if (positionInQue == 4 && lifeTimeOfGameScreen.asSeconds() > 30.f) {
		positionInQue++; 
		m_stoneFormation.SetRandom(StoneFormations::Easy, 5, 200.f);
	} 

	if (positionInQue == 5 && lifeTimeOfGameScreen.asSeconds() > 40) {
		positionInQue++;
		m_stoneFormation.SetArrowFormation(200, 5);
	}

	if (positionInQue == 6 && lifeTimeOfGameScreen.asSeconds() > 50) {
		positionInQue++; 
		m_enemyShipController.AddSingleEnemy(sf::Vector2f(150, -200));
		m_enemyShipController.AddSingleEnemy(sf::Vector2f(300, -200));
	}
	
	
	if (positionInQue == 7 && lifeTimeOfGameScreen.asSeconds() > 60.f) {
		positionInQue++; 
		m_enemyShipController.SetRandom(1, 6, 220.f);
	}  

	if (positionInQue == 8 && lifeTimeOfGameScreen.asSeconds() > 75.f) {
		positionInQue++;
		m_enemyShipController.SetRandom(2, 5, 220.f);
	} 
	if (positionInQue == 9 && lifeTimeOfGameScreen.asSeconds() > 90.f) {
		positionInQue++;
		m_stoneFormation.SetRandom(StoneFormations::Normal, 10, 200.f);
	}

	if (positionInQue == 10 && lifeTimeOfGameScreen.asSeconds() > 120.f) {
		positionInQue++; 
		m_stoneFormation.SetArrowFormation(100, 8);
	} 

	if (positionInQue == 11 && lifeTimeOfGameScreen.asSeconds() > 135.f) {
		positionInQue++; 
		m_stoneFormation.SetRandom(StoneFormations::Hard, 5, 250.f);
	}

	if (positionInQue == 12 && lifeTimeOfGameScreen.asSeconds() > 145.f) {
		positionInQue++; 
		m_enemyShipController.SetRandom(3, 4, 200.f);
	} 

	if (positionInQue == 13 && lifeTimeOfGameScreen.asSeconds() > 160.f) {
		positionInQue++; 
		m_enemyShipController.SetRandom(2, 5, 150.f);
	}

	if (positionInQue == 14 && lifeTimeOfGameScreen.asSeconds() > 175.f) {
		positionInQue++; 
		m_stoneFormation.SetRandom(StoneFormations::Brutal, 6, 250);
	} 

	if (positionInQue == 15 && lifeTimeOfGameScreen.asSeconds() > 205.f) {
		positionInQue++; 
		m_enemyShipController.SetRandom(2, 8, 150.f);
	}

	if (positionInQue == 16 && lifeTimeOfGameScreen.asSeconds() > 230.f) { 
		positionInQue++;
		m_enemyShipController.AddBoss( player_.rect.getPosition());
	}
	/*
	if (positionInQue == 0) {
		positionInQue++;
		m_enemyShipController.AddBoss(player_.rect.getPosition());
	}*/

	if (m_enemyShipController.enemyBoss.m_stateOfObject == Object_Base_Class::toErase) {
		timeFromKillingBoss -= deltaTime;

		TextWin = sf::Text("YOU HAVE \n\t\tWIN!", font, 80);
		TextWin.setPosition(100, 200);
		if (timeFromKillingBoss.asSeconds() <= 0) {
			//po zabiciu bosa i p�ybieciu odpowiedniej ilo�ci czasu 
			bossDead = true;
			cout << "YOU HAVE WIN!!!";
		}
	}
	//cout << "Time" << lifeTimeOfGameScreen.asSeconds() << endl;
}
