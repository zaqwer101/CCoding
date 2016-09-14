#include <stdio.h>

int main(int argc, char **argv)
{	
	system("clear");
	struct Player { int hp; int damage; int lvl; int exp; int exp_to_lvl};
	struct Player player, enemy; 
	int enemy_level = 1;
	player.hp = 50; player.damage = 10; player.lvl = 1; player.exp = 0; player.exp_to_lvl = 100;
	enemy.lvl  = enemy_level; enemy.hp  = 100 * enemy.lvl; enemy.damage  =  5 * enemy.lvl;
	printf("Enemy hp = %i\nYour hp = %i", enemy.hp, player.hp);
	
	while(1)
	{
		//system("clear");
		printf("Enemy hp = %i\nYour hp = %i\n", enemy.hp, player.hp);
		attack(&player.damage, &enemy.hp);
		printf("You attacked enemy\n");
		if(enemy.hp <= 0) 
		{
			printf("Enemy is dead\n");
			break;
		}
		//getchar();
	}
	
	return 0;
}

void attack(int *damage, int *enemyHp)
{
	*enemyHp -= *damage;
}
