#include "stdafx.h"
#include "MatrixHandler.h"


CMatrixHandler::CMatrixHandler(const Matrix initialMatrix)
	: m_initialMatrix(initialMatrix)
{
}

CMatrixHandler::~CMatrixHandler()
{
}

void CMatrixHandler::ShowInitialMatrix() const
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

void CMatrixHandler::ShowMatrixOfCofactors() const
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

void CMatrixHandler::CreateMatrixOfCofactors()
{
	int matrixSize = m_initialMatrix.size();
	std::vector<std::vector<double>> matrixOfCofactors(matrixSize, std::vector<double>(matrixSize));
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			int coeff = pow(-1, i + j);
			matrixOfCofactors[i][j] = coeff * GetMinor(i, j);
		}
	}

	m_matrixOfCofactors = matrixOfCofactors;
}

double CMatrixHandler::GetMinor(int row, int col)
{
	Matrix matrix = GetMinorMatrix(row, col);

	return GetDeterminant(matrix);
}

double CMatrixHandler::GetDeterminant(Matrix minorMatrix)
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

Matrix CMatrixHandler::GetMinorMatrix(int row, int col)
{
	int matrixSize = m_initialMatrix.size();
	Matrix tempMatrix;
	for (int i = 0; i < matrixSize; i++)
	{
		std::vector<double> line;
		for (int j = 0; j < matrixSize; j++)
		{
			if ((i != row) && (j != col))
			{
				line.push_back(m_initialMatrix[i][j]);
			}
		}

		if (line.size() != 0)
		{
			tempMatrix.push_back(line);
		}
	}

	return tempMatrix;
}


