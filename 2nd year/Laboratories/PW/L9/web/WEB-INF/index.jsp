<%@ page import="com.alex.pw.Thread" %>
<%@ page import="java.util.ArrayList" %>
<%-- Created by IntelliJ IDEA. --%>
<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head>
    <title></title>
</head>
<body>
<%
    ArrayList threads = (ArrayList) request.getAttribute("threads");
    for (Object thread : threads) {
        out.print("<p>");
        out.print(((Thread) thread).getContent());
        out.print("</p>");
    }
%>
</body>
</html>