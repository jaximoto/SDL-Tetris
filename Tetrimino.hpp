#include <vector>
#include <memory>
#include "Block.hpp"
class Tetrimino
{
	/*This class will be the parent class that all the shapes will derive from
	It will include all methods that all shapes will be able to perform
	Block moving down automatically (Increasing speed as levels go on, and if player holds down
	Rotate blocks
	Move blocks left and right
	Detect when a block has landed
	Instantiate the array of blocks that make up the shape
	*/

public:

	std::vector<std::shared_ptr<Block>> blocks;
	Tetrimino();
	~Tetrimino();
};