
const mongoose = require("mongoose");
const { Schema } = mongoose;

var messageSchema = Schema({
    date: Date,
    topic: String,
    message: String,
    temp : String, 
    ip: String
});

module.exports = mongoose.model('Message', messageSchema);
