package MINIPROJECT;

import java.io.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.WebServlet;
import java.sql.*;

@WebServlet("/DeleteRideServlet")
public class DeleteRideServlet extends HttpServlet {
    @Override

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {

        try {

            int id = Integer.parseInt(request.getParameter("id"));

            Class.forName("com.mysql.cj.jdbc.Driver");

            Connection con = DriverManager.getConnection(
                "jdbc:mysql://127.0.0.1:3306/ridesync", "root", "25mca20298");

            PreparedStatement ps = con.prepareStatement(
                "DELETE FROM rides WHERE id=?");

            ps.setInt(1, id);
            ps.executeUpdate();

            con.close();

        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}