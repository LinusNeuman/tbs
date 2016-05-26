using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UsefulToolForGameProjectYes
{
    public class Resolution
    {
        public Resolution(int aX, int aY)
        {
            myX = aX;
            myY = aY;
        }

        public string Tag
        {
            get
            {
                return (myX.ToString() + " x " + myY.ToString());
            }
        }

        public int X
        {
            get
            {
                return myX;
            }
            set
            {
                myX = value;
            }
        }
        public int Y
        {
            get
            {
                return myY;
            }
            set
            {
                myY = value;
            }
        }

        private int myX;
        private int myY;
    }
}
