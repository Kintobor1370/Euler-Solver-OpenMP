#include <cassert>
#include "Conversion.hpp"

using namespace std;


//__________________________________________________CONVERTION FUNCTIONS__________________________________________________
Vector MatrixToVector(Matrix mat, bool symmetric)
{
    Vector result;
    if (symmetric)
    {
        for (int i=0; i<mat.size(); i++)
        {
            for (int j=i; j<mat.size(); j++)
            {
                result.add(mat[i][j]);
            }
        }
    }
    else
    {
        for (int i=0; i<mat.size(); i++)
        {
            for (int j=0; j<mat.size(); j++)
            {
                result.add(mat[i][j]);
            }
        }
    }
return result;
}

Vector MatrixOfMatrixToVector(MatrixOfMatrix matOfMat, bool symmetric)
{
    Vector result;
    if (symmetric)
    {
        for (int i=0; i<matOfMat.size(); i++)
        {
            for (int j=0; j<matOfMat.size(); j++)
            {
                for (int k=0; k<matOfMat(i, j).size(); k++)
                {
                    for (int l=k; l<matOfMat(i, j).size(); l++)
                    {
                        result.add(matOfMat(i, j)[k][l]);
                    }
                }
            }
        }
    }
    else
    {
        for (int i=0; i<matOfMat.size(); i++)
        {
            for (int j=0; j<matOfMat.size(); j++)
            {
                for (int k=0; k<matOfMat(i, j).size(); k++)
                {
                    for (int l=0; l<matOfMat(i, j).size(); l++)
                    {
                        result.add(matOfMat(i, j)[k][l]);
                    }
                }
            }
        }
    }
    return result;
}

Matrix VectorToMatrix(Vector vec, int matSize, bool symmetric)
{
    int totalSize = matSize * matSize;
    if (symmetric)
    {
        for (int i=1; i<matSize; i++)
        {
            totalSize -= i;
        }
    }
    assert (vec.size() == totalSize);

    Matrix result(matSize);
    int index = 0;
    if (symmetric)
    {
        for (int i=0; i<result.size(); i++)
        {
            for (int j=i; j<result.size(); j++)
            {
                result[i][j] = vec[index];
                result[j][i] = vec[index];
                index++;
            }
        }
    }
    else
    {
        for (int i=0; i<result.size(); i++)
        {
            for (int j=0; j<result.size(); j++)
            {
                result[i][j] = vec[index];
                index++;
            }
        }
    }
    return result;
}

MatrixOfMatrix VectorToMatrixOfMatrix(
    Vector vec, 
    int matOfMatSize, 
    int matSize, 
    bool symmetric
) {
    int totalSize = matSize * matSize;
    if (symmetric)
    {
        for (int i=1; i<matSize; i++)
        {
            totalSize -= i;
        }
    }
    totalSize *= matOfMatSize * matOfMatSize;
    assert (vec.size() == totalSize);

    MatrixOfMatrix result(matOfMatSize);
    Matrix mat(matSize);
    int index = 0;
    if (symmetric)
    {
        for (int i=0; i<result.size(); i++)
        {
            for (int j=0; j<result.size(); j++)
            {
                for (int k=0; k<mat.size(); k++)
                {
                    for (int l=k; l<mat.size(); l++)
                    {
                        mat[k][l] = vec[index];
                        mat[l][k] = vec[index];
                        index++;
                    }
                }
                result(i, j) = mat;
            }
        }
    }
    else
    {
        for (int i=0; i<result.size(); i++)
        {
            for (int j=0; j<result.size(); j++)
            {
                for (int k=0; k<mat.size(); k++)
                {
                    for (int l=0; l<mat.size(); l++)
                    {
                        mat[k][l] = vec[index];
                        index++;
                    }
                }
                result(i, j) = mat;
            }
        }
    }
    return result;
}

MatrixOfFunction VectorToMatrixOfFunction(
    Vector xVec, 
    Vector yVec, 
    int matOfFuncSize
) {
    assert (yVec.size() == matOfFuncSize * matOfFuncSize * xVec.size());
    MatrixOfFunction result(matOfFuncSize);
    int index = 0;

    for (int i=0; i<result.size(); i++)
    {
        for (int j=0; j<result.size(); j++)
        {
            Vector yVals;

            for (int k=0; k<xVec.size(); k++)
            {
                yVals.add(yVec[index]);
                index++;
            }
            Function funcNew(xVec, yVals);
            result(i, j) = funcNew;
        }
    }
    return result;
    }

    bool IsSymmetric(Matrix mat)
    {
    for (int i=0; i<mat.size(); i++)
    {
        for (int j=i; j<mat.size(); j++)
        {
            if (mat[i][j] != mat[j][i])
            {
                return false;
            }
        }
    }
    return true;
}