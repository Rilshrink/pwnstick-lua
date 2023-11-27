#define STR(a) #a

String style_css = STR(
  body {
    background: #36393e;
    margin: 0;
    color: #bfbfbf;
    font-family: sans-serif;
  }  
  code {
    background: #ccc;
    padding: 3px;
    border-radius: 3px;
    word-break: keep-all !important;
    color: #000;
    line-height: 24px;
  }
);

String index_html = STR(
  <!DOCTYPE html>
   <html>
   <head>
      <title>PwnStick (LUA EDITION)</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <link rel="stylesheet" type="text/css" href="style.css">
      <script src="script.js"></script>
    </head>
    <body>
        <div>
            <h1>ESP32-S3 PwnStick (LUA EDITION)</h1>
            <p>Created by LockManipulator</p>
            <p>Modified by Rilshrink</p>
        </div>
        <div>
            <textarea class="code" id="lua-code" spellcheck="false" rows="16" cols="80" name="input" maxlength="2000"></textarea>
            <br>
            <button id="run-code" onclick="send_code()">Run Code</button>
            <button onclick="stop_code()">Stop Lua Script</button>
            <input id="file">
            <button onclick="save_code()">Save File</button>
            <select name="files" id="files">
            </select>
            <button onclick="reload_file_list()">R</button>
            <button onclick="load_code()">Load File</button>
            <button onclick="remove_file()">Delete File</button>
        </div>
</body>
</html>
);

String script_js = STR(
function stop_code() {
              let xhr = new XMLHttpRequest();
                xhr.open("POST", "http://" + window.location.host + "/stop", true);
                xhr.send();
            }
  
function send_code() {
              let code = document.getElementById("lua-code").value;
              let xhr = new XMLHttpRequest();
                xhr.open("POST", "http://" + window.location.host + "/run", true);
                xhr.send(code);
            }
            function remove_file() {
              let xhr = new XMLHttpRequest();
              let path = document.getElementById("files").value;

                 if(!path.startsWith("/"))
                  path = "/" + path;
                
                xhr.open('GET', "http://" + window.location.host + "/remove?file=" + path, true);
                xhr.send();
            }
            function reload_file_list() {
              let xhr = new XMLHttpRequest();

                xhr.onreadystatechange = function () {
                    if (this.readyState != 4) return;

                    if (this.status == 200) {
                        let files = this.responseText.split(",");
                        document.getElementById("files").innerHTML = "";
                        
                        files.forEach((file) => {
                          if(file.replaceAll(" ", "") == "")
                            return;
                          let option = document.createElement("option");
                            option.value = file;
                            option.innerText = file;
                            document.getElementById("files").appendChild(option);
                        });
                    }
                };
                
                xhr.open('GET', "http://" + window.location.host + "/files", true);
                xhr.send();
            }
            function load_code() {
              let xhr = new XMLHttpRequest();

                xhr.onreadystatechange = function () {
                    if (this.readyState != 4) return;

                    if (this.status == 200) {
                        let code = this.responseText;
                        
                        document.getElementById("lua-code").value = code;
                    }
                };
        
                let path = document.getElementById("files").value;

                 if(!path.startsWith("/"))
                  path = "/" + path;
                
                xhr.open('GET', "http://" + window.location.host + "/load?file=" + path, true);
                xhr.send();
            }
            function save_code() {
              let code = document.getElementById("lua-code").value;
                let path = document.getElementById("file").value;
                
                if(!path.startsWith("/"))
                  path = "/" + path;
                
              let xhr = new XMLHttpRequest();
                xhr.open("POST", "http://" + window.location.host + "/save?file=" + path, true);
                xhr.send(code);
            }
);
