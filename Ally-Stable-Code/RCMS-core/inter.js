const sm = require("./scripts/consoleManger.js");

module.exports = {

inter: function inter(data)
{
    console.log("In inter");
if(data.startsWith("p"))
{
    sm.sendPotUpdate(data);
}
}
}