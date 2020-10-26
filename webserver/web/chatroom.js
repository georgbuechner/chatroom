
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
  //Get username, password and password verification from document.
   
  //Send request
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "/api/send_msg");
  xhttp.send(document.getElementById("msg").value);
                           
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
  var xhttp = new XMLHttpRequest();    
  xhttp.open("POST", "/api/get_msgs");    
  xhttp.send("");    
  xhttp.onload = function(event){    
    if (xhttp.status!=401) {    
      var json_response = JSON.parse(this.responseText);    
      var table = document.createElement("ul");
      for (var i=0; i<json_response.length; i++) {
        var tr = document.createElement("tr")
        var td1 = document.createElement("td");
        td1.appendChild(document.createTextNode(json_response[i][0].toUpperCase() + " - "));
        tr.appendChild(td1);
        var td2 = document.createElement("td");
        td2.appendChild(document.createTextNode(json_response[i][1]));
        tr.appendChild(td2);

        table.appendChild(tr); 
      }
      document.getElementById("chatroom").innerHTML = "";
      document.getElementById("chatroom").appendChild(table);
    }    
  };       
}, 2500);
