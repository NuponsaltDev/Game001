#pragma once

#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include <list>
using namespace std;

namespace KMT {

	class FrameRateCounter
	{
	public :
		// �R���X�g���N�^
		FrameRateCounter(unsigned int sample = 10);
		// �f�X�g���N�^
		virtual ~FrameRateCounter();

		// FPS�l���擾
		double GetFrameRate();
		// �T���v������ύX
		void SetSampleNumber(unsigned int sample);

	private :
		// �g�p����v���֐��̔���t���O
		int _counterFlag;
		// �N���b�N�J�E���g��
		LARGE_INTEGER _counter;
		// 1�b������N���b�N�J�E���g��(���g��)
		double _frequency;
		// �ȑO�̃N���b�N�J�E���g��
		LONGLONG _previousCount;
		// �ȑO�̎����i�~���b�j
		DWORD _tgtPreviousCount;
		// ���ԃ��X�g
		list<double> _diffTimeList;
		// �ړ����όv�Z���̃f�[�^��
		UINT _number;
		// ���ʕ����̍��v�l
		double _summationTimes;

	protected :
		// ���݂̎������擾
		double GetCurrentDiffTime();
		// �t���[�����[�g���X�V
		double UpdateFrameRate(double diff);

	};

}