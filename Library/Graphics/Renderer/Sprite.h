//*********************************************
// �X�v���C�g�`��N���X
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#pragma once

#pragma warning ( disable:4238 )

#include "GraphicBehavior.h"
#include "../Animation.h"
#include <memory>

namespace KMT {

	class CSprite ;
	typedef std::shared_ptr<CSprite> CSpriteSP ;
	typedef std::weak_ptr<CSprite> CSpriteWP ;

	class CSprite : public CGraphicBehavior, public CAnimation
	{
	public :
		// �摜�̂ǂ͈̔͂�`�悷�邩
		RECT _rect;
		
		// �f�X�g���N�^
		~CSprite();

		// �e�N�X�`���̐ݒ�
		void SetTexture(const CTextureSP &texture);
		//* ���� *//
		static CSpriteSP Create();
		// �ꖇ�e�N�X�`��
		// _path : �e�N�X�`���[�̃t�@�C���p�X
		static CSpriteSP CreateFromFile(const std::string &path);
		// �A�j���[�V�����e�N�X�`��
		// path : �e�N�X�`���[�̃t�@�C���p�X
		// width : ������
		// height : �c����
		static CSpriteSP CreateFromFile(const std::string& path, const int &width, const int &height);
		//* �`�� *//
		void Render(const CCamera* camera = NULL);
		
	private :
		// DirectX3D�X�v���C�g
		LPD3DXSPRITE _sprite;
		// ���]�p�񎟌��x�N�g��
		CVector2 _turnVector;
		
		// �R���X�g���N�^
		CSprite();

	};

}