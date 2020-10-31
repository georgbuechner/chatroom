/**
 * Triggers button-click by pressing enter, when on input field and sets
 * focus on input field.
 */
window.onload = function() {
  var input = document.getElementById("msg");
  input.focus();
  input.addEventListener("keyup", function(event) {
    if (event.keyCode === 13) {
      event.preventDefault();
      document.getElementById("send_msg").click();
    }
  });
}

//Sends request to server and loads chatroom if request is successful.
function Logout() {
  //Get username, password and password verification from document.
  var json_request = new Object();
  
  //Send request
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/api/logout");
  xhttp.send("");
                           
  //Function to handle request     
  xhttp.onload = function(event){
                                                                                                  
    //If request fails, display message to user.
    if (xhttp.status == 200) {
      window.location=window.location;
    }
    else {
      alert("Logout failed.");
    }                            
  };                   
}

//Sends request to server and loads chatroom if request is successful.
function Send() {
  //Create request json
  var request = new Object;
  request.msg = document.getElementById("msg").value;
  var pups= window.location.pathname;
  request.room = pups.substr(11);

  //Send request
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/api/send_msg");
  xhttp.send(JSON.stringify(request));
                           
  //Function to handle request     
  xhttp.onload = function(event){
                                                                                                  
    //If request fails, display message to user.
    if (xhttp.status != 200) 
      alert("Sending msg failed.");
    else
      document.getElementById("msg").value="";
  };                   
}

//Constantly reload infos     
setInterval(function(){     
  var request = new Object;
  var pups = window.location.pathname;
  request.room = pups.substr(11);
  console.log(pups.substr(11));

  var xhttp = new XMLHttpRequest();    
  xhttp.open("POST", "/api/get_msgs");    
  xhttp.send(JSON.stringify(request));
  xhttp.onload = function(event){    
    if (xhttp.status!=401) {    
      var json_response = JSON.parse(this.responseText);    
      document.getElementById("chatroom").innerHTML = "";
      for (var i=0; i<json_response.length; i++) {
        var div = document.createElement("div");
        div.setAttribute("class", "msg");
        div.innerHTML = json_response[i][0].toUpperCase() + " - " + json_response[i][1];
        document.getElementById("chatroom").appendChild(div);
      }
    }    
  };       
}, 2500);
