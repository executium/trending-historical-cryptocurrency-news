<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html> 
<html>
<head runat="server">
<title></title>
</head>
<body>

<pre id="GFG_DOWN"> </pre>

<script> 

    var div1 = document.getElementById("GFG_DOWN");
    var obj =<%=Out%>;
    div1.innerHTML = JSON.stringify(obj, undefined, 4);

</script>

</body>
</html>