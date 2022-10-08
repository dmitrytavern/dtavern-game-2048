#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H

class GameMatrix
{
private:
  unsigned int size;
  unsigned int **matrix;

  void CompareCells(unsigned int *previous_cell, unsigned int *current_cell);
  bool ExistCompareCells(unsigned int *previous_cell, unsigned int *current_cell);

public:
  GameMatrix(unsigned int size);
  void SwipeUp();
  void SwipeLeft();
  void SwipeDown();
  void SwipeRight();
  void FillRandomCell();
  unsigned int **GetMatrix();
  unsigned int GetMatrixSize();
  unsigned int GetEmptyCellCount();
};

#endif
