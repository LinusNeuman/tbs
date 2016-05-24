using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Object_Editor
{
    class Gadget
    {

        public string Name { get; set; }
        public int Cost { get; set; }
        public int Damage { get; set; }
        public bool DoesDamage { get; set; }
        public string Level { get; set; }

        private string myName;
        private int myCost;
        private int myDamage;
        private bool myDoesDamage;
        private string myLevel;
    }
}
