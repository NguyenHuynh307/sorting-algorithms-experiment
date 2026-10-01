# Thử nghiệm các thuật toán sắp xếp

## Mục tiêu
Thử nghiệm và so sánh thời gian thực thi của 4 cách sắp xếp trên bộ dữ liệu gồm 10 dãy số thực, mỗi dãy có 1.000.000 phần tử:

- QuickSort
- HeapSort
- MergeSort
- `std::sort` của C++

## Bộ dữ liệu
Thiết kế bộ dữ liệu theo hướng kiểm soát thí nghiệm:

| Dữ liệu | Số phần tử | Trạng thái ban đầu |
|---|---:|---|
| D1 | 1.000.000 | Tăng dần |
| D2 | 1.000.000 | Giảm dần |
| D3 | 1.000.000 | Ngẫu nhiên |
| D4 | 1.000.000 | Ngẫu nhiên |
| D5 | 1.000.000 | Ngẫu nhiên |
| D6 | 1.000.000 | Ngẫu nhiên |
| D7 | 1.000.000 | Ngẫu nhiên |
| D8 | 1.000.000 | Ngẫu nhiên |
| D9 | 1.000.000 | Ngẫu nhiên |
| D10 | 1.000.000 | Ngẫu nhiên |

D1 và D2 được tạo từ cùng một tập giá trị cơ sở. D3–D10 cũng chứa đúng tập giá trị đó nhưng được xáo trộn với các seed khác nhau. Cách này giúp 10 lần thử có cùng dữ liệu gốc, chỉ khác thứ tự.

## Cấu trúc thư mục

- `src/`: mã nguồn chương trình tạo dữ liệu và các thuật toán sắp xếp
- `data/`: các file dữ liệu thử nghiệm
- `results/`: kết quả đo thời gian, bảng và biểu đồ
- `report/`: báo cáo PDF cuối cùng

## Sinh dữ liệu
Mã tạo dữ liệu nằm tại `src/data_generator.cpp`.

Mặc định tạo chính xác `1.000.000` số thực kiểu `double` cho mỗi dãy. Dữ liệu được lưu ở dạng nhị phân `.bin` để tránh kích thước file văn bản quá lớn.

## Trạng thái báo cáo
- Phần 1: thiết kế bộ dữ liệu
- Phần 2: cài đặt 4 thuật toán
- Phần 3: người thực hiện tự chạy thử nghiệm và ghi thời gian
- Phần 4: người thực hiện tự lập bảng, biểu đồ và nhận xét

## GitHub
Đường dẫn repository sẽ được bổ sung sau khi tạo repository public trên GitHub.
