// HelloSFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Collision.hpp"
#include<sstream>
using namespace sf;
using namespace std;
int k = 1;
VideoMode vm(1280, 720);
RenderWindow window(vm, "test", Style::Fullscreen);
class Fireball;
class Player {
public:
	Texture player,lh,ll,rl;
	Sprite splayer,slh,sll,srl;
	float cposx,lhx,llx,rlx,cposy,lly,rly;
	// maxpos=1200;
	Clock clock;
	Time dt;
	bool left_press;
	bool right_press,jump_press=false,jump_press2=true;
	friend class Fireball;
	Player() {
		player.loadFromFile("graphics/player.png");
		lh.loadFromFile("graphics/lefthand.png");
		ll.loadFromFile("graphics/leftleg.png");
		rl.loadFromFile("graphics/rightleg.png");
		splayer.setTexture(player);

		sll.setTexture(ll);
		srl.setTexture(rl);
		
		splayer.setPosition(480, 300);
		sll.setOrigin(0, 0);
		sll.setPosition(590, 450);
		srl.setOrigin(0, 0);
		srl.setPosition(520, 450);
		//cout << sll.getGlobalBounds().left << endl << sll.getGlobalBounds().top << endl;
		
		splayer.setRotation(0);
		cposx = 480.0;
		llx = 590.0;
		lhx = 557.0;
		rlx = 520.0;
		cposy = 300.0;
		lly = 450.0;
		rly = 450.0;

		 left_press = false;
		 right_press = false;
		 jump_press = false;
		
	}
	void dtcalc() {
		dt = clock.restart();
	}
	void mov_left() {

		cposx = cposx - ((250 * (dt.asSeconds())));
		lhx = lhx - ((250 * (dt.asSeconds())));
		llx = llx - ((250 * (dt.asSeconds())));
		rlx = rlx - ((250 * (dt.asSeconds())));

		splayer.setPosition(int(cposx), int(cposy));
		slh.setPosition(int(lhx), 470);
		sll.setPosition(int(llx), int(lly));
		srl.setPosition(int(rlx), int(rly));
		
		if (srl.getRotation() <5) {
	
			srl.rotate(int(1000 * (dt.asSeconds())));
		}
		else {
			
			srl.rotate(int(-63*(dt.asSeconds())));
		}
		if (sll.getRotation() >5) {
			sll.rotate(int(-63 * (dt.asSeconds())));
		}
		else {
			
			sll.rotate(int(1000 * (dt.asSeconds())));
		}

	
	}
	void mov_right() {
		cposx = cposx +((250 * (dt.asSeconds())));
		lhx = lhx + ((250 * (dt.asSeconds())));
		llx = llx + ((250 * (dt.asSeconds())));
		rlx = rlx + ((250 * (dt.asSeconds())));
		splayer.setPosition(int(cposx), int(cposy));

		srl.setPosition(int(rlx), int(rly));
		sll.setPosition(int(llx), int(lly));
		if (srl.getRotation() <5) {
			srl.rotate(int(1000 * (dt.asSeconds())));
		}
		else {
			
			srl.rotate(int(-63 * (dt.asSeconds())));
			//slh.rotate(200 * (dt.asSeconds()));
		}
		if (sll.getRotation() >5) {
			sll.rotate(int(-63 * (dt.asSeconds())));
		}
		else {
			
			sll.rotate(int(1000 * (dt.asSeconds())));
			//slh.rotate(200 * (dt.asSeconds()));

		}



	}
	void jump() {
		if (cposy >70 ) {
			cposy = cposy - (1000 * dt.asSeconds());
			lly = lly - (1000 * dt.asSeconds());
			rly = rly - (1000 * dt.asSeconds());
			splayer.setPosition(int(cposx), int(cposy));
			sll.setPosition(int(llx),int(lly));
			srl.setPosition(int(rlx), int(rly));
			k = 1;
		}
		
	}
	void onMaxRange() {
	
	}


};
class Fireball {
public:
	Texture fireball;
	Sprite sfb[5];
	Player p;
	float fbx[5] = { 0.0,0.0,1100.0,1100.0,0.0 };
	Fireball() {
		fireball.loadFromFile("graphics/fireball.png");
		for (int i = 0; i < 5; i++) {
			sfb[i].setTexture(fireball);
			sfb[i].setPosition(-1-i, 400);
		}
	}
	int mov_right() {
		p.dtcalc();
		for (int i = 0; i < 2; i++) {
			if (sfb[i].getPosition().x==0||fbx[i]!=0.0){
				if (i == 1) {
					fbx[i] = (2*i + 1) + fbx[i] + ((30) * (p.dt.asSeconds()));
				}
				else {
					fbx[i] =  fbx[i] + ((500) * (p.dt.asSeconds()));
				}
				//cout <<"the i is " << i<<"and its speed is  "<<int(fbx) << endl;
				sfb[i].setPosition(int(fbx[i]),400);
				window.draw(sfb[i]);	
			}
			if (fbx[i] >= 1200 && fbx[i+1]>=1200) {
				fbx[i] = 0.0;
				fbx[i+1] = 0.0;
			
			}	
		}
		if (fbx[0] == 0.0) {
			return 1;
		}
		else {
			return 0;
		}

	}
	void onRight() {
		if (fbx[  0] == 0.0||fbx[1]==0.0) {
			srand(time(0));
			int i = rand() % 15 + 1;

			

			if (i <= 5 && i >= 0) {
				sfb[0].setPosition(0, 400);
				window.draw(sfb[0]);
			}
			else if (i > 5 && i <= 7) {
				sfb[1].setPosition(0, 400);
				window.draw(sfb[1]);
			}
			else {
				sfb[1].setPosition(0, 400);
				window.draw(sfb[1]);
				sfb[0].setPosition(0, 400);
				window.draw(sfb[0]);

			}

		}
		}
	int mov_left() {
		p.dtcalc();
		for (int i = 3; i < 5; i++) {
			if (sfb[i].getPosition().x == 1100|| fbx[i] != 1100.0) {
				
				if (i == 3) {
					fbx[i] = fbx[i] - ((30) * (p.dt.asSeconds())) - (2* i + 1);	
				}
				else {
					
					fbx[i] = fbx[i] -((200) * (p.dt.asSeconds()));
					
				}
				sfb[i].setPosition(int(fbx[i]), 400);
				window.draw(sfb[i]);

			}
			
			if (fbx[i] <=5&&fbx[i+1]<=5) {
				
				fbx[i] = 1100.0;
				fbx[i+1] = 1100.0;
				
			}
			
			
		}
		if (fbx[4] == 1100.0) {
			return 0;

		}
		else {
			return 1;
		}

	}
	void onLeft() {
		if (fbx[3] == 1100.0 || fbx[4] == 1100.0) {
			srand(time(0));
			int i = rand() % 15 + 1;
			if (i <= 5 && i >= 0) {
				sfb[3].setPosition(1100, 400);
				window.draw(sfb[3]);
			}
			else if (i > 5 && i <= 7) {
				sfb[4].setPosition(1100, 400);
				window.draw(sfb[4]);
			}
			else {
				sfb[4].setPosition(1100, 400);
				window.draw(sfb[4]);
				sfb[3].setPosition(1100, 400);
				window.draw(sfb[3]);

			}

		}
	}

};

int main()
{
	int side = 0;
	Texture bg;
	bg.loadFromFile("graphics/bg.jpg");
	Sprite sbg;
	sbg.setTexture(bg);
	sbg.setPosition(0,0);
	
	Player player;
	Fireball fb;
	window.setFramerateLimit(60);
	bool pause=false;
	float score = 1.0;
	Text stext,lose,start;
	Font font;
	stext.setCharacterSize(75);
	lose.setCharacterSize(75);
	start.setCharacterSize(75);
	stext.setFillColor(Color::Red);
	lose.setFillColor(Color::Yellow);
	start.setFillColor(Color::Red);
	font.loadFromFile("fonts/FFF_Tusj.ttf");
	stext.setFont(font);
	lose.setFont(font);
	start.setFont(font);
	stext.setString("Score=0");
	start.setString("PRESS ENTER ");
	lose.setString("GAME OVER!!!! :****(   ");
	stext.setPosition(0,0);
	start.setPosition(280, 100);
	lose.setPosition(280,100);
	bool start_pause = false;
	bool start_pause2 = true;
	while (window.isOpen()) {
		/*if (Keyboard::isKeyPressed(Keyboard::Return)) {
			pause = true;
			
		}*/
		 if(pause==false){
			pause = false;
		}
		if(start_pause==true &&start_pause2==true){
			window.clear();
			window.draw(start);
			window.display();
			score = 0.0;
			player.dtcalc();
			
				if (Keyboard::isKeyPressed(Keyboard::Return)) {
				start_pause2 = false;
				score = 0.0;
				player.dtcalc();
			}
		}
		else {
			if (pause == true) {


			}
			else {

				player.dtcalc();
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					player.right_press = true;
				}
				else {
					player.right_press = false;
				}
				if (player.right_press) {

					if ((player.splayer.getPosition().x >= 1100)) {

						player.onMaxRange();
					}
					else {
						if (Keyboard::isKeyPressed(Keyboard::Space)) {
							player.mov_right();
						}
						else {
							player.mov_right();

						}
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					player.left_press = true;
				}
				else {
					player.left_press = false;
					//player.sll.setRotation(0);
				}
				if (player.left_press) {

					if ((player.splayer.getPosition().x <= 0)) {

						player.onMaxRange();
					}
					else {
						if (Keyboard::isKeyPressed(Keyboard::Space)) {
							player.mov_left();
						}
						else {
							player.mov_left();
						}
					}
				}

				if (Keyboard::isKeyPressed(Keyboard::Space)) {

					player.jump_press = true;
					if (Keyboard::isKeyPressed(Keyboard::Right)) {
						player.right_press = true;
					}
					if (Keyboard::isKeyPressed(Keyboard::Left)) {
						player.left_press = true;
					}
					k++;
				}
				else {
					player.jump_press = false;
					if (k <= 3) {
						k = 1;
					}
					else {

					}
				}
				if (k != 2) {
					player.jump_press = false;

				}
				if (player.jump_press) {
					player.jump();

				}
				else {
					if (player.cposy < 300) {
						//cout << player.splayer.getPosition().y << endl;
						player.cposy = player.cposy + (200 * player.dt.asSeconds());
						player.lly = player.lly + (200 * player.dt.asSeconds());
						player.rly = player.rly + (200 * player.dt.asSeconds());
						player.splayer.setPosition(int(player.cposx), int(player.cposy));
						player.sll.setPosition(int(player.llx), int(player.lly));
						player.srl.setPosition(int(player.rlx), int(player.rly));
					}
					if (player.cposy >= 300) {
						k = 1;
					}

				}
				if (player.right_press == false && player.left_press == false) {
					player.sll.setRotation(0);
					player.srl.setRotation(0);
				}
				stringstream ss;
				cout<< int(score)<<endl;
				score = score + (player.dt.asSeconds());
				
				ss << "Score= " << int(score);
				stext.setString(ss.str());
				//player.sll.rotate(1.2);
				window.clear();

				window.draw(sbg);
				window.draw(player.splayer);
				window.draw(player.srl);
				window.draw(player.sll);
				window.draw(stext);
				if (side == 1) {
					fb.onLeft();
					side = fb.mov_left();
					for (int i = 3; i <= 4; i++) {
						if (Collision::PixelPerfectTest(player.splayer, fb.sfb[i])) {
							window.draw(lose);
							pause = true;
						}

					}
				}
				else {
					fb.onRight();
					side = fb.mov_right();
					for (int i = 0; i <= 1; i++) {
						if (Collision::PixelPerfectTest(player.splayer, fb.sfb[i])) {
							window.draw(lose);
							pause = true;

						}

					}
				}

				window.display();
			}
		
		}
		start_pause = true;
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		
			window.close();
		}

		

	}
    return 0;
}

