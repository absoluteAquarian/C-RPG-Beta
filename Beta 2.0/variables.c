struct user{
	int level;
	int exp;
	int class;
	int subclass;
	int damageType;
	int armourH, armourC, armourL;
	int weapon;
	int adventure;
	int potion1_count, potion2_count, potion3_count, potion4_count;
	int ether1_count, ether2_count, ether3_count, ether4_count;
	int maxHealth, currentHealth;
	long long currentCoin;
	float might, wit, pace, focus, vigor, karma, defense, agility;							//Shown stats
	int t_might, t_wit, t_pace, t_focus, t_vigor, t_karma, t_defense, t_agility;			//True stats
	float c_might, c_wit, c_pace, c_focus, c_vigor, c_karma, c_defense, c_agility;			//Stat changes, converts true stats to shown stats
	int stats_points;
	int gameOver;
	int poisoned, burned;
	int hUpCheck, cUpCheck, lUpCheck, wUpCheck;
	int tier8H, tier8C, tier8L, tier8W;
	int turn;
	int potionCheck, etherCheck;
	int luckCheck;
	int secretCheck;
	char name[16];
};
struct monster{
	int currentHealth;
	int currentMon;
};
struct monster enemy = {
	.currentHealth = 0,
	.currentMon = -1,
};
struct eventFlags{
	bool adv1;
	bool adv2;
	bool adv3;
	bool adv4;
	bool adv5;
	bool adv6;
	bool adv7;
	bool adv8;
	bool inmap;
	int speed;
	int mapno;
	int mapx;
	int mapy;
	int cutsceneCounter;
	bool shouldDrawMap
}flags;

flags = {
	.adv1 = false,
	.adv2 = false,
	.adv3 = false,
	.adv4 = false,
	.adv5 = false,
	.adv6 = false,
	.adv7 = false,
	.adv8 = false,
	.inmap = false,
	.speed = 2,
	.mapno = 0,
	.mapx = 0,
	.mapy = 0,
	.cutsceneCounter = 0,
	.shouldDrawMap = true
};

//Function Prototypes
void getFileData();
void new_game();
void updateFileData();
void home();
void town();
void updateStats();
void level_up();
void drops(int mst);
void monStats();
void secret1();		//Defeating Dein with Tier 0 armour
void secret2();		//Achieving maximum level
void tauSecret();	//Obtaining all Tier 8 armour and weapon
void delay(double dly);
void maps(int i);
void story();
void drawMap();
void* keepResizingWindow();
double getTextDelay();

//Map-related variables
char map[MAP];
char compmap[MAP];
bool shouldSaveMap = false;

//Thread names
pthread_t einput, collmov, transit;

//Enums and typedefs
enum damageTypes{
	force = 1, thermal, mechanical, energy, penetration, disruption, TYPE_ERROR
};
enum textColours{
	WHITE_BLACK = 1,
	GREEN_BLACK, RED_BLACK, BLUE_BLACK, MAGENTA_BLACK, CYAN_BLACK, YELLOW_BLACK, UNUSED_EINS,
	WHITE_WHITE, BLACK_BLACK, RED_RED, YELLOW_YELLOW, GREEN_GREEN, UNUSED_ZWEI, MAGENTA_MAGENTA, UNUSED_DREI, BLUE_BLUE,
	WHITE_RED, WHITE_YELLOW, WHITE_GREEN, WHITE_CYAN, WHITE_BLUE, WHITE_MAGENTA
};
typedef struct tileString{
	char wall =			"#";
	char water =		"@";
	char empty =		" ";
	char fakewall =		"*";
	char specialtile =	"!";
	char tree =			"$";
	
	char bordercorner =	"0";
	char borderside =	"|";
	char bordertop =	"-";
};
typedef struct mapTile{
	int x, y, location;
	int palette;		//Currently unused
	tileString tilestr;
};

//Item ID list arrays
char *itemName[ITEMID_MAX] = {
//Classless
	"None", 				"Worn Shirt", 			"Combat Slacks", 		"Dagger",
	"Copper Hat", 			"Copper Shirt", 		"Copper Pants", 		"Old Sword",
	"Iron Pot", 			"Iron Chainmail", 		"Iron Greaves", 		"Iron Sword",
//Melee
	"Rusty Helmet", 		"Broken Chestplate", 	"Tattered Pants", 		"Dull Spear",
	"Polished Headwear", 	"Shiny Chestpiece", 	"Mirror Trousers", 		"Light Axe",
	"Golden Necklace", 		"Jeweled Mail", 		"Jeweled Leggings", 	"Golden Battleaxe",
	"Doulin", 				"Green Chainmail", 		"Ivy Shinguards", 		"Tempered Naginata",
	"Bloody Helmet", 		"Thorned Breastplate", 	"Pointy Legwear", 		"Crimson Hammer",
//Magic
	"Bronze Amulet", 		"Tattered Cloak", 		"Worn Leggings", 		"Short Staff",
	"Choice Cap", 			"Apprentice's Cape", 	"Apprentice's Slacks", 	"Oak Wand",
	"Gold Monocle", 		"Gold Tux", 			"Gold Pants", 			"Gold Pendant",
	"Shadow Hood", 			"Shadow Cloak", 		"Shadow Shinguards", 	"Ancient Tome",
	"Guardian's Flower", 	"Captain's Shirt", 		"Captain's Pants", 		"Mysterious Rock",
//Range
	"Dusty Hat", 			"Faded Poncho", 		"Faded Slacks", 		"Pistol",
	"Bird Cowl", 			"Jade Tunic", 			"Beige Leggings", 		"Tiny Bow",
	"14-Liter Headwear", 	"Justice Vest", 		"Justice Jeans", 		"Hardened Whip",
	"Blue Cap", 			"Name Brand Shirt", 	"Pocket Jeans", 		"Yoyo",
	"Oversized Crown", 		"Fat King's Cape", 		"Alligator Slacks", 	"Hand-cannon",
//Healer
	"Damaged Helmet",		"Vest", 				"Cargo Pants", 			"Syringe",
	"Surgical Mask", 		"Scrub Shirt", 			"Scrub Pants", 			"Hacksaw",
	"", "", "", "",
	"", "", "", "",
	"Tiny Bifocals", 		"Doctor's Jacket", 		"Doctor's Legwear", 	"Heilungspistole",
//Shop Items
	"Small Potion", 		"Potion", 			"Large Potion", 	"Super Potion",
	"Prototype Stampack", 	"Stampack", 		"Stampack Bundle", 	"Mega Stampack",
	"Vial of Ether", 		"Tube of Ether", 	"Flask of Ether", 	"Patented Ether",
	"Small Ammo Box", 		"Ammo Box", 		"Ammo Crate", 		"Ammo Chest",
//Tier 8 Items
	"Impeccable Glasses", 	"Impeccable Jacket", 	"Impeccable Jeans", 	"0Z_.hV2$n^"
};
char* itemNameShortened[ITEMID_MAX] = {
//Classless
	"None", 				"WornShrt", 		"CmbtSlks", 		"Dagger",
	"Cppr Hat", 			"CpprShrt", 		"CpprPnts", 		"OldSword",
	"Iron Pot", 			"IrnChnml", 		"IronGrvs", 		"IronSwrd",
//Melee
	"RstyHelm", 			"BrknChst", 		"TattPant", 		"DllSpear",
	"PlshHead", 			"ShnyChst", 		"MirrTrsr", 		"LightAxe",
	"Golden Necklace", 		"Jeweled Mail", 		"Jeweled Leggings", 	"Golden Battleaxe",
	"Doulin", 				"Green Chainmail", 		"Ivy Shinguards", 		"Tempered Naginata",
	"Bloody Helmet", 		"Thorned Breastplate", 	"Pointy Legwear", 		"Crimson Hammer",
//Magic
	"Bronze Amulet", 		"Tattered Cloak", 		"Worn Leggings", 		"Short Staff",
	"Choice Cap", 			"Apprentice's Cape", 	"Apprentice's Slacks", 	"Oak Wand",
	"Gold Monocle", 		"Gold Tux", 			"Gold Pants", 			"Gold Pendant",
	"Shadow Hood", 			"Shadow Cloak", 		"Shadow Shinguards", 	"Ancient Tome",
	"Guardian's Flower", 	"Captain's Shirt", 		"Captain's Pants", 		"Mysterious Rock",
//Range
	"Dusty Hat", 			"Faded Poncho", 		"Faded Slacks", 		"Pistol",
	"Bird Cowl", 			"Jade Tunic", 			"Beige Leggings", 		"Tiny Bow",
	"14-Liter Headwear", 	"Justice Vest", 		"Justice Jeans", 		"Hardened Whip",
	"Blue Cap", 			"Name Brand Shirt", 	"Pocket Jeans", 		"Yoyo",
	"Oversized Crown", 		"Fat King's Cape", 		"Alligator Slacks", 	"Hand-cannon",
//Healer
	"Damaged Helmet",		"Vest", 				"Cargo Pants", 			"Syringe",
	"Surgical Mask", 		"Scrub Shirt", 			"Scrub Pants", 			"Hacksaw",
	"", "", "", "",
	"", "", "", "",
	"Tiny Bifocals", 		"Doctor's Jacket", 		"Doctor's Legwear", 	"Heilungspistole",
//Shop Items
	"Small Potion", 		"Potion", 			"Large Potion", 	"Super Potion",
	"Prototype Stampack", 	"Stampack", 		"Stampack Bundle", 	"Mega Stampack",
	"Vial of Ether", 		"Tube of Ether", 	"Flask of Ether", 	"Patented Ether",
	"Small Ammo Box", 		"Ammo Box", 		"Ammo Crate", 		"Ammo Chest",
//Tier 8 Items
	"Impeccable Glasses", 	"Impeccable Jacket", 	"Impeccable Jeans", 	"0Z_.hV2$n^"
};
bool canBeUpgraded[ITEMID_MAX] = {
//Classless
	false, false, false, false,
	true, true, true, true,
	true, true, true, true,
//Melee
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
//Magic
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
//Range
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
//Healer
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
	true, true, true, true,
//Shop Items
	false, false, false, false,
	false, false, false, false,
	false, false, false, false,
	false, false, false, false,
//Tier 8 Items
	false, false, false, false
};
int itemStat[ITEMID_MAX] = {
//Classless
	0,	0,	0,	0,
	5,	8,	6,	7,
	12,	18,	14,	10,
//Melee
	22,	28,	24,	13,
	30,	37,	33,	17,
	47,	53,	49,	23,
//Magic
	22,	28,	24,	13,
	30,	37,	33,	17,
	47,	53,	49,	23,
//Range
	22,	28,	24,	13,
	30,	37,	33,	17,
	47,	53,	49,	23,
//Healer
	22,	28,	24,	13,
	30,	37,	33,	17,
	47,	53,	49,	23,
//Shop Items
	20,	45,	75,	200,
	0,	0,	0,	0,
	0,	0,	0,	0,
	0,	0,	0,	0,
//Tier 8 Items
	9999, 9999, 9999, 9999
};
int upgradeStatAdd[ITEMID_MAX] = {
//Classless
	0, 	0, 	0, 	0,
	1, 	2, 	2, 	1,
	4, 	5, 	5, 	2,
//Melee
	7, 	9, 	8, 	2,
	11, 13, 12, 4,
	15, 18, 17, 1,
	18, 23, 20, 3,
	22, 25, 23, 7,
//Magic
	7, 	9, 	8, 	2,
	11, 13, 12, 4,
	15, 18, 17, 1,
	18, 23, 20, 3,
	22, 25, 23, 7,
//Range
	7, 	9, 	8, 	2,
	11, 13, 12, 4,
	15, 18, 17, 1,
	18, 23, 20, 3,
	22, 25, 23, 7,
//Healer
	7, 	9, 	8, 	2,
	11, 13, 12, 4,
	15, 18, 17, 1,
	18, 23, 20, 3,
	22, 25, 23, 7,
//Shop Items
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
//Tier 8 Items
	0, 0, 0, 0
};
long itemCost[ITEMID_MAX] = {
//Classless
	0, 		0, 		0, 		0,
	900, 	1100, 	900, 	650,
	1800, 	2100, 	1950, 	3200,
//Melee
	3150, 	3250, 	3200, 	1800,
	4900,	5000,	4950,	2880,
	7300,	7600,	7450,	3970,
	9300,	9500,	9400,	6540,
	11500,	12500,	12000,	7220,
//Magic
	3150, 	3250, 	3200, 	1800,
	4900,	5000,	4950,	2880,
	7300,	7600,	7450,	3970,
	9300,	9500,	9400,	6540,
	11500,	12500,	12000,	7220,
//Range
	3150, 	3250, 	3200, 	1800,
	4900,	5000,	4950,	2880,
	7300,	7600,	7450,	3970,
	9300,	9500,	9400,	6540,
	11500,	12500,	12000,	7220,
//Healer
	3150, 	3250, 	3200, 	1800,
	4900,	5000,	4950,	2880,
	7300,	7600,	7450,	3970,
	9300,	9500,	9400,	6540,
	11500,	12500,	12000,	7220,
//Shop Items
	210,	560,	950,	2010,
	320,	1240,	2310,	4970,
	320,	1240,	2310,	4970,
	320,	1240,	2310,	4970,
//Tier 8 Items
	9999999, 9999999, 9999999, 9999999
};

//Global variables
WINDOW* window;
struct user player;
struct user player2;
struct user player3;
struct user player4;
struct user entry;
struct monster temp;
int required_exp[MAX_LEVEL];
char *monsterName[MONSTER_ARAY_SIZE] = {
	"Goblin", "Goblin Guard", "Goblin Elite", "Goblin Chief",
	"Bat", "Vampire", "Ghoul", "Dien the Mighty",
	"Wolf", "Beast", "Demon", "Earth Whiz",
	"Sand Worm", "Gargoyle", "Golem", "Krul the Merciless"
};
int monsterType[MONSTER_ARRAY_SIZE] = {
	neutral,		neutral,	neutral,	disruption,
	penetration,	force,		energy,		force,
	penetration,	energy,		thermal,	mechanical,
	disruption,		energy,		mechanical,	force
};
int monsterATK[MONSTER_ARRAY_SIZE] = {
	4, 7, 15, 48,
	78, 101, 156, 210,
	170, 191, 220, 270,
	250, 300, 325, 400
};
int monsterDEF[MONSTER_ARRAY_SIZE] = {
	0, 4, 7, 18,
	46, 66, 78, 160,
	101, 118, 127, 137,
	133, 142, 168, 255
};
int monsterAGL[MONSTER_ARRAY_SIZE] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
};
int monsterHP[MONSTER_ARRAY_SIZE] = {
	25, 47, 68, 93,
	22, 96, 124, 2500,
	156, 170, 181, 192,
	186, 204, 215, 4500
};
int monsterEXP[MONSTER_ARRAY_SIZE] = {
	2, 11, 26, 65,
	30, 59, 133, 600,
	680, 792, 845, 940,
	891, 1011, 1304, 5000
};
int monsterCOIN[MONSTER_ARRAY_SIZE] = {
	71, 139, 151, 179,
	53, 189, 243, 6791,
	455, 501, 569, 670,
	610, 751, 910, 9901
};
int monsterPotionDrop[MONSTER_ARRAY_SIZE] = {
	1, 1, 1, 2,
	1, 2, 3, 4,
	2, 2, 3, 3,
	3, 4, 4, 4
};
char* className[CLASS_AMOUNT]{
//Melee
	"Fencer", "Vanguard", "Artificer", "Lancer", "Poineer",
	"Ranger", "Grenadier", "Arbiter", "Musketeer", "Saboteur",
	"Magician", "Tactician", "Wizard", "Alchemist", "Scientist",
	"Healer", "Doctor", "Shaman", "Cleric", "Medic",
	"ERROR"
};
char* classNameUppercase[CLASS_AMOUNT]{
	"FENCER", "VANGUARD", "ARTIFICER", "LANCER", "POINEER",
	"RANGER", "GRENADIER", "ARBITER", "MUSKETEER", "SABOTEUR",
	"MAGICIAN", "TACTICIAN", "WIZARD", "ALCHEMIST", "SCIENTIST",
	"HEALER", "DOCTOR", "SHAMAN", "CLERIC", "MEDIC",
	"ERROR"
};
int monsterSize = 0;
int extraCoin = 0;
int extraPotion = 0;
long tauHP = 9999999;