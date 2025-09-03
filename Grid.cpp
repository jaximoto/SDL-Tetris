#include "Grid.hpp"
#include "Block.hpp"
#include <algorithm> // For std::all_of
#include <iterator>  // For iterators
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
        if (std::all_of(cells[y].begin(), cells[y].end(), [](std::shared_ptr<Block> cell) { return cell != nullptr; }))
        {
            fullRows.push_back(y);
        }
    }
    return fullRows;
}

void Grid::ClearRows(const std::vector<int>& rows)
{
    for (int i = 0; i < width; i++)
    {
        for(int j : rows)
			cells[j][i] = nullptr;
    }
}
void Grid::ShiftRowsDown(const std::vector<int>& clearedRows)
{
    std::vector<bool> isCleared(height, false);
    for (int y : clearedRows)
        isCleared[y] = true;

    for (int y = 0; y < height; ++y)
    {
        // Count how many cleared rows are below this one
        int fallDistance = 0;
        for (int below = 0; below < y; ++below)
        {
            if (isCleared[below])
                ++fallDistance;
        }

        if (fallDistance > 0 && y - fallDistance >= 0)
            cells[y - fallDistance] = std::move(cells[y]);
    }

    for (int y : clearedRows)
        cells[y].assign(width, nullptr);
}

void Grid::Render(SDL_Renderer* renderer) const
{
    for (const auto& row : this->cells)
    {
        for (const auto& cell : row)
        {
            if (cell)
                cell->Render(renderer);
        }
	}
}