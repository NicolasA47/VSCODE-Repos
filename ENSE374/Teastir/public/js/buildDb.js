const mongoose = require( "mongoose" );
const teaFlavour = require('./models/teaFlavour');

let connection = mongoose.connect( "mongodb://localhost:27017/teaStir", 
                { useNewUrlParser: true, 
                  useUnifiedTopology: true});

mongoose.connection.on('open', function(){
    con.connection.db.dropDatabase(function(err, result){
        done();
    });
});

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



 