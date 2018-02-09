






#include "Grid.h"
#include <iostream>

enum Direction
{
	North,
	East,
	South,
	West,

	NorthEast,
	SouthEast,
	SouthWest,
	NorthWest
};


void Movable(Piece *piece, int roll, Position *moves)
{
	Position& pos = piece->GetPosition();

	// Odd
	if (roll % 2)
	{
		moves[0] = Position(pos.x + roll, pos.y + roll);
		moves[1] = Position(pos.x - roll, pos.y + roll);
		moves[2] = Position(pos.x + roll, pos.y - roll);
		moves[3] = Position(pos.x - roll, pos.y - roll);


		if (pos.y + roll > 6)
		{
			moves[0] = Position(pos.x + roll, 6);
		}
		else if (pos.y - roll < 0)
		{
			moves[1] = Position(pos.x - roll, 0);
		}

		if (pos.x + roll > 11)
		{
			moves[0] = Position(-1, -1);
			moves[2] = Position(-1, -1);
		}
		else if (pos.x - roll < 0)
		{
			moves[1] = Position(-1, -1);
			moves[3] = Position(-1, -1);
		}


	}
	// Even
	else
	{
		moves[0] = Position(pos.x + roll, pos.y);
		moves[1] = Position(pos.x - roll, pos.y);
		moves[2] = Position(pos.x, pos.y + roll);
		moves[3] = Position(pos.x, pos.y - roll);


		if (pos.y + roll > 6)
		{
			moves[0] = Position(pos.x, 6);
		}
		else if (pos.y - roll < 0)
		{
			moves[1] = Position(pos.x, 0);
		}

		if (pos.x + roll > 11)
		{
			moves[0] = Position(-1, -1);
			moves[2] = Position(-1, -1);
		}
		else if (pos.x - roll < 0)
		{
			moves[1] = Position(-1, -1);
			moves[3] = Position(-1, -1);
		}

	}
}


void Movement(Piece * piece, int roll, Direction direction)
{
	Position& pos = piece->GetPosition();
	// Odd
	if (roll % 2)
	{
		switch (direction)
		{
		case NorthEast:
			pos.x += roll;
			pos.y += roll;
			break;
		case SouthEast:
			pos.x += roll;
			pos.y -= roll;
			break;
		case SouthWest:
			pos.x -= roll;
			pos.y -= roll;
			break;
		case NorthWest:
			pos.x -= roll;
			pos.y += roll;
			break;
		}
	}
	// Even
	else
	{
		switch (direction)
		{
		case North:
			pos.y += roll;
			break;
		case East:
			pos.x += roll;
			break;
		case South:
			pos.y += roll;
			break;
		case West:
			pos.y += roll;
			break;
		}	
	}

	// Keep Pieces on the Grid
	
	// Bounce off of walls
	if (pos.y < 0)
	{
		pos.y = 0;
	}
	else if (pos.y > 6)
	{
		pos.y = 6;
	}

	// Can't move off grid
	if (pos.x < 0)
	{
		pos.x -= roll;
	}
	else if (pos.x > 11)
	{
		pos.x -= roll;
	}

}


void Print_Grid(Grid& grid)
{
	printf("\n\n    ");
	Piece *spot = nullptr;
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			if (spot = grid[i][j])
			{
				printf(" %i ", spot->GetPlayer());
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n    ");
	}
	printf("\n\n");
}


int main()
{
	
	Game game;
	bool running = true;

	int coords[2];
	int roll;

	game.Grid().InitGame();

	Piece *selected = nullptr;

	while (running)
	{
		system("cls");
		Print_Grid(game.Grid());

		int * rolls = game.Dice().Roll();

		printf("Rolls are: %i, %i\n", rolls[0], rolls[1]);
		ROLL: printf("Which roll do you want to use? (1/2) ");
		scanf_s("%i", &roll);
		roll -= 1;

		PIECE: printf("Player %i - Enter a X coord: ", game.GetPlayerTurn());
		scanf_s("%d", &coords[0]);
		printf("Player %i - Enter a Y coord: ", game.GetPlayerTurn());
		scanf_s("%d", &coords[1]);

		if (selected = game.Grid()[coords[0] - 1][coords[1] - 1])
		{
			Position moves[4];
			Movable(selected, rolls[roll], moves);
			for (int i = 0; i < 4; ++i)
			{
				if (moves[i].x != -1)
				{
					printf("     - You can move to: %i, %i\n", moves[i].x, moves[i].y);
				}
			}
		}
		else
		{
			printf("\nNo game piece was found there!\n");
			goto PIECE;
		}

		std::cin.ignore();
		std::cin.ignore();
		game.ChangeTurn();
	}


	return 0;
}








