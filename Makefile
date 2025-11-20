SRCS_DIR=srcs
OBJS_DIR=objs
INC_DIR=include

SRCS=$(wildcard $(SRCS_DIR)/*.c)
OBJS=$(subst $(SRCS_DIR),$(OBJS_DIR),$(SRCS:.c=.o))

NAME=libbigshift.a

.PHONY: all clean fclean

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) rv $@ $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) -c $< -I$(INC_DIR) -o $@

$(OBJS_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(OBJS) $(OBJS_DIR)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)
