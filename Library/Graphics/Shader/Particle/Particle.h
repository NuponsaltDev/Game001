#pragma once

#include "../Shader.h"
#include <memory>

namespace KMT {

	class CShaderParticle;
	typedef std::shared_ptr<CShaderParticle> CShaderParticleSP;
	typedef std::weak_ptr<CShaderParticle> CShaderPartcleWP;

	class CShaderParticle : public Shader
	{
	public :
		// �f�X�g���N�^
		~CShaderParticle() { }
		// �V�F�[�_�[����
		static ShaderSP CreateShader();
		// ���f���ɑ΂���G�t�F�N�g�K�p
		void ApplyEffect(const CMatrix& _rotmtx, const CVector4& _campos);

	private :
		// �R���X�g���N�^
		CShaderParticle();

	};
}