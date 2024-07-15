/usr/lib/emscripten/emcc -o game.html src/twhgreloaded.cpp src/editor/editor.cpp src/level/level.cpp src/level/background/background.cpp src/level/gameobject/gameobject.cpp src/level/gameobject/gameobjects/backgroundblock.cpp src/level/gameobject/gameobjects/checkpoint.cpp src/level/gameobject/gameobjects/coin.cpp src/level/gameobject/gameobjects/conveyor.cpp src/level/gameobject/gameobjects/enemy.cpp src/level/gameobject/gameobjects/keyblock.cpp src/level/gameobject/gameobjects/key.cpp src/level/gameobject/gameobjects/wallblock.cpp src/level/hud/hud.cpp src/level/player/player.cpp src/utils/fonts.cpp src/utils/sounds.cpp src/utils/textures.cpp src/widget/widget.cpp src/widget/widgets/booleanwidget.cpp src/widget/widgets/buttonwidget.cpp src/widget/widgets/colorwidget.cpp src/widget/widgets/enumwidget.cpp src/widget/widgets/textfieldwidget.cpp src/level/gameobject/path/path.cpp src/level/gameobject/path/instruction/instruction.cpp src/level/gameobject/path/instruction/instructions/circularinstruction.cpp src/level/gameobject/path/instruction/instructions/waitinstruction.cpp src/level/gameobject/path/instruction/instructions/linealinstruction.cpp src/utils/shaders.cpp src/level/gameobject/gameobjects/fog.cpp -Os -Wall ./../raylib/src/libraylib.a -I. -I ./../raylib/src -s USE_GLFW=3 -DPLATFORM_WEB -sGL_ENABLE_GET_PROC_ADDRESS --preload-file "res@res"

