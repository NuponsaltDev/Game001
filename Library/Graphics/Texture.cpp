//*********************************************
// DirectX�e�N�X�`�����\�[�X�Ǘ��N���X
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#include "DXUT.h"

#include "Texture.h"
#include "../System/Debug.h"
#include "../Extension.h"

#include <sstream>

namespace KMT {

	//-----------------------------------------------------------
	// Texture

	// static parameters
	std::unordered_map<std::string, TextureWP> Texture::_textures;
	std::unordered_map<std::string, TextureWP> Texture::_stringTextures;
	size_t Texture::_textureCount = 0;

	Texture::Texture() : _textureData( NULL )
	{}

	Texture::~Texture()
	{
		// �C�e���[�^������
		// �t�@�C���p�X�Ō���
		std::unordered_map<std::string, TextureWP>::iterator texturesIterator = _textures.find(_filePath);
		// �Y�����肾�����ꍇ
		if(texturesIterator != _textures.end())
			// map�������
			_textures.erase(texturesIterator);

		SAFE_RELEASE(_textureData);
#if _DEBUG
		OutputDebugString(L"Release Texture\n");
#endif
	}

	TextureSP Texture::CreateEmpty( const size_t width, const size_t height )
	{
			
		// �e�N�X�`���N���X�̃|�C���^��p��
		// �V�����e�N�X�`���N���X���쐻
		TextureSP object = TextureSP( new Texture() ) ;

		// width��height�̑傫���ق�����Ƃ���
		int size = width > height ? width : height ;
		int textureSize = 1 ;
		while( textureSize < size )
		{
			textureSize *= 2 ;
		}

		if ( FAILED( D3DXCreateTexture( DXUTGetD3D9Device(), 
			textureSize, 
			textureSize, 
			0, 
			D3DUSAGE_RENDERTARGET, 
			D3DFMT_A8R8G8B8, 
			D3DPOOL_DEFAULT, 
			&object->_textureData ) ) )
		{
			// �e�N�X�`���̍쐬�Ɏ��s
			// �G���[�ɑΉ�����R�[�h�������ɏ���
			//CDebug::AddString("Error : Failed to Create Texture\n"); 
		}
		// �e�N�X�`���̃T�C�Y���L�^
		object->_imageInfo.Width = textureSize ;
		object->_imageInfo.Height = textureSize ;
		// �e�N�X�`���̑������X�V
		_textureCount ++ ;
		// �e�N�X�`��No���t�@�C���p�X�̑���ɃL�[�ɂ��ă}�b�v�ɓo�^
		std::stringstream pathBuffer ;
		pathBuffer.str("");
		pathBuffer << _textureCount << ":" << width << height ;
		std::string path = pathBuffer.str().c_str() ;
		// �t�@�C���p�X��ێ�
		object->_filePath = path;
		// �}�b�v�ɓo�^
		_textures.insert( std::make_pair( path, TextureWP( object ) ) ) ;

		return object ;
	}


	TextureSP Texture::CreateToFont( int width, int height, int color1, int color2, const std::string font, const std::string string_ ) 
	{
		std::stringstream texturePath("") ;
		texturePath << font << string_ ;
		// ���ɂ��̃e�N�X�`���[�����݂���ꍇ�A�Ԃ�
		std::unordered_map<std::string, TextureWP>::iterator texturesIterator = _textures.find( texturePath.str() ) ;
		if(texturesIterator != _textures.end())
			return texturesIterator->second.lock();
		//-------------------------------------------------------------------------------
		// �t�H���g�T�C�Y�̓|���S���ˑ�
		int fontSize = ((width + height) >> 1);
		fontSize = (fontSize <= 32) ? 32 : fontSize;
		int length = 0;

		WCHAR fontBuffer[LF_FACESIZE] = {0};
		DXconvAnsiToWide(fontBuffer, font.c_str(), (font.length()+1));
		// �t�H���g���ݒ�
		LOGFONT logFont = {fontSize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
			CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, 0};
		
		memcpy(logFont.lfFaceName, fontBuffer, sizeof(WCHAR)*LF_FACESIZE);

		HFONT hFont = CreateFontIndirect(&logFont);
		if(!(hFont))
			MessageBox(NULL, TEXT("Error : Failed to create string texture"), NULL, MB_OK | MB_ICONSTOP);

		WCHAR stringBuffer[256] = {0};
		DXconvAnsiToWide(stringBuffer, string_.c_str(), (string_.length() + 1));

		TCHAR *c = stringBuffer;
		length = (int)wcslen(c);
		//-------------------------------------------------------------------------------
		// �f�o�C�X�R���e�L�X�g�擾
		// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
		HDC hdc = GetDC(NULL);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
		//-----------------------------------------------------------------------------------------------
		LPDIRECT3DTEXTURE9 pWkTex = NULL;
		TextureSP object = TextureSP(new Texture());
		//-----------------------------------------------------------------------------------------------
		for(int i = 0; i < 1; i++){
			//-------------------------------------------------------------------------------
			// 1 �����R�[�h�擾
			size_t code = 0;
#if _UNICODE
			// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
			code = (UINT)*c;
#else
			// �}���`�o�C�g�����̏ꍇ�A
			// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
			// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
			if( IsDBCSLeadByte( *c ) ){
				code = (BYTE)c[0]<<8 | (BYTE)c[1];
				c += 2;
			}else{
				code = c[0];
				c++;
			}
#endif	
			//-------------------------------------------------------------------------------
			// �t�H���g�r�b�g�}�b�v�擾
			TEXTMETRIC TM;
			GetTextMetrics(hdc, &TM);
			GLYPHMETRICS GM;
			CONST MAT2 Mat = {{0,1}, {0,0}, {0,0}, {0,1}};

			//DWORD size = GetGlyphOutline( hdc, code, GGO_BITMAP, &GM, 0, NULL, &Mat ) ;			
			//DWORD size = GetGlyphOutline( hdc, code, GGO_GRAY2_BITMAP, &GM, 0, NULL, &Mat ) ;
			//DWORD size = GetGlyphOutline( hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat ) ;
			DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY8_BITMAP, &GM, 0, NULL, &Mat);

			BYTE *ptr = new BYTE[size];

			//BYTE *ptr = ( BYTE* )T2Malloc( sizeof( BYTE ) * size ) ;
			//GetGlyphOutline( hdc, code, GGO_BITMAP, &GM, size, ptr, &Mat ) ;
			//GetGlyphOutline( hdc, code, GGO_GRAY2_BITMAP, &GM, size, ptr, &Mat ) ;
			//GetGlyphOutline( hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat ) ;
			GetGlyphOutline(hdc, code, GGO_GRAY8_BITMAP, &GM, size, ptr, &Mat);
			//---------------------------------------------------------------
			// �e�N�X�`���쐬
			D3DLOCKED_RECT LockedRect;

			if(FAILED(DXUTGetD3D9Device()->CreateTexture(GM.gmCellIncX,
				TM.tmHeight,
				1,
				D3DUSAGE_DYNAMIC,
				D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&pWkTex,
				NULL))){
					MessageBox(NULL, TEXT(" !! Font Create Err 02 !! "), NULL, MB_OK | MB_ICONSTOP);
			}

			if(FAILED(pWkTex->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD))){
				MessageBox(NULL, TEXT(" !! Font Create Err 03 !! "), NULL, MB_OK | MB_ICONSTOP);
			}
			//---------------------------------------------------------------
			// �t�H���g���̏�������
			// iOfs_x, iOfs_y : �����o���ʒu(����)
			// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
			// Level : ���l�̒i�K (GGO_GRAY4_BITMAP��17�i�K�AGGO_GRAY8_BITMAP��65�i�K)
			int iOfs_x = GM.gmptGlyphOrigin.x;
			int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
			int iBmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX%4)) % 4;
			int iBmp_h = GM.gmBlackBoxY;
			int level = 65;
			int x, y;
			DWORD alpha, color;

			FillMemory(LockedRect.pBits , LockedRect.Pitch * TM.tmHeight, 0);

			for(y = iOfs_y; y < iOfs_y+iBmp_h; y++){
				for(x = iOfs_x; x < iOfs_x+iBmp_w; x++){
					//--------------------------------------------------------------
					// �m�[�}���t�H���g
					//if( T2FONT_ANTIALIAS & FLG ){
					//	Alpha = ( 255 * ptr[ x-iOfs_x + iBmp_w * ( y-iOfs_y ) ] ) / ( Level-1 ) ;
					//}else{
					//	Alpha = ( 0 == ptr[ x-iOfs_x + iBmp_w * ( y-iOfs_y ) ] )? 0 : 255 ;
					//}

					alpha = (DWORD)ptr[ x-iOfs_x + iBmp_w * ( y-iOfs_y ) ] ;
					alpha = alpha * ( 256 / ( level - 1 ) ) ;
					if( alpha > 255 )
						alpha = 255 ;
					//Alpha = ( 0 == ptr[ x-iOfs_x + iBmp_w * ( y-iOfs_y ) ] )? 0 : 255 ;
					{
						int wkY = ( iOfs_y + iBmp_h ) ;
						int wkStR = ( color1 & 0x00ff0000 )>>16 ;
						int wkStG = ( color1 & 0x0000ff00 )>>8 ;
						int wkStB = ( color1 & 0x000000ff ) ;

						int wkEnR = ( color2 & 0x00ff0000 )>>16 ;
						int wkEnG = ( color2 & 0x0000ff00 )>>8 ;
						int wkEnB = ( color2 & 0x000000ff ) ;

						int wkSubR = wkStR - wkEnR ;
						int wkSubG = wkStG - wkEnG ;
						int wkSubB = wkStB - wkEnB ;

						float wkAddR = ( (float)wkSubR / (float)wkY ) ;
						float wkAddG = ( (float)wkSubG / (float)wkY ) ;
						float wkAddB = ( (float)wkSubB / (float)wkY ) ;

						int wkR = wkStR - (int)( y * wkAddR ) ;
						int wkG = wkStG - (int)( y * wkAddG ) ;
						int wkB = wkStB - (int)( y * wkAddB ) ;
						color = D3DCOLOR_ARGB( 0, wkR, wkG, wkB ) | ( alpha << 24 ) ;
						memcpy( ( BYTE* )LockedRect.pBits + LockedRect.Pitch*y + 4*x, &color, sizeof(DWORD) ) ;
					}
				}
			}

			pWkTex->UnlockRect( 0 ) ;

			delete[] ptr;		

		}

		//D3DXVECTOR3 v1( -( width * 0.5f ),  ( height * 0.5f ), 0.0f ) ;
		//D3DXVECTOR3 v2(  ( width * 0.5f ),  ( height * 0.5f ), 0.0f ) ;
		//D3DXVECTOR3 v3(  ( width * 0.5f ), -( height * 0.5f ), 0.0f ) ;
		//D3DXVECTOR3 v4( -( width * 0.5f ), -( height * 0.5f ), 0.0f ) ;
		//CreateSprite( v1, v2, v3, v4, NULL ) ;

		//-------------------------------------------------------------------------------
		// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
		SelectObject( hdc, oldFont ) ;
		DeleteObject( hFont ) ;
		ReleaseDC( NULL, hdc ) ;	

		//*ppFont = pWkFont ;
		//pWkFont->Init( pStr ) ;

		object->_textureData = pWkTex ;
		object->_imageInfo.Width = fontSize ;

		_stringTextures.insert(make_pair(texturePath.str(), TextureWP(object)));

		return object ;

	}

	TextureSP Texture::CreateFromFile(const std::string &path, const DWORD filter)
	{
		TextureSP object;
		std::stringstream filePathBuffer;
		filePathBuffer.str("");
		filePathBuffer << path << "Filter : " << filter;
		std::string filePath = filePathBuffer.str().c_str();

		std::unordered_map<std::string, TextureWP>::iterator texturesIterator = _textures.find(filePath);
		// �Y�������������ꍇ
		if(texturesIterator == _textures.end())
		{
			object = TextureSP(new Texture());

			object->_filePath = filePath;
			// �t�@�C���p�X�����C�h�����ɕϊ�����
			WCHAR pathBuffer[256] = {0} ;
			DXconvAnsiToWide( pathBuffer, path.c_str(), ( path.length() + 1 ) ) ;

			// �e�N�X�`���̃��[�h
			D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(),
				// �t�@�C���p�X
				pathBuffer,			
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				D3DPOOL_DEFAULT,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				// �t�B���^�[
				filter,
				D3DX_DEFAULT,
				// �����F�̎w�� �S��0�w��ŃJ���[�L�[�Ȃ�
				D3DXCOLOR(0,0,0,0),	
				// �摜���̎擾
				&object->_imageInfo,		
				NULL,
				// �e�N�X�`���̎󂯎��
				&object->_textureData			
				);

			// �}�b�v�ɓo�^
			_textures.insert(std::make_pair(filePath, TextureWP(object)));
		// �Y�����肾�����ꍇ
		}
		else
			// �쐬�ς݂̃e�N�X�`���N���X�̃|�C���^���擾
			object = TextureSP((*texturesIterator).second);	

		return object;
	}

	void Texture::Destroy(std::string name) 
	{
		// �C�e���[�^��p��
		// �C�e���[�^���n�b�V���}�b�v�̐擪�ɃZ�b�g
		std::unordered_map<std::string, TextureWP>::iterator texturesIterator = _textures.begin() ; 
		// �S�����
		if( name == "all" ){
			while(texturesIterator != _textures.end())
			{
				(*texturesIterator).second.reset();
				_textures.erase(texturesIterator++);
			}
		}
		else
			// �e�N�X�`�����P�������
		{
			texturesIterator = _textures.find(name);
			if(texturesIterator != _textures.end())
			{
				(*texturesIterator).second.reset();
				_textures.erase(texturesIterator);
			}
		}
	}

}