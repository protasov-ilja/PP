#pragma once
#include "stdafx.h"

using Matrix = std::vector<std::vector<double>>;

struct MatrixData
{
public:
	Matrix* resultMatrix;
	Matrix matrix;
	size_t curRow;
};

class CMatrixHandlerParallel
{
	
public:
	CMatrixHandlerParallel(const Matrix initialMatrix);

	void CreateMatrixOfCofactors(size_t amountOfThreads);
	void ShowMatrixOfCofactors() const;
	void ShowInitialMatrix() const;
	~CMatrixHandlerParallel();

private:

	Matrix m_initialMatrix;
	Matrix m_matrixOfCofactors;
};

DWORD WINAPI CreateCofactorMatrixLine(const LPVOID data);
double GetMinor(int row, int col);
double GetDeterminant(Matrix minorMatrix);
Matrix GetMinorMatrix(int row, int col);





