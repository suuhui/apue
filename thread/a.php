<?php
    $esf_info_url = '10.8.9.144:8001/im/api_house_card_protocol';
    $msgs = '[
    {
        "infoid": "1683519390",
        "show_type": "universal_card2",
        "content_type": "ajk_renthouse_card",
        "sender": "0",
        "ajk_info": "{\"id\":\"1683519390\",\"city_id\":\"11\",\"source_type\":\"1\",\"anjuke_bus_type\":\"1\",\"anjuke_scene_type\":\"1\"}"
        }
    ]';

    $data=json_decode($msgs, true);
    var_dump($data);exit;
    // $params = array('msgs' => $data, 'refer' => '');

    // $res = Apf_Http_CurlClient::getInstance()->doPost($esf_info_url, $params, [], [], 3000);
    // echo "result:{$res}\r\n";
    // var_dump(json_decode($res));
    exit;