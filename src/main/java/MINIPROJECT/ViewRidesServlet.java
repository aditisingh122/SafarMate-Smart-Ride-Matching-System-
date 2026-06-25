package MINIPROJECT;

import java.io.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.WebServlet;
import java.sql.*;

@WebServlet("/ViewRidesServlet")
public class ViewRidesServlet extends HttpServlet {
@Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {

        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        try {

            Class.forName("com.mysql.cj.jdbc.Driver");

            Connection con = DriverManager.getConnection(
                "jdbc:mysql://127.0.0.1:3306/ridesync", "root", "25mca20298");

            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery("SELECT * FROM rides");

            out.print("[");
            boolean first = true;

            while(rs.next()) {

                if(!first) out.print(",");

                out.print("{");
                out.print("\"id\":" + rs.getInt("id") + ",");
                out.print("\"source\":\"" + rs.getString("source") + "\",");
                out.print("\"destination\":\"" + rs.getString("destination") + "\",");
                out.print("\"distance\":" + rs.getInt("distance") + ",");
                out.print("\"time\":" + rs.getInt("time") + ",");
                out.print("\"fare\":" + rs.getInt("fare") + ",");
                out.print("\"seats\":" + rs.getInt("seats") + ",");
                out.print("\"driver\":\"" + rs.getString("driver") + "\"");
                out.print("}");

                first = false;
            }

            out.print("]");
            con.close();

        } catch(Exception e) {
            e.printStackTrace();
            out.print("[]");
        }
    }
}