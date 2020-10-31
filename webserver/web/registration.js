/**
 * Triggers button-click by pressing enter, when on last input field and sets
 * focus on first input field.
 */
window.onload = function() {
  document.getElementById("username").focus();
  var r_input_pw2 = document.getElementById("password2");
  r_input_pw2.addEventListener("keyup", function(event) {
    if (event.keyCode === 13) {
      event.preventDefault();
      document.getElementById("register").click();
    }
  });
  SetColorAll("red");
}
                                                                                                  
//Sends request to server and loads chatroom if request is successful.
function DoRegisttration() {
  //Get username, password and password verification from document.
  var json_request = new Object();
  json_request.username = document.getElementById("username").value;
  json_request.password1 = document.getElementById("password1").value;
  json_request.password2 = document.getElementById("password2").value;
  
  //Send request
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/api/registration");
  xhttp.send(JSON.stringify(json_request));
                           
  //Function to handle request     
  xhttp.onload = function(event){
                                                                                                  
    //If request fails, display message to user.
    if (xhttp.status != 200) {
      document.getElementById("password1").value="";
      document.getElementById("password2").value="";
      if (this.responseText != "")
        alert(this.responseText);
      else
        alert("Registration failed!");
      SetColorAll("red");
    }
    else {
      SetColorAll("green");
      window.location.href="/chatrooms";
    }                            
  };                   
}

//Checks, whether passwords match.
function CheckPasswordMatch() {
  if (document.getElementById("password1").value ==
    document.getElementById("password2").value) {
    document.getElementById("pw_match").style = "color: green;"; 
  }
  else {
    document.getElementById("pw_match").style = "display: block";
  }
}

//Determines password strength.
function CheckPasswordStrength() {
  let score = ScorePassword(document.getElementById("password1").value);

  //Change color of succeded fields
  for (type of ["big", "small", "digit", "lower"]) {
    if (score[type]) 
      document.getElementById(type).style = "color: green;";
    else
      document.getElementById(type).style = "color: red;";
  }

  //Set not-used white.
  if (score.success && score.big) 
    SetColor2("black");
  else if (score.success)
    SetColor1("black");
}

/**
 * Determines which parts of password are correct.
 */
function ScorePassword(pass) {
  var obj = new Object;
  obj.success = false;
  obj.big = false;
  obj.small = false;
  obj.digit = false;
  obj.lower = false;

  if (!pass)
    return obj;

  if (pass.length == 15) {
    obj.big = true;
    obj.success = true;
    return obj;
  }

  if (pass.length >= 8) obj.small=true;
  if (/\d/.test(pass)) obj.digit = true;
  if (/[a-z]/.test(pass)) obj.lower = true;
  if (obj.small && obj.digit && obj.lower) obj.success = true;
  return obj;
}

//Sets color of message concerning "atleast 15 digits" 
function SetColor1(color) {
  document.getElementById("big").style = "color: " + color + ";";
}

//Sets color of other messages.
function SetColor2(color) {
  for (let type of ["small", "digit", "lower"]) 
    document.getElementById(type).style = "color: " +color + ";";
}

//Sets color of all messages.
function SetColorAll(color) {
  SetColor1(color);
  SetColor2(color);
}
