#include "DXUT.h"
#include "Animation.h"

namespace KMT 
{
	Animation::Animation() : _divisionWidth(0), _divisionHeight(0), _imageSize(), _centerPosition(), _speed(1), _number(0), _count(0), _currentPlayMode(SELECT_FRAME) { }

	Animation::~Animation()
	{
		_texture.reset();
	}

	void Animation::LoadTextureAndAnimation(const std::string &path, const int &divisionX, const int &divisionY, const DWORD &filter)
	{
		// �e�N�X�`���[�̓ǂݍ���
		_texture = Texture::CreateFromFile(path, filter);
		// ������񔽉f
		_divisionWidth = divisionX;
		_divisionHeight = divisionY;
		// �������1�̃T�C�Y���擾
		D3DXIMAGE_INFO info  = _texture->GetImageInfo();
		_imageSize = Vector3(((float)info.Width / _divisionWidth), ((float)info.Height / _divisionHeight), 0);
		
		// �����񐔂��L��
		int count = 0;
		int sum = divisionX * divisionY;
		// �摜��y�c�ɕ���
		for(int y = 0 ; y < divisionY ; y++){
			// �摜��x���ɕ���
			for(int x = 0 ; x < divisionX ; x++){
				// �����񐔂����������𒴂��Ă����番�����������s���Ȃ�
				if(count >= sum)	continue;
				// �����͈͂̌v�Z
				RECT rect = { 
					LONG(_imageSize.x * x), 
					LONG(_imageSize.y * y), 
					LONG(_imageSize.x * (x + 1)), 
					LONG(_imageSize.y * (y + 1)) 
				};
				// ���������i�[
				_rects.push_back(rect);
				count++;
			}
		}

		// 2D �̒��S
		const float FHALF = 0.5f;
		// �ꖇ���̕�
		float x = _imageSize.x / (float)_divisionWidth;
		float y = _imageSize.y / (float)_divisionHeight;
		_centerPosition = Vector3((x * FHALF), (y * FHALF), 0.0f);
	}

	const bool Animation::UpdateAnimation(const int &frame)
	{
		int frameSize = _rects.size();

		switch(_currentPlayMode){
			// �t���[���w��
		case SELECT_FRAME :
			if(frame < frameSize)
				_number = frame;
			else
				_number = frameSize - 1;
			return false;

			// ��x�����Đ�
		case PLAY_ONCE :
			if(frame == _count)
			{
				_count = 0;
				_number++;
			}
			else
				_count++;

			if(_number >= frameSize)
			{
				_number = frameSize - 1;
				return true;
			}
			break;

			// ���[�v�Đ�
		case PLAY_LOOP :
			if(frame == _count)
			{
				_count = 0;
				_number++;
			}
			else
				_count;

			if(_number >= frameSize)
				_number = 0;
			
			break;

		default :
			break;
		}

		return false;
	}

}