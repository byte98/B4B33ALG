using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkSender
{
    class Program
    {
        static void Main(string[] args)
        {
            int port = GetPortFromArgument(args) == -1 ? 1350 : GetPortFromArgument(args);
            Logger logger = new Logger(Structures.LogLevel.TINY, Structures.DateFormat.NONE, Structures.TimeFormat.NONE);
            logger.LogTiny("Logger started");

            Network net = new Network(System.Net.IPAddress.Loopback, port, logger);

            string data = "";

            do
            {
                Console.ForegroundColor = ConsoleColor.Gray;
                Console.Write("Enter data, ");
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.Write("--help");
                Console.ForegroundColor = ConsoleColor.Gray;
                Console.Write(" for help or ");
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.Write("\\0");
                Console.ForegroundColor = ConsoleColor.Gray;
                Console.WriteLine(" for end:");

                Console.ForegroundColor = ConsoleColor.White;
                data = Console.ReadLine();
                if (data == "--help")
                {
                    ShowHelp();
                    ConsoleKeyInfo key = Console.ReadKey();
                    ConsoleKey k = key.Key;
                    while (k != ConsoleKey.Q && k != ConsoleKey.Escape)
                    {
                        key = Console.ReadKey();
                        k = key.Key;
                    }

                    Console.BackgroundColor = ConsoleColor.Black;
                    Console.ForegroundColor = ConsoleColor.Gray;
                    if (k == ConsoleKey.Q)
                    {
                        Console.Clear();
                        Console.CursorVisible = true;
                    }
                    else if (k == ConsoleKey.Escape)
                    {
                        return;
                    }
                }
                else if (data != "\\0")
                {
                    net.sendMessage(data);
                }

            }
            while (data != "\\0");

        }

        public static int GetPortFromArgument(string[] args)
        {
            int reti = -1;

            foreach (string arg in args)
            {
                if (arg.ToLower().Contains("--port="))
                {
                    char[] separator = { '=' };
                    string[] argument = arg.Split(separator);
                    string value = argument.Last();
                    try
                    {
                        reti = int.Parse(value);

                    }
                    catch { }

                }
            }

            return reti;
        }

        static void ShowHelp()
        {
            Console.Clear();
            string header = "NETWORK SENDER";
            int before = (Console.WindowWidth / 2) - (header.Length / 2);
            int after = Console.WindowWidth - before - header.Length;
            Console.BackgroundColor = ConsoleColor.White;
            Console.ForegroundColor = ConsoleColor.Black;
            for (int i = 0; i < before; i++)
            {
                Console.Write(" ");
            }
            Console.Write(header);
            for (int i = 0; i < after; i++)
            {
                Console.Write(" ");
            }
            Console.WriteLine();
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.BackgroundColor = ConsoleColor.Black;
            Console.WriteLine();
            Console.WriteLine(" Network sender is simple program to send text data (ASCII) over network using UDP.");
            Console.WriteLine();
            Console.WriteLine(" USAGE");
            Console.WriteLine(" It's simple to work with network sender. When program starts, there are three options");
            Console.WriteLine(" what to type to console.");
            Console.Write(" - ");
            Console.ForegroundColor = ConsoleColor.White;
            Console.Write(" some text ");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine();
            Console.WriteLine("   Some text to be sent over network");
            Console.WriteLine();
            Console.Write(" - ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write(" --help");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine();
            Console.WriteLine("   Views this help page");
            Console.WriteLine();
            Console.Write(" - ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write(" \\0");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine();
            Console.WriteLine("   Exits program");
            Console.WriteLine();
            Console.WriteLine(" PARAMETERS");
            Console.WriteLine(" Program can run without parameters, but there is one parameter which can be set:");
            Console.Write(" ");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.Write("--port=");
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.Write("<int>");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine();
            Console.Write(" Where ");
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.Write("<int>");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(" can be any integer number from 0 to 65535 (recommended >= 1024).");
            Console.WriteLine(" This parameter sets port number, to where will be all data sent to.");
            Console.WriteLine();
            Console.WriteLine(" PURPOSE");
            Console.Write(" This program was originally developed for testing functionality of program called ");
            Console.ForegroundColor = ConsoleColor.White;
            Console.Write("NetConsole");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(".");
            Console.WriteLine(" From this there comes main purpose of this program - testing network software.");
            Console.WriteLine(" Because of above, we show manual how to properly send data to NetConsole.");
            Console.WriteLine(" What to type to check NetConsole functionality? Basically it is CSV format:");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write(" C");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" | ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write("E");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" | ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write("W");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" | ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write("I");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" | ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write("B");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" | ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write("S");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" | ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write("T,message");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine();
            Console.WriteLine(" Where first letter defines level of log:");
            Console.Write(" - C for ");
            Console.ForegroundColor = ConsoleColor.Black;
            Console.BackgroundColor = ConsoleColor.Red;
            Console.WriteLine("[CRITICAL]");
            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" - E for ");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("[ ERROR  ]");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" - W for ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("[WARNING ]");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Write(" - I for ");
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine("[  INFO  ]");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(" - B for (basic)");
            Console.Write(" - T for ");
            Console.ForegroundColor = ConsoleColor.DarkGray;
            Console.Write("(  tiny  )");
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine();
            Console.WriteLine(" and message text to be logged.");
            Console.ForegroundColor = ConsoleColor.Black;
            Console.BackgroundColor = ConsoleColor.White;
            string footer = "Press <Q> for quit help, <ESC> for exit program";
            Console.Write(footer);
            for (int i = 0; i < (Console.WindowWidth - footer.Length); i++)
            {
                Console.Write(" ");
            }
            Console.CursorVisible = false;
        }
    }
}
