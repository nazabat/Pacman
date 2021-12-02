#include "PacManAI.hpp"

#include "Board.hpp"
#include <fmt/format.h>

namespace pacman {

void PacManAI::reset() {
  pos = {};
  direction = Direction::RIGHT;
}

Direction PacManAI::suggestedDirection() const {
  return direction;
}

// This function is not yet implemented.
// You will implement it as part of module 25.
GridPosition PacManAI::pelletClosestToPacman(GridPosition pacmanGridPosition,
                                             std::vector<GridPosition> & pellets) {
  (void)pacmanGridPosition;
  (void)pellets;
  return { 0, 0 };
}

// This function is not yet implemented.
// You will implement it as part of module 25.
bool PacManAI::isValidMove(const Move & move) {
  (void)move;
  return false;
}

// This function is not yet implemented.
// You will implement it as part of module 25.
Direction PacManAI::optimalDirection(const std::array<Move, 4> & moves) {
  (void)moves;
  return Direction::NONE;
}

void PacManAI::update(const PacMan & pacMan, const Pellets & pellets) {
  const GridPosition pacManGridPos = pacMan.positionInGrid();
  const GridPosition currentGridPos = positionToGridPosition(pos);

  if (!isIntersection(pacManGridPos) || currentGridPos == pacManGridPos) {
    return;
  }

  auto pelletPositions = pellets.allPellets();
  if (pelletPositions.empty()) {
    return;
  }

  const GridPosition targetPos = pelletClosestToPacman(pacManGridPos, pelletPositions);

  const GridPosition currentPosition = pacMan.positionInGrid();
  const auto [x, y] = currentPosition;
  std::array<Move, 4> possibleMoves = {
    Move{ Direction::UP, { x, y - 1 } },
    Move{ Direction::LEFT, { x - 1, y } },
    Move{ Direction::DOWN, { x, y + 1 } },
    Move{ Direction::RIGHT, { x + 1, y } }
  };

  for (auto & move : possibleMoves) {
    if (!isValidMove(move))
      continue;
    move.distanceToTarget = positionDistance(move.position, targetPos);
  }
  direction = optimalDirection(possibleMoves);
}
} // namespace pacman
