#include <iostream>
#include <iomanip>
#include <string>
#include "interface/Interface.h"
#include "interface/WindowInterface.h"
#include "interface/MatrixInterface.h"

using namespace std;

namespace Interface::Matrix
{
  void Print(unsigned int **matrix, int matrix_size)
  {
    unsigned int output_matrix_rows = CalcMatrixRow(matrix_size);
    unsigned int output_matrix_columns = CalcMatrixColumns(matrix_size);
    unsigned int windows_size = CalcWindowSize(output_matrix_columns);
    unsigned int spaces_count = Interface::Window::CalcSpacesCount(windows_size);

    string **chars_matrix;
    chars_matrix = new string *[output_matrix_rows];
    for (int row = 0; row < output_matrix_rows; row++)
      chars_matrix[row] = new string[output_matrix_columns];

    for (int row = 0; row < matrix_size; row++)
      for (int column = 0; column < matrix_size; column++)
      {
        int number = matrix[row][column];
        int number_row = row * CELL_HEIGHT;
        int number_column = column * CELL_WIDTH;
        int number_color = GetTerminalColorByNumber(number);

        // Row 1
        chars_matrix[number_row + 0][number_column + 0] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_TOP_LEFT_CHAR) : " ";
        chars_matrix[number_row + 0][number_column + 1] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_HORIZONTAL_CHAR) : " ";
        chars_matrix[number_row + 0][number_column + 3] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_HORIZONTAL_CHAR) : " ";
        chars_matrix[number_row + 0][number_column + 2] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_HORIZONTAL_CHAR) : " ";
        chars_matrix[number_row + 0][number_column + 4] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_TOP_RIGHT_CHAR) : " ";

        // Row 2
        chars_matrix[number_row + 1][number_column + 0] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_VERTICAL_CHAR) : " ";
        chars_matrix[number_row + 1][number_column + 1] = number < 100 ? " " : "";
        chars_matrix[number_row + 1][number_column + 2] = number != 0 ? Interface::PaintText(number_color, to_string(number)) : " ";
        chars_matrix[number_row + 1][number_column + 3] = number < 10 ? " " : "";
        chars_matrix[number_row + 1][number_column + 4] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_VERTICAL_CHAR) : " ";
        if (number > 999)
          chars_matrix[number_row + 1][number_column + 4] = "";
        if (number > 9999)
          chars_matrix[number_row + 1][number_column + 0] = "";

        // Row 3
        chars_matrix[number_row + 2][number_column + 0] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_BOTTOM_LEFT_CHAR) : " ";
        chars_matrix[number_row + 2][number_column + 1] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_HORIZONTAL_CHAR) : " ";
        chars_matrix[number_row + 2][number_column + 2] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_HORIZONTAL_CHAR) : " ";
        chars_matrix[number_row + 2][number_column + 3] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_HORIZONTAL_CHAR) : " ";
        chars_matrix[number_row + 2][number_column + 4] = number != 0 ? Interface::PaintText(number_color, Interface::Window::BORDER_BOTTOM_RIGHT_CHAR) : " ";
      }

    Interface::PrintSpaces(spaces_count);
    Interface::Window::PrintBorderTop(windows_size);

    for (int row = 0; row < output_matrix_rows; row++)
    {
      Interface::PrintSpaces(spaces_count);

      for (int column = 0; column < output_matrix_columns; column++)
      {
        if (column == 0)
          cout << Interface::Window::BORDER_VERTICAL_CHAR;

        cout << chars_matrix[row][column];

        if (column == output_matrix_columns - 1)
          cout << Interface::Window::BORDER_VERTICAL_CHAR;
      }

      cout << endl;
    }

    Interface::PrintSpaces(spaces_count);
    Interface::Window::PrintBorderBottom(windows_size);
  }

  static int CalcMatrixRow(int matrix_size)
  {
    return matrix_size * CELL_HEIGHT;
  }

  static int CalcMatrixColumns(int matrix_size)
  {
    return matrix_size * CELL_WIDTH;
  }

  static int CalcWindowSize(int content_size)
  {
    return content_size + BORDER_SIZE * 2;
  }

  static int GetTerminalColorByNumber(int number)
  {
    int color = CELL_START_COLOR;

    for (int i = 1; number > 2; i++)
    {
      number = number / 2;

      if (i % 6 == 0)
        color += 67;
      else
        color += 1;
    }

    if (color > 255)
      color = 255;

    return color;
  }

}