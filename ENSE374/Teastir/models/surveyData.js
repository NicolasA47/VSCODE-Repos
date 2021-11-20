const mongoose = require( "mongoose" );
const Schema = mongoose.Schema;

const surveyDataSchema = new Schema ({      
    caffeineLevels: [{name: String, rating: Number}],
    categories: [{name: String, rating: Number}],
    flavours: [{name: String, rating: Number}],
});
        
const surveyData = mongoose.model ( "surveyData", surveyDataSchema);

module.exports = surveyData;