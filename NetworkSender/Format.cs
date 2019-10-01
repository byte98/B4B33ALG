using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkSender
{
    public static class Format
    {
        public static Structures.ConsoleColorScheme TinyFormat = new Structures.ConsoleColorScheme
        (
            ConsoleColor.Black,
            ConsoleColor.Gray,
            ConsoleColor.Black,
            ConsoleColor.DarkGray
        );

        public static Structures.ConsoleColorScheme BasicFormat = new Structures.ConsoleColorScheme
        (
            ConsoleColor.Black,
            ConsoleColor.White,
            ConsoleColor.Black,
            ConsoleColor.Gray
        );

        public static Structures.ConsoleColorScheme SuccessFormat = new Structures.ConsoleColorScheme
        (
            ConsoleColor.Black,
            ConsoleColor.DarkGreen,
            ConsoleColor.Black,
            ConsoleColor.Green
        );

        public static Structures.ConsoleColorScheme InfoFormat = new Structures.ConsoleColorScheme
        (
            ConsoleColor.Black,
            ConsoleColor.DarkBlue,
            ConsoleColor.Black,
            ConsoleColor.Blue
        );

        public static Structures.ConsoleColorScheme WarningFormat = new Structures.ConsoleColorScheme
        (
            ConsoleColor.Black,
            ConsoleColor.DarkYellow,
            ConsoleColor.Black,
            ConsoleColor.Yellow
        );

        public static Structures.ConsoleColorScheme ErrorFormat = new Structures.ConsoleColorScheme
        (
            ConsoleColor.Black,
            ConsoleColor.DarkRed,
            ConsoleColor.Black,
            ConsoleColor.Red
        );

        public static Structures.ConsoleColorScheme CriticalFormat = new Structures.ConsoleColorScheme
        (
            ConsoleColor.Black,
            ConsoleColor.Red,
            ConsoleColor.Red,
            ConsoleColor.Black
        );
    }
}
