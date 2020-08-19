const SerialPort = require('serialport')
const { read } = require('fs')
require("WebService/webpage.js");

const readline = require('readline');

var online = false;
var end = false;

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

const port = new SerialPort('COM6', {
  baudRate: 9600
})

// Read data that is available but keep the stream in "paused mode"
port.on('readable', function () {
  console.log('Data:', port.read())
})

// Switches the port into "flowing mode"
port.on('data', function (data) {
  console.log('Data:', data)
})

port.on('open', function() {
  console.log("Serial Port Has Connection.");
  online = true;
});

// When a serial link is established start running the 
read.on('true', function()
{
  console.log("Starting RCMS functions");

  

  while(end == false)
  {
    ReadSerial();

  }
})

function ReadSerial()
{

}

function LVS()
{

}