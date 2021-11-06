#include <cstring>
#include <cmath>
#include <iostream>

#include "../headers/matrix.h"
#include "../headers/vec3.h"

Matrix::Matrix () {
    this->data = new float[16];
}
Matrix::Matrix (Matrix&& mat) {
    delete this->data;
    this->data = mat.data;
    mat.data = nullptr;
}
Matrix::Matrix (const Matrix& mat) {
    std::memcpy(this->data, mat.data, 16 * sizeof(float));
}
Matrix::~Matrix() {
    delete this->data;
}

// TODO improve code quality
void Matrix::print() {
    for (size_t i = 0; i < 4; i++) {
		printf("[");
		for (size_t j = 0; j < 3; j++) {
			int len = Matrix::lengthOfWholePart(data[Matrix::mapTo1D(i, j)]);
			std::string x = std::string(Matrix::longestWholePartInColumn(data, j) - len, ' ') + std::string("% ") + std::string(".3f, ");
			printf(x.c_str(), data[4*i + j]);
		}
		int len = Matrix::lengthOfWholePart(data[Matrix::mapTo1D(i, 3)]);
		std::string x = std::string(Matrix::longestWholePartInColumn(data, 3) - len, ' ') + std::string("% ") + std::string(".3f ]\n");
		printf(x.c_str(), data[4*i + 3]);
	}
}

Matrix& Matrix::operator=(Matrix&& mat) {
    delete this->data;
    this->data = mat.data;
    mat.data = nullptr;
    return *this;
}
Matrix& Matrix::operator=(const Matrix& mat) {
    delete this->data;
    std::memcpy(this->data, mat.data, 16 * sizeof(float));
    return *this;
}
Matrix  Matrix::operator*(Matrix&& mat) {
    Matrix output;
    float* res = new float[16];
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			output.data[mapTo1D(i, j)] = calcCell(this->data, mat.data, i, j);
    return output;
}
Matrix  Matrix::operator*(const Matrix& mat) {
    Matrix output;
    float* res = new float[16];
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			output.data[mapTo1D(i, j)] = calcCell(this->data, mat.data, i, j);
    return output;
}

Matrix Matrix::identity () {
    Matrix res;
    float temp[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	memcpy(res.data, temp, sizeof(temp));
	return res;
}
Matrix Matrix::scale    (float x, float y, float z, Vec3&& pivot) {
    Matrix res;
    // the matrix resulting from translating to pivot, scaling and translating back
	float temp[] = {
		x   , 0.0f, 0.0f, pivot.x * (1 - x),
		0.0f, y   , 0.0f, pivot.y * (1 - y),
		0.0f, 0.0f, z   , pivot.z * (1 - z),
		0.0f, 0.0f, 0.0f, 1.0f
	};
	memcpy(res.data, temp, sizeof(temp));
	return res;
}
Matrix Matrix::scale    (float x, float y, float z, const Vec3& pivot) {
    Matrix res;
    // the matrix resulting from translating to pivot, scaling and translating back
	float temp[] = {
		x   , 0.0f, 0.0f, pivot.x * (1 - x),
		0.0f, y   , 0.0f, pivot.y * (1 - y),
		0.0f, 0.0f, z   , pivot.z * (1 - z),
		0.0f, 0.0f, 0.0f, 1.0f
	};
	memcpy(res.data, temp, sizeof(temp));
	return res;
}
Matrix Matrix::rotate   (float angle, Vec3&& pivot) {
    // TODO optimize, also in the overloaded version of this
    // TODO make this a 3d version
    Matrix trans(Matrix::translate(Vec3(-pivot.x, -pivot.y, -pivot.z)));
    Matrix backTrans(Matrix::translate(Vec3(pivot.x, pivot.y, pivot.z)));
	float rotation[] = {
		cos(angle), -sin(angle), 0.0f, 0.0f,
		sin(angle), cos(angle), 0.0f, 0.0f,
		0.0f      , 0.0f      , 1.0f, 0.0f,
		0.0f      , 0.0f      , 0.0f, 1.0f
	};
    Matrix rotationTrans;
    memcpy(rotationTrans.data, rotation, sizeof(rotation));

    rotationTrans = backTrans * (rotationTrans * trans);
	return rotationTrans;
}
Matrix Matrix::rotate   (float angle, const Vec3& pivot) {
    // TODO optimize, also in the overloaded version of this
    // TODO make this a 3d version
    Matrix trans(Matrix::translate(Vec3(-pivot.x, -pivot.y, -pivot.z)));
    Matrix backTrans(Matrix::translate(Vec3(pivot.x, pivot.y, pivot.z)));
	float rotation[] = {
		cos(angle), -sin(angle), 0.0f, 0.0f,
		sin(angle), cos(angle), 0.0f, 0.0f,
		0.0f      , 0.0f      , 1.0f, 0.0f,
		0.0f      , 0.0f      , 0.0f, 1.0f
	};
    Matrix rotationTrans;
    memcpy(rotationTrans.data, rotation, sizeof(rotation));

    rotationTrans = backTrans * (rotationTrans * trans);
	return rotationTrans;
}
Matrix Matrix::translate(Vec3&& delta) {
    Matrix res;
    float temp[] = {
		1.0f, 0.0f, 0.0f, delta.x,
		0.0f, 1.0f, 0.0f, delta.y,
		0.0f, 0.0f, 1.0f, delta.z,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	memcpy(res.data, temp, sizeof(temp));
	return res;
}
Matrix Matrix::translate(const Vec3& delta) {
    Matrix res;
    float temp[] = {
		1.0f, 0.0f, 0.0f, delta.x,
		0.0f, 1.0f, 0.0f, delta.y,
		0.0f, 0.0f, 1.0f, delta.z,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	memcpy(res.data, temp, sizeof(temp));
	return res;
}

int Matrix::mapTo1D(int i, int j) {
	return 4 * i + j;
}
float Matrix::calcCell(float* mat1, float* mat2, int i, int j) {
	float res = 0.0f;
	for (size_t k = 0; k < 4; k++)
		res += mat1[4 * i + k] * mat2[j + 4 * k];
	return res;
}
int Matrix::lengthOfWholePart(float x) {
	x = abs(x);
	if (x < 1.0f) return 1;
	else return floor(log10(x)) + 1;
}
int Matrix::longestWholePartInColumn(float* mat, int c) {
	int longest = 0;
	for (size_t i = 0; i < 4; i++) {
		int length = lengthOfWholePart(mat[c + 4*i]);
		longest = length > longest ? length : longest;
	}
	return longest;
}