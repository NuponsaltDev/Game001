#include "DXUT.h"
#include "Particle.h"

#include "../../../Support/wsb_xml.h"

namespace KMT {

	CShaderParticle::CShaderParticle() : Shader("Resources/HLSL/Particle.xml")
	{ }

	ShaderSP CShaderParticle::CreateShader()
	{
		std::string xmlPath("Resources/HLSL/Particle.xml");

		CWsbXmlSP xml = CWsbXml::LoadXmlFile(xmlPath);
		std::string path = xml->GetElement("path")->GetString();

		std::unordered_map<std::string, ShaderSP>::iterator it = _shaders.find(path);
		ShaderSP shader;
		// ���݂�������v�f��Ԃ�
		if(it != _shaders.end())
		{
			shader = (*it).second;
			return shader;
		}
		// ���݂��Ȃ���ΐV�������[�h
		shader = ShaderSP(new CShaderParticle());
		// �n�b�V���}�b�v�ɑ}��
		_shaders.insert(std::make_pair(path, shader));
		return shader;
	}

	void CShaderParticle::ApplyEffect(const CMatrix& _rotmtx, const CVector4& _campos)
	{
		return;
	}

}