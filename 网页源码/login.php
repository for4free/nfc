<?php
/**
 * Created by PhpStorm.
 * User: leoshi
 * Date: 15-11-7
 * Time: 下午3:58
 */
if(isset($_POST['id']) && isset($_POST['pw'])){
    session_start();	//开启session 用于客户端验证和php文件间传递信息
    $id = intval($_POST['id']);
    $pw = $_POST['pw'];		//获取POST信息
    require_once 'connect.php';	//连接数据库
    if(empty($id) || empty($pw)){
        die("教工号或密码未输入");
    }		//检错
    $sql = "SELECT * FROM `jsb` WHERE id='{$id}'";//SQL语句，选取相关记录
    $stmt = $pdo->query($sql);	//执行查询
    $res = $stmt->fetchAll();	//获取结果
    if(empty($res)){
        die("教工号错误");	//检错
    }
    if($res[0][2] == 0){
        die("抱歉，您没有权限提交请假记录");	//检查权限
    }elseif($res[0][2] != 1){
        die("ERROR");	//检错
    }else{  //检查权限
        if(sha1($pw) != $res[0][1]){    //密码比对
            die("密码错误");
        }else{      //密码正确
            echo "登录成功，跳转中...";
            $_SESSION['id'] = $_POST['id'];//传递id
            header("Location:main.html");	//跳转
        }
    }
}
else{
    echo "Invalid";
}