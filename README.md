
# Viết Linux driver trên hệ điều hành Linux cho module cảm biến áp suất BMP180

# BMP180 Linux I2C Driver

## Giới thiệu driver

Driver này được viết cho cảm biến BMP180 – một cảm biến đo áp suất và nhiệt độ, sử dụng giao tiếp I2C. Dự án gồm hai driver: một driver cơ bản (ghi log) và một driver nâng cao hỗ trợ giao tiếp với user-space qua IOCTL. 

Driver có thể hoạt động trên các hệ thống nhúng như Raspberry Pi (đã cung cấp file `.dts` cho Raspberry Pi Zero 2 W).

##  Tính năng tiêu biểu

•Giao tiếp I2C: Sử dụng SMBus để đọc thanh ghi BMP180.
• Đọc nhiệt độ và áp suất: Đọc dữ liệu từ thanh ghi sau khi gửi lệnh đo.
• Hỗ trợ IOCTL: Cho phép giao tiếp từ không gian người dùng.
• Ghi log dữ liệu: Dữ liệu hiển thị trên dmesg.

##  Ứng dụng

 Thiết bị đo độ cao (altimeter) trong drone, máy bay, thiết bị đeo tay.
 Hệ thống định vị GPS chính xác cao (dựa vào độ cao).
 Thiết bị đo lường thời tiết.
 Hệ thống IoT, cảm biến môi trường, dự báo áp suất.

## Giới thiệu về IC BMP180

Tên IC: BMP180
Nhà sản xuất: Bosch
Địa chỉ I2C: 0x77
Giao tiếp: I2C / SMBus
Chức năng: đo nhiệt độ và áp suất
Các thanh ghi quan trọng:
• 0xF4: Thanh ghi CONTROL - Gửi lệnh đo
• 0xF6: Kết quả MSB
• 0xF7: Kết quả LSB
• 0xF8: XLSB (áp suất)
• Lệnh 0x2E: đo nhiệt độ
• Lệnh 0x34: đo áp suất
Quy trình giao tiếp:
1. Ghi lệnh đo vào thanh ghi CONTROL (0xF4)
2. Chờ thời gian xử lý (4.5ms nhiệt độ, 8ms áp suất)
3. Đọc kết quả từ các thanh ghi (0xF6, 0xF7, 0xF8)

## Tài liệu đi kèm & Thông tin nhóm

1. Datasheet BMP180:
  https://www.alldatasheet.com/datasheet-pdf/download/1132068/BOSCH/BMP180.html
2. Mã nguồn tham khảo từ Linux Kernel:
  https://github.com/torvalds/linux/blob/master/drivers/i2c/i2c-dev.c
3. Thành viên thực hiện:
• Huỳnh Thị Thu Hà      -    22146299
• Đinh Gia Khánh        -    22146330
• Nguyễn Phương Nguyên  -    22146361
