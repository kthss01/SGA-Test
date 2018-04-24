#pragma once

#include "Vector2.h"

// 행, 열 4개씩 들어간게 Matrix

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
		// 전치 행렬 - 행과 열 뒤집어주는거
		Matrix Transpose();

		// 초기화 시켜준다고 보면됨 
		static Matrix Identity(int nDimension);

		// matrix에 이동된 vector를 넣어서 물체를 이동시키는 거
		static Matrix Translation(struct Vector2& v);
		static Matrix View(
			// eye 눈에 대한 좌표값
			struct Vector2& eye,
			// look 바라볼 대상, 방향
			struct Vector2& look,
			// camera에서 윗방향
			struct Vector2& up);
		// z 깊이값 카메라에서 near 가까운 far 먼
		static Matrix Ortho(float left, float right, float bottom, float top, float zn, float zf);
		// 카메라 출력해야할 좌표값
		static Matrix Viewport(float x, float y, float w, float h, float minZ, float maxZ);
		static Matrix Rotate(float fAngle);
	private:
		void ReSize(int nDimension);
		int Dimension();
	};

}