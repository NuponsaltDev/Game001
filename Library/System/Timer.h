#pragma once

#include <memory>

namespace KMT
{

	class Timer ;
	typedef std::shared_ptr< Timer > TimerSP ;

	class Timer
	{
	private :
		int _count ;	// �J�E���g
		int _time ;	// true��Ԃ�����

	public :

		// �f�t�H���g�R���X�g���N�^
		Timer() : _count(0), _time(0)
		{}

		// �R���X�g���N�^
		// arg1... true��Ԃ��܂ł̎���
		Timer(const int time) : _count( 0 ), _time( time )
		{}

		// �f�X�g���N�^
		~Timer(){}

		// �^�C�}�[��i�߂�֐�
		// ret.... [ false : �Z�b�g�������Ԃɂ͂܂��B���Ă��Ȃ� ] [ true : �Z�b�g�������ԂɒB���� ]
		// tips... �Z�b�g�������ԂɂȂ��true��Ԃ��A�J�E���g�����Z�b�g����
		const bool Count() ;

		// �^�C�}�[��i�߂�֐�����2
		// ret.... [ false : �J�E���g��0�ȊO ] [ true : �J�E���g��0 ]
		// tips... Count�֐��Ƃ͈Ⴂ�A�J�E���g��0�ɂȂ����Ƃ���true��Ԃ��B����Count�֐��Ɠ���
		const bool CountZero() ;

		// ���Ԃ��Z�b�g����֐�
		// arg1... �Z�b�g����������
		void SetTime( const int time ){ _time = time ; _count = 0 ; }

		// �J�E���g�����Z�b�g����֐�
		void ResetCount(){ _count = 0 ; }

		// ���݃Z�b�g���Ă��鎞�Ԃ��擾����֐�
		// ret.... [ �߂�l : ���݃Z�b�g���Ă��鎞�� ]
		const int GetTime() const { return _time ; }

		// ���݂̃J�E���g�̎擾�֐�
		// ret.... [ �߂�l : ���݂̃J�E���g ]
		const int GetCount() const { return _count ; }
	} ;

}