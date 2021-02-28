-- MySQL dump 10.13  Distrib 8.0.23, for Linux (x86_64)
--
-- Host: localhost    Database: education_practice
-- ------------------------------------------------------
-- Server version	8.0.23-0ubuntu0.20.10.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Citizen`
--

DROP TABLE IF EXISTS `Citizen`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Citizen` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `FirstName` varchar(50) NOT NULL,
  `LastName` varchar(50) NOT NULL,
  `Patronymic` varchar(50) NOT NULL,
  `Date_of_birth` date NOT NULL,
  `Rank_id` int NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Patronymic` (`Patronymic`),
  KEY `Rank_id` (`Rank_id`),
  CONSTRAINT `Citizen_ibfk_1` FOREIGN KEY (`Rank_id`) REFERENCES `Rank` (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Citizen`
--

LOCK TABLES `Citizen` WRITE;
/*!40000 ALTER TABLE `Citizen` DISABLE KEYS */;
INSERT INTO `Citizen` VALUES (1,'Алексей','Беленов','Дмитриевич','2007-12-23',2),(3,'Дмитрий','Меньшиков','Павлович','2005-06-13',2),(4,'Владимир','Александрович','Иванов','2000-02-22',1),(5,'Яков','Смагин','Валерьевич','1985-10-26',1),(6,'Test2','Test2','Test2','2021-02-23',5),(7,'Test','Test','Test','2021-02-23',4),(8,'Test22','Test22','Test22','0001-02-01',1);
/*!40000 ALTER TABLE `Citizen` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Commander_of_company`
--

DROP TABLE IF EXISTS `Commander_of_company`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Commander_of_company` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Id_of_citizen` int NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Id_of_citizen` (`Id_of_citizen`),
  CONSTRAINT `Commander_of_company_ibfk_1` FOREIGN KEY (`Id_of_citizen`) REFERENCES `Citizen` (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Commander_of_company`
--

LOCK TABLES `Commander_of_company` WRITE;
/*!40000 ALTER TABLE `Commander_of_company` DISABLE KEYS */;
INSERT INTO `Commander_of_company` VALUES (6,4),(7,5),(12,8);
/*!40000 ALTER TABLE `Commander_of_company` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Commander_of_unit`
--

DROP TABLE IF EXISTS `Commander_of_unit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Commander_of_unit` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Id_citizen` int NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Id_citizen` (`Id_citizen`),
  CONSTRAINT `Commander_of_unit_ibfk_1` FOREIGN KEY (`Id_citizen`) REFERENCES `Citizen` (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Commander_of_unit`
--

LOCK TABLES `Commander_of_unit` WRITE;
/*!40000 ALTER TABLE `Commander_of_unit` DISABLE KEYS */;
INSERT INTO `Commander_of_unit` VALUES (1,1),(4,3);
/*!40000 ALTER TABLE `Commander_of_unit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Company`
--

DROP TABLE IF EXISTS `Company`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Company` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Person_number` int NOT NULL,
  `Id_of_unit` int NOT NULL,
  `Id_commander_of_company` int NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Id_of_unit` (`Id_of_unit`),
  UNIQUE KEY `Id_commander_of_company` (`Id_commander_of_company`),
  CONSTRAINT `Company_ibfk_1` FOREIGN KEY (`Id_commander_of_company`) REFERENCES `Commander_of_company` (`Id`),
  CONSTRAINT `Company_ibfk_2` FOREIGN KEY (`Id_of_unit`) REFERENCES `Unit` (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Company`
--

LOCK TABLES `Company` WRITE;
/*!40000 ALTER TABLE `Company` DISABLE KEYS */;
INSERT INTO `Company` VALUES (1,22,8,7),(5,12,7,6);
/*!40000 ALTER TABLE `Company` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Device`
--

DROP TABLE IF EXISTS `Device`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Device` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(50) NOT NULL,
  `Target_of_device` varchar(50) NOT NULL,
  `Have` tinyint(1) NOT NULL,
  `Number` int NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Name` (`Name`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Device`
--

LOCK TABLES `Device` WRITE;
/*!40000 ALTER TABLE `Device` DISABLE KEYS */;
INSERT INTO `Device` VALUES (4,'Test100','Test',1,2);
/*!40000 ALTER TABLE `Device` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Device_and_company`
--

DROP TABLE IF EXISTS `Device_and_company`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Device_and_company` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Id_of_device` int NOT NULL,
  `Id_of_company` int NOT NULL,
  PRIMARY KEY (`Id`),
  KEY `Id_of_device` (`Id_of_device`),
  KEY `Id_of_company` (`Id_of_company`),
  CONSTRAINT `Device_and_company_ibfk_1` FOREIGN KEY (`Id_of_device`) REFERENCES `Device` (`Id`),
  CONSTRAINT `Device_and_company_ibfk_2` FOREIGN KEY (`Id_of_company`) REFERENCES `Company` (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Device_and_company`
--

LOCK TABLES `Device_and_company` WRITE;
/*!40000 ALTER TABLE `Device_and_company` DISABLE KEYS */;
INSERT INTO `Device_and_company` VALUES (4,4,5);
/*!40000 ALTER TABLE `Device_and_company` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Rank`
--

DROP TABLE IF EXISTS `Rank`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Rank` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(50) NOT NULL,
  `Competence` varchar(100) NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Name` (`Name`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Rank`
--

LOCK TABLES `Rank` WRITE;
/*!40000 ALTER TABLE `Rank` DISABLE KEYS */;
INSERT INTO `Rank` VALUES (1,'Командир роты','Командование ротой'),(2,'Командир части','Командование частью'),(4,'Рядовой','Исполнять команды командования'),(5,'Прапорщик','какие-то');
/*!40000 ALTER TABLE `Rank` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Task`
--

DROP TABLE IF EXISTS `Task`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Task` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(50) NOT NULL,
  `Description` varchar(50) NOT NULL,
  `Id_of_citizen` int NOT NULL,
  PRIMARY KEY (`Id`),
  KEY `Id_of_citizen` (`Id_of_citizen`),
  CONSTRAINT `Task_ibfk_1` FOREIGN KEY (`Id_of_citizen`) REFERENCES `Citizen` (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Task`
--

LOCK TABLES `Task` WRITE;
/*!40000 ALTER TABLE `Task` DISABLE KEYS */;
INSERT INTO `Task` VALUES (2,'Test','Test',1);
/*!40000 ALTER TABLE `Task` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Unit`
--

DROP TABLE IF EXISTS `Unit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Unit` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Unit_location` varchar(50) NOT NULL,
  `Id_commander_of_unit` int NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Id_commander_of_unit` (`Id_commander_of_unit`),
  CONSTRAINT `Unit_ibfk_1` FOREIGN KEY (`Id_commander_of_unit`) REFERENCES `Commander_of_unit` (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Unit`
--

LOCK TABLES `Unit` WRITE;
/*!40000 ALTER TABLE `Unit` DISABLE KEYS */;
INSERT INTO `Unit` VALUES (7,'Питер',1),(8,'Беларусь',4);
/*!40000 ALTER TABLE `Unit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `User`
--

DROP TABLE IF EXISTS `User`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `User` (
  `Id` int NOT NULL AUTO_INCREMENT,
  `Login` varchar(60) NOT NULL,
  `Password` varchar(60) NOT NULL,
  `Type` varchar(50) NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Login` (`Login`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `User`
--

LOCK TABLES `User` WRITE;
/*!40000 ALTER TABLE `User` DISABLE KEYS */;
INSERT INTO `User` VALUES (1,'Root','Root','Администратор'),(4,'Test','Test','Офицер'),(6,'Test2','Test10','Администратор');
/*!40000 ALTER TABLE `User` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-02-28 20:20:53
