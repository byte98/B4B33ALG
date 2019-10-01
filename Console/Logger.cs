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
            this.FormatConsole(level);
            Console.WriteLine(message);
            this.ResetFormat();
        }

        public void LogError(string message)
        {
            this.Log(LogLevel.ERROR, message);
        }

        public void LogInfo(string message)
        {
            this.Log(LogLevel.INFO, message);
        }

        public void LogBasic(string message)
        {
            this.Log(LogLevel.BASIC, message);
        }

        public void LogSuccess(string message)
        {
            this.Log(LogLevel.SUCCESS, message);
        }

        public void LogMultiline(LogLevel level, string[] message)
        {
            for (int i = 0; i < message.Length; i++)
            {
                this.Log(level, message[i]);
            }
        }

        private void FormatConsole(LogLevel level)
        {
            switch(level)
            {
                case LogLevel.ERROR:
                    this.FormatError();
                    break;
                case LogLevel.INFO:
                    this.formatInfo();
                    break;
                case LogLevel.BASIC:
                    this.formatBasic();
                    break;
                case LogLevel.SUCCESS:
                    this.formatSuccess();
                    break;
                default:
                    this.ResetFormat();
                    break;
            }
        }

        private void FormatError()
        {
            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Red;
        }

        private void formatInfo()
        {
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.BackgroundColor = ConsoleColor.Black;
        }

        private void formatBasic()
        {
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.BackgroundColor = ConsoleColor.Black;
        }

        private void formatSuccess()
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.BackgroundColor = ConsoleColor.Black;
        }

        private void ResetFormat()
        {
            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Gray;
        }

    }
}
