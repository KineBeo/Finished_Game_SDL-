# SUNNYLAND
* Một Game được tạo bằng C++ và thư viện SDL2.0. Bài tập lớp Lập trình Nâng Cao (INT 2215).
# Introduction
* Thể loại: Game bắn súng kết hợp phiêu lưu.
# Play Guide
* Người chơi điều khiển nhân vật (Fox) khám phá và tiêu diệt quái vật, vượt qua các chướng ngại vật của trò chơi chiến thắng.
# The Ojective 
* Bắn, di chuyển, né tránh, parkour để chiến thắng các thử thách của game.
# Fox Control
* A, D: Di chuyển trái, phải.
* J: Bắn cầu lửa vào quái vật. 
* SPACEBAR: nhảy.
# GamePlay Control 
* Pause Button: Để tạm dừng màn chơi.
* Restart Button: Chơi lại lever hiện tại.
* Home Button: Quay về cửa sổ MENU của game.
# Function
* Trò chơi có các tính năng sau:
# The Main Menu
* Start Button: Khởi tạo Gameplay.
* Exit Button: Đóng Game.
# The GamePlay
 Khi vào game người chơi sẽ có những tính năng sau:
* Fireball: Là vũ khí của người chơi, bạn chỉ có tối đa 5 quả để có thể tiêu diệt các con quái vật của từng lever. Fireball cũng nằm rải rác khắp bản đồ để người chơi có thể nhặt và hồi lại số lượng fireball.
* FoxHealth: Chỉ số máu của người chơi, khi người chơi va chạm với các con quái vật, máu của người chơi sẽ giảm, khi máu giảm xuống bằng 0 thì người chơi mất đi 1 trái tim (Heart).
* Heart: Chỉ số sinh mạng của người chơi, khi số trái tim giảm về 0 thì lúc đó là bạn đã thua.
* Spike: Chướng ngại vật sẽ gây sự ức chế và tạo nên độ khó cho trò chơi vì cách bố trí những chiếc gai sẽ khiến bạn phải cay cú!!!!. Khi chạm vào 1 chiếc gai thì ngay lập tức bạn sẽ mất đi 1 trái tim, và phải chơi lại từ điểm bắt đầu của lever đó.
* Cherry: Vật phẩm giúp bạn hồi máu.
* Diamond: Vật phẩm giúp bạn hồi nhiều máu hơn cherry.
* Eagle: Bay với quỹ đạo khó đoán ở những khúc đường khó nhằn khiến người chơi vừa mất máu vừa cay cú.
* Slime: Lao tới người chơi khi bạn ở trong phạm vi 5 block và khiến người chơi mất máu.
* Dog: Lao tới người chơi khi bạn ở trong phạm vi 7 block và khiến người chơi mất máu.
* Pig: Lao tới người chơi khi bạn ở trong phạm vi 9 block và khiến người chơi mất máu.
* Boss: Trùm cuối của game, có khả năng bắn ra fireball và spawn ra các quái vật để tấn công người chơi gồm Slime, Dog, Pig.
        Boss bị tiêu diệt khi bạn làm máu của nó giảm về 0 bằng cách sử dụng hợp lí số fireball hiện có và tận dụng địa hình của bản đồ.
# The Pause Menu
Nhấn vào nút Pause ở góc trên cùng bên phải màn hình, bạn sẽ thấy có 3 nút lần lượt như sau:
* Resume Button: Thoát trạng thái tạm dừng và tiếp tục trò chơi.
* Restart Button: Thoát trạng thái tạm dừng và chơi lại lever hiện tại.
* Home Button: Thoát trạng thái tạm dừng và quay về MainMenu.
# The Winning Menu
Khi người chơi tiêu diệt được boss, màn hình chiến thắng sẽ xuất hiện, thông báo bạn đã chiến thắng trò chơi và hiển thị 2 nút:
* Yes Button: Bắt đầu một ván mới.
* No Button: Thoát khỏi trò chơi.
# Installation
Note: Trò chơi này chỉ là bản thử trên môi trường Window và được code bằng ngôn ngữ C++, biên dịch bằng CodeBlock.
* Step 1: Dowload CodeBlock phiên bản bất kì [CodeBlock page](https://www.codeblocks.org/).\
* Step 2: Dowload source code từ repository này.
* Step 3: Cài đặt thư viện SDL2 (bao gồm SDL2, SDL2_image, SDL2_ttf, SDL2_mixer).
  * Tạo 1 project và liên kết thư viện SDL2 trong CodeBlock.
  * Copy toàn bộ file .dll và paste chúng vào thư mục của project vừa tạo.
* Step 4: Chạy chương trình.
* Step 5: Nếu đã thực hiện chính xác các bước trên, trò chơi sẽ được khởi và bạn có thể tận hưởng trò chơi =)))
# Credits
* Dự án được tạo bời [Phạm Trung ](https://github.com/KineBeo)

