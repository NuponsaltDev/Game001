#pragma once

#include "../Shader.h"
#include <memory>

namespace KMT {

	class ShaderParticle;
	typedef std::shared_ptr<ShaderParticle> CShaderParticleSP;
	typedef std::weak_ptr<ShaderParticle> CShaderPartcleWP;

	class ShaderParticle : public Shader
	{
	public :
		// �f�X�g���N�^
		~ShaderParticle() { }
		// �V�F�[�_�[����
		static ShaderSP Create();
		// ���f���ɑ΂���G�t�F�N�g�K�p
		void ApplyEffect(const CMatrix& rotation, const CVector4& cameraPosition);

	private :
		// �R���X�g���N�^
		ShaderParticle();

	};
}