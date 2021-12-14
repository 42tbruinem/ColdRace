NAME = philo

SRC_DIR = src/
OBJ_DIR = obj/
PREREQ_DIR = prereq/
DEBUG_DIR = obj_debug/
INCLUDE_DIRS = inc/

CFLAGS = -Wall -Wextra -Werror -O3 -pthread -g

SOURCE_FILES = $(shell find $(SRC_DIR) -type f -name *.c)

OBJECTS = $(SOURCE_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
PREREQS = $(SOURCE_FILES:$(SRC_DIR)%.c=$(PREREQ_DIR)%.d)

CFLAGS += $(INCLUDE_DIRS:%=-I%)

.PHONY: all
all: $(NAME)

include $(PREREQS)

$(NAME): $(OBJECTS) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

$(OBJECTS): Makefile | $(SRC_DIR) $(OBJ_DIR)
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c -o $@ $(@:$(OBJ_DIR)%.o=$(SRC_DIR)%.c)

$(OBJ_DIR) $(SRC_DIR) $(PREREQ_DIR):
	mkdir $@

# magic includes

# make sure to delete the corrupted file in case of a error, since we will include that
# and if its corrupted, the makefile will be "corrupted"

.DELETE_ON_ERROR: $(PREREQS)
$(PREREQS): $(PREREQ_DIR)%.d: $(SRC_DIR)%.c | $(PREREQ_DIR)
	mkdir -p $(shell dirname $@)
	printf "$(shell dirname $(patsubst $(PREREQ_DIR)%,$(OBJ_DIR)%,$@))/" > $@
	$(CC) -MM $(patsubst $(PREREQ_DIR)%.d,$(SRC_DIR)%.c,$@) $(CFLAGS) >> $@

# general management
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(PREREQ_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: | fclean all
