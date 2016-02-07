#include "DXUT.h"
#include "Timer.h"

namespace KMT 
{

	// �^�C�}�[��i�߂�֐�
	const bool Timer::Count()
	{
		if( _count < _time )
		{
			++_count ;
			return false ;
		}
		else
		{
			ResetCount() ;
			return true ;
		}
	}


	// �^�C�}�[��i�߂�֐�����2
	const bool Timer::CountZero()
	{
		if( 0 == _count )
		{
			++_count ;
			return true ;
		}
		else if( _count > 0 && _count < _time )
		{
			++_count ;
			return false ;
		}
		else
		{
			ResetCount() ;
			return false ;
		}
	}

}