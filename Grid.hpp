#include <memory>
#include <vector>
#include "Block.hpp"
#include "Tetrimino.hpp"
class Grid
{
public:
	Grid(int w, int h);
	~Grid() = default;
	bool IsCellOcuppied(int x, int y) const;
	bool IsValidPosition(int x, int y) const;

	bool canPlace(const Tetrimino& t) const;
	void placeTetrimino(const Tetrimino& t);

	std::vector<int> getFullRows() const;
	void clearRows(const std::vector<int>& rows);
	void shiftRowsDown(const std::vector<int>& clearedRows);

	void render(SDL_Renderer* renderer) const;


private:
	const int width = 10;
	const int height = 20;
	std::vector<std::vector<std::shared_ptr<Block>>> cells;

};