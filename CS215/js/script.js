

const email = /^\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,3}$/;   //regex statement for field
const pwLi  = /^[a-zA-Z]*[^a-zA-Z]+$/;
const pwSu = /^[a-zA-Z]*[^a-zA-Z]+$/;
//regex statement for field
const cpw = "";  //regex statement for field
const uname = /^[A-Za-z0-9]*$/;
const bday = ""; //regex statement for field
const profilePic = ""; //regex statement for field   //regex array to insert into fields array
const title = "";
const difficulty = "";
const desc = "";
const inst = "";
const ing = "";
const errors = [
    {error: "Email must follow syntax (something@abc.ca)", id: "emailSynEr"},
    {error: "username can't contain space and must have one non-letter", id: "usernameSynEr"},
    {error: "Must be 8 characters long, have one non-letter character and no spaces", id: "passwordSynEr"},
    {error: "Must be 8 characters long, have one non-letter character and no spaces", id: "passwordSuSynEr"},
    {error: "Passwords must match", id: "passwordMatchEr"},
    {error: "Title must be less than 50 characters", id: "titleSynEr"},
];
//list of errors with id tags for reference 
function validate(event){
    // event.preventDefault();     //stops page from refreshing for testing
    let regexVals = [email, pwSu, cpw, uname, bday, profilePic];  //regex vals for sign up
    if (document.title === "Log In"){     
        regexVals = [email, pwLi]; //regex vals for login
    }
    if (document.title === "Recipe Creator"){     
        regexVals = [title, difficulty, desc, inst, ing]; //regex vals for login
    }

    document.querySelectorAll('.errorMsg').forEach(err => err.remove());    //removes pre existing error messages
    let field = event.currentTarget;    //targets the form elements
    let fields = [];
    
    for(let i = 0; i < field.length; i++){  //push event.current target values into a proper array
    
        if((field[i].tagName == "INPUT")||(field[i].tagName == "TEXTAREA")){ //only for input textarea and select
            
            fields.push({
                object: field[i],       //object variable for field value
                regex: ""     //object variable for regex statement
            });
        }

    }
    Object.entries(fields).forEach(item => {
        const [key, value] = item;
        value.regex = regexVals[key];           //create a key value map to store object to proper key value for regex
    });
    let valid = true;
  
    fields.forEach(element =>{
        let thisValid = true;
        let object = element.object;
        let error = document.createElement('p');        //Creates a paragraph element to be user for errors
        error.classList.add('errorMsg');                //applies error class to it
        
            if(object.id === "file-upload")
            {
                if(object.files.length == 0){
                    error.innerHTML = "Please upload a profile picture"
                    object.parentNode.append(error);
                    valid = false;       
                    thisValid = false;          
                }
                else if(imageChecker(object.files[0]))
                {
                    error.innerHTML = "Please upload a file with file type (.jpg or .png)"
                    object.parentNode.append(error);
                    valid = false;
                    thisValid = false;  
                }   
            }
            if((object.id === "title")&&(object.value.length > 50)){
                error.innerHTML = errors.find(err => (err.id === `${object.id}SynEr`)).error;   //itterates through to find matching error in error list
                object.parentNode.append(error);
                valid = false;
                thisValid = false;  
            }
            if(object.id !== "file-upload")
            {
                if (object.value == '' || object.value == null) {       //if object is empty
                    error.innerHTML = `${object.name} field must not be empty`;   //gives empty message
                    object.parentNode.append(error);
                    valid = false;
                    thisValid = false;  
                }
                else if(element.regex != ""){
                    if(((object.id === "passwordSu")|| (object.id === "password"))&&(object.value.length != 8))
                    {
                        error.innerHTML = errors.find(err => (err.id === `${object.id}SynEr`)).error;   //itterates through to find matching error in error list
                        object.parentNode.append(error);
                        valid = false;
                        thisValid = false;  
                    }
                    else if(element.regex.test(object.value) == false){
                        error.innerHTML = errors.find(err => (err.id === `${object.id}SynEr`)).error;   //itterates through to find matching error in error list
                        object.parentNode.append(error);
                        valid = false;
                        thisValid = false;  
                    }
                }
            }
            if(object.id === "confirm-password"){
                if (object.value != (document.getElementById("passwordSu").value)){
                    error.innerHTML = "Passwords do not match";                             //make sure passwords match
                    object.parentNode.append(error);
                    valid = false;
                    thisValid = false;  
                }
            }
            if((object.tagName == "TEXTAREA")&&(thisValid == false))
            {
                object.classList.add("red-outline");
            }
    });
    if (valid == false){
        event.preventDefault();
    }
}

function imageChecker(file) {
    const acceptedType = ['image/jpeg', 'image/png'];
    return !(file && acceptedType.includes(file.type));     //ensure file type matches accepted types
}

function countChars(p, id){
    document.getElementById(id).innerHTML = p.value.length+' Characters';   //increment while typing
}

function countRating(bool, id){
    event.preventDefault();
    let num = Number(document.getElementById(id).innerHTML);
    document.getElementById(id + 'Sub').style.visibility = "visible";       //show and hide buttons and increments
    document.getElementById(id + 'Add').style.visibility = "visible";
    if(bool && (num < 5)){
        num++;
        document.getElementById(id).innerHTML = num;
    }
    else if(!bool &&(num > 0)){
        num--;
        document.getElementById(id).innerHTML = num;
    }
    if(num == 5){
        document.getElementById(id + 'Add').style.visibility = "hidden";
    } 
    
    else if(num == 0){
        document.getElementById(id + 'Sub').style.visibility = "hidden";
    } 
}