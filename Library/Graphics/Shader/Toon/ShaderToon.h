#pragma once

#include "../Shader.h"
#include <memory>

namespace KMT {

	class CTexture;
	typedef std::shared_ptr<CTexture> CTextureSP;

	class ShaderToon : public Shader
	{
	public :
		// �f�X�g���N�^
		~ShaderToon() { }
	
		// �V�F�[�_�[����
		static ShaderSP CreateShader();
		// ���f���ɑ΂���G�t�F�N�g�ݒ�
		void ApplyEffect(const CMatrix& _rotmtx, const CVector4& _campos);
	
	private :
		// �g�D�[���e�N�X�`���[
		CTextureSP ToonTexture;

		// �R���X�g���N�^
		ShaderToon();
	
	protected :
	};

}
