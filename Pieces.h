


struct Position
{
	explicit Position(int x = 0, int y = 0) : x(x), y(y)
	{
	}

	int x;
	int y;
};


class Piece
{
	bool      hasKing;
	Position  pos;
	int       player;
	int       id;
public:
	Piece() : Piece(false, Position(), 0, 0) {}
	Piece(bool hasKing, Position & pos, int player, int id) : hasKing(hasKing), pos(pos), player(player), id(id) {}
	Piece(bool hasKing, Position && pos, int player, int id) : hasKing(hasKing), pos(pos), player(player), id(id) {}

	void SetPosition(Position & Pos)
	{
		pos = Pos;
	}

	Position& GetPosition()
	{
		return pos;
	}

	bool HasKing() const
	{
		return hasKing;
	}

	int GetPlayer() const
	{
		return player;
	}

	int GetId() const
	{
		return id;
	}

};




class King : public Piece
{
	bool isPickedUp = false;

public:
	King() : Piece(false, Position{ 0, 0 }, 0, 0), isPickedUp(false) {}
	King(bool pickUp, Position & pos, int player, int id) : Piece(false, pos, player, id), isPickedUp(pickUp) {}
	King(bool pickUp, Position && pos, int player, int id) : Piece(false, pos, player, id), isPickedUp(pickUp) {}
};



