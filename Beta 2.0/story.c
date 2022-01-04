void titleCutscene(){
	float d;
	char str[64];
	if(flags.speed == 1)
		d = 0.1;
	else if(flags.speed == 2)
		d = 0.05;
	else if(flags.speed == 3)
		d = 0.025;
	else
		d = 0.1;		//Fail-safe
	drawTextBox();
	pthread_create(&einput, NULL, eatInput, NULL);
	mvprintw(21, 2, "->");		drawText(21, 4, 1.5, ".....");
	delay(4.0);
	drawNameBox(2, 1, "? ? ?");
	strcat(strcat(str, player.name), ", are you awake?");
	mvprintw(21, 2, "->");		drawText(21, 4, d, str);
	setColour(1);
	refresh();
	delay(2.0);
	drawNameBox(2, 1, player.name);
}

void tutorialCutscene(){
	
}

void firstBattleCutscene(){
	
}

void postTutorialBattleCutscene(){
	
}

void classesCutscene(){
	
}

void innCutscene(){
	
}

void shopCutscene(){
	
}

void smitheryCutscene(){
	
}

void statsCutscene(){
	
}

void firstAdventureCutscene(){
	
}

void bossOneCutscene(){
	
}

void bossTwoCutscene(){
	
}

void bossThreeCutscene(){
	
}

void bossFourCutscene(){
	
}

void bossFiveCutscene(){
	
}

void bossSixCutscene(){
	
}

void bossSevenCutscene(){
	
}

void bossEightCutscene(){
	
}

void finaleCutscene(){
	
}

void story(){		//TODO: paramter "int cutscene" for a future Records system
	int *cutscene = &flags.cutsceneCounter;
	if(*cutscene == 0){
		titleCutscene();
		*cutscene = 1;
		return;
	}
	if(*cutscene == 1){
		tutorialCutscene();
		*cutscene = 2;
		return;
	}
	if(*cutscene == 2){
		firstBattleCutscene();
		*cutscene = 3;
		return;
	}
	if(*cutscene == 3){
		classesCutscene();
		*cutscene = 4;
		return;
	}
	if(*cutscene == 4){
		innCutscene();
		*cutscene = 5;
		return;
	}
	if(*cutscene == 5){
		shopCutscene();
		*cutscene = 6;
		return;
	}
	if(*cutscene == 6){
		smitheryCutscene();
		*cutscene = 7;
		return;
	}
	if(*cutscene == 7){
		statsCutscene();
		*cutscene = 8;
		return;
	}
	if(*cutscene == 8){
		firstAdventureCutscene();
		*cutscene = 9;
		return;
	}
	if(*cutscene == 9){
		bossOneCutscene();
		*cutscene = 10;
		return;
	}
	if(*cutscene == 10){
		bossTwoCutscene();
		*cutscene = 11;
		return;
	}
	if(false && *cutscene == 11){
		bossThreeCutscene();
		*cutscene = 12;
		return;
	}
	if(*cutscene == 12){
		bossFourCutscene();
		*cutscene = 13;
		return;
	}
	if(*cutscene == 13){
		bossFiveCutscene();
		*cutscene = 14;
		return;
	}
	if(*cutscene == 14){
		bossSixCutscene();
		*cutscene = 15;
		return;
	}
	if(*cutscene == 15){
		bossSevenCutscene();
		*cutscene = 16;
		return;
	}
	if(*cutscene == 16){
		bossEightCutscene();
		return;
	}
	if(*cutscene == 99){
		finaleCutscene();
		return;
	}
}