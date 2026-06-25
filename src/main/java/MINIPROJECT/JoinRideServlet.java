package MINIPROJECT;

import java.io.*;
import java.sql.*;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.WebServlet;

@WebServlet("/JoinRideServlet")
public class JoinRideServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("application/json");

        String idParam = request.getParameter("id");
        String user = request.getParameter("user");   // 🔥 NEW

        // 🔥 VALIDATION
        if (idParam == null || user == null || user.trim().isEmpty()) {
            response.getWriter().write("{\"status\":\"error\",\"message\":\"Missing data\"}");
            return;
        }

        int id = Integer.parseInt(idParam);

        Connection con = null;
        PreparedStatement updateSeats = null;
        PreparedStatement insertBooking = null;

        try {

            Class.forName("com.mysql.cj.jdbc.Driver");

            con = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/ridesync", "root", "25mca20298");

            con.setAutoCommit(false); // 🔥 START TRANSACTION

            // 🔥 1. DECREASE SEATS (SAFE)
            updateSeats = con.prepareStatement(
                "UPDATE rides SET seats = seats - 1 WHERE id = ? AND seats > 0"
            );

            updateSeats.setInt(1, id);

            int rows = updateSeats.executeUpdate();

            if (rows > 0) {

                // 🔥 2. STORE BOOKING
                insertBooking = con.prepareStatement(
                    "INSERT INTO bookings (ride_id, user_name) VALUES (?, ?)"
                );

                insertBooking.setInt(1, id);
                insertBooking.setString(2, user);

                insertBooking.executeUpdate();

                con.commit(); // ✅ SAVE BOTH

                response.getWriter().write(
                    "{\"status\":\"success\",\"message\":\"Ride joined successfully 🚗\"}"
                );

            } else {

                con.rollback(); // ❌ no seat → rollback

                response.getWriter().write(
                    "{\"status\":\"full\",\"message\":\"No seats available ❌\"}"
                );
            }

        } catch (Exception e) {

            try {
                if (con != null) con.rollback();
            } catch (Exception ex) {
                ex.printStackTrace();
            }

            e.printStackTrace();

            response.getWriter().write(
                "{\"status\":\"error\",\"message\":\"Server error\"}"
            );

        } finally {

            try {
                if (updateSeats != null) updateSeats.close();
                if (insertBooking != null) insertBooking.close();
                if (con != null) con.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }
}