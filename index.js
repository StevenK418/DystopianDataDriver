var express = require('express');
var app = express(); 
var bodyParser = require('body-parser') 

app.get('/', function (req, res) 
{ 
    res.send("Hello from Server"); 
}) 

app.get('/dogs', function (req, res) 
{ 
    res.send("BoofBoof!!! from Server"); 
}) 

app.use(bodyParser.urlencoded({ extended: false })) 

//HTTP Methods
app.post('/', function(req, res) 
{    
    res.send('Got the temp data, thanks..!!');     
    console.log(JSON.stringify(req.body)); 
}) 

//Create a new server instance and start the connection
var server = app.listen(8081, function () 
{    
    var host = server.address().address    
    var port = server.address().port
    console.log("Example server listening at localhost:%s", host, port) 
})