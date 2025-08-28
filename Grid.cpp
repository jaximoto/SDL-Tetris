#include "Grid.hpp"
Grid::Grid(int w, int h) : width(w), height(h)
{
    cells.resize(height, std::vector<std::shared_ptr<Block>>(width, nullptr));
}

bool Grid::IsValidPosition(int x, int y) const
{
    return x >= 0 && x < this->width && y >= 0 && y < this->height;
}

bool Grid::IsCellOcuppied(int x, int y) const
{
    return IsValidPosition(x, y) && cells[y][x] != nullptr;
}

bool Grid::CanPlace(const Tetrimino& t) const
{
	return true;
    // TO DO
}

void Grid::PlaceTetrimino(const Tetrimino& t)
{
    return;
}

std::vector<int> Grid::GetFullRows() const
{
    std::vector<int> fullRows;
    for (int y = 0; y < height; ++y)
    {
        bool isFull = true;
        for (int x = 0; x < width; ++x)
        {
            if (cells[y][x] == nullptr)
            {
                isFull = false;
                break;
            }
        }
        if (isFull)
            fullRows.push_back(y);
    }
	return fullRows;
}
void Grid::ClearRows(const std::vector<int>& rows)
{
    for (int i = 0; i < rows.size(); i++)
    {
        
    }
}
void ShiftRowsDown(const std::vector<int>& clearedRows);

void Render(SDL_Renderer* renderer) const;