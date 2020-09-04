process.env.PWD = process.cwd()
const SerialPort = require('/usr/local/lib/node_modules/serialport');
const Readline = require('@serialport/parser-readline');


const express = require('express');
const app = express();
var fs = require('fs');
const { protocol } = require('socket.io-client');
var http = require("http").createServer( app );
var io = require('socket.io')(http);

const port = new SerialPort('/dev/ttyAMA0', { baudRate: 115200 });
const parser = new Readline();
port.pipe(parser);
//parser.on('data', console.log);
//port.write('pi_online\n');

parser.on('data', sendUpdate);

function sendUpdateSerial(msg)
{
  port.write(msg + "\n");
  console.log(msg);
}

//#### Allow console input ################################################3
const readline = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
})

readline.on("line", (name) => {
  if(name == "u")
  {
    displayRoster();
  }
  if(name.startsWith("avr "))
  {
      var msg = name.substring(4, name.length)
      port.write(msg);
      console.log("msg:" + msg);
  }
  if(name == "s")
  {
    port.write('pi_offline\n');
    process.abort()
  }
  if(name == "g")
  {
    port.write('pi_online\n');
  }
})



// WEBPAGE #################################################################################################
process.env.PWD = process.cwd()

const PORT = 3000;

app.use(express.static(process.env.PWD + '/'));
  
app.get( "/", function( req, res ) {
  res.sendFile( __dirname + "/index.html" );
  });


// SOCKET IO ################################################################################################



http.listen(PORT, function() {
  console.log("listening on *:" + PORT );
  });

  io.on('connection', (socket) => {
    console.log("User Connected.")
  });

  function sendUpdate(data)
  {
      io.sockets.emit("update", data);
  }

  io.on('connection', (socket) => {
    socket.on("avrcommand", (msg) => {
      console.log("command Recived: " + msg);
      port.write(msg + "\n");
    });
  });


