#include "stdafx.h"
#include "Matrix.h"

namespace MyDirectX {
	Matrix::Matrix() {

	}

	Matrix::Matrix(int nDimension)
	{
		ReSize(nDimension);
	}

	Matrix::~Matrix() {

	}

	Matrix::cRow & Matrix::operator[](int nIndex)
	{
		return vecRow[nIndex];
	}

	Matrix Matrix::operator*(Matrix & mat)
	{
		Matrix ret(Dimension());
		for (int i = 0; i < Dimension(); i++) {
			for (int j = 0; j < Dimension(); j++) {
				ret[i][j] = 0.0f;
				for (int k = 0; k < Dimension(); k++) {
					ret[i][j] += (*this)[i][k] * mat[k][j];
				}
			}
		}
		return ret;
	}

	Matrix Matrix::Transpose()
	{
		Matrix ret(Dimension());
		for (int i = 0; i < Dimension(); i++) {
			for (int j = 0; j < Dimension(); j++) {
				ret[i][j] = (*this)[j][i];
			}
		}
		return ret;
	}

	Matrix Matrix::Identity(int nDimension)
	{
		Matrix ret(nDimension);
		for (int i = 0; i < nDimension; i++) {
			for (int j = 0; j < nDimension; j++) {
				ret[i][j] = (i == j) ? 1 : 0;
			}
		}
		return ret;
	}

	Matrix Matrix::Translation(Vector2& v)
	{
		Matrix mat = Matrix::Identity(4);

		mat[3][0] = v.x;
		mat[3][1] = v.y;

		return mat;
	}

	Matrix Matrix::View(Vector2 & eye, Vector2 & look, Vector2 & up)
	{
		Matrix mat = Matrix::Identity(4);

		Vector2 l = (look - eye).Normalize();
		Vector2 r = Vector2::Cross(up, l).Normalize();
		Vector2 u = Vector2::Cross(l, r).Normalize();

		mat[0][0] = r.x; mat[0][1] = u.x; mat[0][2] = l.x;
		mat[1][0] = r.y; mat[1][1] = u.y; mat[1][2] = l.y;
		mat[1][0] = r.z; mat[2][1] = u.z; mat[2][2] = l.z;

		mat[3][0] = -Vector2::Dot(r, eye);
		mat[3][1] = -Vector2::Dot(u, eye);
		mat[3][2] = -Vector2::Dot(l, eye);

		return mat;
	}

	Matrix Matrix::Ortho(float left, float right, float bottom, float top, float zn, float zf)
	{
		// Ư���Ѱ� �ƴϸ� ViewPort�� �ٸ��� ���� �����
		Matrix mat = Matrix::Identity(4);

		// x �������� �Ǿ��ִ� ���̰�
		// �� �࿡ ���� ũ�Ⱚ��
		mat[0][0] = 2 / (right - left);
		mat[1][1] = 2 / (bottom - top);
		mat[2][2] = 1 / (zf - zn);

		mat[3][0] = (right + left) / (right - left);
		// ��ġ���� ��Ÿ�� �ִ� �༮ ȭ���� �߽����� �Ҳ���
		mat[3][1] = (bottom + top) / (bottom - top);
		mat[3][2] = zn / (zn - zf);

		return mat;
	}

	Matrix Matrix::Viewport(float x, float y, float w, float h, float minZ, float maxZ)
	{
		Matrix mat = Matrix::Identity(4);

		mat[0][0] = w / 2.0f;
		mat[1][1] = -h / 2.0f;
		mat[2][2] = maxZ - minZ;
		// ȭ���� �߽��� x
		mat[3][0] = x + w / 2.0f;
		// ȭ���� �߽��� y
		mat[3][1] = y + h / 2.0f;
		mat[3][2] = minZ;

		return mat;
	}

	Matrix Matrix::Rotate(float fAngle)
	{
		Matrix mat = Matrix::Identity(4);

		mat[0][0] = cosf(fAngle);
		mat[0][1] = sinf(fAngle);
		mat[1][0] = -sinf(fAngle);
		mat[1][1] = cosf(fAngle);

		return mat;
	}

	void Matrix::ReSize(int nDimension)
	{
		vecRow.resize(nDimension);
		for (int i = 0; i < nDimension; i++) {
			vecRow[i].ReSize(nDimension);
		}
	}

	int Matrix::Dimension()
	{
		return vecRow.size();
	}
}