# Unity use Bluetooth Control Arduino

Unity結合Arduino 控制兩個風扇
1=>根據踩踏的速度，傳給arduino，arduino在依照踩踏的值來切換風扇的風速
2=>當經過花香區域時，會啟動ardunio風扇

Unity Package-Arduino Bluetooth Plugin
https://assetstore.unity.com/packages/tools/input-management/arduino-bluetooth-plugin-98960

Arduino使用工具:
>Arduino Uno R3
>HC 05藍牙模組
>L298N 馬達驅動模組
>12V 風扇(3pin) *2
>12V 電源供應線

說明:
利用HC 05藍芽模組來接受資料
判斷資料是否為數字，再傳送給L298N
L298N再判斷要啟用何種風扇

