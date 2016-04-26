#include "stdafx.h"

#include "video/video_instance.h"
#include "engine.h"
#include "d3d/direct_3d.h"
#include "sprite/sprite.h"
#include "vfw.h"
#include "texture/texture.h"
#include "sprite/textured_quad.h"
#include "math/vector2.h"
#include "texture/texture_manager.h"
#include <stdio.h>
#include <comutil.h>
#include <thread>
#include <d3d11.h>


#pragma comment(lib,"WMVCORE.lib")

#pragma pack(2)

using namespace DX2D;
CVideoInstance::CVideoInstance()
{

	myFailedResource = nullptr;

	mySprite = new CSprite(nullptr);

	mySyncReader = NULL;
	m_qwCurrrentPostionInSeconds = 0;
	m_qwTotalTimeInSeconds = 0;
	myBuffer = nullptr;
	myCanChangeFrame = false;
	myIsRenderingFrame = false;
	myIsInitialized = false;
	myShouldStopThread = false;
	myThreadIsDone = true;
	myOpenSuccesfully = false;
	myIsStreamDone = false;
}


CVideoInstance::~CVideoInstance()
{

	Release();
}

void CVideoInstance::Release()
{
	myShouldStopThread = true;
	SAFE_RELEASE(myTexture);
	SAFE_RELEASE(myFailedResource);

	if (myCruncherThread)
	{
		myCruncherThread->join();
		delete myCruncherThread;
		myCruncherThread = nullptr;
	}

	if (mySprite)
	{
		delete mySprite;
		mySprite = nullptr;
	}
}


bool CVideoInstance::Init(LPCWSTR lpszFileName)
{
	myFileName = lpszFileName;
	return true;
}

// THREADED, NO TOUCH
int CVideoInstance::NextFrame()
{
	HRESULT hr = S_OK;
	QWORD cnsSampleTime = 0;
	QWORD cnsSampleDuration = 0;
	DWORD dwFlags = 0;
	if (!mySyncReader)
	{
		return 0;
	}

	INSSBuffer* iNSSBuffer;
	hr = mySyncReader->GetNextSample(myVideoStreamNumber,
		&iNSSBuffer,
		&cnsSampleTime,
		&cnsSampleDuration,
		&dwFlags,
		NULL,//&dwOutputNumber,
		NULL);
	if (hr == NS_E_NO_MORE_SAMPLES)
	{
		//no more samples to read in file
		myIsStreamDone = true;
		return 0;
	}

	
	if (SUCCEEDED(hr))
	{
		// TODO: Process the sample in whatever way is appropriate 
		// to your application. When finished, clean up.
		if (dwFlags == WM_SF_CLEANPOINT) //this a clean point frame, a picture to take read sdk for explantion 
		{
			//					AfxMessageBox("found new sample");
			//1. Get the Bitmap from the frame
			//BYTE* meir;
			unsigned char *buffer;
			iNSSBuffer->GetBufferAndLength(&buffer, &myDwrdBitmapBufferLength);
			if (myBitmapBuffer == NULL)
			{
				myBitmapBuffer = new unsigned char[myDwrdBitmapBufferLength];
			}
			memcpy(myBitmapBuffer, buffer, myDwrdBitmapBufferLength);
			//calc the current postion in seconds
			m_qwCurrrentPostionInSeconds = (cnsSampleTime * 100) / 1000000000;
			myFramesRead++;


		}
		iNSSBuffer->Release();
		iNSSBuffer = NULL;
	}

	return 1;
}

unsigned long createRGB(BYTE iB, BYTE iG, BYTE iR, BYTE iA)
{
	return ((iA * 256 + iR) * 256 + iG) * 256 + iB;
}

#ifndef DibNumberColors
#define DibNumColors( lpbi ) ( ( lpbi )->biClrUsed == 0 && ( lpbi )->biBitCount <= 8 ) ? (( int )( 1 << ( int )( lpbi )->biBitCount ))  : (( int )(( lpbi )->biClrUsed )) 
#endif

#ifndef DibPaletteSize
#define DibPaletteSize( lpbi ) ( DibNumColors( lpbi ) * sizeof( RGBQUAD ) ) 
#endif
#ifndef BFT_BITMAP
#define BFT_BITMAP 0X4D42
#endif


#define Uint8 unsigned char
void DX2D::CVideoInstance::Render()
{
	if (!myIsInitialized)
	{
		return;
	}

	if (mySprite)
	{
		mySprite->Render();
	}

	if (myFailedResource)
	{	
		myTexture->Release();
		myTexture = nullptr;
		myFailedResource->Release();
		myFailedResource = nullptr;
	}
	
	if (!myFailedResource)
	{
		D3D11_TEXTURE2D_DESC texture_desc;
		D3D11_SUBRESOURCE_DATA tbsd;
		tbsd.pSysMem = (void *)myBuffer;
		tbsd.SysMemPitch = myWidth * 4;


		texture_desc.Width = myWidth;
		texture_desc.Height = myHeight;
		texture_desc.MipLevels = 1;
		texture_desc.ArraySize = 1;
		texture_desc.MipLevels = 1;
		texture_desc.ArraySize = 1;

		texture_desc.SampleDesc.Count = 1;
		texture_desc.SampleDesc.Quality = 0;
		texture_desc.Usage = D3D11_USAGE_DYNAMIC;
		texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		texture_desc.MiscFlags = 0;

		// TODO update instead
		CEngine::GetInstance()->GetDirect3D().GetDevice()->CreateTexture2D(&texture_desc, &tbsd, &myTexture);
		CEngine::GetInstance()->GetDirect3D().GetDevice()->CreateShaderResourceView(myTexture, NULL, &myFailedResource);
	}
	

	mySprite->GetTexturedQuad()->myTexture->myResource = myFailedResource;
	
	DX2D::Vector2f texSize = CEngine::GetInstance()->GetTextureManager().GetTextureSize(myFailedResource);

	mySprite->SetSize(DX2D::Vector2f(texSize.x, -texSize.y));

}

void DX2D::CVideoInstance::Play()
{
	if (myThreadIsDone)
	{
		myCruncherThread = new std::thread(CVideoInstance::StartCruncher, this);
	}
	else
	{
		myShouldStopThread = false;
	}
	
}

void DX2D::CVideoInstance::Stop()
{
	myShouldStopThread = true;
}


bool DX2D::CVideoInstance::IsDone()
{
	return myIsStreamDone;
}

std::mutex DX2D::CVideoInstance::g_pages_mutex;
void CVideoInstance::StartCruncher(CVideoInstance* aInstance)
{
	aInstance->myThreadIsDone = false;
	::CoInitialize(nullptr);
	HRESULT hr;
	hr = WMCreateSyncReader(NULL, 0, &aInstance->mySyncReader);
	if (hr != S_OK)
	{
		INFO_PRINT("%s", "Error: Could not create WMCreateSyncReader, video can not be played!");
		return;
	}
	//Step 2: Open the file
	//note: When the synchronous reader opens the file, it assigns an output number to each stream

	hr = aInstance->mySyncReader->Open(aInstance->myFileName);
	if (hr != S_OK)
	{
		INFO_PRINT("%s%ls", "Error: Could not open file, video can not be played! ", aInstance->myFileName);
		return;
	}


	aInstance->mySyncReader->GetOutputCount(&aInstance->mytheOutputsCount);

	int videoIndex = 0;
	DWORD theSize;
	IWMOutputMediaProps* videoOutputProps = nullptr;
	for (unsigned int i = 0; i<aInstance->mytheOutputsCount; i++)
	{
		SAFE_ARRAYDELETE(aInstance->mytheMediaType);
		aInstance->mySyncReader->GetOutputProps(i, &videoOutputProps);
		hr = videoOutputProps->GetMediaType(NULL, &theSize);
		aInstance->mytheMediaType = (WM_MEDIA_TYPE*) new BYTE[theSize];
		hr = videoOutputProps->GetMediaType(aInstance->mytheMediaType, &theSize);

		if (FAILED(hr))
		{
			INFO_PRINT("%s%s", "Error: Could not query for the space needed for media type, video can not be played!", aInstance->myFileName);
			return;
			//_tcscpy( tszErrMsg, _T( "Could not query for the space needed for media type" ) );
			//break;
		}

		if (WMMEDIATYPE_Video == aInstance->mytheMediaType->majortype)//pMediaType->majortype )
		{
			videoIndex = i;
			aInstance->mySyncReader->GetStreamNumberForOutput(videoIndex, (WORD*)&aInstance->myVideoStreamNumber);

			if (aInstance->mytheMediaType->formattype == WMFORMAT_VideoInfo)
			{
				//setting the bitmapInfoHeader by reading the WmvInfoHeader
				memcpy(&aInstance->myTheVideoInfoHeader, aInstance->mytheMediaType->pbFormat, sizeof(WMVIDEOINFOHEADER));
				aInstance->myBitmapInfoHdr = aInstance->myTheVideoInfoHeader.bmiHeader;

				aInstance->myWidth = aInstance->myBitmapInfoHdr.biWidth;
				aInstance->myHeight = aInstance->myBitmapInfoHdr.biHeight;

				WORD bitCount = aInstance->myBitmapInfoHdr.biBitCount;
				aInstance->myBytes_per_pixel = bitCount / 8;


				unsigned int rowSize = (bitCount * aInstance->myBitmapInfoHdr.biWidth + 7) / 8; // +7 to round up
				if (rowSize % 4)
					rowSize += (4 - (rowSize % 4)); // Pad to DWORD Boundary

				aInstance->myRow_increment = rowSize;// theInfoHeader.biWidth * bytes_per_pixel_;

			}


		}
		if (WMMEDIATYPE_Audio == aInstance->mytheMediaType->majortype)
		{
			aInstance->myAudioOutputNumber = i;
			aInstance->mySyncReader->GetStreamNumberForOutput(aInstance->myAudioOutputNumber, (WORD*)&aInstance->m_iAudioStreamNumber);
		}

	}
	//relesae the memory
	SAFE_RELEASE(videoOutputProps);
	videoOutputProps = nullptr;
	SAFE_ARRAYDELETE(aInstance->mytheMediaType);

	BYTE* pValue = new BYTE[5];
	strcpy((char*)pValue, "TRUE");
	hr = aInstance->mySyncReader->SetOutputSetting(videoIndex, g_wszVideoSampleDurations, WMT_TYPE_BOOL, pValue, sizeof(pValue));
	delete[]pValue;
	if (FAILED(hr))
	{
		INFO_PRINT("%s%s", "Error: Could not set Video Ouptut Sample durations, video can not be played!", aInstance->myFileName);
		return;
		//AfxMessageBox("could not set Video Ouptut Sample durations");
	}


	hr = aInstance->mySyncReader->SetReadStreamSamples(aInstance->myVideoStreamNumber, FALSE);
	if (FAILED(hr))
	{
		INFO_PRINT("%s%s", "Error: Could not set Video Stream to give Uncompressed Samples, video can not be played!", aInstance->myFileName);
		return;
		//AfxMessageBox("could not set Video Stream to give Uncompressed Samples");
	}

	IWMMetadataEditor *pEditor;

	hr = WMCreateEditor(&pEditor);
	if (hr == S_OK)
	{
		pEditor->Open(aInstance->myFileName);
		IWMHeaderInfo3* pHdrInfo;
		pHdrInfo = NULL;
		hr = pEditor->QueryInterface(IID_IWMHeaderInfo3, (void**)&pHdrInfo);
		WORD wStream = 0;
		WMT_ATTR_DATATYPE dType;
		QWORD dwDuration;
		WORD wSize = 0;
		hr = pHdrInfo->GetAttributeByName(&wStream, L"Duration", &dType, (BYTE*)NULL, &wSize);

		BYTE* pValue = nullptr;
		if (wSize > 0)
		{
			pValue = new BYTE[wSize];
			hr = pHdrInfo->GetAttributeByName(&wStream, L"Duration", &dType, pValue, &wSize);
			dwDuration = *((QWORD*)pValue);
			aInstance->m_qwTotalTimeInSeconds = (dwDuration * 100) / 1000000000;
			SAFE_ARRAYDELETE(pValue);
			SAFE_RELEASE(pHdrInfo);
			SAFE_RELEASE(pEditor);
		}

	}
	aInstance->myOpenSuccesfully = true;
	StartUpdateLoop(aInstance);
}

void CVideoInstance::StartUpdateLoop(CVideoInstance* aInstance)
{
	aInstance->myThreadIsDone = false;
	int *buffer = new int[(aInstance->myHeight*aInstance->myWidth)];


	while (!aInstance->myShouldStopThread)
	{
		aInstance->NextFrame();
		if (!aInstance->myBitmapBuffer)
		{
			return;
		}


		for (int i = 0; i < aInstance->myHeight; i++)
		{
			for (int j = 0; j < aInstance->myWidth; j++)
			{
				unsigned char red = 0;
				unsigned char green = 0;
				unsigned char blue = 0;
				aInstance->get_pixel(j, i, red, green, blue);

				long hexRGB = createRGB(red, green, blue, 255);
				buffer[i*aInstance->myWidth + j] = hexRGB;
			}

		}

		g_pages_mutex.lock();

		aInstance->myBuffer = buffer;
		aInstance->myIsInitialized = true;

		g_pages_mutex.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		
	}
	if (aInstance->myBitmapBuffer)
		delete[] aInstance->myBitmapBuffer;
	aInstance->myBitmapBuffer = NULL;
	SAFE_RELEASE(aInstance->mySyncReader);
	delete[] buffer;
	aInstance->myThreadIsDone = true;

	::CoUninitialize();
}

void CVideoInstance::get_pixel(const unsigned int x, const unsigned int y, unsigned char& red, unsigned char& green, unsigned char& blue)
{
	const unsigned int y_offset = y * myRow_increment;
	const unsigned int x_offset = x * myBytes_per_pixel;
	blue = myBitmapBuffer[y_offset + x_offset + 0];
	green = myBitmapBuffer[y_offset + x_offset + 1];
	red = myBitmapBuffer[y_offset + x_offset + 2];
}

int CVideoInstance::SaveCurrentFrameToBmp(char* filename)
 {
	ULONG theFileLen = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + myBitmapInfoHdr.biSizeImage;
	BITMAPFILEHEADER theFileHeader = { 'BM', theFileLen, 0, 0, (sizeof(BITMAPFILEHEADER) + myBitmapInfoHdr.biSize + DibPaletteSize(&myBitmapInfoHdr)) };// };
	theFileHeader.bfType = BFT_BITMAP;// 0X4D42;
	BITMAPINFOHEADER theInfoHeader = myBitmapInfoHdr;
	FILE *theFile = fopen(filename, "w");
	fwrite(&theFileHeader, sizeof(BITMAPFILEHEADER), 1, theFile);
	fwrite(&theInfoHeader, sizeof(BITMAPINFOHEADER), 1, theFile);
	fwrite(myBitmapBuffer, myDwrdBitmapBufferLength, 1, theFile);
	fclose(theFile);

	return 0;
 }