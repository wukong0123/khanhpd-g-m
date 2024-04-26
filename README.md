# Zelda Survival Game - PDK Edititon
- Cấu trúc code và thử nghiệm game: https://www.youtube.com/watch?v=RQPNB_nGnp0
- Gameplay: https://youtu.be/8594_P90XB8

## Giới thiệu 
Game thuộc thể loại survial. Hãy cùng sắm vai nhân vật Link sử dụng linh hoạt các loại vũ khí để diệt boss và đem lại sự bình yên cho thảo nguyên xanh . 

- [0. Cách tải game](#0-cách-tải-game)
- [1. Bắt đầu game](#1-bắt-đầu-game)
- [2. Các thành phần trong game](#2-các-thành-phần-trong-game)
  * [a. Người chơi](#a-người-chơi)
  * [b. Kẻ địch](#b-kẻ-địch)
  * [c. Khác](#c-khác)
- [3. Điều khiển và gameplay](#3-điều-khiển-và-gameplay)
- [4. Một vài đồ họa trong game](#4-một-vài-đồ-họa-trong-game)
- [5. Về source code của game](#5-về-source-code-của-game)

## 0. Cách tải game
**Bước 1:** Clone repo này về hoặc chọn Code -> Download Zip

**Bước 2:** Cài codeblocks-20.03mingw

**Bước 3:** Thêm các file SDL2.dll, SDL2_image.dll, SDL2_mixer.dll, SDL2_ttf.dll vào thư mục gốc.

**Bước 4:** Chạy file [survival_mine_game.cbp](survival_mine_game.cbp) và chạy game bằng phím F9

**Hoặc vào link sau để tải và chỉ cần chạy file .exe để chơi game:** (https://drive.google.com/drive/folders/1qcqrJtz_gv7JFCbKwid1en_5LqH9eGmJ?usp=sharing)

## 1. Bắt đầu game

- Màn hình chính:

![1](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/5904721d-3661-4423-8422-a7af4f0fab93)

- Click vào "Regime" để chọn chế độ chơi. Có 2 chế độ:
  * Boss slayer: đánh boss
  * Survival score : đánh lính tính điểm

![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/238134dc-3160-4b2b-8c09-303dbf35e7d5)

- Chọn "Sound" để thay đổi âm thanh.
  * Âm thanh:  thay đổi độ lớn của nhạc và âm thanh hiệu ứng , press up để tăng và down đề giảm âm lượng 

![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/e148302c-256e-49f6-a61f-beb3482a4bf7)

- Chọn "Guide" để xem hướng dẫn chung cho game. 

![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/bf0a7b0c-dc4b-4a65-9dd9-ece7e585fd90)

## 2. Các thành phần trong game
### a. Người chơi
- Người chơi sẽ có 5 mạng và game sẽ bị thua khi số mạng trở về không

![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/56e9e639-333d-486a-8dbb-43bb3447feda) 

- Cung là vũ khí chính của Link và luôn được mang theo bên người cậu ta
  
![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/56e9e639-333d-486a-8dbb-43bb3447feda) 

- Kiếm là một trong hai special skill của Link sẽ càn quét xung quanh và tiêu diệt kẻ địch mà nó đi qua vaf mỗi khi chọn sẽ thêm vĩnh viễn một kiếm
  
![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/3e65e4bf-c226-480f-afa2-566718cee718)

- Đại bác cũng là vũ khí mạnh nhất của Link mang theo một sức mạnh hủy diệt và sát thương diện rộng .

![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/31c8ffc3-3162-4ec2-8161-1310282cf8ad)

### b. Kẻ địch
- Dơi quỷ bay với tốc độ cao và liều lĩnh , tuy nhiên máu chúng khá mỏng .
  
![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/7f1ff829-96bb-4a5e-b046-6000e98cd49c)

- Tree monster máu trâu và hung hãn , tiêu nhiên di chuyển chậm .
  
![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/456f3c72-54f3-4604-b364-bd7a879fa68b)

- Magician những kẻ đánh tầm xa với ma thuật lửa đốt rất nguy hiểm và sát thương cao , ta phải ưu tiên diệt chúng trước .
  
 ![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/568cdeec-f1e4-4098-9c17-60cf32b4acf4)
 
- Boss là trùm cuối mà nhân vật của chúng ta phải vượt qua để dành chiến thắng

 ![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/2cf56073-f61e-47df-9061-e829ccca5986)

### c. Khác

- Nút tạm dừng (pause) : Click 'Q' trên bàn phím sẽ tạm dừng trò chơi. 
- Người chơi kick chuột để chỉ hướng đạn bắn
- Những thanh kiếm luôn quay xung quanh người chơi và gây sát thương nên hãy di chuyển khéo léo để né và gây nhiều sát thương nhất có thể
- Chú ý hãy cố gắng để tiêu diệt boss càng nhanh càng tốt vì nếu để càng lâu chúng sẽ di chuyển càng nhanh và chém càng nhiều 
  ![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/55b5ba22-bc85-4e9e-8d96-1901e6822424)

## 3. Điều khiển và gameplay

- Các phím điều khiển:
  * Di chuyển: các phím W, A, S, D tương ứng với di chuyển lên, sang trái, xuống, sang phải
  * Quit game / pause game : Q
- Về gameplay
  * Press một nút bất kì để chơi bắt đầu game 
  * Chế độ 1 : đánh quái tính điểm , số lượng quái sẽ tăng theo thời gian yêu cầu người chơi phải linh hoạt và bình tĩnh xử lí . 
  * Chế độ 2 : diệt boss , người chơi phải diệt lũ lính lác trong 2 phút sau đó đánh boss để phá đảo trò chơi .
    
  * Sau mỗi 17 giây bạn có thể chọn một trong hai loại vũ khí ( press 'K' để thêm vĩnh viễn 1 kiếm , 'C' để thêm một đại bác trong 5 giây )
    ![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/83f559cb-ed87-409e-94e2-b35ba519f2b0)

  * Thua game sẽ hiện ra một màn cho có 3 option
    ![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/1dd2dc9f-855a-4c9d-923b-314cbc1f119c)

  * Tương tự khi thắng và phá đảo game sẽ xuất hiện 3 option
    ![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/17097bd5-fdee-4490-bd12-7a215d0b260a)

## 4. Một vài đồ họa trong game
  ![1](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/5904721d-3661-4423-8422-a7af4f0fab93)

  ![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/83f559cb-ed87-409e-94e2-b35ba519f2b0)

  ![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/1dd2dc9f-855a-4c9d-923b-314cbc1f119c)

  ![image](https://github.com/wukong0123/khanhpd-g-m/assets/162539932/17097bd5-fdee-4490-bd12-7a215d0b260a)
## 5. Về source code của game
- File Game.cpp / Game.hpp: là quan trọng nhất với các logic game chính bao gồm menu , xử lí logic game , xử lí hình ảnh , âm thanh , chữ 
- File CommonFuction.cpp / CommonFuction.hpp : chứa các hàm cơ bản nhất của game bao gồm init game , quit game , ... 
- File Entity.cpp / Entity.hpp : là class đại diện cho một vật thể , cũng là thành phần cơ bản cấu thành nên các thành phần quan trọng khác của game
- File Player.cpp / Player.hpp : là class đại diện cho nhân vật người chơi của chúng ta ( bao gồm cung , kiếm , bom ) và các thành phần cơ bản khác của một vật thể
- File TTF.cpp / TTF.hpp : là class đại diện cho các chữ viết ( dùng cho các hoạt động như tính điểm , tính thời gian cho game )
- Và một vài file khác ( tải file code để biết thêm thông tin chi tiết )  
