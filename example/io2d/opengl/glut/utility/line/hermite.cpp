#include <srook/io2d/third_party/opengl/glut/utility/painter.hpp>
#include <srook/math/geometry/algorithm/line/curve/parametrics/hermite.hpp>

int main(int argc, char** argv)
{
    srook::io2d::glut::utility::params setting(argc, argv);
    setting(640, 480)("my lines");

    srook::io2d::glut::utility::painter<srook::math::geometry::algorithm::line::curve::hermite_points> painter(setting, 2048);
    
    namespace sg = srook::math::geometry::fundamental;
    painter.display(std::make_tuple(sg::point<>(1, 0), sg::vector<>(0, 1), sg::point<>(-1, 0), sg::vector<>(0, -1)));
    painter.loop();
}
