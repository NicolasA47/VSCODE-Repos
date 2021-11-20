const mongoose = require( "mongoose" );
const surveyData = require("../../models/surveyData");
const teaFlavour = require("../../models/teaFlavour");

mongoose.connect( "mongodb://localhost:27017/teaStir", 
                { useNewUrlParser: true, 
                  useUnifiedTopology: true});

let flavour;

flavour = new teaFlavour({
   name: "chocolate chili chai",
   category: "black",
   flavour: "chai",
   caffeineLevel: "high",
   imagePath: "../Images/teas/chocolate-chili-chai.jpg"
});

flavour.save();

flavour = new teaFlavour({
    name: "pumpkin chai",
    category: "black",
    flavour: "chai",
    caffeineLevel: "medium",
    imagePath: "../Images/teas/pumpkin-chai.jpg"
 });
 
 flavour.save();
//////////////////////////////////// Test Data For Survey

testData = new surveyData({
   

})
///////////////////////////////////


 