const mongoose = require( "mongoose" );
const Schema = mongoose.Schema;

const teaFlavourSchema = new Schema ({      
    name: String,
    category: String,
    flavour: String,
    caffeineLevel: String,
    imagePath: String,
});
        
const teaFlavour = mongoose.model ( "teaFlavour", teaFlavourSchema);

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

 module.exports = teaFlavour;