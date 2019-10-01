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
            Logger logger = new Logger(Structures.LogLevel.BASIC, Structures.DateFormat.NONE, Structures.TimeFormat.NONE);
            logger.LogBasic("Logger started...");
            Network provider = new Network(System.Net.IPAddress.Loopback, 1350, logger);
            provider.sendMessage("Test");

            Console.ReadKey();

        }

        
    }
}
