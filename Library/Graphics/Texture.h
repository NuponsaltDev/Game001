//*********************************************
// DirectX�e�N�X�`�����\�[�X�Ǘ��N���X
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace KMT {

	//--------------------------------------------------------------------
	// Texture

	class Texture;

	typedef std::shared_ptr<Texture> TextureSP;
	typedef std::weak_ptr<Texture> TextureWP;

	class Texture sealed
	{
	private :
		// �e�N�X�`���̃}�b�v
		static std::unordered_map<std::string, TextureWP> _textures;
		// �����e�N�X�`���}�b�v
		static std::unordered_map<std::string, TextureWP> _stringTextures;
		// �t�@�C���p�X
		std::string _filePath;
		// �e�N�X�`���f�[�^
		LPDIRECT3DTEXTURE9 _textureData;
		// �摜���
		D3DXIMAGE_INFO _imageInfo;
		// �e�N�X�`���[�̔ԍ�
		static size_t _textureCount;

		// �R���X�g���N�^
		Texture();

	public :
		// �f�X�g���N�^
		~Texture();
		// ��̃e�N�X�`������
		// width : �������̃e�N�X�`���̕�
		// height : �������̃e�N�X�`���̍���
		static TextureSP CreateEmpty(const size_t width, const size_t height);
		// �������������܂ꂽ�e�N�X�`���̐���
		// width : �e�N�X�`���̕�
		// height : �e�N�X�`���̍���
		// color1 : �t�H���g�̃O���f�[�V�����̊J�n�F( ARGB�̘_���a�w�� )
		// color1 : �t�H���g�̃O���f�[�V�����̏I���F( ARGB�̘_���a�w�� )
		// font : �g�p����t�H���g
		// string_ : �������镶��
		// ���l : �}�b�v�o�^�L�[�̓t�H���g���{��������
		static TextureSP CreateToFont(int width, int height, int color1, int color2, const std::string font, const std::string string_);
		// ���\�[�X����̃e�N�X�`������
		// path : �t�@�C���p�X
		// filter : �t�B���^�����O�̐ݒ�
		static TextureSP CreateFromFile(const std::string &path, const DWORD filter = D3DX_FILTER_NONE);
		// �j��
		// name : �j������I�u�W�F�N�g�̖��O
		// tips : �f�t�H���g������all�őS�Ă̔z����I�u�W�F�N�g��j��
		static void Destroy(std::string name = "all");

		// �擾 : �t�@�C���p�X
		inline std::string GetFilePath() { return _filePath; }
		// �擾 : DirectX�e�N�X�`�����
		inline LPDIRECT3DTEXTURE9 GetTextureData() { return _textureData; }
		// �擾 : �C���[�W���擾
		inline D3DXIMAGE_INFO GetImageInfo() { return _imageInfo; }

	} ;

}