const char HTML[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<head>
<style>
html,
body {
  height: 100%;
  margin: 0;
  padding: 0;
  font-family: 'Consolas', cursive;
  background-color: #212121;
}

h1,
h2,
p,
span,
textarea {
  font-family: 'Consolas', cursive;
}
.console {
  position: relative;
  width: 100%;
  height: 100%;
  overflow: hidden;
  padding: 10px;
  box-sizing: border-box;
}
.console .output {
  width: 100%;
  font-size: 12px;
  color: #cccccc;
}
.console .output span {
  line-height: 20px;
}
.console .output span.grey {
  color: #cccccc;
}
.console .output span.green {
  color: #2ecc71;
}
.console .output span.red {
  color: #e74c3c;
}
.console .output span.blue {
  color: #3498db;
}
.console .output pre {
  font-size: 9px;
  -webkit-animation: glitch 0.2s linear infinite;
          animation: glitch 0.2s linear infinite;
  -webkit-animation-play-state: paused;
          animation-play-state: paused;
}
.console .output pre:hover {
  -webkit-animation-play-state: running;
          animation-play-state: running;
}
.console .action {
  width: 100%;
  font-size: 14px;
  margin-top: 20px;
}
.console .action span {
  display: inline-block;
  width: 60px;
  float: left;
  color: white;
}
.console .action textarea {
  width: calc(100% - 65px);
  float: left;
  background: none;
  border: none;
  color: white;
  padding: 0;
  margin: 0;
}
.console .action textarea:focus {
  outline: none;
}
span.seperator {
  font-size: 12px;
  -webkit-animation: changeColor 10s ease-in-out infinite;
          animation: changeColor 10s ease-in-out infinite;
}
@-webkit-keyframes glitch {
  0% {
    color: white;
    -webkit-transform: translateX(0) translateY(0%);
            transform: translateX(0) translateY(0%);
  }
  25% {
    color: #3498db;
    -webkit-transform: translateX(1px) translateY(1px);
            transform: translateX(1px) translateY(1px);
  }
  40% {
    color: #e74c3c;
    -webkit-transform: translateX(-2px) translateY(-2px);
            transform: translateX(-2px) translateY(-2px);
  }
  50% {
    color: #cccccc;
    -webkit-transform: translateX(0) translateY(0);
            transform: translateX(0) translateY(0);
  }
  80% {
    color: #3498db;
    -webkit-transform: translateX(2px) translateY(2px);
            transform: translateX(2px) translateY(2px);
  }
  90% {
    color: #e74c3c;
    -webkit-transform: translateX(-1px) translateY(-1px);
            transform: translateX(-1px) translateY(-1px);
  }
  100% {
    color: white;
    -webkit-transform: translateX(0) translateY(0);
            transform: translateX(0) translateY(0);
  }
}
@keyframes glitch {
  0% {
    color: white;
    -webkit-transform: translateX(0) translateY(0%);
            transform: translateX(0) translateY(0%);
  }
  25% {
    color: #3498db;
    -webkit-transform: translateX(1px) translateY(1px);
            transform: translateX(1px) translateY(1px);
  }
  40% {
    color: #e74c3c;
    -webkit-transform: translateX(-2px) translateY(-2px);
            transform: translateX(-2px) translateY(-2px);
  }
  50% {
    color: #cccccc;
    -webkit-transform: translateX(0) translateY(0);
            transform: translateX(0) translateY(0);
  }
  80% {
    color: #3498db;
    -webkit-transform: translateX(2px) translateY(2px);
            transform: translateX(2px) translateY(2px);
  }
  90% {
    color: #e74c3c;
    -webkit-transform: translateX(-1px) translateY(-1px);
            transform: translateX(-1px) translateY(-1px);
  }
  100% {
    color: white;
    -webkit-transform: translateX(0) translateY(0);
            transform: translateX(0) translateY(0);
  }
}
@-webkit-keyframes changeColor {
  0% {
    color: #cccccc;
  }
  25% {
    color: #2ecc71;
  }
  50% {
    color: #e74c3c;
  }
  75% {
    color: #3498db;
  }
  100% {
    color: #cccccc;
  }
}
@keyframes changeColor {
  0% {
    color: #cccccc;
  }
  25% {
    color: #2ecc71;
  }
  50% {
    color: #e74c3c;
  }
  75% {
    color: #3498db;
  }
  100% {
    color: #cccccc;
  }
}
</style>
</head>
<body>

<div class="console">
  <div class="output" id="consoleOutput">
    <span class="green">--- ready!</span><br/>
    <span class="seperator">== == == == == == == == == == == == == == == == == ==</span></br>
    <pre contenteditable="false">
     ________          __ 
    / ____/ /_  ____ _/ /_
   / /   / __ \/ __ `/ __/
  / /___/ / / / /_/ / /
  \____/_/ /_/\__,_/\__/</pre></br>
    <span>Max. mensajes mostrados: 10 </span><br/>
    <span>Para cambiar el nombre de usuario: name [nombre] </span><br/>
    <span class="seperator">== == == == == == == == == == == == == == == == == ==</span></br>
  </div>
  <div class="output" id="messagesOutput">
  </div>
  <div class="action">
    <span id="clientName">user$</span>
    <textarea class="input" id="input" name="input" cols="60" rows="1"></textarea>
  </div>
  
</div>

<br>
<script>

    var clientName = "";
    var message = "";
    var inputTag = document.getElementById('input');
    var consoleOutput = document.getElementById('consoleOutput');
    var messagesOutput = document.getElementById('messagesOutput');
    
    input.addEventListener('keypress', function (e){
        if (e.which == 13) {
          var inputValue = inputTag.value;
          var result = inputValue.trim();
          if (result.startsWith("name") === true) {
            result = result.substr(result.indexOf(' ') + 1);
            clientName = result;
            var name = document.getElementById('clientName');
            name.innerHTML = clientName + "$";
            consoleOutput.innerHTML += '<span>Nombre cambiado!</span><br/>';
          }else{
            message = result;
            sendMessage();
            
          }
          input.value = "";
        }
    }, false);
   
   function sendMessage() {
       var xhttp = new XMLHttpRequest();
       xhttp.onreadystatechange = function() {
         if (this.readyState == 4 && this.status == 200) {
            var messages = JSON.parse(this.responseText);
            var result = "";
            messages.forEach(function(entry){
              result = "<span>" + entry.name + " -> " + entry.message + "</span><br/>" + result;
            });
            messagesOutput.innerHTML = result;
         }
       };

       var data = {};
       data.name = clientName;
       data.message = message;
       var json = JSON.stringify(data);
       
       xhttp.open("POST", "sendMessage", true);
       xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
       xhttp.send("json="+json);

       message = "";
  }

  setInterval(getMessages, 2000);

  function getMessages(){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var messages = JSON.parse(this.responseText);
            var result = "";
            messages.forEach(function(entry){
              result = "<span>" + entry.name + " -> " + entry.message + "</span><br/>" + result;
            });
            messagesOutput.innerHTML = result;
        }
      };
      xhttp.open("GET", "getMessages", true);
      xhttp.send();
  }
   
</script> 
</body>
</html>

)=====";
