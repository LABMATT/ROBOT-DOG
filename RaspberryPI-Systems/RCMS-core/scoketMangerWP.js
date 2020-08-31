var socket = io();

socket.on('update', function(msg){
    console.log(msg);
    var info = msg.split(":");

    if(info[0] != null && info[1] != null && !(info[0].startsWith("_")))
    {
        console.log("info0: " + info[0]);
        console.log("info0: " + info[1]);

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
}
  });

  function updatePID()
  {
    var angle = document.getElementById("L1angle").value;
    var kp = document.getElementById("kp").value;
    var ki = document.getElementById("ki").value;
    var kd = document.getElementById("kd").value;

    console.log("button pressed");
    socket.emit("pid", "hello");
  }
  
  socket.on('disconnect', function(){
    location.reload();
});