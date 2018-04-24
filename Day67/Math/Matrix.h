#pragma once

#include "Vector2.h"

// ��, �� 4���� ���� Matrix

namespace MyDirectX {

	class Matrix {
	private:
		class cRow {
		public:
			vector<float> vecCol;

			float& operator[](int index) { return vecCol[index]; }
			void ReSize(int nDimension) { vecCol.resize(nDimension); }
		};
	private:
		vector<cRow> vecRow;
	public:
		Matrix();
		Matrix(int nDimension);
		~Matrix();

		cRow& operator[](int nIndex);
		Matrix operator*(Matrix& mat);
		// ��ġ ��� - ��� �� �������ִ°�
		Matrix Transpose();

		// �ʱ�ȭ �����شٰ� ����� 
		static Matrix Identity(int nDimension);

		// matrix�� �̵��� vector�� �־ ��ü�� �̵���Ű�� ��
		static Matrix Translation(struct Vector2& v);
		static Matrix View(
			// eye ���� ���� ��ǥ��
			struct Vector2& eye,
			// look �ٶ� ���, ����
			struct Vector2& look,
			// camera���� ������
			struct Vector2& up);
		// z ���̰� ī�޶󿡼� near ����� far ��
		static Matrix Ortho(float left, float right, float bottom, float top, float zn, float zf);
		// ī�޶� ����ؾ��� ��ǥ��
		static Matrix Viewport(float x, float y, float w, float h, float minZ, float maxZ);
		static Matrix Rotate(float fAngle);
	private:
		void ReSize(int nDimension);
		int Dimension();
	};

}