-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Mar 14, 2022 at 06:23 PM
-- Server version: 10.4.22-MariaDB
-- PHP Version: 8.1.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `plant_companion`
--

-- --------------------------------------------------------

--
-- Table structure for table `config`
--

CREATE TABLE `config` (
  `id` int(11) NOT NULL,
  `plant_id` varchar(255) NOT NULL,
  `ssid` varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `status` int(2) NOT NULL DEFAULT 0,
  `last_update` varchar(255) NOT NULL,
  `user` varchar(100) DEFAULT NULL,
  `plant_type` int(5) NOT NULL DEFAULT 0,
  `manual_pump` varchar(5) NOT NULL DEFAULT '0',
  `moisture` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `config`
--

INSERT INTO `config` (`id`, `plant_id`, `ssid`, `password`, `status`, `last_update`, `user`, `plant_type`, `manual_pump`, `moisture`) VALUES
(1, 'COMPANION-000001', NULL, NULL, 1, '1647214425', 'kingmr2019@gmail.com', 1, '0', '30');

-- --------------------------------------------------------

--
-- Table structure for table `rating`
--

CREATE TABLE `rating` (
  `id` int(11) NOT NULL,
  `image_url` varchar(5000) NOT NULL,
  `rating` varchar(255) NOT NULL,
  `plant_id` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `rating`
--

INSERT INTO `rating` (`id`, `image_url`, `rating`, `plant_id`) VALUES
(1, 'uploads/1647213339612-slider_1.jpg', 'Healthy', 'COMPANION-000001');

-- --------------------------------------------------------

--
-- Table structure for table `sensor_data`
--

CREATE TABLE `sensor_data` (
  `id` int(11) NOT NULL,
  `plant_id` varchar(255) NOT NULL,
  `moisture` float NOT NULL,
  `humidity` float NOT NULL,
  `light` float NOT NULL,
  `color` varchar(255) NOT NULL,
  `temperature` float NOT NULL,
  `update_time` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `sensor_data`
--

INSERT INTO `sensor_data` (`id`, `plant_id`, `moisture`, `humidity`, `light`, `color`, `temperature`, `update_time`) VALUES
(1, 'COMPANION-000001', 61.39, 40, 0, 'Green', 25.4, '2022-03-14 00:06:29'),
(2, 'COMPANION-000001', 60.9, 41, 0, 'Green', 25.4, '2022-03-14 00:06:57'),
(3, 'COMPANION-000001', 60.8, 41, 0, 'Green', 25.4, '2022-03-14 00:07:25'),
(4, 'COMPANION-000001', 60.8, 41, 0, 'Green', 25.4, '2022-03-14 00:07:53'),
(5, 'COMPANION-000001', 60.7, 41, 0, 'Green', 25.4, '2022-03-14 00:08:21'),
(6, 'COMPANION-000001', 60.7, 41, 0, 'Green', 25.3, '2022-03-14 00:08:50'),
(7, 'COMPANION-000001', 60.7, 41, 0, 'Green', 25.3, '2022-03-14 00:09:18'),
(8, 'COMPANION-000001', 59.53, 41, 0, 'Green', 25.3, '2022-03-14 00:09:46'),
(9, 'COMPANION-000001', 86.41, 0, 0, 'Unknown', 0, '2022-03-14 00:17:13'),
(10, 'COMPANION-000001', 67.64, 0, 0, 'Unknown', 0, '2022-03-14 00:17:41'),
(11, 'COMPANION-000001', 57.77, 41, 0, 'Unknown', 25.7, '2022-03-14 00:18:09'),
(12, 'COMPANION-000001', 57.28, 41, 0, 'Unknown', 25.6, '2022-03-14 00:18:37'),
(13, 'COMPANION-000001', 58.26, 0, 0, 'Orange', 0, '2022-03-14 00:19:05'),
(14, 'COMPANION-000001', 67.06, 41, 0, 'Orange', 25.7, '2022-03-14 00:19:33'),
(15, 'COMPANION-000001', 65.2, 42, 0, 'Unknown', 25.5, '2022-03-14 00:20:01'),
(16, 'COMPANION-000001', 57.77, 0, 0, 'Orange', 0, '2022-03-14 00:20:29'),
(17, 'COMPANION-000001', 57.18, 41, 0, 'Orange', 25.6, '2022-03-14 00:20:57'),
(18, 'COMPANION-000001', 57.38, 42, 0, 'Orange', 25.5, '2022-03-14 00:21:25'),
(19, 'COMPANION-000001', 57.77, 42, 0, 'Orange', 25.5, '2022-03-14 00:21:54'),
(20, 'COMPANION-000001', 57.48, 42, 0, 'Orange', 25.6, '2022-03-14 00:22:22'),
(21, 'COMPANION-000001', 60.02, 42, 0, 'Orange', 25.6, '2022-03-14 00:22:50'),
(22, 'COMPANION-000001', 57.97, 43, 0, 'Red', 25.6, '2022-03-14 00:23:18'),
(23, 'COMPANION-000001', 58.36, 42, 0, 'Yellow', 25.6, '2022-03-14 00:23:47'),
(24, 'COMPANION-000001', 58.26, 42, 0, 'Unknown', 25.6, '2022-03-14 00:24:15'),
(25, 'COMPANION-000001', 58.36, 42, 0, 'Green', 25.7, '2022-03-14 00:24:43'),
(26, 'COMPANION-000001', 58.65, 42, 0, 'Unknown', 25.7, '2022-03-14 00:25:11'),
(27, 'COMPANION-000001', 58.26, 43, 0, 'Unknown', 25.7, '2022-03-14 00:25:39'),
(28, 'COMPANION-000001', 58.65, 42, 0, 'Green', 25.7, '2022-03-14 00:26:07'),
(29, 'COMPANION-000001', 58.75, 42, 0, 'Unknown', 25.7, '2022-03-14 00:26:36'),
(30, 'COMPANION-000001', 59.53, 42, 0, 'Orange', 25.7, '2022-03-14 00:27:05'),
(31, 'COMPANION-000001', 59.53, 43, 0, 'Yellow', 25.7, '2022-03-14 00:27:34'),
(32, 'COMPANION-000001', 60.02, 42, 0, 'Yellow', 25.7, '2022-03-14 00:28:02'),
(33, 'COMPANION-000001', 59.43, 43, 0, 'Unknown', 25.7, '2022-03-14 00:28:33'),
(34, 'COMPANION-000001', 58.65, 42, 0, 'Unknown', 25.7, '2022-03-14 00:29:01'),
(35, 'COMPANION-000001', 58.26, 43, 0, 'Unknown', 25.7, '2022-03-14 00:29:29'),
(36, 'COMPANION-000001', 59.14, 43, 0, 'Unknown', 25.6, '2022-03-14 00:29:57'),
(37, 'COMPANION-000001', 57.77, 43, 0, 'Green', 25.6, '2022-03-14 00:30:25'),
(38, 'COMPANION-000001', 68.91, 0, 0, 'Unknown', 0, '2022-03-14 00:30:53'),
(39, 'COMPANION-000001', 69.11, 0, 0, 'Unknown', 0, '2022-03-14 00:31:22'),
(40, 'COMPANION-000001', 58.16, 43, 0, 'Green', 25.7, '2022-03-14 00:31:51'),
(41, 'COMPANION-000001', 57.87, 44, 0, 'Green', 25.7, '2022-03-14 00:32:20'),
(42, 'COMPANION-000001', 57.77, 43, 0, 'Green', 25.7, '2022-03-14 00:32:48'),
(43, 'COMPANION-000001', 57.77, 43, 0, 'Unknown', 25.6, '2022-03-14 00:33:17'),
(44, 'COMPANION-000001', 57.28, 43, 0, 'Unknown', 25.6, '2022-03-14 00:33:45');

-- --------------------------------------------------------

--
-- Table structure for table `threshold`
--

CREATE TABLE `threshold` (
  `id` int(11) NOT NULL,
  `moisture` int(11) NOT NULL,
  `temperature` int(11) NOT NULL,
  `humidity` int(11) NOT NULL,
  `light` varchar(100) NOT NULL,
  `plant_type` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `threshold`
--

INSERT INTO `threshold` (`id`, `moisture`, `temperature`, `humidity`, `light`, `plant_type`) VALUES
(1, 30, 21, 30, 'Green', 1),
(2, 20, 15, 23, 'Yellow', 2),
(3, 25, 18, 38, 'Orange', 3);

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `name` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `password` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `name`, `email`, `password`) VALUES
(1, 'Chinonso Ngwu', 'kingmr2019@gmail.com', '123'),
(3, 'zzzzz', 'kingmrz2019@gmail.com', '123'),
(4, 'MrScan', 'kingmrz20d19@gmail.com', '123'),
(5, 'MrScan', 'kingmrz20dd19@gmail.com', '123'),
(6, 'MrScan', 'kingmrz20dd1n9@gmail.com', '123'),
(7, 'MrScan', 'kingmrz20dnnnd19@gmail.com', '123'),
(8, 'MrScan', 'hhh@gmail.com', '123'),
(9, 'aaaa', 'hhkhkhh@gmail.com', 'bbb'),
(10, 'MrScan', 'hhhh@gmail.com', '123'),
(11, 'MrScan', 'ngwucs@gmail.com', 'th');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `config`
--
ALTER TABLE `config`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `plant_id` (`plant_id`);

--
-- Indexes for table `rating`
--
ALTER TABLE `rating`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sensor_data`
--
ALTER TABLE `sensor_data`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `threshold`
--
ALTER TABLE `threshold`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `email` (`email`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `config`
--
ALTER TABLE `config`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `rating`
--
ALTER TABLE `rating`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `sensor_data`
--
ALTER TABLE `sensor_data`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=45;

--
-- AUTO_INCREMENT for table `threshold`
--
ALTER TABLE `threshold`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
