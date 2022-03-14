<?php if(!isset($_SESSION["user"])){
echo "<script>alert('Unauthourized access, kindly login or signup');window.location.href ='../index.php'</script>";
}
?>