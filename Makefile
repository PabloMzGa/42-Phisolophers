# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablo <pablo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:30 by pabmart2          #+#    #+#              #
#    Updated: 2025/06/23 00:21:06 by pablo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
DEBUG_FLAGS = -g -fno-inline
BUILD_DIR = build

OBJ_DIR = build/obj

NAME = philo

HEADERS = \
	philo/include/philosophers.h \
	philo/include/colors.h

SRC = \
	philo/src/main.c \
	philo/src/philo_populate.c \
	philo/src/philo_behaviour/philo_eat.c \
	philo/src/philo_behaviour/philo_sleep_think.c \
	philo/src/philo_behaviour/philo_start.c \
	philo/src/philo_behaviour/philo_wait.c \
	philo/src/utils/get_time_ms.c \
	philo/src/utils/arg_check.c \
	philo/src/utils/args_parse/ft_atoi.c \
	philo/src/utils/args_parse/ft_atol.c \
	philo/src/utils/args_parse/ft_atosize_t.c \
	philo/src/utils/args_parse/ft_isdigit.c \
	philo/src/utils/args_parse/ft_isspace.c \
	philo/src/utils/philo_list_helpers/add_philo.c \
	philo/src/utils/philo_list_helpers/clean_philos.c \
	philo/src/utils/philo_list_helpers/create_philo.c \
	philo/src/utils/philo_list_helpers/get_philo.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

INCLUDES = \
	-Iphilo/include \

all: $(NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[31mObject files removed\033[0m"

fclean: clean
	@rm -f $(BUILD_DIR)/$(NAME)
	@echo "\033[31m$(NAME) removed\033[0m"

re: fclean
	$(MAKE) all

$(NAME): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(OBJ) -o $(BUILD_DIR)/$(NAME)  $(INCLUDES)
	@echo "\033[32m\n¡$(NAME) compiled! \
	ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\n"

$(OBJ) : $(OBJ_DIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[34mCompiling: \033[0m$<"


################################################
.PHONY: all debug clean fclean re
