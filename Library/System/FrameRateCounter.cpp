#include "DXUT.h"
#include "FrameRateCounter.h"

const int FPSCOUNTER_QUERYPER_COUNTER = 1;
const int FPSCOUNTER_TIMEGETTIME = 2;

namespace KMT {

	FrameRateCounter::FrameRateCounter(unsigned int sample)
	{
		// �T���v�����̐ݒ�
		SetSampleNumber(sample);
		// �v�����鎞�v�̑I��
		if(QueryPerformanceCounter(&_counter) != 0)
		{
			// QueryPerformanceCounter�֐����g���t���O
			_counterFlag = FPSCOUNTER_QUERYPER_COUNTER;
			// �������̎����i�N���b�N���j���擾
			_previousCount = _counter.QuadPart;
			LARGE_INTEGER frequency;
			// 1�b������N���b�N�����擾
			QueryPerformanceFrequency(&frequency);
			_frequency = (double)frequency.QuadPart;
		}
		else
		{
			// timeGetTime�֐����g���t���O
			_counterFlag = FPSCOUNTER_TIMEGETTIME;
			// ���x���グ��
			timeBeginPeriod(1);
			// �������̎����i�~���b�j���擾
			_tgtPreviousCount = timeGetTime();
		}
		// �v��
		GetFrameRate();
	}

	FrameRateCounter::~FrameRateCounter()
	{
		if(_counterFlag == FPSCOUNTER_TIMEGETTIME)
			// �^�C�}�[�̐��x��߂�
			timeEndPeriod(1);
	}

	double FrameRateCounter::GetFrameRate()
	{
		double diff = GetCurrentDiffTime();
		// �v�Z�ł��Ȃ��̂ŕԂ�
		if (diff == 0)	return 0;

		return UpdateFrameRate(diff);
	}

	double FrameRateCounter::GetCurrentDiffTime()
	{
		// �������Ԃ��v��
		if(_counterFlag == FPSCOUNTER_QUERYPER_COUNTER)
		{
			// QueryPerformanceCounter�֐��ɂ��v��
			QueryPerformanceCounter(&_counter); // ���݂̎������擾���A
			LONGLONG diff = _counter.QuadPart - _previousCount; // �����J�E���g�����Z�o����B
			//double dDef = (double)diff; // �{���x���������_�ɕϊ�
			_previousCount = _counter.QuadPart; // ���݂̎�����ێ�
			return (double)diff * 1000 / _frequency; // �������Ԃ��~���b�P�ʂŕԂ�
		}
		// timeGetTime�֐��ɂ��v��
		DWORD CurrentTime = timeGetTime();
		DWORD CurrentDiff = CurrentTime - _tgtPreviousCount; // �����J�E���g�����Z�o����
		_tgtPreviousCount = CurrentTime; // ���݂̎�����ێ�
		return CurrentDiff;
	}

	double FrameRateCounter::UpdateFrameRate(double diff)
	{
		// �ł��Â��f�[�^������
		_diffTimeList.pop_front();
		// �V�����f�[�^��ǉ�
		_diffTimeList.push_back(diff);
		// �t���[�����[�g�Z�o
		double fps = 0.0;
		double averagingDiff = (_summationTimes + diff) / _number;
		if (averagingDiff != 0)
			fps = 1000.0 / averagingDiff;
		// ���ʉ��Z�����̍X�V
		_summationTimes += diff - *_diffTimeList.begin();
		// ���ʂ��߂�
		return fps;
	}

	void FrameRateCounter::SetSampleNumber(unsigned int sample)
	{
		// ���ς��v�Z�����
		_number = sample;
		// ���X�g������
		_diffTimeList.resize(_number, 0.0);
		_summationTimes = 0;
	}

}