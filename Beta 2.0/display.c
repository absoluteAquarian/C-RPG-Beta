void displayHP(char* target, int HP, int maxHP){
	float newHP = (float) HP;
	float newMaxHP = (float) maxHP;
	float bar = newHP / newMaxHP;
	if(bar < 0.05){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[--------------------]\n");
	}else if(bar < 0.1){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[#-------------------]\n");
	}else if(bar < 0.15){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[##------------------]\n");
	}else if(bar < 0.2){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[###-----------------]\n");
	}else if(bar < 0.25){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[####----------------]\n");
	}else if(bar < 0.3){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[#####---------------]\n");
	}else if(bar < 0.35){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[######--------------]\n");
	}else if(bar < 0.4){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[#######-------------]\n");
	}else if(bar < 0.45){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[########------------]\n");
	}else if(bar < 0.5){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[#########-----------]\n");
	}else if(bar < 0.55){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[##########----------]\n");
	}else if(bar < 0.6){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[###########---------]\n");
	}else if(bar < 0.65){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[############--------]\n");
	}else if(bar < 0.7){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[#############-------]\n");
	}else if(bar < 0.75){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[##############------]\n");
	}else if(bar < 0.8){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[###############-----]\n");
	}else if(bar < 0.85){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[################----]\n");
	}else if(bar < 0.9){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[#################---]\n");
	}else if(bar < 0.95){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[##################--]\n");
	}else if(bar < 1){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[###################-]\n");
	}else if(bar < 1.05){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[####################]\n");
	}else if(bar <= 0){
		printf("\n%s: %d/%d\n", target, HP, maxHP);
		printf("[-------ERROR--------]\n");
	}
}