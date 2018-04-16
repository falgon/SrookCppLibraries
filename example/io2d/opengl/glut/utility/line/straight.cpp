#include <srook/io2d/third_party/opengl/glut/utility/painter.hpp>
#include <srook/math/geometry/algorithm/line/straight/simple_equation.hpp>

int main(int argc, char** argv)
{
    srook::io2d::glut::utility::params setting(argc, argv);
    setting(640, 480)("my lines");

    srook::io2d::glut::utility::painter<srook::math::geometry::algorithm::line::straight::simple_equation> painter(setting);
    
    namespace sg = srook::math::geometry::fundamental;
    painter.display(std::make_pair(sg::point<>(-100, -100), sg::point<>(200, 400)), std::make_pair(sg::point<>(-300, -100), sg::point<>(100, 400)));
    painter.loop();
}
