using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static NetworkSender.Structures;

namespace NetworkSender
{
    class Logger
    {
        private LogLevel level;
        private DateFormat date;
        private TimeFormat time;
        private int header_len;

        public Logger(LogLevel level, DateFormat date, TimeFormat time)
        {
            this.level = level;
            this.date = date;
            this.time = time;
            this.header_len = this.GetHeader(LogLevel.CRITICAL).Length;
        }

        public void Log(LogLevel level, string message)
        {
            if (level <= this.level)
            {
                ConsoleColorScheme scheme = this.SelectColorScheme(level);
                this.FormatHeader(scheme);
                Console.Write(this.GetHeader(level));
                this.FormatBody(scheme);
                Console.WriteLine(message);
                this.ResetFormat();
            }
            
        }

        private string GetHeader(LogLevel level)
        {
            string reti = "";
            DateTime now = DateTime.Now;

            if (date == DateFormat.LONG)
            {
                reti += now.ToLongDateString() + " ";
            }
            else if (date == DateFormat.SHORT)
            {
                reti += now.ToShortDateString() + " ";
            }

            if (time == TimeFormat.HH)
            {
                reti += now.ToString("hh") + " ";
            }
            else if (time == TimeFormat.HH_MM)
            {
                reti += now.ToString("hh:mm") + " ";
            }
            else if (time == TimeFormat.HH_MM_SS)
            {
                reti += now.ToString("hh:mm:ss") + " ";
            }

            if (level < LogLevel.BASIC)
            {
                reti += "[";
            }
            else
            {
                reti += " ";
            }

            switch (level)
            {
                case LogLevel.CRITICAL:
                    reti += "CRITICAL]";
                    break;
                case LogLevel.ERROR:
                    reti += " ERROR  ]";
                    break;
                case LogLevel.WARNING:
                    reti += "WARNING ]";
                    break;
                case LogLevel.SUCCESS:
                    reti += "SUCCESS ]";
                    break;
                case LogLevel.INFO:
                    reti += " INFO   ]";
                    break;
                default:
                    reti += "         ";
                    break;
            }
            reti += " ";
            
            
            return reti;
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

        public void LogTiny(string message)
        {
            this.Log(LogLevel.TINY, message);
        }

        public void LogMultiline(LogLevel level, string[] message)
        {
            for (int i = 0; i < message.Length; i++)
            {
                if (i == 0)
                {
                    this.Log(level, message[i]);
                }
                else
                {
                    for (int j = 0; j <this.header_len; j++)
                    {
                        Console.Write(" ");
                    }
                    this.FormatBody(this.SelectColorScheme(level));
                    Console.WriteLine(message[i]);
                }
                
            }
            this.ResetFormat();
        }


        

        private void FormatBody(ConsoleColorScheme colors)
        {
            Console.ForegroundColor = colors.body_foreground;
            Console.BackgroundColor = colors.body_background;
        }

        private void FormatHeader(ConsoleColorScheme colors)
        {
            Console.ForegroundColor = colors.header_foreground;
            Console.BackgroundColor = colors.header_background;
            
        }

        private ConsoleColorScheme SelectColorScheme(LogLevel level)
        {
            ConsoleColorScheme reti = Format.BasicFormat;
            switch(level)
            {
                case LogLevel.TINY:

                case LogLevel.BASIC:
                    reti = Format.BasicFormat;
                    break;
                case LogLevel.INFO:
                    reti = Format.InfoFormat;
                    break;
                case LogLevel.SUCCESS:
                    reti = Format.SuccessFormat;
                    break;
                case LogLevel.WARNING:
                    reti = Format.WarningFormat;
                    break;
                case LogLevel.ERROR:
                    reti = Format.ErrorFormat;
                    break;
                case LogLevel.CRITICAL:
                    reti = Format.CriticalFormat;
                    break;
                default:
                    reti = Format.BasicFormat;
                    break;
            }
            return reti;
        }

        private void ResetFormat()
        {
            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Gray;
        }

    }
}
