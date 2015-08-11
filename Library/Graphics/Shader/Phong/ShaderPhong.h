#pragma once

#include "../Shader.h"

namespace KMT {

	class ShaderPhong : public Shader
	{
	public :
		// �f�X�g���N�^
		~ShaderPhong() { }

		// ����
		static ShaderSP CreateShader();
		// ���f���ɑ΂���G�t�F�N�g�K�p
		void ApplyEffect(const CMatrix& rotation, const CVector4& cameraPosition);

	private :
		// �R���X�g���N�^
		ShaderPhong();

	protected :
	};

}