/**
 * Triggers button-click by pressing enter, when on last input field and sets
 * focus on first input field.
 */
window.onload = function() {
  document.getElementById("username").focus();
  var r_input_pw2 = document.getElementById("password");
  r_input_pw2.addEventListener("keyup", function(event) {
    if (event.keyCode === 13) {
      event.preventDefault();
      document.getElementById("login").click();
    }
  });
}
                                                                                                  
//Sends request to server and loads chatroom if request is successful.
function DoLogin() {
  //Get username, password and password verification from document.
  var json_request = new Object();
  json_request.username = document.getElementById("username").value;
  json_request.password = document.getElementById("password").value;
  
  //Send request
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/api/login");
  xhttp.send(JSON.stringify(json_request));
                           
  //Function to handle request     
  xhttp.onload = function(event){
                                                                                                  
    //If request fails, display message to user.
    if (xhttp.status != 200) {
      document.getElementById("password").value="";
      document.getElementById("login_error").style.display="block";
    }
    else {
      alert("Login success!");
    }                            
  };                   
}
