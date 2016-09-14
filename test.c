#include <stdio.h>

int main(int argc, char **argv)
{	
	system("clear");
	struct Player { int hp; int damage; int lvl; int exp; int exp_to_lvl};
	struct Player player, enemy; 
	
	player.hp = 50; player.damage = 10; player.lvl = 1; player.exp = 0; player.exp_to_lvl = 100;
	printf("Enemy hp = %i\nYour hp = %i", enemy.hp, player.hp);
	
	while(true)
	{
		int enemy_level = 1;
		system("clear");
		enemy.lvl  = enemy_level; enemy.hp  = 10 * enemy.lvl; enemy.damage  =  5 * enemy.lvl;
		printf("Enemy hp = %i\nYour hp = %i", enemy.hp, player.hp);
		attack(&player.damage, &enemy.hp);
		
		if(enemy.hp <= 0) 
		{
			printf("Enemy is dead");
		}

	}
	
	return 0;
}

void attack(int *damage, int *enemyHp)
{
	*enemyHp -= *damage;
}
