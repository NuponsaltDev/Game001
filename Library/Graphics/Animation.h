#pragma once 

#include "Texture.h"
#include "../Math/Vector.h"

namespace KMT 
{

	// �A�j���[�V�����Đ����[�h
	enum PlayMode{
		// �t���[���w��
		SELECT_FRAME,			
		// ��x�����Đ�
		PLAY_ONCE,
		// ���[�v�Đ�
		PLAY_LOOP	
	};

	class Animation 
	{
	public :
		// �R���X�g���N�^
		Animation();
		// �f�X�g���N�^
		virtual ~Animation();

		// �e�N�X�`�����摜�t�@�C������ǂݍ���
		// path : �摜�̃t�@�C���p�X
		// divisionX : ������
		// divisionY : �c����
		void LoadTextureAndAnimation(const std::string &path, const int &divisionX = 1, const int &divisionY = 1, const DWORD &filter = D3DX_FILTER_NONE);
		
		//* �擾 *//
		// ���݂̃A�j���[�V�����ԍ����擾����
		inline int GetAnimationNumber() const { return _number; }

		//* �ݒ� *//
		// ������
		inline void SetDivisionWidth(const int &num) { _divisionWidth = num; }
		inline void SetDivisionHeight(const int &num) { _divisionHeight = num; }
		// �Đ����x
		inline void SetAnimationSpeed(int speed) { _speed = speed; }
		// �Đ����[�h
		inline void SetPlayMode(PlayMode mode) { _currentPlayMode = mode; }

		// �A�j���[�V��������
		// mode : �Đ����[�h
		// frame : �t���[����
		// �߂�l : �Đ������ۂ�(false�͍Đ����Atrue�͍Đ��I��)
		// ���l : �t���[���w�胂�[�h�̏ꍇ�͑������Ƀt���[���ԍ����A����ȊO�̃��[�h�ł͉��t���[�����ɃA�j���[�V���������邩��n��
		const bool UpdateAnimation(const int &frame = 0);

	protected :
		// �e�N�X�`���[
		TextureSP _texture;
		// ������(width:��, height:�c)
		int _divisionWidth, _divisionHeight;
		// �`��͈�
		std::vector<RECT> _rects;
		// �摜������̃T�C�Y
		Vector3 _imageSize;
		// �`�撆�S���W
		Vector3 _centerPosition;
		// �A�j���[�V�����̑���
		int _speed;
		// �\������A�j���[�V�����ԍ�
		int _number;
		// �A�j���[�V�����p�̃J�E���^
		int _count;
		// �Đ����[�h
		PlayMode _currentPlayMode;
		
	};
}