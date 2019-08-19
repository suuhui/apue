<?php
$str = '{
    "send_chat_id": "2064109102",
    "send_user_source": "4",
    "to_user_source": "4",
    "to_chat_id": "2062415121",
    "user_id": "162077206",
    "refer": "{"scene":"listing","transfer_info":{"houseid":"956289148935168","website":"anjuke","fromcateid":"1,8"}}",
    "msgs":
    "[{"ajk_info":"{\"houseid\":\"956289148935168\"}","show_type":"universal_card2","infoid":"1328162323","sender":"","content_type":"ajk_renthouse_card"}]"
    }';

$str = str_replace('"{', '{', $str);
$str = str_replace('}"', '}', $str);
$str = str_replace('"[', '[', $str);
$str = str_replace(']"', ']', $str);
$str = str_replace('\"', '"', $str);
echo $str;