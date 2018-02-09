



#pragma once
#include "Pieces.h"
#include <cstdlib>


struct Dice
{
	int rolled[2]{0};
	int *Roll()
	{
		rolled[0] = rand() % 6 + 1;
		rolled[1] = rand() % 6 + 1;
		return rolled;
	}
};


class Grid
{
	Piece * pieces[12][7];
public:
	Grid() : pieces{ nullptr } {}
	~Grid()
	{
		Clear();
	}

	Piece ** operator[](int index)
	{
		return pieces[index];
	}

	void Clear()
	{
		for (int i = 0; i < 7; ++i)
			for (int j = 0; j < 12; ++j)
			{
				delete pieces[i][j];
				pieces[i][j] = nullptr;
			}
	}

	void InitGame()
	{
		
		Clear();

		int id_start = 0;
		int king_id[2];

		for (int i = 0; i < 7; ++i)
			pieces[0][i] = new Piece(false, Position(0, i), 1, ++id_start);

		for (int i = 0; i < 3; ++i)
			pieces[1][i + 2] = new Piece(false, Position(1, i + 2), 1, ++id_start);


		for (int i = 0; i < 7; ++i)
			pieces[6][i] = new Piece(false, Position(6, i), 2, ++id_start);

		for (int i = 0; i < 3; ++i)
			pieces[5][i + 2] = new Piece(false, Position(1, i + 2), 2, ++id_start);


		king_id[0] = pieces[0][3]->GetId();
		king_id[1] = pieces[6][3]->GetId();
		
		delete pieces[0][3];
		pieces[0][3] = new King(false, Position(0, 3), 1, king_id[0]);
		
		delete pieces[6][3];
		pieces[6][3] = new King(false, Position(6, 3), 2, king_id[1]);
	}
};


class Game
{
	Grid grid;
	Dice dice;
	int turn = 1;
public:

	Dice & Dice()
	{
		return dice;
	}
	Grid & Grid()
	{
		return grid;
	}

	void ChangeTurn()
	{
		switch (turn)
		{
		case 1:
			turn = 2;
			break;
		case 2:
			turn = 1;
			break;
		default:
			turn = 1;
			break;
		}
	}

	int GetPlayerTurn() const
	{
		return turn;
	}
};

