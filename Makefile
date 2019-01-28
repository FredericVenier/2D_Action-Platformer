CC = g++
CFLAGS = -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

game: obj/GameComponent.o obj/Game.o obj/InputHandler.o obj/Menu.o obj/ButtonsMenu.o obj/TitleMenu.o obj/MenuButton.o obj/Text.o obj/Player.o obj/Image.o obj/Sprite.o obj/Animation.o obj/BlockedAnimation.o obj/Level.o obj/Room.o obj/RoomPrototype.o obj/Cloud.o obj/Entity.o obj/MovableEntity.o obj/InteractiveObject.o obj/Springboard.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

obj/%.o: src/%.cpp src/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/gui/%.cpp src/gui/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/menus/%.cpp src/menus/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/menus/menu_objects/%.cpp src/menus/menu_objects/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/entities/%.cpp src/entities/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/entities/objects/%.cpp src/entities/objects/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/levels/%.cpp src/levels/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/levels/rooms/%.cpp src/levels/rooms/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/levels/rooms/room_objects/%.cpp src/levels/rooms/room_objects/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@