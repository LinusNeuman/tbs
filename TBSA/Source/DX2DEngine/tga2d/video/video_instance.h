/*
This class is the internal logic for playing a video
*/

#pragma once
#include <wtypes.h>
#include <wmsdk.h>
#include <thread>
#include <mutex>

#define MAX_AUDIO_STREAMS 5
#define MAX_VIDEO_STREAMS 5

namespace DX2D
{
	class CSprite;
	class CVideoInstance
	{
	public:
		CVideoInstance();
		~CVideoInstance();
		void Release();

		bool Init(LPCWSTR lpszFileName);
		void Render();

		void Play();
		void Stop();
		bool IsDone();
		CSprite* mySprite;
	private:
		
		int NextFrame();
		IWMSyncReader* mySyncReader;// opens the file and gets all its properties
		// this is an INSSBuffer (an Interface)  that when reading from a stream gets the data, then there is another step to retrive the daa from this Interfaced buffer
		
		// this interface can receive the properties of a specific output in the wmv file
		
		WM_MEDIA_TYPE* mytheMediaType;
		// this struct would hold the information about the bitmaps extracted from the video stream
		BITMAPINFOHEADER myBitmapInfoHdr;
		WMVIDEOINFOHEADER myTheVideoInfoHeader;
		// this is the original bitmap extracted from the file, the gray is m_grayBitmapBuffer
		BYTE* myBitmapBuffer;
		// this contains the original(no manipulations straight from the file)  bitmapBuffer length
		DWORD myDwrdBitmapBufferLength;
		HRESULT hr;
		DWORD mytheOutputsCount;
		int myAudioOutputNumber;
		WORD myVideoStreamNumber;
		int m_iAudioStreamNumber;
		QWORD m_qwTotalTimeInSeconds;
		QWORD m_qwCurrrentPostionInSeconds;
		int myFramesRead;
		bool myIsStreamOpen;
		bool myOpenSuccesfully;
		bool myThreadIsDone;

		
		
		

		void get_pixel(const unsigned int x, const unsigned int y, unsigned char& red, unsigned char& green, unsigned char& blue);
		int SaveCurrentFrameToBmp(char* filename);
		int myRow_increment;

		std::thread* myCruncherThread;
		static std::mutex g_pages_mutex;
		int myWidth;
		int myHeight;
		int myBytes_per_pixel;

		int *myBuffer;

		ID3D11ShaderResourceView* myFailedResource;
		ID3D11Texture2D *myTexture;
		bool myCanChangeFrame;
		bool myIsRenderingFrame;
		bool myIsInitialized;
		bool myShouldStopThread;
		LPCWSTR myFileName;
		bool myIsStreamDone;

		static void StartCruncher(CVideoInstance* aInstance);
		static void StartUpdateLoop(CVideoInstance* aInstance);
	};

}