#include <stdio.h>
#include <ncurses.h>
struct Player { int hp; int max_hp; int damage; int lvl; int exp; int exp_to_lvl; char name[64]; int mana; int max_mana; int magic_power; };
int current_line;
int main(int argc, char **argv)
{	
	
	WINDOW *log_win;
	current_line = 2;
	system("clear");
	initscr();
	int enemy_level = 1;
	
	struct Player player = { 100,  100,   10,  1,  0,  100,  "Hero",  100,  100,  1};
	struct Player enemy  = { 100, 100,    10,  1,  0,  100,  "Ogre",  100,  100,  1};
	
	int turn = 1;
	while(1)
	{
		noecho();
		if(current_line >= 34)
		{
			clear();
			refresh();
			current_line = 2;
		}
		int action;
		draw_ui(&player.hp, &enemy.hp, turn);
		if(enemy.hp <= 0) 
		{
			printw("%s is dead\n", enemy.name);
			break;
		}
		refresh();
		action = getch();
		if(player.hp > 0)
		{ 
			switch( action )
			{
				case 'a':
					if(enemy.hp > 0)
					{
						attack(&player, &enemy, turn);
					}
					turn++;
					break;
				case 'h':
					heal(&player, turn);
					turn++;
					break;
			}
		}
		else
		{
			break;
		}
		enemy_turn(&enemy, &player, turn);

	}
	endwin();
	if(player.hp > 0)
	{
		printf("Game over in %i turns. You win\n", turn);
	}
	else
	{
		printf("Game over in %i turns. You dead\n", turn);
	}
	return 0;
}

void attack(struct Player *attacker, struct Player *defender, int turn)
{
	defender->hp -= attacker->damage;
	add_exp(attacker, attacker->damage);
	move(current_line, 5);
	current_line++;
	printw("%s attacked %s with %i damage", attacker->name, defender->name, attacker->damage);
}

void heal(struct Player *target, int turn)
{
	if(target->mana >= 25)
	{
		target->mana -= 25;
		target->hp += 25 * target->magic_power;
		move(current_line, 5);
		current_line++;
		printw("%s hp += %i", target->name, 25 * target->magic_power);
	}
}

void draw_ui(struct Player *player, struct Player *enemy, int turn_number)
{
	move(0,1);
	printw("HP: %i" , player->hp);
	move(0,15);
	printw("Mana: %i", player->mana);
	move(0,30);
	printw("LVL: %i", player->lvl); 
	move(0,45);
	printw("EXP: %i/%i", player->exp, player->exp_to_lvl);
	move(0,60);
	printw("Enemy HP: %i", enemy->hp);
	move(0,100);
	printw("Turn: %i", turn_number);
	refresh();
}

void lvlup(struct Player *player)
{
	player->lvl++;
	player->exp = 0;
	player->exp_to_lvl = player->exp_to_lvl * 2;
	player->max_hp += 50;
	player->damage += 5;
	player->hp = player->max_hp;
	player->max_mana += 50;
	player->mana = player->max_mana;
	player->magic_power++;
	
	move(current_line, 5);
	current_line++;
	printw("%s lvlupped", player->name);
}

void add_exp(struct Player *player, int exp)
{
	player->exp += exp;
	if(player->exp >= player->exp_to_lvl)
	{
		lvlup(player);
	}
}

void enemy_turn(struct Player *enemy, struct Player *player, int turn)
{
	if(enemy->hp >= (enemy->hp / 2))
	{
		attack(enemy, player, turn);
	}
	else
		if(enemy->mana >= 25)
		{
			heal(enemy,turn);
		}
}
