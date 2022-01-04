void stats(){
	updateStats();
	int choice = 0, menu = 0;
	char hC, cC, lC, wC;
	if(player.hUpCheck != 0 && player.hUpCheck == player.armourH)
		hC = '+';
	else
		hC = ' ';
	if(player.cUpCheck != 0 && player.cUpCheck == player.armourC)
		cC = '+';
	else
		cC = ' ';
	if(player.lUpCheck != 0 && player.lUpCheck == player.armourL)
		lC = '+';
	else
		lC = ' ';
	if(player.wUpCheck != 0 && player.wUpCheck == player.weapon)
		wC = '+';
	else
		wC = ' ';
	printf("====================\n");	//20 equals signs, indicates new menu
	while(true){
		fflush(stdin);
		printf("\nWould you like to...\n(1) view your stats?\n(2) change your stats?\n(3) Leave\n-> ");
		scanf("%d", &menu);
		if(menu == 1){
			updateStats();
			update_player_data();
			printf("====PLAYER STATS====\n");
			printf("PLAYER: %s\nLEVEL: %d\tEXP: %d/%d\n", player.name, player.level, player.exp, required_exp[player.level]);
			delay(1);
			printf("CLASS: %s\tTYPE: %s\n", getClass(player.class, player.subclass), getMonType(player.damageType));
			delay(1);
			printf("ARMOUR:\n\tHELMET: %s%c\n\tCHESTPLATE: %s%c\n\tLEGGINGS: %s%c\n\tWEAPON: %s%c\n", armourName(player.class, 1, player.armourH), hC, armourName(player.class, 2, player.armourC), cC, armourName(player.class, 3, player.armourL), lC, armourName(player.class, 4, player.weapon), wC);
			delay(1);
			printf("HP: %d/%d\nMIT: %d\nWIT: %d\nPACE: %d\nDEF: %d\nFCS: %d\nVGR: %d\nKMA: %d\n", player.currentHealth, player.maxHealth, (int) (player.might + 0.5), (int) (player.wit + 0.5), (int) (player.pace + 0.5), (int) (player.def + 0.5), (int) (player.focus + 0.5), (int) (player.vigor + 0.5), (int) (player.karma + 0.5));
			delay(1);
			printf("COIN: %lli\nPOINTS: %d\n", player.currentCoin, player.stats_points);
			delay(1);
			printf("POTIONS:\n\tSMALL: %d\n\tREGULAR: %d\n\tLARGE: %d\n\tSUPER: %d\n", player.potion1_count, player.potion2_count, player.potion3_count, player.potion4_count);
			delay(1);
			printf("ETHERS:\n\tSMALL: %d\n\tREGULAR: %d\n\tLARGE: %d\n\tSUPER: %d\n", player.ether1_count, player.ether2_count, player.ether3_count, player.ether4_count);
			delay(1);
		}else if(menu == 2){
			if(player.stats_points == 0){
				printf("\n\nYou have no points to use...\n\n");
			}else{
				while(true){
					fflush(stdin);
					delay(1);
					updateStats();
					printf("\n\nYou have %d points left.", player.stats_points);
					printf("\nUse a point on:\n(1) Might: %d\n(2) Wit: %d\n(3) Pace: %d\n(4) Defense: %d\n(5) Focus: %d\n(6) Vigor: %d\n(7) Karma: %d\nor enter -1 to quit.\n", (int) (player.might + 0.5), (int) (player.wit + 0.5), (int) (player.pace + 0.5), (int) (player.def + 0.5), (int) (player.focus + 0.5), (int) (player.vigor + 0.5), (int) (player.karma + 0.5));
					printf("-> ");
					scanf("%d", &choice);
					if(choice == -1){
						break;
					}else if(choice == 1){
						player.tmight++;
						player.stats_points--;
					}else if(choice == 2){
						player.twit++;
						player.stats_points--;
					}else if(choice == 3){
						player.tpace++;
						player.stats_points--;
					}else if(choice == 4){
						player.tdef++;
						player.stats_points--;
					}else if(choice == 5){
						player.tfocus++;
						player.stats_points--;
						if(player.tfocus >= 100){
							player.tfocus--;
							player.stats_points++;
							printf("FOCUS is maxed.\n");
						}
					}else if(choice == 6){
						player.tvigor++;
						player.stats_points--;
					}else if(choice == 7){
						player.tkarma++;
						player.stats_points--;
						if(player.tkarma >= 450){
							player.tkarma--;
							player.stats_points++;
							printf("KARMA is maxed.\n");
						}
					}
					if(player.stats_points <= 0){
						printf("\nYour stats are now:\nMight: %d\nWit: %d\nPace: %d\nDefense: %d\nFocus: %d\nVigor: %d\nKarma: %d\n", (int) (player.might + 0.5), (int) (player.wit + 0.5), (int) (player.pace + 0.5), (int) (player.def + 0.5), (int) (player.focus + 0.5), (int) (player.vigor + 0.5), (int) (player.karma + 0.5));
						break;
					}
				}
			}
		}else if(menu == 3){
			updateStats();
			update_player_data();
			return;
		}else
			printf("Invalid input.\n");
	}
	updateStats();
	update_player_data();
}