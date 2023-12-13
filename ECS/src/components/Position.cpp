#include "../../include/components/Position.hpp"

namespace Ecs {

    Position::Position(int X, int Y)
        : _x(X), _y(Y)
    { _type = Constants::POSITION; }
    Position::~Position() {}

}