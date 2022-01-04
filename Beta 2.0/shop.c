void drawShopOutline(){
									 //			 1		   2		 3		   4
									 //0123456789A123456789A123456789A123456789A1234567
	char shopBox[SHOP_BOX_SIZE] =	  "-----------------------------------------------"//1
									  "|                                             |"//2
									  "|                                             |"//3
									  "|                                             |"//4
									  "|                                             |"//5
									  "|                                             |"//6
									  "|                                             |"//7
									  "|                                             |"//8
									  "|                                             |"//9
									  "|                                             |"//A	1
									  "|                                             |"//1
									  "|                                             |"//2
									  "-----------------------------------------------";//3
	setColour(WHITE_BLACK);
	for(int y = 0; y < 14; y++){
		for(int x = 0; x < 47; x++){
			int loc = (47 * y) + x;
			mvaddch(y + 2, x + 17, shopBox[loc]);
		}
	}
}

void drawItemDescriptionBox(){
	
}

void shopOptions(){
	mvprintw(6, 22, "(1) Weapons");
	mvprintw(7, 22, "(2) Armour");
	mvprintw(8, 22, "(3) Consumables");
	mvprintw(9, 22, "(4) Artifacts");
	mvprintw(11, 28, "-> ");
}

bool wantsToContinueShopping = false;

void shop(){
	//Shop, used to buy items
	/*	Rows available for shop:	1-24
		Rows used for shop text:	3-16
		Rows used for name boxes:	17-19
		Rows used for dialogue:		21-23
		
		Columns available for shop:	1-79
	*/
	double textDelay = getTextDelay();
	scr_dump(MAPFILE_EINS);			//Pre-shop screen
	flags.shouldDrawMap = false;
continueShopping:
	drawMap();
	drawText(3, 27, 0, "====SHOP====");
	shopOptions();
	drawTextBox();
	drawNameBox(1, CYAN_BLACK, "Shopkeeper");
	setColour(GREEN_BLACK);
	drawText(2, 21, textDelay, "-> Whad'ya want to buy, eh?");
	char choice;
	int intChoice;
	while(1){
		choice = wgetch(window);
		mvprintw(2, 21, "                                              ");
		intChoice = choice - "0";
		mvprintw(11, 28, "                          ");
		if(intChoice > 0 && intChoice < 5)
			break;
		else{
			drawTextBox();
			drawText(2, 21, textDelay, "-> Don't be a fool.  Choose from what's there!");
			wmove(window, 11, 31);
		}
	}
	char* shopNames[] = {"Weapons", "Armours", "Consumables", "Artifacts"};
	drawShopOutline();
	mvprintw(2, 18, shopNames[intChoice - 1]);
	
	if(wantsToContinueShopping)
		goto continueShopping;
	
	flags.shouldDrawMap = true;
}