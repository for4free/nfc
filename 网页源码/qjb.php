<?php
/**
 * Created by PhpStorm.
 * User: leoshi
 * Date: 15-11-7
 * Time: 下午4:45
 */
session_start();
if(isset($_POST['no']) &&isset($_POST['start']) &&isset($_POST['end']) &&isset($_SESSION['id'])){
    $no = $_POST['no'];
    $start = $_POST['start'];
    $end = $_POST['end'];
    $teaid = $_SESSION['id'];	//获取POST信息
    if(empty($no) || empty($start) || empty($end) || empty($teaid)){
        die("信息不完整");		//检错
    }
    require_once 'connect.php';	//连接数据库
    $sql = "INSERT INTO `qjb` VALUES ('{$no}', '{$start}', '{$end}', '{$teaid}')";
	//SQL 插入语句
    $pdo->beginTransaction();	//开启事务，保证数据库一致性
    $stmt = $pdo->query($sql);	//查询语句
    $res = $stmt->rowCount();	//得到影响行数
    if($res == 1){				//影响行数为1时提交事务
        $pdo->commit();
        echo "信息插入成功！";
        header("Location:main.html");	//跳转
    }else{
        $pdo->rollBack();	//影响行数不为1时操作失败进行事务回滚
        echo "失败，请稍后重试";
    }
}
else{
    echo "INVALID";
}