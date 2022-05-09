{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ 
        "../engine_wrapper/source/addon.cpp",
        "../engine_wrapper/source/NapiWrappers.cpp",
        "../../engine/source/core/Angle.cpp",
        "../../engine/source/core/Circle.cpp",
        "../../engine/source/core/Collision.cpp",
        "../../engine/source/core/CollisionSimplex.cpp",
        "../../engine/source/core/ConvexShape.cpp",
        "../../engine/source/core/ConvexShapeWrapper.cpp",
        "../../engine/source/core/EPA.cpp",
        "../../engine/source/core/GJK.cpp",
        "../../engine/source/core/Object.cpp",
        "../../engine/source/core/outputOverloads.cpp",
        "../../engine/source/core/outputOverloads.cpp",
        "../../engine/source/core/Shape.cpp",
        "../../engine/source/core/Vec2.cpp",
        "../../engine/source/core/Simplex.cpp",
        "../../engine/source/core/Polygon.cpp",
        "../../engine/source/core/Rect.cpp",
        "../../engine/source/custom/Environment.cpp",
        "../../engine/source/custom/ObservableObject.cpp",
        "../../engine/source/custom/ObservableState.cpp",
        "../../engine/source/custom/RawControls.cpp",
        "../../engine/source/custom/SegmentShape.cpp",
        "../../engine/source/env/World.cpp"
       ],
      'include_dirs': [
          '../../engine/',
          '../engine_wrapper/',
          '../node_modules/node-addon-api/'
        ],
        "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
          }
        },
        "conditions": [
          ["OS=='win'", {
            "defines": [
              "_HAS_EXCEPTIONS=1"
            ]
          }]
        ]
    }
  ]
}