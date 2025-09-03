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

	bool CanPlace(const Tetrimino& t) const;
	void PlaceTetrimino(const Tetrimino& t);

	std::vector<int> GetFullRows() const;
	void ClearRows(const std::vector<int>& rows);
	void ShiftRowsDown(const std::vector<int>& clearedRows);

	void Render(SDL_Renderer* renderer) const;


private:
	const int width = 10;
	const int height = 20;
	std::vector<std::vector<std::shared_ptr<Block>>> cells;

};