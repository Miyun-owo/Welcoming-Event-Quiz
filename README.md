# 檔案操作須知

## 使用與安裝方式(安裝人員，非玩家)
1. 到SFML官網，對要"執行該功能的電腦"下載SFML。[操作說明](https://www.sfml-dev.org/tutorials/3.0/getting-started/build-from-source/?utm_source#building-sfml)
2. 完成下載後，照[這個說明](https://www.sfml-dev.org/tutorials/3.0/graphics/text/?utm_source)建置ttf.檔案。 這個檔案可以直接被包在Github專案裡面，不用每個電腦都做一次。極度建議不要打中文或一些奇怪符號，用ASCII能表示的字元就好。這個是決定你檔案的文字風格用的。
3. (跟ttf.檔要有共同的父資料夾) 建置一個可執行的cpp.檔案。(檔名為puzzle.cpp)，記得要下載完SFML再來，不然code會報錯。 
(目前這個檔案是GPT給我的，還沒測試過，先不要真的執行，我不知道它會不會跳出什麼嚇到人的東西)
4. 完成之後，把檔案另存下來，存到USB裡面。
5. 活動進行時，務必確保有一台電腦是開著原始碼的，如果有出任何問題可以及時修改。

## 其他要修改的地方
1. 記得每台電腦都要去改`puzzle.cpp`裡面的password，否則玩家會無法通關。(password會是上一關的答案，做這個只是預防玩家暴力解，跳過關卡)
2. 再開一個flie，存一些線索的資料。裡面可以包含: 
    (1) READMEEE.md / 存官網連結，點下去之後是小遊戲(?)
    (2) image.jpg / 熟悉的瑞克搖最對味w
    (3) essay.txt / 黃的論文，重點在署名"黃&教學"
    (4) interview (flie) / 裡面有每個npc的面試資料，會是很多個txt。
