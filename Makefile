all: engine editor

engine:
	$(MAKE) -C Engine
editor: engine
	$(MAKE) -C Editor

clean:
	$(MAKE) -C Engine clean
	$(MAKE) -C Editor clean