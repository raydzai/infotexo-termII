from docx import Document

# Manually transcribed text
text = """
I. ĐỌC HIỂU                                   ĐỀ ÔN TẬP CUỐI HỌC KÌ 2
Đọc đoạn trích sau và thực hiện các yêu cầu:
(Lược phần đầu: Điền là một trí thức nghèo, gia đình có hai đứa con nhỏ hay bị đau ốm là
Hương và Chuyện. Hôm ấy, lúc Điền dậy sớm sửa soạn lên tỉnh để nhận thư và lĩnh tiền
thì vợ dẫn Điền mua thuốc cho bé Hương. Điền đi bộ một chặng đường rất dài, dưới cái
nắng nóng bức, đến nơi lĩnh tiền đã tầm giờ trưa. Ông kỹ - người cho Điền lĩnh tiền, lại
có thái độ rất cộc cằn với Điền. Điền muốn nhờ ông ký cho mình một tờ tiền nát, không
thể tiêu được thì ông lại ném tờ tiền ấy xuống đất, gió thổi bay mất... Điền lủi thủi trở về
nhà...)

(1) Về đến nhà thì trời đã sẩm sẩm tối. Điền nhọc uể oải. Hắn đi tập tềnh như một
người què, bước vào sân. Vợ hắn gọi hốt hãi ngay: "Thuốc của cái Hương đâu?" Hắn chợt nhớ
ra, thở mệt, rồi chẳng đáp nửa lời, hất lại chén mốc, rót ra chén, ừng ực uống.
Hắn uống hết chén này đến chén khác, không còn biết bao nhiêu chén. Mồ hôi vã ra như
tắm. Uống xong, hắn mới vác thằng bé vào bảo: "Tôi quên rồi!". Người đàn bà buông mặt
xuống ngay. Thị giận dỗi với chồng: "Quên! Chí quên suốt đời... Có mà tiếc tiền ấy!... Quên
quên thế nào! Người đâu mà người tệ thế!" [...]

(2) Hắn vùng vằng đi vào nhà, quăng mũ quăng áo, quẳng nốt cả cái thân xác mỏi mệt
xuống một cái giường, thở hổn hển, như để đẩy bớt ra ngoài cái khí giận đang cuồn cuộn
trong ngực. Hắn thấy mình khô quá, khô như một con cỏ vậy. Hắn nhìn đôi chân rét sém cả da.
Hắn sờn từng đồng xu uống nước. Hắn chịu nhục với mọi người... Như thế, bởi vì đâu? Chẳng 
phải vì vợ vì con ư?... Nhưng nào vợ con ở thôn biết cho đâu! Đã chẳng an ủi một lời, vợ 
hắn còn lấy một sự hằn hộc để mạ đáy nghiến hắn. Ừ, mà cho rằng hắn không quên nữa, cho 
rằng hắn không lấy thuốc cho con là cố ý, là muốn khơi mắt mấy đồng bạc nữa, thì vợ hắn 
có nên nói tệ hẳn như vậy hay không? Hắn hả tiện vì ai? Hắn khổ sở vì ai, riêng vào cái 
thân hắn chẳng phải phạm một đồng xu nào cả? Mấy mươi lần vợ hắn giục hắn mang một cái 
áo sơ-mi, hắn chỉ ừ hự rồi để đấy, chưa bao giờ dám bỏ tiền ra mà may cả. Thế rồi bao nhiêu 
tiền cũng đổ vào vợ, vào con hết... Hắn bần tiện, hắn tiếc tiền... ừ, nhưng mà hắn tiếc tiền 
cho ai?... Điền cứ càng nghĩ càng thấy mình là người khổ, vợ hắn là người tệ bạc. Hắn 
muốn chẳng thiết gì vợ con, nhà cửa nữa. Hắn sẽ đi phát một nơi nào, sống cho mình, đứa 
nào chết mặc thây, bấy giờ họa chẳng vợ hắn mới biết thân! [...]

(3) Nhưng bỗng con bé Hương chạy vội ra đằng cửa, về phía giếng Điền. Điền nghe
tiếng đôi guốc của nó lẹt xẹt rất nhanh một thoáng, rồi im lặng. Rồi Hương xịt mũi. Nó sụt
sịt rất lâu ngoài ấy. Nó nghẹn mũi hay nó khóc? Điền cố lắng tai nghe. Hắn nghe thấy những
tiếng Hương rì rầm. Hắn đột nhiên run người. Lòng hắn quặn lại. Những ý giận hờn bữa
bực vụt tan. Còn lại cái hình ảnh bé nhỏ của Hương, với cái mặt đầy mụn và sưng lên của
nó, đôi mắt giàn giụa nước và miệng mèo. Con bé còn nhỏ tuổi nhưng đã rất hay khóc vụng;
mỗi lần muốn khóc, nó lại tránh ra một chỗ, cố nén tiếng, không cho ai biết. Điền thấy
thương nó quá. Tội nghiệp cho con bé! Nó ôm đầu luôn và thường bị mẹ mắng chửi suốt
ngày như tát nước. Mẹ nó mắng chửi nó, nhiều khi bất công và vô lý. Nhưng lạ thay! Lúc
này Điền không vội vào đấy mà trách vợ. Hắn thấy vợ hắn không tệ. Thị vốn thương con
lắm. Những lúc thị gắt gỏng với con như thế chỉ là những lúc thị sợ ruột quá, lo lắng quá.
Cũng như hắn vậy, sao hắn nỡ đem lòng giận thị? Ai chả thế? Người không phải là thánh.
Sự khổ sở dễ khiến lòng chưa chát. Khi người ta làm lũ quá, lại còn lo trăm thứ, bị làm đầy
vì trăm thứ, thì ai bình tĩnh được? Ai mà chả hay gắt gỏng? Gắt gỏng thì chính mình khổ
trước. Không giữ được thì phải bật ra ngoài như vậy. Thật ra có ai muốn cau có làm chi?...
Vậy thì vì sao hắn gắt lên với con như thế chỉ là việc thường thôi. Cũng như hắn gắt lại
với vợ và gắt với con.
[...] Bây giờ trong lòng hắn chỉ còn lại sự xót thương. Hắn thương vợ, thương con,
thương tất cả những người phải khổ đau. Lòng hắn thiết tha rướn lên, muốn vươn ra để ép
thấy con!" [...]

(Trích Nước mắt, Nam Cao (3), Nam Cao tuyển tập - https://trinhdinhlinh.com)

*Chú thích:
(1) chai: gian nhỏ lợp một mái, là phần mở rộng hoặc kéo dài thêm của phần nhà chính
(2) quang: sáng sủa, thông suốt
(3) Nam Cao (1917-1951) tên khai sinh là Trần Hữu Tri, quê ở tỉnh Hà Nam. Trước Cách
mạng, đề tài sáng tác của Nam Cao xoay quanh đời sống cơ cực của người nông dân và
tầng lớp trí thức nghèo ở thành thị. Ông rất chú trọng diễn tả, phân tích tâm lý nhân vật,
xây dựng các tính cách phức tạp... Truyện ngắn Nước mắt được sáng tác vào năm 1943, in
trong tờ tuần báo Tiểu thuyết thứ Bảy.

Câu 1. Xác định ngôi kể và nêu tác dụng của ngôi kể trong đoạn trích
Câu 2. Nhân vật chính trong đoạn trích là nhân vật nào?
Câu 3. Theo đoạn trích, Điền có hành động như thế nào khi nghe vợ hỏi về việc mua thuốc
cho con?
Câu 4. Anh/chị hãy nêu hiệu quả biểu đạt của những câu hỏi tu từ: Hắn chịu nhục với mọi
người... Như thế, bởi vì đâu? Chẳng phải vì vợ vì con ư?... Hắn hả tiện vì ai? Hắn khổ sở
vì ai, riêng vào cái thân hắn chẳng phải phạm một đồng xu nào cả?
Câu 5. Chi tiết: Con bé còn nhỏ tuổi nhưng đã rất hay khóc vụng; mỗi lần muốn khóc, nó
lại tránh ra một chỗ, cố nén tiếng, không cho ai biết cho thấy Hương là một nhân vật như
thế nào?
Câu 6. Anh/chị hãy lý giải tại sao khi nghe tiếng khóc của bé Hương, Điền lại cảm thấy
lòng hắn quặn đau rân. Những ý giận hờn bữa bằn vụt tan?
Câu 7. Trình bày một thông điệp mà anh/chị rút ra được từ đoạn trích trên.
Câu 8. Từ nhân vật Điền trong đoạn trích, anh/chị hãy nêu cách để thấu hiểu và cảm thông
với người khác?

II. LÀM VĂN
Viết bài văn nghị luận trình bày cảm nhận của anh/chị về nhân vật Điền và chủ đề
của truyện trong đoạn trích ở phần Đọc hiểu.
"""

# Create Word document
doc = Document()
for line in text.strip().split('\n'):
    doc.add_paragraph(line)

# Save the document
output_path = '/mnt/data/de_on_tap_cuoi_hoc_ki2.docx'
doc.save(output_path)

output_path
