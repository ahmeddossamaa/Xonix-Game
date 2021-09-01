#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<iostream>
#include<time.h>

using namespace sf;
using namespace std;

const int width = 53;
const int height = 30;
const int res = 36;
const int maxmenu = 3;

int graph[width][height] = { 0 };
int live = 3;
int nenemy = 3;
int counter = 0;

bool game = true;
bool gamee = false;
bool windowBool = true;
bool checkwin = true;

Clock checktime;

Music music, mPlay, mGameOverMusic, mComplete, mDeath, mWin;

RenderWindow window(VideoMode(1920, 1080), "Xonix", Style::Fullscreen);

struct sPlayer
{
	int x = 0.5 * width;
	int y = height - 1;
	int dx = 0;
	int dy = 0;

	void motion() {
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			dx = 0;
			dy = -1;
		}if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			dx = 0;
			dy = 1;
		}if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			dx = 1;
			dy = 0;
		}if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			dx = -1;
			dy = 0;
		}
	}

	void lives() {
		if (!mDeath.openFromFile("data/death.ogg"))
		{
			cout << "Error" << endl;
		}
		live--;
		x = 0.5 * width;
		y = height - 1;
		if (live != 0)
		{
			mDeath.play();
		}
		if (live == 0)
		{
			game = false;
		}
	}

	Texture tPlayer;
};
sPlayer p;

struct sEnemy
{
	int x = 0.5 * width * res;
	int y = 0.5 * height * res;
	int dx = rand() % 6 - rand() % 12;
	int dy = rand() % 6 - rand() % 12;

	void move()
	{
		if (dx == 0)
		{
			dx++;
		}if (dy == 0)
		{
			dy++;
		}
		x += dx;
		if (graph[x / res][y / res] == 1)
		{
			dx = -dx;
			x += dx;
		}
		y += dy;
		if (graph[x / res][y / res] == 1)
		{
			dy = -dy;
			y += dy;
		}
		if (graph[x / res][y / res] == 2)
		{
			p.lives();
		}

	}


	void drop(int x, int y)
	{
		if (graph[x][y] == 0)
		{
			graph[x][y] = -1;
		}
		if (graph[x - 1][y] == 0)
		{
			drop(x - 1, y);
		}
		if (graph[x + 1][y] == 0)
		{
			drop(x + 1, y);
		}
		if (graph[x][y - 1] == 0)
		{
			drop(x, y - 1);
		}
		if (graph[x][y + 1] == 0)
		{
			drop(x, y + 1);
		}
	}
};
sEnemy e;


void levelDraw() {
	for (int i = 1; i < width; i++)
	{
		for (int j = 1; j < height; j++)
		{
			if (i == 1 || j == 1 || j == 5 || i == width - 1 || j == height - 1)
			{
				graph[i][j] = 1;
			}
			else
			{
				graph[i][j] = 0;
			}
		}
	}
}

class Menu
{
public:
	Menu(float h, float w) {
		if (!menuFont.loadFromFile("data/Aldo.ttf")) {}
		if (!stateFont.loadFromFile("data/Freedom.ttf")) {}
		//play
		menue[0].setFont(menuFont);
		menue[0].setFillColor(Color::Red);
		menue[0].setString("Play");
		menue[0].setCharacterSize(110);
		menue[0].setPosition(400, 165);
		menue[0].setScale(1.2, 1.2);

		//about
		menue[1].setFont(menuFont);
		menue[1].setFillColor(Color::Black);
		menue[1].setString("Team");
		menue[1].setCharacterSize(110);
		menue[1].setPosition(400, 470);
		//exit
		menue[2].setFont(menuFont);
		menue[2].setFillColor(Color::Black);
		menue[2].setString("Exit");
		menue[2].setCharacterSize(110);
		menue[2].setPosition(400, 790);

		select = 0;

		

		gameStates[0].setFont(stateFont);
		gameStates[0].setFillColor(Color::White);
		gameStates[0].setString("Three lives left");
		gameStates[0].setCharacterSize(50);
		gameStates[0].setPosition(90, 70);

		gameStates[1].setFont(stateFont);
		gameStates[1].setFillColor(Color::White);
		gameStates[1].setString("Percent is");
		gameStates[1].setCharacterSize(50);
		gameStates[1].setPosition(820, 70);

		gameStates[2].setFont(stateFont);
		gameStates[2].setFillColor(Color::White);
		gameStates[2].setString("Time");
		gameStates[2].setCharacterSize(50);
		gameStates[2].setPosition(1450, 70);

	};
	void ddraw(RenderWindow& window) {

		for (int i = 0; i < 3; i++) {

			window.draw(menue[i]);
		}

	};
	void sdraw(RenderWindow& window) {

		for (int i = 0; i < 3; i++) {

			window.draw(gameStates[i]);
		}
		switch (live)
		{
		case 0:
			gameStates[0].setString("Zero lives left");
			break;
		case 1:
			gameStates[0].setString("One live left");
			break;
		case 2:
			gameStates[0].setString("Two lives left");
			break;
		case 3:
			gameStates[0].setString("Three lives left");
			break;
		}
	};
	void uup() {

		if (select - 1 >= -1)
		{
			menue[select].setFillColor(Color::Black);
			select--;
			if (select == -1)
			{
				select = 2;
			}
			menue[select].setFillColor(Color::Red);
			switch (select)
			{
			case 0:
				menue[0].setScale(1.2, 1.2);
				menue[1].setScale(1, 1);
				menue[2].setScale(1, 1);
				break;
			case 1:
				menue[0].setScale(1, 1);
				menue[1].setScale(1.2, 1.2);
				menue[2].setScale(1, 1);
				break;
			case 2:
				menue[0].setScale(1, 1);
				menue[1].setScale(1, 1);
				menue[2].setScale(1.2, 1.2);
				break;
			}
		}
	};
	void down() {
		if (select + 1 <= maxmenu)
		{
			menue[select].setFillColor(Color::Black);
			select++;
			if (select == 3)
			{
				select = 0;
			}
			menue[select].setFillColor(Color::Red);


			switch (select)
			{
			case 0:
				menue[0].setScale(1.2, 1.2);
				menue[1].setScale(1, 1);
				menue[2].setScale(1, 1);
				break;
			case 1:
				menue[1].setScale(1.2, 1.2);
				menue[0].setScale(1, 1);
				menue[2].setScale(1, 1);
				break;
			case 2:
				menue[2].setScale(1.2, 1.2);
				menue[1].setScale(1, 1);
				menue[0].setScale(1, 1);
				break;
			}


		}
	};
	void play();
	void about();
	int menupresed()
	{
		return select;
	}
private:
	int select = 0;
	Font menuFont, stateFont;
	Text menue[maxmenu];
	Text gameStates[3];
};

Menu me(width* res, height* res);

int main()
{
	int index = 0;
	while (windowBool)
	{
		window.setFramerateLimit(30);

		Texture tMenuBg;
		tMenuBg.loadFromFile("data/backgroundNew.png");
		Sprite menuBg(tMenuBg);


		if (!music.openFromFile("data/Windowtrack.ogg"))
		{
			cout << "Error" << endl;
		}
		if (!mPlay.openFromFile("data/soundTrack.ogg"))
		{
			cout << "Error" << endl;
		}

		music.play();
		music.setLoop(1);

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == event.Closed) {
					window.close();
					windowBool = false;
				}
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					me.uup();
					break;
				}
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					me.down();
					break;
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					if (me.menupresed() == 0)
					{
						index = 0;
						music.stop();
						mPlay.play();
						live = 3;
						game = true;
						checkwin = true;
						me.play();
					}
					if (me.menupresed() == 1)
					{
						index = 1;
						me.about();
					}
					if (me.menupresed() == 2)
					{
						index = 2;
						window.close();
						windowBool = false;
						break;
					}
				}
			}
			window.clear();
			window.draw(menuBg);
			me.ddraw(window);
			window.display();
		}
		if (index == 0) {
			me.play();
		}
		else if (index == 1) {
			me.about();
		}
		else if (index == 2) {
			break;
		}
	}
	return 0;
}
void Menu::play() {
	Menu me(width * res, height * res);

	while (windowBool)
	{

		//play
		window.setFramerateLimit(75);

		if (!mGameOverMusic.openFromFile("data/gameover.ogg"))
		{
			cout << "Error" << endl;
		}
		if (!mComplete.openFromFile("data/CompleteDraw.ogg"))
		{
			cout << "Error" << endl;
		}
		if (!mWin.openFromFile("data/winn.ogg"))
		{
			cout << "Error" << endl;
		}

		//Player's Texture

		p.tPlayer.loadFromFile("data/player.png");
		Sprite player(p.tPlayer);
		player.setOrigin(40, 40);

		//Tiles' Texture

		Texture tTiles;
		tTiles.loadFromFile("data/tiles.png");
		Sprite tiles(tTiles);
		tiles.setOrigin(18, 18);

		//Gameover's Texture

		Texture tGame;
		tGame.loadFromFile("data/gameover.png");
		Sprite gameOver(tGame);
		gameOver.setScale(4, 4);
		gameOver.setOrigin(0.5 * 500, 0.5 * 250);
		gameOver.setPosition(0.5 * width * res, 0.5 * height * res);

		// win texture
		Texture twin;
		twin.loadFromFile("data/win.png");
		Sprite win(twin);
		win.setScale(4, 4);
		win.setOrigin(0.5 * 500, 0.5 * 250);
		win.setPosition(0.5 * width * res, 0.5 * height * res);
		//Background's Texture

		Texture tBackground;
		tBackground.loadFromFile("data/playbackgroundNew.png");
		Sprite bg(tBackground);

		//Enemy's Texture

		Texture tEnemy;
		tEnemy.loadFromFile("data/enemy.png");
		Sprite Enemy(tEnemy);
		Enemy.setOrigin(30, 30);
		sEnemy a[10];

		Clock clock;



		//Drawing
		levelDraw();

		while (window.isOpen())
		{


			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window.close();
					windowBool = false;
				}if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					main();
					game = false;
				}
			}

			p.motion();

			if (clock.getElapsedTime().asSeconds() > 0.07)
			{

				p.x += p.dx;
				p.y += p.dy;

				if (p.x < 1)
				{
					p.x = 1;
				}if (p.y < 5)
				{
					p.y = 5;
				}if (p.x > width - 1)
				{
					p.x = width - 1;
				}if (p.y > height - 1)
				{
					p.y = height - 1;
				}if (!game)
				{
					continue;
				}if (!checkwin)
				{
					continue;
				}if (graph[p.x][p.y] == 2)
				{
					p.lives();
					mDeath.play();
				}for (int i = 0; i < nenemy; i++)
				{
					if (p.x == a[i].x && p.y == a[i].y)
					{
						p.lives();
						a[i].dx = -a[i].dx;
						a[i].dy = -a[i].dy;
						mDeath.play();
					}
				}
				if (graph[p.x][p.y] == 0)
				{
					graph[p.x][p.y] = 2;
				}

				clock.restart();
			}

			for (int i = 0; i < nenemy; i++)
			{
				a[i].move();
			}

			if (graph[p.x][p.y] == 1)
			{

				p.dx = p.dy = 0;

				for (int i = 0; i < nenemy; i++)
				{
					e.drop(a[i].x / res, a[i].y / res);
				}
				for (int i = 1; i < width - 1; i++)
				{
					for (int j = 5; j < height - 1; j++)
					{
						if (graph[i][j] == -1)
						{
							graph[i][j] = 0;
						}
						else
						{
							graph[i][j] = 1;
						}
					}
				}
			}


			counter = 0;
			for (int i = 2; i < 51; i++)
			{
				for (int j = 5; j < 28; j++)
				{
					float winnum = 950;
					if (graph[i][j] == 1)
					{
						counter++;
					}
					if (counter > winnum)
					{
						checkwin = false;
					}
				}
			}
			if (checktime.getElapsedTime().asSeconds() >= 60)
			{
				game = false;
				checktime.restart();
			}
			window.clear();


			window.draw(bg);

			me.sdraw(window);

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					if (graph[i][j] == 0) {
						continue;
					}if (graph[i][j] == 1) {
						tiles.setTextureRect(IntRect(0, 0, res, res)); // Textures
					}if (graph[i][j] == 2) {
						tiles.setTextureRect(IntRect(72, 0, res, res)); // Textures
					}

					tiles.setPosition(i * res, j * res); //Texture Position
					window.draw(tiles); //Texture draw
				}
			}

			Enemy.rotate(10);
			for (int i = 0; i < nenemy; i++)
			{
				Enemy.setPosition(a[i].x, a[i].y);
				window.draw(Enemy);
			}

			player.rotate(5);
			player.setPosition(p.x * res, p.y * res);
			window.draw(player);

			if (!game)
			{
				window.draw(gameOver);
				mPlay.stop();
				mGameOverMusic.play();
				checktime.restart();
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					main();
					checktime.restart();
				}
			}
			if (!checkwin)
			{
				window.draw(win);
				mPlay.stop();
				mWin.play();
				checktime.restart();
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					main();
					checktime.restart();
				}
			}
			window.display();

		}
	}
};
void Menu::about() {
	Texture tAbout;
	tAbout.loadFromFile("data/aboutbackgroundNew.png");
	Sprite aboutUS(tAbout);

	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed) {
				window.close();
				windowBool = false;
			}if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				main();
				music.stop();
			}
		}
		window.clear();

		window.draw(aboutUS);

		window.display();
	}
}