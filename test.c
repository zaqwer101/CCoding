#include <stdio.h>

int main(int argc, char **argv)
{	
	struct Player { int X; int Y; int hp; int damage };
	struct Player player;
	system("clear");
	
	player.damage = 5;
	player.hp = 20;
	player.X = 10; 
	player.Y = 10; 
	
	int directionX, directionY;
	
	changePosition(&player.X , &player.Y, -1, 1);
	
	printf("Current coodrds: [%i, %i]\n", player.X, player.Y);
	
	return 0;
}

void changePosition(int *playerX, int *playerY, int x, int y)
{
	*playerX += x;
	*playerX += x;
	*playerY += y;
}
