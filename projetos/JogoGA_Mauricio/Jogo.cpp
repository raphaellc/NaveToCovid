#include "Jogo.h"
#include <time.h>
#include <fstream>

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
	exit(0);
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);
	uniRandSetSemente(time(NULL));

	statusGame = 0;

#pragma region PLAYER

	gRecursos.carregarSpriteSheet("player", "assets/sprite/nave2.png", 1, 1);
	gRecursos.carregarSpriteSheet("tiro", "assets/sprite/tiro2.png", 1, 1);
	player.setSpriteSheet("player");
	player.Tiro::setSpriteSheet("tiro");
	
#pragma endregion
		
#pragma region SOM

	//tiro do jogador
	gRecursos.carregarAudio("effectShoot", "assets/audio/effectShoot.aiff");
	player.setAudioEffect("effectShoot");

	//musica
	gRecursos.carregarAudio("music", "assets/audio/music2.wav");
	music.setAudio("music");
	music.tocar(true);

	//damage tiro colider
	gRecursos.carregarAudio("damage", "assets/audio/damage.mp3");
	damage.setAudio("damage");

	//damage nave colider
	gRecursos.carregarAudio("damageShip", "assets/audio/naveColider.wav");
	damageShip.setAudio("damageShip");

	//power up
	gRecursos.carregarAudio("powerUp", "assets/audio/powerUp.wav");
	powerUp.setAudio("powerUp");

	//button effect
	gRecursos.carregarAudio("ButtonEffect", "assets/audio/buttonEffect.wav");
	buttonEffect.setAudio("ButtonEffect");

#pragma endregion
	
#pragma region GERAL

	item = new Item();
	item->itemInicializar();

	maxCounter = uniRandEntre(100, 500);
	counterItem = 0;

	gRecursos.carregarSpriteSheet("title", "assets/sprite/title.png", 1, 1);
	sprTitle.setSpriteSheet("title");

	gRecursos.carregarSpriteSheet("background", "assets/sprite/backGround2.png", 1, 1);
	background.setSpriteSheet("background");

#pragma endregion
	
#pragma region BUTTONS

	gRecursos.carregarSpriteSheet("buttonStart", "assets/sprite/ButtonStart2.png", 3, 1);
	buttonStart.setSpriteSheet("buttonStart");
	buttonStart.setPos(gJanela.getLargura() / 2, gJanela.getAltura() / 2 + 100);

	gRecursos.carregarSpriteSheet("buttonContinue", "assets/sprite/ButtonContinuar.png", 3, 1);
	buttonContinuar.setSpriteSheet("buttonContinue");
	buttonContinuar.setPos(gJanela.getLargura() / 2, gJanela.getAltura() / 2 + 200);

	gRecursos.carregarSpriteSheet("buttonGameOver", "assets/sprite/ButtonGameOver2.png", 3, 1);
	buttonGameOver.setSpriteSheet("buttonGameOver");
	buttonGameOver.setPos(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

#pragma endregion
	
#pragma region ENEMY

	gRecursos.carregarSpriteSheet("asteroid", "assets/sprite/asteroid2.png", 1, 1);
	asteroid[0].setSpriteSheet("asteroid");
	asteroid[1].setSpriteSheet("asteroid");
	asteroid[2].setSpriteSheet("asteroid");
	asteroid[3].setSpriteSheet("asteroid");
	
#pragma endregion
}

void Jogo::finalizar()
{
	save();
	gRecursos.descarregarSpriteSheet("player");
	gRecursos.descarregarSpriteSheet("asteroid");
	gRecursos.descarregarSpriteSheet("tiro");
	gRecursos.descarregarSpriteSheet("buttonStart");
	gRecursos.descarregarSpriteSheet("buttonContinue");
	gRecursos.descarregarSpriteSheet("buttonGameOver");
	gRecursos.descarregarSpriteSheet("title");
	gRecursos.descarregarSpriteSheet("background");

	gRecursos.descarregarAudio("music");
	gRecursos.descarregarAudio("effectShoot");
	gRecursos.descarregarAudio("damage");
	gRecursos.descarregarAudio("damageShip");
	gRecursos.descarregarAudio("powerUp");
	gRecursos.descarregarAudio("ButtonEffect");


	//gRecursos.descarregarTudo();
	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();
		
		setColorBackground();
		background.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
		
		switch (statusGame)
		{
		case 0:
#pragma region Case0

			sprTitle.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 150);
			buttonStart.atualizar();
			buttonStart.desenhar();
			buttonContinuar.atualizar();
			buttonContinuar.desenhar();
			
			if (buttonStart.estaClicado())
			{
				buttonEffect.tocar();
				GameStart(0);
			}
			else if (buttonContinuar.estaClicado())
			{
				buttonEffect.tocar();
				GameStart(1);
			}
#pragma endregion

			break;
		case 1:
#pragma region Case1
			player.update();

			for (int i = 0; i < 4; i++)
			{
				asteroid[i].update();
				asteroid[i].draw();
				collisionTest(i);
			}

			if (!isItemActive)
				counterItem += 1;
			else
				item->draw();

			if (counterItem >= maxCounter && !isItemActive)
			{
				startNewItem();
				isItemActive = true;
			}
#pragma endregion

			break;
		case 2:
#pragma region Case2
			buttonGameOver.atualizar();
			buttonGameOver.desenhar();

			if (buttonGameOver.estaClicado())
			{
				statusGame = 0;
			}
#pragma endregion

			break;
		default:
			break;
		}

#pragma region DebugTela

		if (gTeclado.soltou[TECLA_D])
			debug = !debug;

		if (statusGame == 1)
		{
			if (debug)
			{
				string txt = "pos X: " + to_string(player.getPosX()) + "\n" +
					"pos Y: " + to_string(player.getPosY()) + "\n" +
					"pode atirar: " + to_string(player.getIsShoot()) + "\n" +
					"counterMax: " + to_string(maxCounter) + "\n" +
					"counter: " + to_string(counterItem) + "\n" +
					"tempo de powerUp nave: " + to_string(player.getPowerUpTime()) + "\n" + 
					"tempo de powerUp Tiro: " + to_string(player.Tiro::getPowerUpTime());

				gGraficos.desenharTexto(txt, 25, 25, 255, 255, 255, 255, 0, 0);
			}

			string pointsStr = "PONTOS: " + to_string(points);
			gGraficos.desenharTexto(pointsStr, gJanela.getLargura() / 2, 25, 255, 255, 255, 255, 0.5f, 0.5f);
		}

#pragma endregion

	uniTerminarFrame();
	}
}

void Jogo::collisionTest(int p_obj)
{
#pragma region COLISAO_NAVE_X_INIMIGO

	if (uniTestarColisao(asteroid[p_obj].getSprite(), asteroid[p_obj].getPosX(), asteroid[p_obj].getPosY(), 0,
		player.getSprite(), player.getPosX(), player.getPosY(), player.getRot()))
	{
		asteroid[p_obj].asteroidStart();

		if (points > 30)
			points -= 30;
		else
			statusGame = 2;

		damageShip.tocar(false);
	}

#pragma endregion

#pragma region COLISAO_INIMIGO_X_TIRO

	if (uniTestarColisao(asteroid[p_obj].getSprite(), asteroid[p_obj].getPosX(), asteroid[p_obj].getPosY(), 0,
		player.Tiro::getSprite(), player.Tiro::getPosX(), player.Tiro::getPosY(), 0))
	{
		asteroid[p_obj].asteroidStart();
		player.Tiro::setPosition(0, 0);
		player.setIsShoot(false);
		points += 10;
		damage.tocar(false);
	}

#pragma endregion

#pragma region COLISAO_ITEM_X_NAVE

	if (item)
	{
		if (uniTestarColisao(item->getSprite(), item->getPosX(), item->getPosY(), 0,
			player.getSprite(), player.getPosX(), player.getPosY(), 0))
		{
			powerUp.tocar(false);

			if (item->getPowerUp() == 0)
			{
				player.setSpeed(item->getSpeed());
				player.setIsPowerUp(true);
			}
			else if (item->getPowerUp() == 1)
			{
				player.Tiro::setSpeed(item->getSpeed());
				player.Tiro::setIsPowerUp(true);
			}

			resetItem();
		}
	}

#pragma endregion
	
}

#pragma region METODOS_LOCAIS

void Jogo::startNewItem()
{
	int posX = uniRandEntre(10, gJanela.getLargura() - 10);
	int posY = uniRandEntre(10, gJanela.getAltura() - 10);
	int type = uniRandEntre(0, 1);

	item->startNewItem(posX, posY, type);
}

void Jogo::resetItem()
{
	counterItem = 0;
	maxCounter = uniRandEntre(500, 1000);
	isItemActive = false;
}

void Jogo::setColorBackground()
{
	if (gTeclado.soltou[TECLA_0])
		gJanela.setCorDeFundo(0, 0, 0);
	else if (gTeclado.soltou[TECLA_1])
		gJanela.setCorDeFundo(255, 255, 255);
	else if (gTeclado.soltou[TECLA_2])
		gJanela.setCorDeFundo(255, 0, 0);
	else if (gTeclado.soltou[TECLA_3])
		gJanela.setCorDeFundo(0, 255, 0);
	else if (gTeclado.soltou[TECLA_4])
		gJanela.setCorDeFundo(0, 0, 255);
}

void Jogo::GameStart(int p_status)
{
	if (p_status == 0)
		points = 0;
	else
		points = load();
	statusGame = 1;

	player.playerInicializar();

	asteroid[0].asteroidStart();
	asteroid[1].asteroidStart();
	asteroid[2].asteroidStart();
	asteroid[3].asteroidStart();
}

void Jogo::save()
{
	ofstream archive;
	archive.open("dados.bin", ios::binary);

	if (archive.is_open())
	{
		archive.write(reinterpret_cast<char *>(&points), sizeof(int));
	}
	archive.close();
}

int Jogo::load()
{
	ifstream archive;
	archive.open("dados.bin", ios::binary);

	int __points;

	if (!archive.is_open())
	{
		return 0;
	}
	else
	{
		archive.read(reinterpret_cast<char *>(&__points), sizeof(int));
		return __points;
	}
}

#pragma endregion
