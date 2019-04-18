#pragma once
#include "stdafx.h"

using Matrix = std::vector<std::vector<double>>;

class CMatrixHandler
{
public:
	CMatrixHandler(const Matrix initialMatrix);

	void CreateMatrixOfCofactors();
	void ShowInitialMatrix() const;
	void ShowMatrixOfCofactors() const;
	~CMatrixHandler();

private:
	double GetMinor(int row, int col);
	Matrix GetMinorMatrix(int row, int col);
	double GetDeterminant(Matrix minorMatrix);

	Matrix m_initialMatrix;
	Matrix m_matrixOfCofactors;
};

