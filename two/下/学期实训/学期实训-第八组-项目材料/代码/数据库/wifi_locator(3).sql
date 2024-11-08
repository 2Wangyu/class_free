/*
 Navicat Premium Data Transfer

 Source Server         : Remote-Link
 Source Server Type    : MySQL
 Source Server Version : 80037 (8.0.37-0ubuntu0.22.04.3)
 Source Host           : 119.3.163.32:3306
 Source Schema         : wifi_locator

 Target Server Type    : MySQL
 Target Server Version : 80037 (8.0.37-0ubuntu0.22.04.3)
 File Encoding         : 65001

 Date: 15/07/2024 20:24:55
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for login
-- ----------------------------
DROP TABLE IF EXISTS `login`;
CREATE TABLE `login`  (
  `uid` int NOT NULL AUTO_INCREMENT,
  `username` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户名',
  `password` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `ctime` datetime NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `name` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT '起个名字可以让人更好的认识你',
  PRIMARY KEY (`username`) USING BTREE,
  UNIQUE INDEX `unique_id`(`uid` ASC) USING BTREE COMMENT '唯一性id'
) ENGINE = InnoDB AUTO_INCREMENT = 35 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of login
-- ----------------------------
INSERT INTO `login` VALUES (1, 'admin', 'p123', '2024-07-15 11:14:22', 'yw');
INSERT INTO `login` VALUES (24, 'cxk111', '1', '2024-07-14 14:53:10', '起个名字可以让人更好的认识你');
INSERT INTO `login` VALUES (10, 'test', 'test', '2024-07-14 15:43:32', '起个名字可以让人更好的认识你');
INSERT INTO `login` VALUES (25, 'test1', 't1', '2024-07-14 22:36:18', '22300');
INSERT INTO `login` VALUES (2, 'user1', 'p1', '2024-07-15 18:47:07', 'uuyu');
INSERT INTO `login` VALUES (3, 'user2', 'p2', '2024-07-15 11:05:19', '常高林');
INSERT INTO `login` VALUES (4, 'user3', 'p3', '2024-07-08 22:10:33', '小杨');
INSERT INTO `login` VALUES (5, 'user4', 'p4', '2024-07-12 21:11:25', '旺旺旺仔仔仔');
INSERT INTO `login` VALUES (33, 'yu', '123', '2024-07-15 18:45:55', '起个名字可以让人更好的认识你');

-- ----------------------------
-- Table structure for uic_path
-- ----------------------------
DROP TABLE IF EXISTS `uic_path`;
CREATE TABLE `uic_path`  (
  `uid` int NOT NULL,
  `user_ic_path` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`uid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of uic_path
-- ----------------------------
INSERT INTO `uic_path` VALUES (1, '1.jpg');
INSERT INTO `uic_path` VALUES (2, '2.jpg');
INSERT INTO `uic_path` VALUES (3, '3.jpg');
INSERT INTO `uic_path` VALUES (4, '4.jpg');
INSERT INTO `uic_path` VALUES (25, '25.jpg');

-- ----------------------------
-- Table structure for user_comment
-- ----------------------------
DROP TABLE IF EXISTS `user_comment`;
CREATE TABLE `user_comment`  (
  `uid` int NOT NULL COMMENT '用户id',
  `sid` int NOT NULL COMMENT '商店id',
  `stars` float NULL DEFAULT NULL COMMENT '星级',
  `comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '评论',
  `data` datetime NULL DEFAULT CURRENT_TIMESTAMP,
  `id` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 97 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user_comment
-- ----------------------------
INSERT INTO `user_comment` VALUES (2, 1, 4, '香的', '2024-07-09 15:33:52', 2);
INSERT INTO `user_comment` VALUES (2, 2, 4, '好吃', '2024-07-09 15:47:05', 3);
INSERT INTO `user_comment` VALUES (3, 3, 5, '想喝可乐', '2024-07-09 15:53:52', 4);
INSERT INTO `user_comment` VALUES (3, 4, 5, '想吃冰淇凌', '2024-07-09 15:55:02', 5);
INSERT INTO `user_comment` VALUES (3, 2, 3, '太咸啦', '2024-07-09 15:56:27', 8);
INSERT INTO `user_comment` VALUES (4, 3, 3, '太辣了', '2024-07-09 15:56:50', 9);
INSERT INTO `user_comment` VALUES (4, 4, 3, '不好吃', '2024-07-09 15:57:28', 10);
INSERT INTO `user_comment` VALUES (1, 0, 5, '我的新评论我喜欢阿喜烧烤', '2024-07-09 22:18:53', 11);
INSERT INTO `user_comment` VALUES (5, 5, 5, '好喝', '2024-07-12 21:17:32', 12);
INSERT INTO `user_comment` VALUES (1, 5, 4, '欧克！', '2024-07-12 21:17:57', 13);
INSERT INTO `user_comment` VALUES (1, 4, 4, '很好', '2024-07-12 21:19:16', 14);
INSERT INTO `user_comment` VALUES (2, 0, 4, 'lol', '2024-07-12 21:22:13', 17);
INSERT INTO `user_comment` VALUES (2, 0, 4, '美味，爱来自北京', '2024-07-12 21:25:10', 18);
INSERT INTO `user_comment` VALUES (2, 0, 4, '怎么回事', '2024-07-12 21:25:50', 19);
INSERT INTO `user_comment` VALUES (1, 0, 4, '挺干净的', '2024-07-12 21:34:03', 20);
INSERT INTO `user_comment` VALUES (3, 0, 4, '这是我最满意的一次', '2024-07-12 21:43:31', 21);
INSERT INTO `user_comment` VALUES (10, 1, 5, '测试默认头像', '2024-07-14 15:42:18', 35);
INSERT INTO `user_comment` VALUES (25, 4, 4, '123456', '2024-07-14 19:52:06', 39);
INSERT INTO `user_comment` VALUES (1, 2, 5, '1', '2024-07-14 23:51:57', 87);
INSERT INTO `user_comment` VALUES (1, 2, 5, '2', '2024-07-14 23:52:00', 88);
INSERT INTO `user_comment` VALUES (1, 2, 5, '3', '2024-07-14 23:52:03', 89);
INSERT INTO `user_comment` VALUES (1, 0, 4, '一般', '2024-07-15 10:25:57', 90);
INSERT INTO `user_comment` VALUES (1, 1, 5, '1', '2024-07-15 11:18:02', 91);
INSERT INTO `user_comment` VALUES (1, 1, 5, '2', '2024-07-15 11:18:06', 92);
INSERT INTO `user_comment` VALUES (1, 1, 5, '3', '2024-07-15 11:18:10', 93);
INSERT INTO `user_comment` VALUES (2, 2, 5, '1', '2024-07-15 18:48:21', 94);
INSERT INTO `user_comment` VALUES (2, 2, 5, '2', '2024-07-15 18:48:25', 95);
INSERT INTO `user_comment` VALUES (2, 2, 5, '3', '2024-07-15 18:48:28', 96);

-- ----------------------------
-- Table structure for userdata
-- ----------------------------
DROP TABLE IF EXISTS `userdata`;
CREATE TABLE `userdata`  (
  `username` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `time` time NOT NULL,
  `position` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`username`, `time`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of userdata
-- ----------------------------

-- ----------------------------
-- Table structure for userdata_copy1
-- ----------------------------
DROP TABLE IF EXISTS `userdata_copy1`;
CREATE TABLE `userdata_copy1`  (
  `username` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `time` time NOT NULL,
  `position` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`username`, `time`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of userdata_copy1
-- ----------------------------

SET FOREIGN_KEY_CHECKS = 1;
