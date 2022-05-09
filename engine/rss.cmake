set(HEADERS
    ${RSS_PATH}/include/RSS.hpp

    ${RSS_PATH}/include/core/core.hpp
    ${RSS_PATH}/include/core/Circle.hpp 
    ${RSS_PATH}/include/core/ConvexShape.hpp 
    ${RSS_PATH}/include/core/GJK.hpp 
    ${RSS_PATH}/include/core/Shape.hpp
    ${RSS_PATH}/include/core/Vec2.hpp 
    ${RSS_PATH}/include/core/outputOverloads.hpp
    ${RSS_PATH}/include/core/Polygon.hpp
    ${RSS_PATH}/include/core/misc.hpp
    ${RSS_PATH}/include/core/AABB.hpp
    ${RSS_PATH}/include/core/Angle.hpp
    ${RSS_PATH}/include/core/EPA.hpp
    ${RSS_PATH}/include/core/Simplex.hpp
    ${RSS_PATH}/include/core/CollisionSimplex.hpp
    ${RSS_PATH}/include/core/Collision.hpp
    ${RSS_PATH}/include/core/Object.hpp
    ${RSS_PATH}/include/core/ConvexShapeWrapper.hpp
    ${RSS_PATH}/include/core/Rect.hpp

    ${RSS_PATH}/include/env/env.hpp
    ${RSS_PATH}/include/env/World.hpp

    ${RSS_PATH}/include/custom/custom.hpp
    ${RSS_PATH}/include/custom/SegmentShape.hpp
    ${RSS_PATH}/include/custom/Environment.hpp
    ${RSS_PATH}/include/custom/ObservableState.hpp
    ${RSS_PATH}/include/custom/RawControls.hpp
    ${RSS_PATH}/include/custom/ObservableObject.hpp
)

set (SRC
    ${RSS_PATH}/source/core/Circle.cpp
    ${RSS_PATH}/source/core/GJK.cpp
    ${RSS_PATH}/source/core/Shape.cpp 
    ${RSS_PATH}/source/core/Vec2.cpp 
    ${RSS_PATH}/source/core/ConvexShape.cpp
    ${RSS_PATH}/source/core/Polygon.cpp
    ${RSS_PATH}/source/core/outputOverloads.cpp
    ${RSS_PATH}/source/core/Angle.cpp
    ${RSS_PATH}/source/core/EPA.cpp
    ${RSS_PATH}/source/core/Simplex.cpp
    ${RSS_PATH}/source/core/CollisionSimplex.cpp
    ${RSS_PATH}/source/core/Collision.cpp
    ${RSS_PATH}/source/core/Object.cpp
    ${RSS_PATH}/source/core/ConvexShapeWrapper.cpp
    ${RSS_PATH}/source/core/Rect.cpp

    ${RSS_PATH}/source/env/World.cpp

    ${RSS_PATH}/source/custom/SegmentShape.cpp
    ${RSS_PATH}/source/custom/Environment.cpp
    ${RSS_PATH}/source/custom/ObservableState.cpp
    ${RSS_PATH}/source/custom/RawControls.cpp
    ${RSS_PATH}/source/custom/ObservableObject.cpp
)

message("All RSS files are loaded!")