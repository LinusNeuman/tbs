using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    class Animation
    {
        public Animation()
        {
            myName = "";
            myAmountOfColumns = 0;
            myAmountOfRows = 0;
            myAmountOfFrames = 0;
            myAnimationSpeed = 1;
            myShouldLoop = false;

            myCurrentColumn = 0;
            myCurrentRow = 0;
            myCurrentFrame = 0;
            myAnimationTimer = 0;
            myIsRunning = true;

            myCurrentColumn = 1;
            myCurrentRow = 1;
            myCurrentFrame = 0;
            myAnimationTimer = 0;
            myHasPlayed = false;
        }

        public void Initialize(string aName, string aSpritePath, int aSizeX, int aSizeY
            , int anAmountOfColumns, int anAmountOfRows, int anAmountOfFrames, int anAnimationSpeed
            , int aLoopStartFrame, int aLoopEndFrame, bool aShouldLoop, bool anIsInterruptible
            , string anInTransition, string anOutTransition)
        {
            myName = aName;
	        myFilePath = aSpritePath;
            mySizeX = aSizeX;
            mySizeY = aSizeY;
	        myAmountOfColumns = anAmountOfColumns;
	        myAmountOfRows = anAmountOfRows;
	        myAmountOfFrames = anAmountOfFrames;
	        myAnimationSpeed = anAnimationSpeed;
	        myIsRunning = true;
            myHasPlayed = false;
	        myShouldLoop = aShouldLoop;
	        myIsInterruptible = anIsInterruptible;
            myLoopStartFrame = aLoopStartFrame;
            myLoopEndFrame = aLoopEndFrame;
	        myInTransition = anInTransition;
            myOutTransition = anOutTransition;

            StartAnimation();
        }

        public void Update(int aDeltaTime)
        {
            if (myIsRunning == true)
	        {
                myAnimationTimer += aDeltaTime;

		        if (myAnimationTimer >= 1000 / myAnimationSpeed)
		        {
			        if ((myHasPlayed == false && myCurrentFrame < myAmountOfFrames - 1)
                     || (myHasPlayed == true && myCurrentFrame < myLoopEndFrame - 1))
			        {
					    myCurrentFrame++;
                        myCurrentRow = myCurrentFrame / myAmountOfColumns + 1;
                        myCurrentColumn = myCurrentFrame - myAmountOfColumns * (myCurrentRow - 1);
			        }
			        else
			        {
				        if (myShouldLoop == false)
				        {
					        StopAnimation();
				        }
				        else
                        {
                            myHasPlayed = true;
                            myCurrentFrame = myLoopStartFrame - 1;
                            myCurrentRow = myCurrentFrame / myAmountOfColumns + 1;
                            myCurrentColumn = myCurrentFrame - myAmountOfColumns * (myCurrentRow - 1);
				        }
			        }
			        myAnimationTimer = 0;
		        }
	        }
        }

        public void StartAnimation()
        {
	        myCurrentColumn = 1;
	        myCurrentRow = 1;
	        myCurrentFrame = 1;
	        myIsRunning = true;
        }

        public void StopAnimation()
        {
	        myCurrentColumn = 0;
	        myCurrentRow = 0;
	        myCurrentFrame = 0;
	        myIsRunning = false;
        }

        void SaveAnimation()
        {
        }

        public AnimationData myAnimationData = new AnimationData();

        string myInTransition;
	    string myOutTransition;
	    public string myName;
        string myFilePath;
        public int mySizeX;
        public int mySizeY;
	    int myAmountOfColumns;
	    int myAmountOfRows;
	    int myAmountOfFrames;
        int myLoopStartFrame;
        int myLoopEndFrame;
        int myAnimationSpeed;
        bool myShouldLoop;

        public int myCurrentColumn;
	    public int myCurrentRow;
        public int myCurrentFrame;
        int myAnimationTimer;

	    bool myHasPlayed;
	    bool myIsRunning;
	    bool myIsInterruptible;
    }
}
