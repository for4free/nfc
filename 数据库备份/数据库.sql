-- phpMyAdmin SQL Dump
-- version 3.5.8
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2015 年 12 月 24 日 19:04
-- 服务器版本: 5.1.50-community-log
-- PHP 版本: 5.2.17

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `data`
--

-- --------------------------------------------------------

--
-- 表的结构 `dmb`
--

CREATE TABLE IF NOT EXISTS `dmb` (
  `id` int(15) NOT NULL,
  `no` varchar(20) NOT NULL,
  `sum` int(11) NOT NULL,
  `lea` varchar(20) DEFAULT NULL,
  `att` varchar(20) DEFAULT NULL,
  `leav` varchar(20) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `dmb`
--

INSERT INTO `dmb` (`id`, `no`, `sum`, `lea`, `att`, `leav`) VALUES
(1, '201301052101', 51, '24', '0', '0'),
(2, '201301052102', 55, '12', '0', '0'),
(3, '201301052103', 48, '1', '0', '0'),
(4, '201301052104', 2, '0', '0', '0');

-- --------------------------------------------------------

--
-- 表的结构 `dmb111`
--

CREATE TABLE IF NOT EXISTS `dmb111` (
  `id` varchar(20) COLLATE hp8_bin DEFAULT NULL,
  `no` varchar(20) COLLATE hp8_bin DEFAULT NULL,
  `att` varchar(20) COLLATE hp8_bin DEFAULT NULL,
  `sum` varchar(20) COLLATE hp8_bin DEFAULT NULL,
  `lea` varchar(20) COLLATE hp8_bin DEFAULT NULL,
  `leav` varchar(20) COLLATE hp8_bin DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=hp8 COLLATE=hp8_bin;

--
-- 转存表中的数据 `dmb111`
--

INSERT INTO `dmb111` (`id`, `no`, `att`, `sum`, `lea`, `leav`) VALUES
('1', '201301052101', '0', '0', '2', '1'),
('2', '201301052103', '0', '1', '0', '0'),
('3', '201301052104', '0', '0', '0', '0'),
('4', '', '0', '0', '0', '0');

-- --------------------------------------------------------

--
-- 表的结构 `dyb`
--

CREATE TABLE IF NOT EXISTS `dyb` (
  `bm` varchar(20) NOT NULL,
  `id` varchar(20) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `dyb`
--

INSERT INTO `dyb` (`bm`, `id`) VALUES
('dmb', '15001'),
('dmb111', '15001');

-- --------------------------------------------------------

--
-- 表的结构 `jsb`
--

CREATE TABLE IF NOT EXISTS `jsb` (
  `id` varchar(20) NOT NULL,
  `pass` varchar(50) NOT NULL,
  `hol` varchar(20) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `jsb`
--

INSERT INTO `jsb` (`id`, `pass`, `hol`) VALUES
('15001', '698d51a19d8a121ce581499d7b701668', '0'),
('15002', '6216f8a75fd5bb3d5f22b6f9958cdede3fc086c2', '1');

-- --------------------------------------------------------

--
-- 表的结构 `qjb`
--

CREATE TABLE IF NOT EXISTS `qjb` (
  `no` varchar(20) CHARACTER SET utf8 NOT NULL,
  `start` varchar(20) CHARACTER SET utf8 NOT NULL,
  `end` varchar(20) CHARACTER SET utf8 NOT NULL,
  `pas` varchar(20) COLLATE hp8_bin DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=hp8 COLLATE=hp8_bin;

--
-- 转存表中的数据 `qjb`
--

INSERT INTO `qjb` (`no`, `start`, `end`, `pas`) VALUES
('201301052101', '1', '1', '15002');

-- --------------------------------------------------------

--
-- 表的结构 `zb`
--

CREATE TABLE IF NOT EXISTS `zb` (
  `no` varchar(20) NOT NULL,
  `name` varchar(10) NOT NULL,
  `cardid` varchar(20) NOT NULL,
  `leav` varchar(20) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `zb`
--

INSERT INTO `zb` (`no`, `name`, `cardid`, `leav`) VALUES
('201301052102', '习平', 'C7EB2FA4', '0'),
('201301052101', '李白', '002BAB9D', '0'),
('201301052103', '唐僧', 'F50103DC', '0'),
('201301052104', '吉亮', 'F5D204DC', '0');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
