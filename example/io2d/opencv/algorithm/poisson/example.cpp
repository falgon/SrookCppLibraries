#include <srook/io2d/third_party/opencv/algorithm/poisson.hpp>

int main(const int argc, const char* const* const argv)
{
    if (argc != 4) return EXIT_FAILURE;

    cv::CascadeClassifier face_cascade("/usr/local/Cellar/opencv@2/2.4.13.6/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml");
    cv::Mat org = cv::imread(argv[1]), syn = cv::imread(argv[2]), mask = cv::imread(argv[3]);

    if (const srook::uint8_t errcheck = (static_cast<srook::uint8_t>(org.empty()) << 2) | (static_cast<srook::uint8_t>(syn.empty()) << 1) | static_cast<srook::uint8_t>(mask.empty()); errcheck) {
        std::cerr << (errcheck & 0x01 ? argv[3] : errcheck & 0x02 ? argv[2] : argv[1]) << ": failed to open" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<cv::Rect> faces_org, faces_syn;
    cv::Mat frame_gray;

    for (auto&& v : srook::make_array(std::make_tuple(std::ref(org), std::ref(faces_org)), std::make_tuple(std::ref(syn), std::ref(faces_syn)))) {
        cv::cvtColor(std::get<0>(v), frame_gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(frame_gray, frame_gray);
        face_cascade.detectMultiScale(frame_gray, std::get<1>(v));
    }

    cv::Mat
        face(syn, cv::Rect(faces_syn[0].x, faces_syn[0].y, faces_syn[0].width, faces_syn[0].height)),
        mask_face(mask, cv::Rect(faces_syn[0].x, faces_syn[0].y, faces_syn[0].width, faces_syn[0].height)),
        face_resized,
        mask_resized;
    cv::resize(face, face_resized, cv::Size(faces_org[0].width, faces_org[0].height));
    cv::resize(mask_face, mask_resized, cv::Size(faces_org[0].width * 1.1, faces_org[0].height));

    const srook::array<int, 2> offset = {{faces_org[0].y, faces_org[0].x - static_cast<int>(faces_org[0].width * 0.03)}};
    const cv::Mat result = srook::io2d::opencv::algorithm::poisson_compute(face_resized, org, mask_resized, offset);
    cv::imshow("Result", result);
    cv::imwrite("result.jpg", result);

    std::cout << "complete" << std::endl;
    cv::waitKey(0);
}
