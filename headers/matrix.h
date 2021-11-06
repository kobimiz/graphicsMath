#ifndef MATRIX_H
#define MATRIX_H

class Vec3;

// A 4-D matrix.
class Matrix {
private:
    static int mapTo1D(int i, int j);
    static int lengthOfWholePart(float x);
    static int longestWholePartInColumn(float* mat, int c);
    static float* multiplyMatrices(float* mat1, float* mat2);
    static float  calcCell(float* mat1, float* mat2, int i, int j);

public:
    float* data;

    Matrix ();
    Matrix (Matrix&& mat);
    Matrix (const Matrix& mat);
    ~Matrix();

    void print();

    Matrix& operator=(Matrix&& mat);
    Matrix& operator=(const Matrix& mat);
    Matrix  operator*(Matrix&& mat);
    Matrix  operator*(const Matrix& mat);
    
    static Matrix identity ();
    static Matrix scale    (float x, float y, float z, Vec3&& pivot);
    static Matrix scale    (float x, float y, float z, const Vec3& pivot);
    // NOTE not yet support for 3d rotations
    static Matrix rotate   (float angle, Vec3&& pivot);
    // NOTE not yet support for 3d rotations
    static Matrix rotate   (float angle, const Vec3& pivot);
    static Matrix translate(Vec3&& delta);
    static Matrix translate(const Vec3& delta);
};

#endif