using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetConsole
{
    public static class Structures
    {
        public enum LogLevel
        {
            CRITICAL,

            ERROR,

            WARNING,

            SUCCESS,

            INFO,

            BASIC,

        }

        public enum DateFormat
        {
            NONE,

            SHORT,

            LONG
        }

        public enum TimeFormat
        {
            NONE,

            HH,

            HH_MM,

            HH_MM_SS
        }

        public struct ConsoleColorScheme
        {
            public ConsoleColor header_background;
            public ConsoleColor header_foreground;
            public ConsoleColor body_background;
            public ConsoleColor body_foreground;

            public ConsoleColorScheme(ConsoleColor header_background,
                                      ConsoleColor header_foreground,
                                      ConsoleColor body_background,
                                      ConsoleColor body_foreground)
            {
                this.header_background = header_background;
                this.header_foreground = header_foreground;
                this.body_background = body_background;
                this.body_foreground = body_foreground;
            }
        }

    }
}
