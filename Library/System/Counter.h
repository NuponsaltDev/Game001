#pragma once

#include <string>
#include <memory>
#include "../Graphics/Renderer/Sprite.h"

namespace KMT {

	class Counter ;
	typedef std::shared_ptr<Counter> CounterSP ;

	class Counter
	{
	public :
		// �񂹃^�C�v
		enum AlignState{
			// ����
			LEFT_ALIGN,	
			// �E��
			RIGHT_ALIGN	
		};

		// �R���X�g���N�^
		Counter();
		// �f�X�g���N�^
		~Counter(){ _image.reset(); }
		// ����
		static CounterSP CreateCounter() ;
		static CounterSP CreateCounter(const std::string &_path);
		/* �擾 */
		// ��_���W�̎擾�֐�
		inline const Vector3 GetPosition() const { return _position; }
		
		inline SpriteSP GetImage() const { return _image; }
		/* �ݒ� */
		// ���W
		inline void SetPosition(const Vector3& position){ _position = position; }
		inline void SetPosition(const float &x, const float &y, const float &z) { _position = Vector3(x, y, z); }
		// �`�抴�o
		inline void SetInterval(const float interval){ _interval = interval; }
		// �`��֐�
		void Render(const AlignState &type, const int &num);
		

	private :
		// �����ɑ΂��镪����
		static const int DIV_X_NUM = 10;
		// �����ɑ΂��镪����
		static const int DIV_Y_NUM = 1;
		// �\���ł��錅��
		static const int MAX_NUM = 10;

		// �����摜
		SpriteSP _image;
		// �`�悷��ۂ̊�_���W
		Vector3 _position;
		// �`��Ԋu
		float _interval;

		// �����摜�̃��[�h�֐�
		// _path : �g�p���鐔���摜�̃t�@�C����
		void LoadFromFile(const std::string& _path);
		
	};

}