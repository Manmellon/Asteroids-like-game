#ifndef PLAYER_H_
#define PLAYER_H_
class Player
{
	protected:
	char *name;
	int spaceships_count;
	int *spaceships;
	int active;
	public:
	Player();
	int getSpaceshipsCount();
	int* getSpaceshipsArray();
};
#endif
