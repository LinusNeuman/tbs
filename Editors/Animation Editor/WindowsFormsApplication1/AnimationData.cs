using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApplication1
{
    class AnimationData
    {
        public string Name;
        public string FilePath;
        public int SizeX;
        public int SizeY;
        public int AmountOfColumns;
        public int AmountOfRows;
        public int AmountOfFrames;
        public int AnimationSpeed;
        public int LoopStart;
        public int LoopEnd;
        public bool ShouldLoop;
        public bool IsInterruptible;
        public string InTransition;
        public string OutTransition;
    }
}
