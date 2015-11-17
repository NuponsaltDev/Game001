#pragma once

#include "../Math/Vector.h"

namespace KMT {

	// ���_���
	class Vertex
	{
	public :
		// ���_���W
		Vector3 _position;
		// �@��
		Vector3 _normal;
		// ���_�J���[
		DWORD	 _color;
		// �e�N�Z�����W
		Vector2 _uv;

		// �萔FVF
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;

		// �R���X�g���N�^
		Vertex() : _position(0, 0, 0), _normal(0, 1, 0), _uv(0, 0), _color(0xFFFFFFFF) { }

	};

	struct SCREEN_VERTEX
	{
		// XYZRHW
		float _x, _y, _z, _rhw ;

		//DIFFUSE
		DWORD _color ;

		// TEX1
		float _u, _v ;

		static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ;
	} ;

}