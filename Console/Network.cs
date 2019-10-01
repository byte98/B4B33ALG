using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Net;
using NetConsole;
using static NetConsole.Structures;

namespace NetConsole
{
    class Network
    {
        private UdpClient udpClient;
        private int port;
        private IPAddress ipAddress;
        private IPEndPoint ipEndPoint;
        private Logger logger;

        public Network(IPAddress address, int port, Logger logger)
        {
            this.ipAddress = address;
            this.port = port;
            this.logger = logger;
            this.init();
        }

        public Network(string address, int port, Logger logger)
        {
            this.ipAddress = Dns.GetHostEntry(address).AddressList[0];
            this.port = port;
            this.logger = logger;
            this.init();
        }

        private void init()
        {
            this.udpClient = new UdpClient();
            this.ipEndPoint = new IPEndPoint(this.ipAddress, this.port);
        }

        public void sendMessage(string message)
        {
            Byte[] buffer = Encoding.ASCII.GetBytes(message);
            try
            {
                this.udpClient.Send(buffer, buffer.Length, this.ipEndPoint);
            }
            catch (Exception ex)
            {
                string[] log =
                {
                    "Sending failed",
                    ex.Message
                };
                this.logger.LogMultiline(LogLevel.ERROR,log);
            }
            this.logger.LogSuccess("Data sent");
        }
    }
}
