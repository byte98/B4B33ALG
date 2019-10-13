using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
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
            this.udpClient = new UdpClient(this.port);
            this.ipEndPoint = new IPEndPoint(this.ipAddress, this.port);
            this.logger.LogTiny("Client started; listening on port " + this.port);
        }

        public void SendMessage(string message)
        {
            byte[] buffer = Encoding.ASCII.GetBytes(message);
            try
            {
                this.udpClient.Send(buffer, buffer.Length, this.ipEndPoint);
                this.logger.LogSuccess("Data sent");
            }
            catch (NullReferenceException ex)
            {
                string[] log =
                {
                    "Sending failed",
                    ex.Message
                };

                this.logger.LogMultiline(LogLevel.CRITICAL, log);
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
            
        }
        
        public string ReceiveMessage()
        {
            string reti = null;
            //TODO: Repair receiving
            
            byte[] buffer = this.udpClient.Receive(ref this.ipEndPoint);
            reti = Encoding.ASCII.GetString(buffer);
            this.logger.LogTiny(reti);

            return reti;
        }

        public void LogMessage(string message)
        {
            if (message.Contains(","))
            {
                string[] info = message.Split(',');
                if (info.Length == 2)
                {
                    string[] available_levels = { "C", "E", "W", "I", "S", "B", "T" };
                    bool allowed_level = false;
                    foreach (string level in available_levels)
                    {
                        if (info[0] == level)
                        {
                            allowed_level = true;
                            break;
                        }
                    }
                    if (allowed_level == true)
                    {
                        switch (info[0])
                        {
                            case "C":
                                this.logger.LogCritical(info[1]);
                                break;
                            case "E":
                                this.logger.LogError(info[1]);
                                break;
                            case "W":
                                this.logger.LogWarning(info[1]);
                                break;
                            case "I":
                                this.logger.LogInfo(info[1]);
                                break;
                            case "S":
                                this.logger.LogSuccess(info[1]);
                                break;
                            case "B":
                                this.logger.LogBasic(info[1]);
                                break;
                            case "T":
                                this.logger.LogTiny(info[1]);
                                break;
                        }
                    }
                    else
                    {
                        string[] log =
                        {
                            "Message parsing failed.",
                            "Input: " + message,
                            "Unknown log level!"
                        };
                        this.logger.LogMultiline(LogLevel.WARNING, log);
                    }
                }
                else
                {
                    string[] log =
                    {
                        "Message parsing failed.",
                        "Input: " + message,
                        "Unknown format!"
                    };
                    this.logger.LogMultiline(LogLevel.WARNING, log);
                }

            }
            else
            {
                string[] log =
                {
                    "Message parsing failed.",
                    "Input: " + message,
                    "Not comma(,) found!"
                };
                this.logger.LogMultiline(LogLevel.WARNING, log);
            }
        }

        
    
    }
}
