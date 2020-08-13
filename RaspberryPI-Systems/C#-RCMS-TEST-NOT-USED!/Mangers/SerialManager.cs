using System;
using System.IO.Ports;
using System.Threading;
namespace RCMS
{
    class SerialManger
    {
        static SerialPort _serialPort = new SerialPort();
        public void getSerial() 
        {
    
            _serialPort.PortName = "/dev/ttyACM0";//Set your board COM
            _serialPort.BaudRate = 9600;
            _serialPort.Open();
            while (true)
            {
                string a = _serialPort.ReadExisting();
                Console.WriteLine(a);
                Thread.Sleep(200);
            }
        }
    }
}