#pragma once

#include "../Shader.h"
#include <memory>

namespace KMT {

	class Texture;
	typedef std::shared_ptr<Texture> TextureSP;

	class ShaderToon : public Shader
	{
	public :
		// �f�X�g���N�^
		~ShaderToon() { }
	
		// �V�F�[�_�[����
		static ShaderSP Create();
		// ���f���ɑ΂���G�t�F�N�g�ݒ�
		void ApplyEffect(const CMatrix& rotation, const CVector4& cameraPosition);
	
	private :
		// �g�D�[���e�N�X�`���[
		TextureSP _toonTexture;

		// �R���X�g���N�^
		ShaderToon();
	
	protected :
	};

}
