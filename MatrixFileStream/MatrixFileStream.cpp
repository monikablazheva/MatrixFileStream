#include <iostream>
#include <fstream>
#include <sstream>

constexpr int MAX_ROWS = 100;
constexpr int MAX_COLS = 100;
constexpr int MAX_NUMBER_LEN = 10;
constexpr char FILE1[] = "matrix1.txt";
constexpr char FILE2[] = "matrix2.txt";
constexpr char RESULT[] = "result.txt";

typedef char Row[MAX_COLS];

int colNumber(std::stringstream& row) {
	char number[MAX_NUMBER_LEN];
	row.getline(number, MAX_NUMBER_LEN, ',');
	return std::stoi(number);
}

void readRowNumbers(std::ifstream& file, int matrix[][MAX_COLS], int& curRow, int& curCol) {
	curCol = 0;

	char buff[MAX_COLS];
	file.getline(buff, MAX_COLS, '|');
	std::stringstream row(buff);

	while (!row.eof()) {
		matrix[curRow][curCol] = colNumber(row);
		curCol++;
	}

	curRow++;
}

void populateMatrix(int matrix[][MAX_COLS], int& rowLen, int& colLen, const char* fileName) {

	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Error!" << std::endl;
		return;
	}

	while (!file.eof()) {
		readRowNumbers(file, matrix, rowLen, colLen);
	}

	file.close();
}

void multiplyMatrix(int mat1[][MAX_COLS], int mat2[][MAX_COLS], int** result, int col1, int i, int j) {
	//k = col1 = row2
	for (int k = 0; k < col1; k++) {
		result[i][j] += mat1[i][k] * mat2[k][j];
	}
}

void multiplyMatrix(int mat1[][MAX_COLS], int row1, int col1, int mat2[][MAX_COLS], int row2, int col2, int** result)
{
	if (col1 != row2) {
		return;
	}
	
	for (int i = 0; i < row1; i++) {

		for (int j = 0; j < col2; j++) {

			multiplyMatrix(mat1, mat2, result, col1, i, j);
			std::cout << result[i][j] << "  ";
		}
		std::cout << "\n";
	}
}

int main()
{
	int matrix1[MAX_ROWS][MAX_COLS]{};
	int row1 = 0;
	int col1 = 0;

	int matrix2[MAX_ROWS][MAX_COLS]{};
	int row2 = 0;
	int col2 = 0;

	populateMatrix(matrix1, row1, col1, FILE1);
	populateMatrix(matrix2, row2, col2, FILE2);
	
	if (col1 != row2) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	int** result = new int* [row1] {};

	for (int i = 0; i < row1; i++) {
		result[i] = new int[col2] {};
	}

	multiplyMatrix(matrix1, row1, col1, matrix2, row2, col2, result);

	std::ofstream resultFile(RESULT);
	if (!resultFile.is_open()) {
		std::cout << "Error!" << std::endl;
		return -1;
	}
	
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++)
		{
			resultFile << result[i][j] << ",";
		}
		resultFile << "|";
	}
}