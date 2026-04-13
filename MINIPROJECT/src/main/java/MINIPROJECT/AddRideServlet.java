package MINIPROJECT;

import java.io.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.WebServlet;
import java.sql.*;

@WebServlet("/AddRideServlet")
public class AddRideServlet extends HttpServlet {
       @Override

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {

        try {

            // Get form data
            String source = request.getParameter("source");
            String destination = request.getParameter("destination");
            int distance = Integer.parseInt(request.getParameter("distance").trim());
            int time = Integer.parseInt(request.getParameter("time").trim());
            int fare = Integer.parseInt(request.getParameter("fare").trim());
            int seats = Integer.parseInt(request.getParameter("seats").trim());
            String driver = request.getParameter("driver");

            // Load driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Connect DB
            Connection con = DriverManager.getConnection(
                "jdbc:mysql://127.0.0.1:3306/ridesync", "root", "25mca20298");

            // Insert data
            PreparedStatement ps = con.prepareStatement(
                "INSERT INTO rides(source,destination,distance,time,fare,seats,driver) VALUES(?,?,?,?,?,?,?)");

            ps.setString(1, source);
            ps.setString(2, destination);
            ps.setInt(3, distance);
            ps.setInt(4, time);
            ps.setInt(5, fare);
            ps.setInt(6, seats);
            ps.setString(7, driver);

            ps.executeUpdate();

            con.close();

            // ✅ DIRECT REDIRECT (BEST METHOD)
            response.sendRedirect("myride.html");

        } catch(Exception e) {
            e.printStackTrace();

            response.setContentType("text/html");
            PrintWriter out = response.getWriter();

            out.println("<h2 style='color:red;'>Error:</h2>");
            out.println("<pre>" + e + "</pre>");
        }
    }
}