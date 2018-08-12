<?php
/**
 * Created by PhpStorm.
 * User: leoshi
 * Date: 15-10-14
 * Time: 下午7:04
 */
//用于连接数据库，然后被require once 调用，有一个PDO对象$pdo 返回

////远程
//try{
//    $pdo = new PDO("mysql:hostname=d.leoshi.me;dbname=here4",'root','Wj1301052119');
//}catch (PDOException $e){
//    die("Connect Failed\n".$e->getMessage());
//}


//本地
try{
    $pdo = new PDO("mysql:hostname=localhost;dbname=data",'root','miniserver');
}catch (PDOException $e){
    die("Connect Failed\n".$e->getMessage());
}
header('Content-Type: text/html; charset=UTF-8');
$pdo->query("SET NAMES 'UTF8'");
