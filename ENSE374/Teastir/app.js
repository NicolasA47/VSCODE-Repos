const express = require("express");
const mongoose = require("mongoose");
const teaFlavour = require('./models/teaFlavour');


const app = express();
const url = 'mongodb://localhost:27017/teaStir';
const port = 2000; 


mongoose.connect( url, { useNewUrlParser: true, useUnifiedTopology: true})
.then((result) => {
    app.listen (port, () => {
        console.log (`Server is running on http://localhost:${port}`);
    });
})
.catch((err) => console.log(err));


app.set("view engine", "ejs");
app.use(express.urlencoded({ extended: true}));
app.use(express.static("public"));



app.get("/", (req, res) => {
    res.render('homepage');                 //render the homepage
});

app.post("/get-teas", (req, res) => {
    teaFlavour.find()                       //search database for teas
    .then((result) =>{                      //if teas are found the return the teas to the response
        res.send(result);
    })
    .catch((err)=>{                         //if error is caught then console log the error
        console.log(err);
    });

})