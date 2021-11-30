const express = require("express");
const mongoose = require("mongoose");
const teaFlavour = require('./models/teaFlavour');
const surveyData = require('./models/surveyData');



const app = express();
const url = 'mongodb://localhost:27017/teaStir';
const port = 2000; 

let surveyResults = new surveyData({    //test object for survey data
    caffeineLevels: [
        {name: "none", rating: 1},{name: "low", rating: 1}, {name: "medium", rating: 3}, {name: "high", rating: 4}
    ],
    categories: [
        {name: "herbal", rating: 3},{name: "green", rating: 3},{name: "black", rating: 3},
        {name: "white", rating: 3},{name: "rooibus", rating: 3},{name: "oolong", rating: 3},
        {name: "pu'erh", rating: 3},{name: "maté", rating: 3}
    ],
    flavours:[
        {name: "chai", rating: 4},{name: "pumkin", rating: 2},{name: "earl-grey", rating: 1},
        {name: "coffee", rating: 0},{name: "chocolate", rating: 3},{name: "berries", rating: 3},
        {name: "mint", rating: 4},{name: "vanilla", rating: 2},{name: "natural", rating: 1},
        {name: "unflavoured", rating: 0},{name: "stevie-free", rating: 0},{name: "citrus", rating: 2},
        {name: "ginger", rating: 4},{name: "hibiscus", rating: 3},{name: "jasmine", rating: 1},
    ],
});


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
    .then((result) =>{     
        let scores = calcScores(result, surveyResults);                //if teas are found the return the teas to the response
        console.log(scores);     
    })
    .catch((err)=>{                         //if error is caught then console log the error
        console.log(err);
    });
})




function calcScores(teaList, surveyData){
    console.log(teaList);
    let scoreArray = [];
    teaList.forEach(tea => {
        let cafScore = ((surveyData.caffeineLevels.find(level => (level.name == tea.caffeineLevel))).rating)*25;  
        let flavScore = ((surveyData.flavours.find(flavour => (flavour.name == tea.flavour))).rating)*25;
        let catScore = ((surveyData.categories.find(category => (category.name == tea.category))).rating)*25;
        let simScore = (flavScore * 0.4)+(cafScore * 0.3)+(catScore * 0.3);
        let scoreObj = {
            teaName: tea.name,
            similarityScore: simScore,
            caffieneScore: cafScore,
            flavourScore: flavScore
        }
        scoreArray.push(scoreObj);
        return scoreArray;
    });
   
}