

function calcScores(teaList, surveyData){
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
    });
}