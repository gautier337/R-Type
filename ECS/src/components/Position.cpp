#include "../../include/components/Position.hpp"

namespace Ecs {

    Position::Position(int X, int Y, int direction)
        : _x(X), _y(Y), _direction(direction)
    { _type = Constants::POSITION; }
    Position::~Position() {}

}