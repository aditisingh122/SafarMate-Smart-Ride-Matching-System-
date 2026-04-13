CREATE DATABASE ridesync;

USE ridesync;

CREATE TABLE rides (
    id INT AUTO_INCREMENT PRIMARY KEY,
    source VARCHAR(50),
    destination VARCHAR(50),
    distance INT,
    time INT,
    fare INT,
    seats INT,
    driver VARCHAR(50)
);
select  * from ridesync;
