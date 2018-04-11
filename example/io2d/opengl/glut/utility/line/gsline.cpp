#include <srook/io2d/third_party/opengl/glut/utility/gsline.hpp>

int main(int argc, char** argv)
{
    namespace sg = srook::math::geometry::fundamental;

    srook::io2d::glut::utility::gsline l(argc, argv, "lines", 640, 480);
    l.display(std::make_pair(sg::point<>(-100, -100), sg::point<>(200, 400)), std::make_pair(sg::point<>(-300, -100), sg::point<>(100, 400)));
    l.loop();
}
