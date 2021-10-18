function calculateResult(event){
    var valid = true;
    var num1 = document.getElementById("number1");
    var num2 = document.getElementById("number" + 2);
    var n1Err = document.getElementById("n1Err")
    var n2Err = document.getElementById("n2Err")
    var regex = /^[0-9]+$/;
    event.preventDefault();

    if(!regex.test(num1.value)){
        n1Err.style.display = "inline";
        valid = false;
    }
    if(!regex.test(num2.value)){
        n2Err.style.display = "inline";
        valid = false;
    }

    if (valid == false)
    {
        event.preventDefault();
    }
    else{
        n1Err.style.display = "none";
        n2Err.style.display = "none";
        var sum = (parseInt(num1.value)+ parseInt(num2.value));
        document.getElementById("result-text").innerHTML += (' '+ sum);
    }
}
