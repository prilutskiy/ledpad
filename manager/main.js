var express = require('express');
var app = express();
var path = require('path');

function entryPoint(req, res) {
  console.log('Requested page: ' + req.params.page);
  res.sendFile(path.resolve(__dirname + '/../pages/index.html'));
}

app.get('/', function(req, res){
    res.sendFile(path.resolve(__dirname + '/ui/index.html'));
});

app.use("/", express.static(__dirname + '/ui/'));

app.listen(3000, function () {
  console.log('Server started on port 3000');
});
