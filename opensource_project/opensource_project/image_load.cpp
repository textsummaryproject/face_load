#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // �̹��� ���� ��� ����
    std::string image_path = "test.png";

    // �̹��� ���� �о����
    cv::Mat original_image = cv::imread(image_path);

    // �̹����� ���������� �о����� Ȯ��
    if (original_image.empty()) {
        std::cerr << "�̹����� ���� �� �����ϴ�." << std::endl;
        return -1;
    }

    // �̹��� ũ�� ����
    cv::resize(original_image, original_image, cv::Size(), 2.0, 2.0); // ���÷� �̹����� 2�� Ȯ���߽��ϴ�.

    // �̹����� �׷��̽����Ϸ� ��ȯ
    cv::Mat gray_image;
    cv::cvtColor(original_image, gray_image, cv::COLOR_BGR2GRAY);

    // �̹��� ����ȭ
    cv::Mat binary_image;
    cv::threshold(gray_image, binary_image, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // MSER ��ü ����
    cv::Ptr<cv::MSER> mser = cv::MSER::create();

    // MSER �˰����� �̿��Ͽ� �ؽ�Ʈ ���� ����
    std::vector<std::vector<cv::Point>> regions;
    std::vector<cv::Rect> rects;
    mser->detectRegions(binary_image, regions, rects);

    // ����� �ؽ�Ʈ ������ �׸�ڽ� �׸���
    for (size_t i = 0; i < rects.size(); ++i) {
        cv::rectangle(original_image, rects[i], cv::Scalar(0, 255, 0), 2);
    }

    // �ؽ�Ʈ ������ ǥ�õ� �̹��� ���
    cv::imshow("�ؽ�Ʈ ���� ���� ���", original_image);

    // Ű �Է� ���
    cv::waitKey(0);

    return 0;
}
