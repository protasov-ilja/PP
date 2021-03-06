// lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrixHandler.h"

bool ReadStringsInMatrix(std::ifstream& fileIn, Matrix& inputMatrix);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: lab1.exe <input matrix file>"
			<< std::endl;
		return 1;
	}

	std::ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	Matrix inputMatrix;
	if (ReadStringsInMatrix(fileIn, inputMatrix))
	{
		std::cout << "matrix size: " << inputMatrix.size() << std::endl;
		int startTime = clock();
		CMatrixHandler handler(inputMatrix);
		handler.CreateMatrixOfCofactors();
		std::cout << clock() - startTime << " ms" << std::endl;
		// handler.ShowMatrixOfCofactors();
	}
	
	std::cout << std::endl;
    return 0;
}

bool ReadStringsInMatrix(std::ifstream& fileIn, Matrix& inputMatrix)
{
	int matrixSize = 0;
	fileIn >> matrixSize;
	std::vector<std::vector<double>> tempMatrix(matrixSize, std::vector<double>(matrixSize));
	double number;
	for (size_t i = 0; i < matrixSize; ++i)
	{
		for (size_t j = 0; j < matrixSize; ++j)
		{
			if (!(fileIn >> tempMatrix[i][j]))
			{
				return false;
			}
		}
	}

	inputMatrix = tempMatrix;

	return true;
}

