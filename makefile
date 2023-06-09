# Define the link target
linktarget = qbRay

# Define the necessary libraries
LIBS = -lSDL2

# Define the flags
CFLAGS = -std=c++17

# Define the object files
objects = main.o \
          capp.o \
          $(patsubst %.cpp,%.o,$(wildcard ./RayTrace/*.cpp))
          
# Define Rebuildables
rebuildables = $(objects) $(linktarget)

# Link the object files
$(linktarget): $(objects)
  g++ -g -o $(linktarget) $(objects) $(LIBS) $(CFLAGS)
  
# Create .o (object) files
%.o: %.cpp
  g++ -o $@ -c $< $(CFLAGS)
  
.PHONEY:
clean:
  rm $(rebuildables)
