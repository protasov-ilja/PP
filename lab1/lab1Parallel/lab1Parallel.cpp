// lab1Parallel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrixHandlerParallel.h"

bool ReadStringsInMatrix(std::ifstream& fileIn, Matrix& inputMatrix);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: lab1.exe <input matrix file> <threads amount>"
			<< std::endl;
		return 1;
	}

	int threadsAmount = atoi(argv[2]);
	if (threadsAmount < 1)
	{
		std::cout << "Count of threads must be greater than 0" << std::endl;
		return 1;
	}

	std::ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	HANDLE process = GetCurrentProcess();
	SetProcessAffinityMask(process, 0b1111);

	Matrix inputMatrix;
	if (ReadStringsInMatrix(fileIn, inputMatrix))
	{
		std::cout << "matrix size: " << inputMatrix.size() << std::endl;
		int startTime = clock();
		CMatrixHandlerParallel handler(inputMatrix);
		handler.CreateMatrixOfCofactors(threadsAmount);
		std::cout << clock() - startTime << " ms" << std::endl;
		//handler.ShowMatrixOfCofactors();
	}

	std::cout << std::endl;
	return 0;
}

bool ReadStringsInMatrix(std::ifstream& fileIn, Matrix& inputMatrix)
{
	int matrixSize = 0;
	fileIn >> matrixSize;
	std::vector<std::vector<double>> tempMatrix(matrixSize, std::vector<double>(matrixSize));
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

