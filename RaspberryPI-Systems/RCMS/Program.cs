using System;

namespace RCMS
{
    class Program
    {
        static void Main(string[] args)
        {

    Console.WriteLine("Hellow World PRD! Softwere is starting.");
    
    SignalRChat signal = new SignalRChat();
    signal.Startup();
    
    //SerialManger sm = new SerialManger();

    //sm.getSerial();

        }
    }
}
