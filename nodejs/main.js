var mqtt = require('mqtt');
var Topic = '#'; //subscribe to all topics
var Broker_URL = 'mqtt://192.168.0.22';

var options = {
	clientId: 'MyMQTT',
	port: 1883,
	keepalive : 60
};

const { mongoose } = require("./database");
const Message = require("./database.model.message");


var client  = mqtt.connect(Broker_URL, options);
client.on('connect', mqtt_connect);
client.on('reconnect', mqtt_reconnect);
client.on('error', mqtt_error);
client.on('message', mqtt_messsageReceived);
client.on('close', mqtt_close);

function mqtt_connect()
{
    console.log("Connecting MQTT");
    client.subscribe(Topic, mqtt_subscribe);
}

function mqtt_subscribe(err, granted)
{
    console.log("Subscribed to " + Topic);
    if (err) {console.log(err);}
}

function mqtt_reconnect(err)
{
    console.log("Reconnect MQTT");
    if (err) {console.log(err);}
	client  = mqtt.connect(Broker_URL, options);
}

function mqtt_error(err)
{
    console.log("Error!");
	if (err) {console.log(err);}
}

function after_publish()
{
	//do nothing
}

function mqtt_messsageReceived(topic, message, packet)
{
    var date = new Date(); 
    console.log(date.toJSON().slice(0,19).replace('T',':') +'  Topic=' +  topic + '  Message=' + message);
    
   try{
    var tmp = JSON.parse(message);

    const msg = new Message({
        date,
        topic,
        message,
        temp : tmp.temp,
        ip: tmp.ip
    });
    msg.save();
   }catch (e){
       console.log("error trying save" , e);
   }
}

function mqtt_close()
{
	console.log("Close MQTT");
}