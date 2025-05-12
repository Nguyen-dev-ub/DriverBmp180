
# BMP180 Linux I2C Driver

## Giới thiệu

BMP180 là một cảm biến áp suất số chính xác cao được sản xuất bởi Bosch. Nó có thể đo áp suất khí quyển và nhiệt độ, đồng thời được sử dụng để tính toán độ cao. Cảm biến giao tiếp thông qua giao thức I2C, dễ tích hợp vào các hệ thống nhúng như Raspberry Pi, BeagleBone, hoặc các hệ thống Linux khác.

Driver này được viết cho nhân Linux để giao tiếp với BMP180 thông qua giao tiếp I2C.


##  Tính năng tiêu biểu

- Hỗ trợ giao tiếp I2C chuẩn của Linux kernel.
- Đọc dữ liệu nhiệt độ và áp suất sau khi bù hệ số hiệu chuẩn.
- Cung cấp giao diện ioctl để tương tác từ user-space.
- Không yêu cầu GPIO hay interrupt.
- Hỗ trợ tính toán độ cao từ áp suất (tùy chọn).


##  Ứng dụng

- Thiết bị đo độ cao (altimeter) trong drone, máy bay, thiết bị đeo tay.
- Hệ thống định vị GPS chính xác cao (dựa vào độ cao).
- Thiết bị đo lường thời tiết.
- Hệ thống IoT, cảm biến môi trường, dự báo áp suất.


##  Giao tiếp I2C và hoạt động

Địa chỉ I2C mặc định: 0x77

### Trình tự đọc dữ liệu:

#### 1. Đọc hệ số hiệu chuẩn từ EEPROM:
- Địa chỉ từ 0xAA đến 0xBF.

#### 2. Đọc nhiệt độ:
- Ghi 0x2E vào thanh ghi 0xF4.
- Chờ ít nhất 4.5ms.
- Đọc 2 byte tại 0xF6 và 0xF7.

#### 3. Đọc áp suất:
- Ghi 0x34 + (OSS << 6) vào `0xF4.
- Chờ 4.5ms đến 25.5ms tùy OSS (Oversampling Setting).
- Đọc 3 byte tại 0xF6, 0xF7, 0xF8.

