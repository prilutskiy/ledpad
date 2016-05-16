var express = require('express');
var app = express();
var path = require('path');
var ledpad = require("./ledpad.js");

function entryPoint(req, res) {
  console.log('Requested page: ' + req.params.page);
  res.sendFile(path.resolve(__dirname + '/../pages/index.html'));
}
function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}
app.get('/set', function (req, res){
  var rawX = parseInt(req.query["x"]);
  var rawY = Math.abs(7 - parseInt(req.query["y"]));
  
  var x = pad(rawX, 2);
  var y = pad(rawY, 2);
  ledpad.setCell(x, y);  
  res.send("OK");
})

app.get('/', function(req, res){
    res.sendFile(path.resolve(__dirname + '/ui/index.html'));
});

app.use("/", express.static(__dirname + '/ui/'));

app.listen(3000, function () {
  console.log('Server started on port 3000');
});
