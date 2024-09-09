SRCS = ./philosopher.c ./ft_error.c  \
		./utils.c ./ft_init.c ./ft_routine.c ./ft_monitoring.c ./ft_init_utils.c
OBJDIR = objets
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
INCS = includes
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo

GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[1;34m
NC = \033[0m
PURPLE=\033[0;35m

all: titre ${NAME}

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR) $(OBJDIR)/philo
	@${CC} ${CFLAGS} -I ${INCS} -c $< -o $@

${NAME}: ${OBJS}
	@${LIB}
	@echo "${GREEN}compiling philosopher...${NC}"
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@printf "\r${PURPLE}Compiling: [${GREEN}%-50s${PURPLE}] %d/%d${NC}" $$(printf "#%.0s" $$(seq 1 $$(expr $$(find $(OBJDIR) -type f -name '*.o' | wc -l) \* \
	 50 / $(words $(SRCS))))) $$(find $(OBJDIR) -type f -name '*.o' | wc -l) $(words $(SRCS))
	@echo "\n${GREEN} ./philo [nbr_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_max_each_philo_eat] ready to use ${NC}\n"


titre:
	@echo "\n"
	@echo "${PURPLE}           ___              ___                                           ___                            "
	@echo "          (   )       .-.  (   )                                         (   )                           "
	@echo "   .-..    | | .-.   ( __)  | |    .--.       .--.      .--.      .-..    | | .-.     .--.    ___ .-.    "
	@echo "  /    \   | |/   \  (''\")  | |   /    \    /  _  \    /    \    /    \   | |/   \   /    \  (   )   \   "
	@echo " ' .-,  ;  |  .-. .   | |   | |  |  .-. ;  . .' \`. ;  |  .-. ;  ' .-,  ;  |  .-. .  |  .-. ;  | ' .-. ;  "
	@echo " | |  . |  | |  | |   | |   | |  | |  | |  | '   | |  | |  | |  | |  . |  | |  | |  |  | | |  |  / (___) "
	@echo " | |  | |  | |  | |   | |   | |  | |  | |  _\_'.(___) | |  | |  | |  | |  | |  | |  |  |/  |  | |        "
	@echo " | |  | |  | |  | |   | |   | |  | |  | | (   ). '.   | |  | |  | |  | |  | |  | |  |  ' _.'  | |        "
	@echo " | |  ' |  | |  | |   | |   | |  | '  | |  | |  \`\\ |  | '  | |  | |  ' |  | |  | |  |  .'.-.  | |        "
	@echo " | \`-'  '  | |  | |   | |   | |  '  \`-' /  ; '._,' '  '  \`-' /  | \`-'  '  | |  | |  '  \`-' /  | |        "
	@echo " | \\__.'  (___)(___) (___) (___)  \`.__.'    \`.___.'    \`.__.'   | \\__.'  (___)(___)  \`.__.'  (___)       "
	@echo " | |                                                            | |                                      "
	@echo "(___)                                                          (___)                                     "
	@echo "${RESET}\n"

clean:
	@${RM} -r ${OBJDIR}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re