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
