package MINIPROJECT;

import java.io.*;
import java.sql.*;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.WebServlet;

@WebServlet("/MatchServlet")
public class MatchServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("application/json");

        String userFrom = request.getParameter("from");
        String userTo = request.getParameter("to");

        if (userFrom == null || userFrom.isEmpty()) userFrom = "ARA";
        if (userTo == null || userTo.isEmpty()) userTo = "PATNA";

        Connection con = null;

        try {

            // ✅ DB CONNECTION
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/ridesync", "root", "25mca20298");

            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery("SELECT * FROM rides");

            // ✅ RUN C++ PROGRAM
            ProcessBuilder pb = new ProcessBuilder(
                    "C:\\Users\\ranvi\\OneDrive\\Desktop\\sem2 project\\matchalgo.exe",
                    userFrom,
                    userTo
            );

            Process process = pb.start();

            // 🔥 SEND DATA TO C++ (stdin)
            BufferedWriter writer = new BufferedWriter(
                    new OutputStreamWriter(process.getOutputStream())
            );

            while (rs.next()) {

                String line =
                        rs.getInt("id") + "," +
                        rs.getString("driver") + "," +
                        rs.getString("source") + "," +
                        rs.getString("destination") + "," +
                        rs.getInt("fare") + "," +
                        rs.getInt("seats");   // ✅ FIXED (IMPORTANT)

                writer.write(line);
                writer.newLine();

                // 🔍 DEBUG (optional)
                System.out.println("Sent to C++: " + line);
            }

            writer.flush();
            writer.close();

            // 🔥 READ OUTPUT FROM C++
            BufferedReader reader = new BufferedReader(
                    new InputStreamReader(process.getInputStream())
            );

            StringBuilder output = new StringBuilder();
            String line;

            while ((line = reader.readLine()) != null) {
                output.append(line);
            }

            reader.close();

            // ✅ SEND RESPONSE
            response.getWriter().write(output.toString());

        } catch (Exception e) {

            e.printStackTrace();
            response.setContentType("text/plain");
            e.printStackTrace(response.getWriter());

        } finally {
            try {
                if (con != null) con.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}