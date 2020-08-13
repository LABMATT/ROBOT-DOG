const express = require('express');
const app = express();
var fs = require('fs');
process.env.PWD = process.cwd()

app.use(express.static(process.env.PWD + '/'));

const server = app.listen(7000, () => {
    console.log(`Express running → PORT ${server.address().port}`);
  });
  
  app.get('/', (req, res) => {
    //res.send(index.html);

    fs.readFile('index.html', function(err, data) {
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write(data);
        return res.end();
    });
});
  