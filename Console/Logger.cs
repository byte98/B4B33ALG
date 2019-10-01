using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static NetConsole.Structures;

namespace NetConsole
{
    class Logger
    {
        private int mode;

        public Logger(int mode)
        {
            this.mode = mode;
        }

        public void Log(LogLevel level, string message)
        {
            Console.WriteLine("E: " + message);
        }

        public void LogError(string message)
        {
            this.Log(LogLevel.ERROR, message);
        }

    }
}
