using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            int port = GetPortFromArgument(args) == -1 ? 1350 : GetPortFromArgument(args);
            Logger logger = new Logger(Structures.LogLevel.TINY, Structures.DateFormat.NONE, Structures.TimeFormat.NONE);
            logger.LogTiny("Logger started...");
            Network provider = new Network(System.Net.IPAddress.Loopback, port, logger);
            provider.sendMessage("Test");
            Console.ReadKey();

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

        
    }
}
