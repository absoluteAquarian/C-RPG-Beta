float getTypeAdv(int playerType, int monster, int target){
	int p = player.damageType, m = monsterType[monster];
	if(p == 0 || m == 0 || p == m)
		return 1.0;
	if(target == 0){
		//Player
		if(p == 1 && (m == 2 || m == 3))
			return 1.2;
		else if(p == 2 && (m == 3 || m == 6))
			return 1.2;
		else if(p == 3 && (m == 4 || m == 5))
			return 1.2;
		else if(p == 4 && (m == 5 || m == 2))
			return 1.2;
		else if(p == 5 && (m == 6 || m == 1))
			return 1.2;
		else if(p == 6 && (m == 1 || m == 4))
			return 1.2;
		
		else if(p == 1 && (m == 5 || m == 6))
			return 0.8;
		else if(p == 2 && (m == 1 || m == 5))
			return 0.8;
		else if(p == 3 && (m == 1 || m == 2))
			return 0.8;
		else if(p == 4 && (m == 3 || m == 6))
			return 0.8;
		else if(p == 5 && (m == 3 || m == 4))
			return 0.8;
		else if(p == 6 && (m == 2 || m == 5))
			return 0.8;
		
		else
			return 1.0;
	}else if(target == 1){
		//Monster
		if(m == 1 && (p == 2 || p == 3))
			return 1.2;
		else if(m == 2 && (p == 3 || p == 6))
			return 1.2;
		else if(m == 3 && (p == 4 || p == 5))
			return 1.2;
		else if(m == 4 && (p == 5 || p == 2))
			return 1.2;
		else if(m == 5 && (p == 6 || p == 1))
			return 1.2;
		else if(m == 6 && (p == 1 || p == 4))
			return 1.2;
		
		else if(m == 1 && (p == 5 || p == 6))
			return 0.8;
		else if(m == 2 && (p == 1 || p == 5))
			return 0.8;
		else if(m == 3 && (p == 1 || p == 2))
			return 0.8;
		else if(m == 4 && (p == 3 || p == 6))
			return 0.8;
		else if(m == 5 && (p == 3 || p == 4))
			return 0.8;
		else if(m == 6 && (p == 2 || p == 5))
			return 0.8;
		
		else
			return 1.0;
	}
}

void damage(int victim, int mst, int monsterCurrentHealth){
	updateStats();
	int playerAtk;
	float typeAdv, newDmg;
	if(player.damageType == 1 || player.damageType == 2)
		playerAtk = (int) (player.might + 0.5);
	else if(player.damageType == 3 || player.damageType == 6)
		playerAtk = (int) (player.wit + 0.5);
	else if(player.damageType == 4 || player.damageType == 5)
		playerAtk = (int) (player.pace + 0.5);
	else if(player.damageType == 0)
		playerAtk = (int) (player.might + 0.5);
	int dmg, crit;
	int chance = rand() % 450 + 1;
	int hit = rand() % 100 + 1;
	int miss = 0;
	int dealt;
	int prevH = player.hUpCheck, prevC = player.cUpCheck, prevL = player.lUpCheck, prevW = player.wUpCheck;
	char *poisMsg = {" "};
	char *burnMsg = {" "};
	if(prevH != player.armourH)
		player.hUpCheck = 0;
	if(prevC != player.armourC)
		player.cUpCheck = 0;
	if(prevL != player.armourL)
		player.lUpCheck = 0;
	if(prevW != player.weapon)
		player.wUpCheck = 0;
	float pDef = 0.5 * (player.def + ((float) hDef[player.armourH]) + ((float) hUpgrade[player.hUpCheck]) + ((float) cDef[player.armourC]) + ((float) cUpgrade[player.cUpCheck]) + ((float) lDef[player.armourL]) + ((float) lUpgrade[player.lUpCheck]));
	int playerDef = (int) pDef;
	float monstCurrentHealth, prevHP;
	int previousHP = player.currentHealth;
	if(victim == 0){			//Player attacks
		//Damage
		if(hit <= ((int) player.focus))
			miss = 1;
		dmg = playerAtk + wStr[player.weapon] + wUpgrade[player.wUpCheck] - monsterDef[mst];
		typeAdv = getTypeAdv(player.damageType, mst, 0);
		newDmg = typeAdv * ((float) dmg) + 0.5;
		dmg = (int) newDmg;
		if(dmg < 1)
			dmg = 1;
		//Critical Chance
		if(chance <= ((int)player.karma))
			crit = 2;
		else
			crit = 1;
		if(miss == 0){
			monstCurrentHealth = (float) monsterCurrentHealth - ((float) (dmg * crit)) + 0.5;
			enemy.currentHealth = (int) monstCurrentHealth;
			dealt = monsterCurrentHealth - enemy.currentHealth;
			if(dmg == 1){
				if(crit == 2){
					printf("\n\nPlayer -> Monster\nCRITICAL HIT!!!  But it dealt minimal damage...\n\n");
					delay(1);
				}else{
					printf("\n\nPlayer -> Monster\nThe attack dealt minimal damage...\n\n");
					delay(1);
				}
			}else{
				if(crit == 2){
					printf("\n\nPlayer -> Monster\nCRITICAL HIT!!!  %d dmg dealt.\n\n", dealt);
					delay(1);
				}else{
					printf("\n\nPlayer -> Monster\nSuccess!  %d dmg dealt.\n\n", dealt);
					delay(1);
				}
			}
		}else if(miss == 1){
			printf("\n\nPlayer -> Monster\nThe attack missed!\n\n");
			delay(1);
		}
	}else if(victim == 1){		//Monster attacks
		dmg = monsterAtk[mst] - playerDef;
		typeAdv = getTypeAdv(player.damageType, mst, 1);
		newDmg = typeAdv * ((float) dmg) + 0.5;
		dmg = (int) newDmg;
		if(dmg < 3)
			dmg = 3;
		if(rand() % 100 == 0)
			crit = 2;
		else
			crit = 1;
		//Poisoned
		if(mst == 1|| mst == 2 || mst == 3|| mst == 4 || mst == 5 || mst == 10 || mst == 11 || mst == 13 || mst == 14){
			if(rand() % 50 == 0){
				player.poisoned = 5;
				poisMsg = "\nYou were poisoned!";
			}else
				poisMsg = " ";
		}
		//Burned
		if(mst == 6 || mst == 7 || mst == 11 || mst == 12 || mst == 15){
			if(rand() % 10 == 0){
				player.burned = 2;
				burnMsg = "\nYou went up in flames!  How shocking.";
			}else
				burnMsg = " ";
		}
		//Poison Damage
		if(player.poisoned == 5)
			dmg += 2;
		else if(player.poisoned == 4)
			dmg += 3;
		else if(player.poisoned == 3)
			dmg += 5;
		else if(player.poisoned == 2)
			dmg += 7;
		else if(player.poisoned == 1)
			dmg += 8;
		//Fire Damage
		if(player.burned == 2)
			dmg += 5;
		else if(player.burned == 1)
			dmg += 7;
		prevHP = (float) player.currentHealth - ((float) (dmg * crit)) + 0.5;
		player.currentHealth = (int) prevHP;
		dealt = previousHP - player.currentHealth;
		if(dmg == 3){
			if(crit == 2){
				printf("\n\nMonster -> Player\nCRITICAL HIT!!!  But it dealt minimal damage...%s%s\n\n", poisMsg, burnMsg);
				delay(1);
			}else{
				printf("\n\nMonster -> Player\nThe attack dealt minimal damage...%s%s\n\n", poisMsg, burnMsg);
				delay(1);
			}
		}else{
			if(crit == 2){
				printf("\n\nMonster -> Player\nCRITICAL HIT!!!  %d dmg dealt.%s%s\n\n", dealt, poisMsg, burnMsg);
				delay(1);
			}else{
				printf("\n\nMonster -> Player\nSuccess!  %d dmg dealt.%s%s\n\n", dealt, poisMsg, burnMsg);
				delay(1);
			}
		}
	}
	player.hUpCheck = prevH;
	player.cUpCheck = prevC;
	player.lUpCheck = prevL;
	player.wUpCheck = prevW;
	updateStats();
	update_player_data();
}