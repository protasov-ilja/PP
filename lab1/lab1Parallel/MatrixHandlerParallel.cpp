#include "stdafx.h"
#include "MatrixHandlerParallel.h"

Matrix initMatrix;

CMatrixHandlerParallel::CMatrixHandlerParallel(const Matrix initialMatrix)
{
	m_initialMatrix = initialMatrix;
}

CMatrixHandlerParallel::~CMatrixHandlerParallel()
{
}

void CMatrixHandlerParallel::ShowInitialMatrix() const
{
	size_t matrixSize = m_initialMatrix.size();
	for (size_t i = 0; i < matrixSize; ++i)
	{
		for (size_t j = 0; j < matrixSize; ++j)
		{
			std::cout << m_initialMatrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

void CMatrixHandlerParallel::ShowMatrixOfCofactors() const
{
	size_t matrixSize = m_matrixOfCofactors.size();
	for (size_t i = 0; i < matrixSize; ++i)
	{
		for (size_t j = 0; j < matrixSize; ++j)
		{
			std::cout << m_matrixOfCofactors[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

void CMatrixHandlerParallel::CreateMatrixOfCofactors(size_t amountOfThreads)
{
	amountOfThreads = amountOfThreads > m_initialMatrix.size() ? m_initialMatrix.size() : amountOfThreads;
	HANDLE *handles = new HANDLE[amountOfThreads];
	int matrixSize = m_initialMatrix.size();
	std::vector<std::vector<double>> matrixOfCofactors(matrixSize, std::vector<double>(matrixSize));
	int threadIndex = 0;
	for (size_t i = 0; i < matrixSize; i++)
	{
		if (threadIndex == amountOfThreads) {
			WaitForMultipleObjects(amountOfThreads, handles, TRUE, INFINITE);
			threadIndex = 0;
		}

		auto* matrixData = new MatrixData;
		matrixData->matrix = m_initialMatrix;
		matrixData->resultMatrix = &matrixOfCofactors;
		matrixData->curRow = i;

		handles[threadIndex] = CreateThread(NULL, 0, &CreateCofactorMatrixLine, (LPVOID)matrixData, 0, NULL);
		threadIndex++;
	}

	WaitForMultipleObjects(amountOfThreads, handles, TRUE, INFINITE);
	m_matrixOfCofactors = matrixOfCofactors;
}

DWORD WINAPI CreateCofactorMatrixLine(const LPVOID data)
{
	MatrixData *matrixData = (MatrixData*)data;
	initMatrix = matrixData->matrix;
	int matrixSize = matrixData->matrix.size();
	for (int j = 0; j < matrixSize; j++)
	{
		int coeff = pow(-1, matrixData->curRow + j);
		(*(matrixData->resultMatrix))[matrixData->curRow][j] = (coeff * GetMinor(matrixData->curRow, j));
	}

	return 0;
}

double GetMinor(int row, int col)
{
	Matrix matrix = GetMinorMatrix(row, col);

	return GetDeterminant(matrix);
}

double GetDeterminant(Matrix minorMatrix)
{
	if (minorMatrix.size() == 2)
	{
		return (minorMatrix[0][0] * minorMatrix[1][1]) - (minorMatrix[0][1] * minorMatrix[1][0]);
	}

	double det = 0;
	for (int i = 0; i < minorMatrix.size(); ++i)
	{
		int prod = 1;
		int col = i;
		for (int row = 0; row < minorMatrix.size(); ++row)
		{
			prod *= minorMatrix[row][col];
			col++;
			if (col >= minorMatrix.size())
			{
				col = 0;
			}
		}

		det += prod;
	}

	for (int i = minorMatrix.size() - 1; i >= 0; --i)
	{
		int prod = 1;
		int col = i;
		for (int row = 0; row < minorMatrix.size(); ++row)
		{
			prod *= minorMatrix[row][col];
			col--;
			if (col < 0)
			{
				col = minorMatrix.size() - 1;
			}
		}

		det -= prod;
	}

	return det;
}

Matrix GetMinorMatrix(int row, int col)
{
	int matrixSize = initMatrix.size();
	Matrix tempMatrix;
	for (int i = 0; i < matrixSize; i++)
	{
		std::vector<double> line;
		for (int j = 0; j < matrixSize; j++)
		{
			if ((i != row) && (j != col))
			{
				line.push_back(initMatrix[i][j]);
			}
		}

		if (line.size() != 0)
		{
			tempMatrix.push_back(line);
		}
	}

	return tempMatrix;
}


