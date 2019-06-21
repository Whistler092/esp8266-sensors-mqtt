const mongoose = require("mongoose");

// Import .env
//require("dotenv").config();
//console.log("env", process.env.MDBPASS);
//const pass = process.env.MDBPASS;
//const URI = `mongodb+srv://bby-list:${pass}@rbmongotest-0vdzl.mongodb.net/test?retryWrites=true`;
const URI = 'mongodb://192.168.0.22/sensors';

const options = {
    autoIndex: false, // Don't build indexes
    reconnectTries: 30, // Retry up to 30 times
    reconnectInterval: 500, // Reconnect every 500ms
    poolSize: 10, // Maintain up to 10 socket connections
    // If not connected, return errors immediately rather than waiting for reconnect
    bufferMaxEntries: 0
}


mongoose.connect(URI, options)
    .then(db => console.log('Db is connected'))
    .catch(error => console.error(error));
