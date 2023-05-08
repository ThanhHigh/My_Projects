# Knight-Run
![alt text](<a href="https://ibb.co/Dkp5KQt"><img src="https://i.ibb.co/BjNqsBt/Man-Hinh-Nho.jpg" alt="Man-Hinh-Nho" border="0"></a>)
Nguyễn Đức Thành - UET
22021150 - K67CB

### Introduction
Bài tập lớn - Game (môn học: Lập trình Nâng cao - INT2215_1)
Ý tưởng Knight-Run được lấy từ tựa game Hollow Knight với một vài yếu tố thêm thắt sáng tạo, phù hợp hơn.
- Nhân vật chính là một hiệp sĩ (Knight) cố gắng di chuyển để thoát khỏi sự tàn phá của vụ nổ.
- Nhiệm vụ của bạn là điều khiển nhân vật vượt qua chướng ngại vật một cách nhanh chóng

### Quá trình chuẩn bị (Preparation)
- Đọc tài liệu, slide và làm bài tập của thầy Long, thầy Thủy để trau dồi kiến thức Lập trình nâng cao.
- Tham khảo thêm kiến thức SDL2 từ trang [Layzyfoo](https://lazyfoo.net/tutorials/SDL/index.php#True%20Type%20Fonts)
- Tham khảo cách tổ chức game và khung chương trình theo một series Youtube: [How to Make 2D Game Engine in C++ and SDL2](https://www.youtube.com/playlist?list=PL-K0viiuJ2RctP5nlJlqmHGeh66-GOZR_)
-  Kiến thức về lập trình ứng dụng
    - Cách tổ chức chương trình
    - Quản lý các thành phần, file game
    - Cách chia file
- Tài nguyên game:
    - Hình ảnh: Tham khảo trên mạng và vẽ lại, thêm thắt sáng tạo
    - Âm thanh: Lấy từ một số nguồn tài nguyên
- Thời gian thu thập, chuẩn bị những đầu mục trên


### Tổng quan (Overview)
##### Cách build
Game có thể được chạy dễ dàng trên VS Code bằng cách chọn Terminal -> RunTask -> C++: Build Debug and Run
##### Chạy Game:
Khi game chạy bạn sẽ bắt đầu từ Menu với 2 sự lựa chọn: Play Game và Quit Game. Chọn Play Game bạn sẽ điều khiển Knight tiến lên phía trước vượt nhảy qua các cột đá. Để cho nhân vật bạn xảy chân hoặc chạy quá chậm : Game sẽ kết thúc.

Ở màn hình kết thúc bạn có thể chọn chơi lại hoặc thoát game.

##### Video Demo: [Chơi thử demo](https://youtu.be/Y4vagr7xQJM)

##### Điều khiển:
A,D hoặc mũi tên để sang trái, phải.
W / Space / K: để nhảy ( khi giữ phím càng lâu, nhân vật nhảy càng cao )

### Cơ chế mới (New Features)
Một vài cơ chế đặc biệt của Game:
- Xử lý thời gian trong game bằng phương pháp DeltaTime thay cho FrameRate truyền thống. Giúp người chơi đạt trải nghiệm chơi game ổn định trên mọi loại máy. Đồng thời áp dụng vận tốc, gia tốc tính toán vật lý giúp trải nghiệm chơi một cách chân thật.

- Cơ chế tự động vẽ bản đồ (Map) trên file Tmx. Giúp dễ dàng sửa map và vẽ thêm bản đồ từ bên thứ 3 (Tiled_Map).

- Thuật toán sinh bản đồ game vô tận và ngẫu nhiên:
````C++
    //Debug check x viewbox
    int LevelPosX = m_LevelPartMapList.at(0).getX();
    int viewBoxX  = Camera::getInstance()->getViewBox().x;
    if ((LevelPosX - viewBoxX) <= (-LEVEL_WIDTH + 1)) 
    {
        int setXlevelMap = m_LevelPartMapList.at(m_LevelPartMapList.size() - 1).getX();
        setXlevelMap += LEVEL_WIDTH;
        int random = rand() % (TOTAL_MAP - 1);
        GameMap* mapTemp = m_MapList.at(random);
        m_LevelPartMapList.at(0).setLevelMap(mapTemp);
        m_LevelPartMapList.at(0).setLevelX(setXlevelMap);

        LevelPart level = m_LevelPartMapList.at(0);
        m_LevelPartMapList.erase(m_LevelPartMapList.begin());
        m_LevelPartMapList.push_back(level);
    }
    if (viewBoxX == 0)
    {
        for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
        {
            m_LevelPartMapList.at(i).renderLevelPart(i * LEVEL_WIDTH);       
        }
        // m_level0map->render();
    }
    else
    {
        for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
        {
            m_LevelPartMapList.at(i).renderLevelPart();
        }
    }
````
##### Nguyên lý:
- Ý tưởng của em là tạo một mảng Vector gồm 3 map: "m_LevelPartMapList" có độ lớn là 3.
- Khi nhân vật chạy qua Map thứ 2 trong mảng, lập tức xóa map đầu và thêm một map vào cuối mảng
(Map được thêm này sẽ được random ngẫu nhiên trong số tổng 5 map được vẽ sẵn " TOTAL_LEVEL_MAP")
- Việc này được lặp liên tục tạo ra hiệu ứng map liên tục khiến trò chơi sinh động hơn.

### Nguồn Tham Khảo (References)
Trong quá trình làm game em có tham khảo tài liêu, hình ảnh, âm thanh ở một số nguồn sau:
##### File Phương tiện:
- Hình ảnh: đồ họa pixel [Itchi](https://itch.io/game-assets/tag-tileset)
- Map: Bên thứ 3 [Tiled](https://www.mapeditor.org/)
- Âm thanh: Lấy cảm hứng [Hollow Knight](https://archive.org/details/official-hollow-knight-original-soundtrack/Hollow+Knight+-+Official+Soundtrack/18+-+Broken+Vessel.mp3) và trên [FreeSound](http://freesound.org)

##### Thuật toán
- Tham khảo thuật toán [DeltaTime](https://www.youtube.com/watch?v=rWtfClpWSb8)
- Tham khảo cách áp dụng kiến thức cơ bản của TMX vào chương trình thông qua Video hướng dẫn: [Tile Map Parser SDL Game](https://www.youtube.com/watch?v=3DKriWbJJ50&list=PL-K0viiuJ2RctP5nlJlqmHGeh66-GOZR_&index=15)

### Tổng kết (Review)
Sau quãng thời gian làm Bài tập lớn, em cảm thấy mình tiến bộ hơn về cả kiến thức và tư duy lập trình. Cảm ơn vì đã dành thời gian để đọc, em mong sẽ nhận được số điểm xứng đáng cho bài tập lớn này.
