#include <ncurses/curses.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <pthread.h>
#include <math.h>

#define STATFILE_EINS	"seins.bin"		//Player 1 stats
#define STATFILE_ZWEI	"szwei.bin"		//Player 2 stats
#define STATFILE_DREI	"sdrei.bin"		//Player 3 stats
#define STATFILE_VEIR	"sveir.bin"		//Player 4 stats
#define MISCFILE		"ms.bin"		//Miscellaneous stats, flags and map values
#define MAPFILE_EINS	"mdeins.bin"	//Files for storing map data, used with scr_dump() and scr_restore()
#define MAPFILE_ZWEI	"mdzwei.bin"
#define MAPFILE_DREI	"mddrei.bin"
#define MAPFILE_VEIR	"mdveir.bin"
#define MAPFILE_FUNF	"mdfunf.bin"
#define MONSTER_ARRAY_SIZE 16			//Size determinant for monster-related arrays
#define POTION_ARRAY_SIZE 5		//Size determinant different types of potions
#define WINDOW_MAX_X 120
#define WINDOW_MAX_Y 29
#define COLORMIN 1
#define COLORMAX 16
#define MAP_SIZE (24 * 79 + 1)
#define BORDER_SIZE (26 * 81 + 1)
#define TEXT_BOX_LENGTH 81
#define NAME_BOX_SIZE (3 * 21 + 1)
#define ITEMID_MAX (108 + 1)		//Highest ID value + 1
#define CLASS_AMOUNT (4 * 5 + 1)	//Amount of classes plus an "ERROR" class
#define MAX_LEVEL 100
#define SHOP_BOX_SIZE (46 * 14 + 1)

#include "variables.c"		//All global variables, function prototypes, and structs
#include "draw.c"			//Drawing anything
#include "delays.c"			//Time delays
#include "descriptions.c"	//Describes armours and classes/subclasses
#include "display.c"		//Drawing the health bars of enemies and allies
#include "dojo.c"			//Dojo
#include "smithery.c"		//smithery() and armourName() functions
#include "inn.c"			//inn() function
#include "damage.c"			//damage() function
#include "potion.c"			//potion() function
#include "adventure.c"		//adventure() function
#include "shop.c"			//shop() function
#include "stats.c"			//stats() function
#include "story.c"			//Draws story text when certain flags are set
#include "maps.c"			//Maps

int main(){
	pthread_t krw;
	pthread_create(krw, NULL, keepResizingWindow, NULL);
	initWindow();
	setColour(2);
	for(int i = 0; i < MAX_LEVEL + 1; i++){
/*	Old method - Beta 1.0
		required_exp[i] = (int) ((5.0 / 4.0) * (i * i) + (10.0 - (0.02 * i)));
	New method - Beta 2.0
	-upper limit of i should be 341 since 1.01^342 > 30
*/
		required_exp[i] = (int) ((7.0/9.0) * (i * i) + (30 - pow(1.01, i))) + 0.5;
	}
	required_exp[MAX_LEVEL] = 0;
	srand(time(0));
	getFileData();
	double textDelay = getTextDelay();
	drawMap();
	if(player.gameOver == 1){
		setColour(WHITE_BLACK);
		drawText(3, 35, textDelay, "Well then, looks like you all died.");
		drawText(4, 35, textDelay, "Your progess will be read from your last save.");
		drawText(6, 35, textDelay, "Press any key to continue...");
		wgetch(window);
		player.gameOver = 0;
		refresh();
		delay(6);
	}
	if(enemy.currentHealth <= 0){
		enemy.currentMon = -1;
		player.adventure = -1;
		updateFileData();
	}
	drawMap();
	drawText(10, 40, 0, "Konin's Tale");
	refresh();
	delay(1);
	drawText(12, 30, 0, "Version: Beta 2.0");
	refresh();
	delay(1);
	drawText(15, 50, 0.05, "Press any key to start...");
	refresh();
	char c = wgetch(window);
	if(player.adventure == -1){
		home();
	}else if(player.adventure != -1){
		adventure();
		home();
	}
	delwin(window);
	endwin();
	return EXIT_SUCCESS;
}

double getTextDelay(){
	return flags.speed > 0 && flags.speed < 4 ? 0.05 * flags.speed : 0.05;
}

void* keepResizingWindow(){
	while(true){
		wresize(window, WINY, WINX);
		delay(0.8);
	}
}

void getFileData(){
	FILE* fd;
}

void new_game(){
	FILE* fd;
	int ret = remove(DATAFILE);
	mvprintw(10, 20, "What's your name? ");
	refresh();
	wgetnstr(window, player.name, 16);
	//Player stats
	player.level = 0;	player.exp = 0;		player.stats_points = 0;
	player.class = 0;	player.subclass = 0;
	player.armourH = 0;	player.armourC = 0;		player.armourL = 0;
	player.weapon = 0;	player.damageType = 0;
	player.adventure = -1;
	player.potion1_count = 1;	player.potion2_count = 0;	player.potion3_count = 0;	player.potion4_count = 0;
	player.ether1_count = 0;	player.ether2_count = 0;	player.ether3_count = 0;	player.ether4_count = 0;
	player.maxHealth = 40;		player.currentHealth = player.maxHealth;
	player.currentCoin = 500;
	player.tmight = 5;		player.twit = 5;		player.tpace = 5;	player.tfocus = 80;	player.tvigor = 0;	player.tkarma = 0;	player.tdef = 0;
	player.cmight = 1.0;		player.cwit = 1.0;		player.cpace = 1.0;	player.cfocus = 1.0;	player.cvigor = 1.0;	player.ckarma = 1.0;	player.cdef = 1.0;
	player.might = 5.0;		player.wit = 5.0;		player.pace = 5.0;	player.focus = 80.0;	player.vigor = 0.0;	player.karma = 0.0;	player.def = 0.0;
	player.gameOver = 0;	player.poisoned = 0;	player.burned = 0;
	player.hUpCheck = -1;	player.cUpCheck = -1;	player.lUpCheck = -1;	player.wUpCheck = -1;
	player.tier8H = 0;		player.tier8C = 0;		player.tier8L = 0;		player.tier8W = 0;
	player.turn = 2;	player.potionCheck = 0;		player.luckCheck = 0;	player.secretCheck = 0;		player.etherCheck = 0;
	enemy.currentMon = -1;
	enemy.currentHealth = 0;
	//File writing
	
}

void updateFileData(){
	FILE* fd;
}

void home(){
	int choice, decision;
	char c[16];
	while(true){
		fflush(stdin);
		player.adventure = -1;
		enemy.currentMon = -1;
		updateStats();
		updateFileData();
		if(player.gameOver == 1)
			return;
		mvprintw(3, 39, "===HOME===");
		mvprintw(5, 25, "\"Where should we go...\"");
		refresh();
		delay(2);
		(flags.inmap) ? mvprintw(7,25, "(1) Go back to the overworld.") : mvprintw(7, 25, "(1) Leave the town.");
		mvprintw(8, 25, "(2) Waste time at the shop.");
		mvprintw(10, 25, "(3) View our stats.");
		mvprintw(11, 25, "(4) Visit the Smithery.");
		mvprintw(12, 25, "(5) Rest at the Inn.");
		mvprintw(13, 25, "(6) Save and quit.");
		mvprintw(15, 27, "-> ");
		refresh();
		wgetnstr(window, c, 1);
		choice = atoi(c);
		if(choice == 1 && flags.inmap){
			adventure();
		}else if(choice == 1 && !flags.inmap){
			town();
		}else if(choice == 2)
			shop();
		else if(choice == 3){
			stats();
		}else if(choice == 4){
			smithery();
		}else if(choice == 5){
			inn();
		}else if(choice == 6){
			update_player_data();
			mvprintw(15, 40, "Goodbye!");
			delay(4);
			return;
		}
	}
}

void monStats(int mst){
	printf("\n\nMONSTER STATS:\nNAME: %s\nATK: %d\tDEF: %d\nTYPE: %s\n\n", monsterName[mst], monsterAtk[mst], monsterDef[mst], getMonType(monsterType[mst]));
	delay(5);
}

void drops(int mst){
	int coinDrop, potionDrop;
	coinDrop = rand() % 60;
	potionDrop = rand() % 100;
	if(coinDrop == 0)
		extraCoin = monsterCoin[mst];
	else
		extraCoin = 0;
	if(potionDrop == 0){
		extraPotion = monsterPotionDrop[mst];
	}else
		extraPotion = 0;
}

void level_up(){
	updateStats();
	float vigorIncrease = player.vigor / 25.0;
	int choice = -1, decision = -1;
	int vigorInc = (int) (vigorIncrease + 0.5);
	if(player.secretCheck == 0 && player.level == 150){
		secret2();
	}
	if(player.level + 1 > 150)
		return;
	player.exp = player.exp - required_exp[player.level];
	player.level++;
	printf("%s has levelled up to Lvl %d!  3 points gained.  Max HP increased by %d.\n", player.name, player.level, vigorInc + 3);
	if(player.level % 3 == 0){
		player.tmight++;
		player.twit++;
		player.tpace++;
		player.tdef++;
		player.tfocus++;
		player.tvigor++;
		player.tkarma++;
		printf("MIT increased by 1.  WIT increased by 1.  PACE increased by 1.\nDEF increased by 1.  FCS increased by 1.  VGR increased by 1.  KMA increased by 1.\n");
	}
	//Code for levelling up was here
	updateStats();
	update_player_data();
}

void updateStats(){
	player.might = ((float) player.tmight) * player.cmight;
	player.wit = ((float) player.twit) * player.cwit;
	player.pace = ((float) player.tpace) * player.cpace;
	player.def = ((float) player.tdef) * player.cdef;
	player.focus = ((float) player.tfocus) * player.cfocus;
	player.vigor = ((float) player.tvigor) * player.cvigor;
	player.karma = ((float) player.tkarma) * player.ckarma;
	if(player.focus > 100.0)
		player.focus = 100.0;
	if(player.karma > 450.0)
		player.karma = 450.0;
}

void secret1(){
	printf("\nHello?  Is anyone here?\n\nAh, it's you.  \"%s\".  I've been looking forward to seeing you.\n", player.name);
	delay(3.0);
	printf("So, you managed to defeat Dien with your bare hands?\nNothing to cover yer head, with rags and a loincloth to cover yer body?\n");
	delay(4.0);
	printf("I'm impressed!  I'm so impressed, that I'll give you 19,999,998 coin as a reward.\n");
	player.currentCoin += 19999998;
	delay(4.0);
	printf("The man in the shop...  I think that he has some artifacts of me.\nGather all 4 artifacts, and when you're ready...\n\n");
	printf("I'll be waiting for you, \"%s\".\n\n\n", player.name);
	delay(6.0);
}

void secret2(){
	printf("\nIs this thing on?  Ah, hello there, \"%s\".\n", player.name);
	delay(3.0);
	printf("You got to the maximum level!  Congradulations on your achievement!\n");
	delay(3.0);
	printf("That must've taken a lot of grinding to get here, yes?  Or did you cheat?\n");
	printf("I'll know if you cheated.\n");
	delay(6.0);
	printf("Anyway, here's 9,999,999 coin as a reward.");
	player.currentCoin += 9999999;
	delay(3.0);
	printf("I think that the guy in the shop has artifacts of me.  Gather them and face me when you are ready!\n\n\n");
	player.secretCheck = 1;
	delay(5.0);
}

int damagevary(){
	int first, second;
	first = rand() % 26;
	second = rand() % 2;
	if(second == 0)
		first *= -1;
	return first;
}

void tauSecret(){
	int choice, potionCheck, damage;
	FILE* fd;
	printf("\n...\n\n");
	delay(7.0);
	printf("So...  you've finally arrived.\n");
	delay(4.0);
	printf("\"%s\", your adventure has come to an end.\n", player.name);
	delay(4.0);
	printf("You unified my artifacts, and here you stand, looking like an imposter.\n");
	delay(5.0);
	printf("What?  Did you think that you could waltz through your\nworld after getting my artifacts?\n");
	delay(6.0);
	printf("Hehehe...\n\nI've watched you, you know.  You stumble\nwhere you go, a glazed look in your eyes\n");
	printf("as if you were controlled like a puppet.  Yes, yes...\n");
	delay(8.0);
	printf("You must be shocked, right?  To see me refer to\nyou, not your puppet?\n");
	delay(4.0);
	printf("Hehehe...\n\nSo, \"%s\",are you ready to meet your maker?\n\n\n", player.name);
	delay(6.0);
	player.maxHealth = 9999;	player.currentHealth = player.maxHealth;
	int potion5_count = 1750;
	player.level = -1;	player.exp = 0;
	int turn = 1;
	while(true){
		fflush(stdin);
		damage = damagevary();
		printf("---TURN %d---", turn);
		displayHP("Tau", tauHP, 9999999);
		displayHP(player.name, player.currentHealth, player.maxHealth);
		printf("(1) Attack\n(2) Use Potion\n(3) Cry\n(4) View My Stats\n(5) View Your Stats\n-> ");
		scanf("%d", &choice);
		if(choice < 1 || choice > 5)
			printf("Don't play stupid.\n\n");
		else if(choice == 1){
			potionCheck = 0;
			if(rand() % 2 == 0){
				printf("You try to attack me.  %d dmg dealt.\n\n", 1000 + damage);
				tauHP -= 1000 + damage;
			}else{
				printf("You attack me with all your might.  Critical hit.  %d dmg dealt.\n\n", (1000 + damage) * 2);
				tauHP -= (1000 + damage) * 2;
			}
		}else if(choice == 2){
			potion5_count--;
			if(potion5_count < 0){
				potion5_count++;
				printf("Whoops!  Looks like yer out of potions.\n\n");
			}else if(potionCheck == 0){
				player.currentHealth += 500;
				if(player.currentHealth > player.maxHealth)
					player.currentHealth = player.maxHealth;
				printf("You now have %d Ultra Potions left.\n\n", potion5_count);
				potionCheck = 1;
			}else if(potionCheck == 1)
				printf("Don't be cheeky.\n\n");
		}else if(choice == 3){
			printf("You cry out for help.  No one answered.\n\n");
		}else if(choice == 4){
			printf("Tau:\nCLASS: Creator\tLEVEL: 9999\nTYPE: %s\nMIT: 9999\tWIT: 9999\tPACE: 9999\nDEF: 9999\tFCS: 9999\nVGR: 9999\tKMA: 9999\n", getMonType(-1));
			printf("ARMOUR:\n\tHELMET: Impeccable Glasses\n\tCHEST: Impeccable Jacket\n\tLEGS: Impeccable Jeans\n\tWEAPON: 0Z_.hV2$n^");
		}else if(choice == 5){
			printf("%s:\nCLASS: Imposter\tLEVEL: 0\nTYPE: %s\nMIT: 0\tWIT: 0\tPACE: 0\nDEF: 0\tFCS: 0\nVGR: 0\tKMA: -1\n", player.name, getMonType(-1));
			printf("ARMOUR:\n\tHELMET: Impeccable Glasses\n\tCHEST: Impeccable Jacket\n\tLEGS: Impeccable Jeans\n\tWEAPON: 0Z_.hV2$n^");
		}
		if(choice == 1 || choice == 3){
			if(rand() % 2 == 0){
				printf("I attack.  %d dmg dealt.\n\n", 100 + damage);
				player.currentHealth -= 100 + damage;
			}else{
				printf("You cower from my might.  Critical hit.  %d dmg dealt.\n\n", (100 + damage) * 2);
				player.currentHealth -= (100 + damage) * 2;
			}
			potionCheck = 0;
		}
		if(player.currentHealth < 0){
			printf("Oh, what's this?  You died?  Hah!  Come back when\nyou're actually ready to face me.\n\n");
			exit(0);
		}else if(tauHP < 0){
			printf("Defeated... by an imposter...\n");
			delay(2);
			printf("How could... this happen...?\n");
			delay(2);
			printf("Hehehe...  I guess that I underestimated you, \"%s\".\n");
			delay(3);
			printf("*cough* Blood...?  Why am I bleeding...?\n");
			delay(2);
			printf("\n\n\n\t====================\n\t|      THE END     |\n\t====================");
			delay(15);
			int ret = remove(DATAFILE);
			exit(0);
		}
		turn++;
	}
}