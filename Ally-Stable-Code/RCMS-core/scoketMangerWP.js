var socket = io();
var online = false;

socket.on('update', function(msg){
    console.log(msg);
    var info = msg.split(":");

    if(info[0].startsWith("p"))
    {
        document.getElementById(info[0]).innerHTML = info[1];

        if(info[1] != 0 && info[1] != 1023)
        {
            document.getElementById(info[0]).style.backgroundColor = "green";
        } else{
            document.getElementById(info[0]).style.backgroundColor = "red";
        }
    }

    //input
    if(info[0].startsWith("sL"))
    {
        document.getElementById(info[0]).innerHTML = info[1];

        if(info[1] != 0 && info[1] != 1023)
        {
            document.getElementById(info[0]).style.backgroundColor = "green";
        } else{
            document.getElementById(info[0]).style.backgroundColor = "red";
        }
    }

    // output
    if(info[0].startsWith("mL"))
    {
        document.getElementById(info[0]).innerHTML = info[1];

        if(info[1] != 0 && info[1] != 1023)
        {
            document.getElementById(info[0]).style.backgroundColor = "green";
        } else{
            document.getElementById(info[0]).style.backgroundColor = "red";
        }
    }
    
    if(info[0].startsWith("eL"))
    {

        if(info[1] == 1)
        {
            document.getElementById(info[0]).style.backgroundColor = "green";
            document.getElementById(info[0]).innerHTML = "true";

            console.log("shes green");
        } else{
            document.getElementById(info[0]).style.backgroundColor = "red";
            document.getElementById(info[0]).innerHTML = "false";
            console.log("shes red");
        }
    }

    if(info[0].startsWith("aL"))
    {
        document.getElementById(info[0]).innerHTML = info[1];
        if(info[1] > 0)
        {
            document.getElementById(info[0]).style.backgroundColor = "green";

        } else{
            document.getElementById(info[0]).style.backgroundColor = "red";
        }
    }

    if(info[0].startsWith("_"))
    {
        for(var i = 10; i > 1; i--)
        {
            var currentCM = "cm" + i;
            var preCM = "cm" + (    i - 1);
            document.getElementById(currentCM).innerHTML = document.getElementById(preCM).innerHTML;
            console.log("the elemnt is " + currentCM + ". Prevous cm" + preCM);
        }

        document.getElementById("cm1").innerHTML = "avr > " + msg.substring(1);
    }

  });

  function updatePID(atr)
  {

    console.log("Sendin PID:" + atr);


    switch(atr)
    {
        case 0:
        var angle = document.getElementById("L1angle").value;
        console.log("sending angle: " + angle);
        command(106);
        if(angle == 0)
        {
            angle = 2000;
        }
        command((angle * -1));
        break;

        case 1:
        var kp = document.getElementById("kp").value;
        console.log("sending kp: " + kp);
        if(kp == 0)
        {
            kp = 2000;
        }
        command(103);
        command(((kp * -1)));
        break;

        case 2:
        var ki = document.getElementById("ki").value;
        if(ki == 0)
        {
            ki = 2000;
        }
        command(104);
        command((ki * -1));
        break;

        case 3:
        var kd = document.getElementById("kd").value;
        if(kd == 0)
        {
            kd = 2000;
        }
        command(105);
        command((kd * -1));
        break;
    }
  }

  function sendCommand()
  {
    console.log("sending Command");
    socket.emit("avrcommand", document.getElementById("commandbox").value);
    document.getElementById("commandbox").value = "";
  }

  function command(cmd)
  {
    console.log("sending Command: " + cmd);
    socket.emit("avrcommand", cmd);
  }
  
  socket.on('disconnect', function(){
    //location.reload();
});